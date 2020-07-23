#include "newgameparametersdialog.h"

NewGameParametersDialog::NewGameParametersDialog(QString positionFen, QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint), _positionFen(positionFen)
{
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(10);

    _chessBoard = new loloof64::ChessBoard(50);
    loloof64::HistoryItem historyItem("", positionFen, loloof64::MoveCoordinates(-1,-1,-1,-1));
    _chessBoard->setPosition(historyItem);
    _chessBoard->setWhitePlayerType(loloof64::PlayerType::EXTERNAL);
    _chessBoard->setBlackPlayerType(loloof64::PlayerType::EXTERNAL);

    _playerTypeSelectionLine = new QHBoxLayout();
    _playerTypeSelectionLine->setSpacing(10);
    _playerTypeSelectionLabel = new QLabel(tr("Player side"));
    _playerTypeSelectionCombo = new QComboBox();
    _playerTypeSelectionCombo->setEditable(false);
    _playerTypeSelectionCombo->addItem(tr("White"));
    _playerTypeSelectionCombo->addItem(tr("Black"));
    _playerTypeSelectionCombo->setCurrentIndex(0);

    _playerTypeSelectionLine->addWidget(_playerTypeSelectionLabel);
    _playerTypeSelectionLine->addWidget(_playerTypeSelectionCombo);
    _playerTypeSelectionLine->addStretch();

    _validationButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    _mainLayout->addWidget(_chessBoard);
    _mainLayout->addLayout(_playerTypeSelectionLine);
    _mainLayout->addWidget(_validationButtons);

    connect(_validationButtons, &QDialogButtonBox::accepted, [this]() {
        bool playerHasWhite = _playerTypeSelectionCombo->currentIndex() == 0;
        emit newGameRequest(_positionFen, playerHasWhite);
        close();
    });

    connect(_validationButtons, &QDialogButtonBox::rejected, [this]() {
        close();
    });
}

NewGameParametersDialog::~NewGameParametersDialog()
{
    delete _validationButtons;
    delete _playerTypeSelectionCombo;
    delete _playerTypeSelectionLabel;
    delete _playerTypeSelectionLine;
    delete _chessBoard;
    delete _mainLayout;
}
