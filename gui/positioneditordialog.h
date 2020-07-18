#ifndef POSITIONEDITORDIALOG_H
#define POSITIONEDITORDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include "position_editor/positioneditor.h"

class PositionEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PositionEditorDialog(QWidget *parent = nullptr);
    virtual ~PositionEditorDialog() override;
signals:

public slots:

private:
    QVBoxLayout * _mainLayout;
    QHBoxLayout * _whitePiecesButtonsLine;
    QHBoxLayout * _blackPiecesButtonsLine;

    QDialogButtonBox * _validationButtons;
    loloof64::PositionEditor * _editorComponent;
    QPushButton * _trashCanButton;
    QPushButton * _whitePawnButton;
    QPushButton * _whiteKnightButton;
    QPushButton * _whiteBishopButton;
    QPushButton * _whiteRookButton;
    QPushButton * _whiteQueenButton;
    QPushButton * _whiteKingButton;
    QPushButton * _blackPawnButton;
    QPushButton * _blackKnightButton;
    QPushButton * _blackBishopButton;
    QPushButton * _blackRookButton;
    QPushButton * _blackQueenButton;
    QPushButton * _blackKingButton;
};

#endif // POSITIONEDITORDIALOG_H
