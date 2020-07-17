#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _componentsZone = new loloof64::ComponentsZone(this);
    _mainToolBar = new QToolBar;

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/swap.svg")), QString(tr("Toggle side", "Caption for the button 'toggle side'")), [this](){
        this->_componentsZone->reverseBoard();
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

