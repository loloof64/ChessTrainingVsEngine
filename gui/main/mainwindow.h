#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include <QString>
#include "componentszone.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QToolBar *_mainToolBar;
    loloof64::ComponentsZone *_componentsZone;
    bool _engineReady;
    QString _fileChooserDir;
    void startNewGame(QString positionFen, bool playerHasWhite);
    void loadGameFromPgn();
    void loadRegisteredEnginePath();
};
#endif // MAINWINDOW_H
