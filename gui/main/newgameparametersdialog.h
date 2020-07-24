#ifndef NEWGAMEPARAMETERSDIALOG_H
#define NEWGAMEPARAMETERSDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QDialogButtonBox>

#include "../chessboard/chessboard.h"

class NewGameParametersDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameParametersDialog(QString positionFen, QWidget *parent = nullptr);
    virtual ~NewGameParametersDialog();

signals:
    void newGameRequest(QString positionFen, bool playerHasWhite);

private:
    QVBoxLayout * _mainLayout;
    loloof64::ChessBoard * _chessBoard;
    QHBoxLayout * _playerTypeSelectionLine;
    QLabel * _playerTypeSelectionLabel;
    QComboBox * _playerTypeSelectionCombo;
    QCheckBox * _mustUseTimer;

    QHBoxLayout * _playerTimerLine;
    QLabel * _playerTimerLineLabel;
    QLineEdit * _playerMinutesVal;
    QLabel *_playerMinutesLabel;
    QLineEdit * _playerSecondsVal;
    QLabel * _playerSecondsLabel;

    QCheckBox * _mustUseAsymetricTiming;

    QHBoxLayout * _cpuTimerLine;
    QLabel * _cpuTimerLineLabel;
    QLineEdit * _cpuMinutesVal;
    QLabel *_cpuMinutesLabel;
    QLineEdit * _cpuSecondsVal;
    QLabel * _cpuSecondsLabel;

    QDialogButtonBox * _validationButtons;

    QString _positionFen;

    void updateTimeComponentsVisibility();
};

#endif // NEWGAMEPARAMETERSDIALOG_H
