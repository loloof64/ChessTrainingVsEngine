#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

namespace loloof64 {
class GameTimer : public QWidget
{
    Q_OBJECT
public:
    explicit GameTimer(QWidget *parent = nullptr);
    ~GameTimer() override;

    void startNewTimedGame(bool playerHasWhite, int whiteTimeMs, int blackTimeMs, bool blackStartGame = false);
    void startNewIllimitedGame(bool playerHasWhite);

    int getRemainingWhiteTimeMs() const { return _remainingWhiteTimeMs; }
    int getRemainingBlackTimeMs() const { return _remainingBlackTimeMs; }
    bool isActive() const { return _isActive; }
    void toggleClockSide();
    void stop();

signals:
    void whiteOutOfTime();
    void blackOutOfTime();

private:
    bool _isActive = false;
    bool _blackTimerActive = false;
    int _remainingWhiteTimeMs = 0;
    int _remainingBlackTimeMs = 0;
    QHBoxLayout * _mainLayout;
    QLabel * _whiteSideLabel;
    QLabel * _blackSideLabel;
    QLabel * _whiteTime;
    QLabel * _blackTime;

    QTimer * _whiteTimerComp;
    QTimer * _blackTimerComp;

    void updateTimerTexts();
};
}

#endif // GAMETIMER_H
