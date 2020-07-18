#include "mainwindow.h"
#include "settingsdialog.h"
#include "../positioneditordialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _componentsZone = new loloof64::ComponentsZone(this);
    _mainToolBar = new QToolBar;

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/start.svg")), QString(tr("New game", "Caption for the button 'new game'")), [this](){
        //////////////////////////////////////////////////
        //_componentsZone->setEnginePath(enginePath);
        //////////////////////////////////////////////////

        PositionEditorDialog editorDialog(this);
        editorDialog.exec();
    });

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/swap.svg")), QString(tr("Toggle side", "Caption for the button 'toggle side'")), [this](){
        this->_componentsZone->reverseBoard();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/settings.svg")), QString(tr("Settings", "Caption for the button 'settings'")), [this](){
        SettingsDialog settingsDialog(this);
        settingsDialog.exec();
    });

    addToolBar(_mainToolBar);
    setCentralWidget(_componentsZone);

    setFixedSize(755, 600);
}

MainWindow::~MainWindow()
{
    delete _mainToolBar;
    delete _componentsZone;
}

