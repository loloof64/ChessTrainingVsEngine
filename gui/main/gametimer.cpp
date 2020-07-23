#include "gametimer.h"

loloof64::GameTimer::GameTimer(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout();

    _whiteSideLabel = new QLabel("White side");
    _blackSideLabel = new QLabel("Black side");
    _whiteTime = new QLabel("--:--");
    _blackTime = new QLabel("--:--");

    _whiteTime->setStyleSheet("color: black; background-color: white; font-size: 25px; font-family: Sans");
    _blackTime->setStyleSheet("color: white; background-color: black; font-size: 25px; font-family: Sans");

    _mainLayout->addStretch();
    _mainLayout->addWidget(_whiteSideLabel);
    _mainLayout->addWidget(_whiteTime);
    _mainLayout->addWidget(_blackTime);
    _mainLayout->addWidget(_blackSideLabel);
    _mainLayout->addStretch();

    setMinimumSize(500, 50);
    setMaximumSize(500, 50);

    setLayout(_mainLayout);
}

loloof64::GameTimer::~GameTimer()
{
    delete _blackTime;
    delete _whiteTime;
    delete _blackSideLabel;
    delete _whiteSideLabel;

    delete _mainLayout;
}
