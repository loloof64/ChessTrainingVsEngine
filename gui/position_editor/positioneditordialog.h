#ifndef POSITIONEDITORDIALOG_H
#define POSITIONEDITORDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPixmap>
#include <QMessageBox>
#include "positioneditor.h"

class PositionEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PositionEditorDialog(QWidget *parent = nullptr);
    virtual ~PositionEditorDialog() override;

signals:
    void newGamePosition(QString positionFen);

private:
    QVBoxLayout * _mainLayout;
    QWidget * _mainEditorZone;
    QHBoxLayout * _mainEditorZoneLayout;
    QVBoxLayout * _piecesButtonsLayout;
    QHBoxLayout * _whitePiecesButtonsLine;
    QHBoxLayout * _blackPiecesButtonsLine;
    QHBoxLayout * _selectedPieceLine;

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
    QLabel * _currentSelectionLabel;
    QLabel * _currentSelectionComponent;

    QTabWidget * _optionsZone;

    QWidget * _generalOptions;
    QVBoxLayout * _generalOptionsLayout;
    QGroupBox * _playerTurnGroup;
    QHBoxLayout * _playerTurnGroupLayout;
    QRadioButton * _whiteTurnButton;
    QRadioButton * _blackTurnButton;
    QHBoxLayout * _moveNumberLayout;
    QLabel * _moveNumberLabel;
    QLineEdit * _moveNumberValue;
    QHBoxLayout * _easyModificationButtonsLine;
    QPushButton * _eraseAllButton;
    QPushButton * _standardPositionButton;

    QWidget * _advancedOptions;
    QVBoxLayout * _advancedOptionsLayout;
    QGroupBox * _castlesGroup;
    QHBoxLayout * _castlesGroupLayout;
    QCheckBox * _whiteOO;
    QCheckBox * _whiteOOO;
    QCheckBox * _blackOO;
    QCheckBox * _blackOOO;
    QHBoxLayout * _enPassantSquareLayout;
    QLabel * _enPassantLabel;
    QComboBox * _enPassantSquareFileCombo;
    QLabel * _enPassantSquareRankLabel;
    QHBoxLayout * _fiftyMovesRuleLayout;
    QLabel * _fiftyMovesRuleLabel;
    QLineEdit * _fiftyMovesRuleValue;

    QWidget * _fenOptions;
    QVBoxLayout * _fenOptionsLayout;
    QHBoxLayout * _fenValueLineLayout;
    QLabel * _fenValueLabel;
    QLineEdit * _fenValueValue;
    QHBoxLayout * _fenButtonsLine;
    QPushButton * _copyFenButton;
    QPushButton * _pasteFenButton;
    loloof64::PositionBuilder * _positionBuilder;

    char _editingValue = ' ';

    void synchronizeWithBuilder();
    void connectComponents();
    void updateSelectedPiece();
};

#endif // POSITIONEDITORDIALOG_H
