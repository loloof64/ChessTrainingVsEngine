#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

namespace loloof64 {
class GameTimer : public QWidget
{
    Q_OBJECT
public:
    explicit GameTimer(QWidget *parent = nullptr);
    ~GameTimer() override;

private:
    QHBoxLayout * _mainLayout;
    QLabel * _whiteSideLabel;
    QLabel * _blackSideLabel;
    QLabel * _whiteTime;
    QLabel * _blackTime;
};
}

#endif // GAMETIMER_H
