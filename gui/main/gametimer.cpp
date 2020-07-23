#include "gametimer.h"

loloof64::GameTimer::GameTimer(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout();

    _whiteSideLabel = new QLabel(tr("White side"));
    _blackSideLabel = new QLabel(tr("Black side"));
    _whiteTime = new QLabel("--:--");
    _blackTime = new QLabel("--:--");

    _whiteTime->setStyleSheet("color: black; background-color: white; font-size: 25px; font-family: Sans");
    _blackTime->setStyleSheet("color: white; background-color: black; font-size: 25px; font-family: Sans");

    _whiteTimerComp = new QTimer(this);
    _whiteTimerComp->setSingleShot(false);
    _blackTimerComp = new QTimer(this);
    _blackTimerComp->setSingleShot(false);

    _mainLayout->addStretch();
    _mainLayout->addWidget(_whiteSideLabel);
    _mainLayout->addWidget(_whiteTime);
    _mainLayout->addWidget(_blackTime);
    _mainLayout->addWidget(_blackSideLabel);
    _mainLayout->addStretch();

    setMinimumSize(500, 50);
    setMaximumSize(500, 50);

    setLayout(_mainLayout);

    connect(_whiteTimerComp, &QTimer::timeout, [this]() {
        _remainingWhiteTimeMs -= 1000;
        if (_remainingWhiteTimeMs <= 0) emit whiteLostOnTime();
    });

    connect(_blackTimerComp, &QTimer::timeout, [this]() {
        _remainingBlackTimeMs -= 1000;
        if (_remainingBlackTimeMs <= 0) emit blackLostOnTime();
    });
}

loloof64::GameTimer::~GameTimer()
{
    _blackTimerComp->stop();
    _whiteTimerComp->stop();

    delete _blackTimerComp;
    delete _whiteTimerComp;

    delete _blackTime;
    delete _whiteTime;
    delete _blackSideLabel;
    delete _whiteSideLabel;

    delete _mainLayout;
}

void loloof64::GameTimer::startNewTimedGame(bool playerHasWhite, int whiteTimeMs, int blackTimeMs, bool blackStartGame)
{
    _whiteTimerComp->stop();
    _blackTimerComp->stop();

    _isActive = true;
    _blackTimerActive = blackStartGame;
    _remainingWhiteTimeMs = whiteTimeMs;
    _remainingBlackTimeMs = blackTimeMs;

    _whiteSideLabel->setText(QString(tr(playerHasWhite ? "Player" : "Computer")));
    _blackSideLabel->setText(QString(tr(playerHasWhite ? "Computer" : "Player")));

    updateTimerTexts();

    if (blackStartGame)
    {
        _blackTimerComp->start();
    }
    else {
        _whiteTimerComp->start();
    }
}

void loloof64::GameTimer::startNewIllimitedGame(bool playerHasWhite)
{
    _whiteTimerComp->stop();
    _blackTimerComp->stop();

    _isActive = false;
    _remainingWhiteTimeMs = 0;
    _remainingBlackTimeMs = 0;

    _whiteSideLabel->setText(QString(tr(playerHasWhite ? "Player" : "Computer")));
    _blackSideLabel->setText(QString(tr(playerHasWhite ? "Computer" : "Player")));

    _whiteTime->setText("--:--");
    _blackTime->setText("--:--");
}

void loloof64::GameTimer::toggleClockSide()
{
    if (!_isActive) return;
    if (_blackTimerActive)
    {
        _blackTimerComp->stop();
        _whiteTimerComp->start();
        int remainingInterval = _blackTimerComp->remainingTime();
        _remainingBlackTimeMs -= 1000 - remainingInterval;

        updateTimerTexts();
    }
    else
    {
        _whiteTimerComp->stop();
        _blackTimerComp->start();
        int remainingInterval = _whiteTimerComp->remainingTime();
        _remainingWhiteTimeMs -= 1000 - remainingInterval;

        updateTimerTexts();
    }
}

void loloof64::GameTimer::updateTimerTexts()
{
    int whiteSeconds = _remainingWhiteTimeMs / 1000;
    int whiteMinutes = whiteSeconds / 60;

    int blackSeconds = _remainingBlackTimeMs / 1000;
    int blackMinutes = blackSeconds / 60;

    QString whiteTimeStr;
    _whiteTime->setText(whiteTimeStr.sprintf("%02d:%02d", whiteMinutes, whiteSeconds));
    _blackTime->setText(whiteTimeStr.sprintf("%02d:%02d", blackMinutes, blackSeconds));
}
