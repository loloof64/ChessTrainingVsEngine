#include "mainwindow.h"
#include "settingsdialog.h"
#include "../position_editor/positioneditordialog.h"
#include "newgameparametersdialog.h"
#include "../../libs/mini-yaml/Yaml.hpp"
#include "../../libs/chessx-pgn/database/pgndatabase.h"
#include "../game_selection/gameselectiondialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _componentsZone = new loloof64::ComponentsZone(this);
    _mainToolBar = new QToolBar;

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/start.svg")), QString(tr("New game", "Caption for the button 'new game'")), [this](){
        if (!_engineReady) {
            QMessageBox::critical(this, tr("Engine not set"), tr("You must configure the engine first"));
            return;
        };

        PositionEditorDialog editorDialog(this);

        connect(&editorDialog, &PositionEditorDialog::newGamePosition, [this](QString positionFen) {
            NewGameParametersDialog gameParametersDialog(positionFen, this);

            connect(&gameParametersDialog, &NewGameParametersDialog::newGameRequest, [this](QString positionFen, bool playerHasWhite) {
                startNewGame(positionFen, playerHasWhite);
            });

            connect(&gameParametersDialog, &NewGameParametersDialog::newTimedGameRequest, [this](QString positionFen, bool playerHasWhite, int whiteTimeMs, int blackTimeMs) {
               startNewTimedGame(positionFen, playerHasWhite, whiteTimeMs, blackTimeMs);
            });

            gameParametersDialog.exec();
        });

        editorDialog.exec();
    });

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/folder.svg")), QString(tr("New game from PGN file", "Caption for the button 'new game from PGN'")), [this](){
        if (!_engineReady) {
            QMessageBox::critical(this, tr("Engine not set"), tr("You must configure the engine first"));
            return;
        }

        loadGameFromPgn();
    });

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/stop.svg")), QString(tr("Stop game")), [this]() {
        auto gameInProgress = _componentsZone->gameInProgress();
        if (gameInProgress)
        {
            auto validation = QMessageBox::question(this, tr("Stop game"), tr("Do you really want to stop the game ?"));
            if (validation == QMessageBox::Yes)
            {
                _componentsZone->stopGame();
            }
        }
    });

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/swap.svg")), QString(tr("Toggle side", "Caption for the button 'toggle side'")), [this](){
        this->_componentsZone->reverseBoard();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/settings.svg")), QString(tr("Settings", "Caption for the button 'settings'")), [this](){
        SettingsDialog settingsDialog(this);

        connect(&settingsDialog, &SettingsDialog::enginePathChanged, [this](QString newPath) {
           _componentsZone->setEnginePath(newPath);
        });

        settingsDialog.exec();
    });

    connect(_componentsZone, &loloof64::ComponentsZone::engineReady, [this]() {
        _engineReady = true;
    });

    connect(_componentsZone, &loloof64::ComponentsZone::engineNotReady, [this]() {
        _engineReady = false;
    });

    loadRegisteredEnginePath();

    addToolBar(_mainToolBar);
    setCentralWidget(_componentsZone);

    setFixedSize(895, 680);
}

MainWindow::~MainWindow()
{
    delete _mainToolBar;
    delete _componentsZone;
}

void MainWindow::startNewGame(QString positionFen, bool playerHasWhite)
{
    _componentsZone->startNewGame(positionFen, playerHasWhite);
}

void MainWindow::loadRegisteredEnginePath()
{
    try {
        Yaml::Node root;
        auto filePath = QDir::toNativeSeparators(QDir::homePath() + "/ChessTrainingVsEngine.yml");
        Yaml::Parse(root, filePath.toStdString().c_str());

        auto uciEnginePath = QString::fromStdString(root["uci_engine"].As<std::string>());
        _componentsZone->setEnginePath(uciEnginePath);
    }
    catch (Yaml::OperationException &ex) {
        QMessageBox::critical(this, tr("Loading error"), tr("No configuration file !"));
    }
    catch (Yaml::ParsingException &ex) {
        QMessageBox::critical(this, tr("Loading error"), tr("Failed reading configuration file !"));
    }
}

void MainWindow::loadGameFromPgn()
{
    auto choosenFile = QFileDialog::getOpenFileName(this, tr("Choose pgn"), _fileChooserDir, tr("Pgn file (*.pgn)"));
    if ( ! choosenFile.isEmpty() ) {
        _fileChooserDir = QDir(choosenFile).absolutePath();

        try  {
            auto pgnDatabase = new PgnDatabase(false);
            pgnDatabase->open(choosenFile, true);

            loloof64::GameSelectionDialog gameSelectionDialog;
            gameSelectionDialog.setPgnDatabase(pgnDatabase);
            if (gameSelectionDialog.exec() != QDialog::Accepted)
            {
                return;
            }

            auto selectedGameIndex = static_cast<GameId>(gameSelectionDialog.getSelectedGameIndex());

            Game currentGame;

            pgnDatabase->loadGame(selectedGameIndex, currentGame);
            currentGame.moveToEnd();
            auto isOver = currentGame.result() != Result::ResultUnknown;
            if (isOver)
            {
                QMessageBox::critical(this, tr("Game already over"), tr("The game is already over. You can't play it."));
                return;
            }

            NewGameParametersDialog gameParametersDialog(currentGame.toFen(), this);
            connect(&gameParametersDialog, &NewGameParametersDialog::newGameRequest, [this](QString positionFen, bool playerHasWhite) {
                startNewGame(positionFen, playerHasWhite);
            });
            connect(&gameParametersDialog, &NewGameParametersDialog::newTimedGameRequest, [this](QString positionFen, bool playerHasWhite, int whiteTimeMs, int blackTimeMs) {
               startNewTimedGame(positionFen, playerHasWhite, whiteTimeMs, blackTimeMs);
            });
            gameParametersDialog.exec();
        }
        catch (loloof64::IllegalPositionException const &/* e */)
        {
            QMessageBox::information(this, tr("Unable to open file"),
                            tr("Wrong game data"));
                        return;
        }
        catch (std::exception const &e)
        {
            QMessageBox::information(this, tr("Unable to open file"),
                            tr("Misc reading error"));
                        return;
            qDebug() << "Pgn file reading error : " << e.what();
        }

    }
}

void MainWindow::startNewTimedGame(QString positionFen, bool playerHasWhite, int whiteTimeMs, int blackTimeMs)
{
    _componentsZone->startNewTimedGame(positionFen, playerHasWhite, whiteTimeMs, blackTimeMs);
}
