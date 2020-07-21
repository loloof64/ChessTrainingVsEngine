#ifndef NEWGAMEPARAMETERSDIALOG_H
#define NEWGAMEPARAMETERSDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

#include "chessboard/chessboard.h"

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
    QDialogButtonBox * _validationButtons;

    QString _positionFen;
};

#endif // NEWGAMEPARAMETERSDIALOG_H
