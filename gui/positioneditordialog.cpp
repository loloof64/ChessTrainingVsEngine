#include "positioneditordialog.h"

#include <QHeaderView>
#include <QIcon>
#include <QApplication>
#include <QClipboard>

PositionEditorDialog::PositionEditorDialog(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint)
{
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(10);

    _mainEditorZone = new QWidget();

    _mainEditorZoneLayout = new QHBoxLayout();
    _mainEditorZoneLayout->setSpacing(10);

    _piecesButtonsLayout = new QVBoxLayout();
    _piecesButtonsLayout->setSpacing(10);

    _whitePiecesButtonsLine = new QHBoxLayout();
    _whitePiecesButtonsLine->setSpacing(10);

    _blackPiecesButtonsLine = new QHBoxLayout();
    _blackPiecesButtonsLine->setSpacing(10);

    _validationButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    _editorComponent = new loloof64::PositionEditor(45, this);

    _trashCanButton = new QPushButton();
    _trashCanButton->setIcon(QIcon(":/icons/trashCan.svg"));
    _trashCanButton->setIconSize(QSize(50, 50));

    _whitePawnButton = new QPushButton();
    _whitePawnButton->setIcon(QIcon(":/chess_vectors/pl.svg"));
    _whitePawnButton->setIconSize(QSize(50, 50));

    _whiteKnightButton = new QPushButton();
    _whiteKnightButton->setIcon(QIcon(":/chess_vectors/nl.svg"));
    _whiteKnightButton->setIconSize(QSize(50, 50));

    _whiteBishopButton = new QPushButton();
    _whiteBishopButton->setIcon(QIcon(":/chess_vectors/bl.svg"));
    _whiteBishopButton->setIconSize(QSize(50, 50));

    _whiteRookButton = new QPushButton();
    _whiteRookButton->setIcon(QIcon(":/chess_vectors/rl.svg"));
    _whiteRookButton->setIconSize(QSize(50, 50));

    _whiteQueenButton = new QPushButton();
    _whiteQueenButton->setIcon(QIcon(":/chess_vectors/ql.svg"));
    _whiteQueenButton->setIconSize(QSize(50, 50));

    _whiteKingButton = new QPushButton();
    _whiteKingButton->setIcon(QIcon(":/chess_vectors/kl.svg"));
    _whiteKingButton->setIconSize(QSize(50, 50));

    _blackPawnButton = new QPushButton();
    _blackPawnButton->setIcon(QIcon(":/chess_vectors/pd.svg"));
    _blackPawnButton->setIconSize(QSize(50, 50));

    _blackKnightButton = new QPushButton();
    _blackKnightButton->setIcon(QIcon(":/chess_vectors/nd.svg"));
    _blackKnightButton->setIconSize(QSize(50, 50));

    _blackBishopButton = new QPushButton();
    _blackBishopButton->setIcon(QIcon(":/chess_vectors/bd.svg"));
    _blackBishopButton->setIconSize(QSize(50, 50));

    _blackRookButton = new QPushButton();
    _blackRookButton->setIcon(QIcon(":/chess_vectors/rd.svg"));
    _blackRookButton->setIconSize(QSize(50, 50));

    _blackQueenButton = new QPushButton();
    _blackQueenButton->setIcon(QIcon(":/chess_vectors/qd.svg"));
    _blackQueenButton->setIconSize(QSize(50, 50));

    _blackKingButton = new QPushButton();
    _blackKingButton->setIcon(QIcon(":/chess_vectors/kd.svg"));
    _blackKingButton->setIconSize(QSize(50, 50));

    _optionsZone = new QTabWidget();

    _generalOptions = new QWidget();
    _generalOptionsLayout = new QVBoxLayout();
    _generalOptionsLayout->setSpacing(10);
    _playerTurnGroup = new QGroupBox(tr("Turn"));
    _playerTurnGroupLayout = new QHBoxLayout();
    _playerTurnGroupLayout->setSpacing(10);
    _whiteTurnButton = new QRadioButton(tr("White"));
    _blackTurnButton = new QRadioButton(tr("Black"));
    _whiteTurnButton->setChecked(true);
    _moveNumberLayout = new QHBoxLayout();
    _moveNumberLayout->setSpacing(10);
    _moveNumberLabel = new QLabel(tr("Move number"));
    _moveNumberValue = new QLineEdit();
    _moveNumberValue->setMaxLength(3);
    _moveNumberValue->setFixedWidth(45);
    _moveNumberValue->setText("1");

    _advancedOptions = new QWidget();
    _advancedOptionsLayout = new QVBoxLayout();
    _advancedOptionsLayout->setSpacing(10);
    _castlesGroup = new QGroupBox(tr("Castles"));
    _castlesGroupLayout = new QHBoxLayout();
    _castlesGroupLayout->setSpacing(10);
    _whiteOO = new QCheckBox(tr("white O-O"));
    _whiteOOO = new QCheckBox(tr("white O-O-O"));
    _blackOO = new QCheckBox(tr("black O-O"));
    _blackOOO = new QCheckBox(tr("black O-O-O"));
    _whiteOO->setChecked(true);
    _whiteOOO->setChecked(true);
    _blackOO->setChecked(true);
    _blackOOO->setChecked(true);
    _enPassantSquareLayout = new QHBoxLayout();
    _enPassantSquareLayout->setSpacing(10);
    _enPassantLabel = new QLabel(tr("En-passant square"));
    _enPassantSquareFileCombo = new QComboBox();
    _enPassantSquareFileCombo->addItem("-");
    int ascii_lower_a = 97;
    for (auto val = 0; val < 8; val++) {
        auto letter = val + ascii_lower_a;
        auto letterString = QString(letter);
        _enPassantSquareFileCombo->addItem(letterString);
    }
    _enPassantSquareRankLabel = new QLabel();
    _fiftyMovesRuleLayout = new QHBoxLayout();
    _fiftyMovesRuleLabel = new QLabel(tr("50 moves rule counter"));
    _fiftyMovesRuleValue = new QLineEdit();
    _fiftyMovesRuleValue->setMaxLength(2);
    _fiftyMovesRuleValue->setFixedWidth(38);
    _fiftyMovesRuleValue->setText("0");

    _fenOptions = new QWidget();
    _fenOptionsLayout = new QVBoxLayout();
    _fenOptionsLayout->setSpacing(10);
    _fenValueLineLayout = new QHBoxLayout();
    _fenValueLineLayout->setSpacing(10);
    _fenValueLabel = new QLabel(tr("FEN"));
    _fenValueValue = new QLineEdit();
    _fenValueValue->setReadOnly(true);
    _fenButtonsLine = new QHBoxLayout();
    _fenButtonsLine->setSpacing(10);
    _copyFenButton = new QPushButton(tr("Copy FEN"));
    _pasteFenButton = new QPushButton(tr("Paste FEN"));

    _positionBuilder = new loloof64::PositionBuilder();

    _fenButtonsLine->addWidget(_copyFenButton);
    _fenButtonsLine->addWidget(_pasteFenButton);
    _fenButtonsLine->addStretch();
    _fenValueLineLayout->addWidget(_fenValueLabel);
    _fenValueLineLayout->addWidget(_fenValueValue);
    _fenValueLineLayout->addStretch();
    _fenOptionsLayout->addLayout(_fenValueLineLayout);
    _fenOptionsLayout->addLayout(_fenButtonsLine);
    _fenOptions->setLayout(_fenOptionsLayout);

    _fiftyMovesRuleLayout->addWidget(_fiftyMovesRuleLabel);
    _fiftyMovesRuleLayout->addWidget(_fiftyMovesRuleValue);
    _fiftyMovesRuleLayout->addStretch();
    _enPassantSquareLayout->addWidget(_enPassantLabel);
    _enPassantSquareLayout->addWidget(_enPassantSquareFileCombo);
    _enPassantSquareLayout->addWidget(_enPassantSquareRankLabel);
    _enPassantSquareLayout->addStretch();
    _castlesGroupLayout->addWidget(_whiteOO);
    _castlesGroupLayout->addWidget(_whiteOOO);
    _castlesGroupLayout->addWidget(_blackOO);
    _castlesGroupLayout->addWidget(_blackOOO);
    _castlesGroupLayout->addStretch();
    _castlesGroup->setLayout(_castlesGroupLayout);
    _castlesGroup->setStyleSheet("QGroupBox::title {position: left; margin: 5px;}");
    _advancedOptionsLayout->addWidget(_castlesGroup);
    _advancedOptionsLayout->addLayout(_enPassantSquareLayout);
    _advancedOptionsLayout->addLayout(_fiftyMovesRuleLayout);
    _advancedOptions->setLayout(_advancedOptionsLayout);

    _playerTurnGroupLayout->addWidget(_whiteTurnButton);
    _playerTurnGroupLayout->addWidget(_blackTurnButton);
    _playerTurnGroupLayout->addStretch();
    _playerTurnGroup->setLayout(_playerTurnGroupLayout);
    _playerTurnGroup->setStyleSheet("QGroupBox::title {position: left; margin: 5px;}");
    _moveNumberLayout->addWidget(_moveNumberLabel);
    _moveNumberLayout->addWidget(_moveNumberValue);
    _moveNumberLayout->addStretch();
    _generalOptionsLayout->addWidget(_playerTurnGroup);
    _generalOptionsLayout->addLayout(_moveNumberLayout);
    _generalOptions->setLayout(_generalOptionsLayout);

    _optionsZone->addTab(_generalOptions, tr("General", "General options of position editor"));
    _optionsZone->addTab(_advancedOptions, tr("Advanced", "Advanced options of position editor"));
    _optionsZone->addTab(_fenOptions, tr("FEN", "Fen options of position editor"));

    _whitePiecesButtonsLine->addWidget(_whitePawnButton);
    _whitePiecesButtonsLine->addWidget(_whiteKnightButton);
    _whitePiecesButtonsLine->addWidget(_whiteBishopButton);
    _whitePiecesButtonsLine->addWidget(_whiteRookButton);
    _whitePiecesButtonsLine->addWidget(_whiteQueenButton);
    _whitePiecesButtonsLine->addWidget(_whiteKingButton);

    _blackPiecesButtonsLine->addWidget(_blackPawnButton);
    _blackPiecesButtonsLine->addWidget(_blackKnightButton);
    _blackPiecesButtonsLine->addWidget(_blackBishopButton);
    _blackPiecesButtonsLine->addWidget(_blackRookButton);
    _blackPiecesButtonsLine->addWidget(_blackQueenButton);
    _blackPiecesButtonsLine->addWidget(_blackKingButton);

    _piecesButtonsLayout->addStretch();
    _piecesButtonsLayout->addWidget(_trashCanButton);
    _piecesButtonsLayout->addLayout(_whitePiecesButtonsLine);
    _piecesButtonsLayout->addLayout(_blackPiecesButtonsLine);
    _piecesButtonsLayout->addStretch();

    _mainEditorZoneLayout->addWidget(_editorComponent);
    _mainEditorZoneLayout->addLayout(_piecesButtonsLayout);
    _mainEditorZone->setLayout(_mainEditorZoneLayout);

    _mainLayout->addWidget(_mainEditorZone);
    _mainLayout->addWidget(_optionsZone);
    _mainLayout->addWidget(_validationButtons);

    connect(_whiteTurnButton, &QRadioButton::clicked, [this]() {
        _positionBuilder->setTurn(true);
        synchronizeWithBuilder();
    });

    connect(_blackTurnButton, &QRadioButton::clicked, [this]() {
        _positionBuilder->setTurn(false);
        synchronizeWithBuilder();
    });

    connect(_moveNumberValue, &QLineEdit::editingFinished, [this]() {
        bool conversionOk;
        int newMoveNumber = _moveNumberValue->text().toInt(&conversionOk);

        if (conversionOk) {
         _positionBuilder->setMoveNumber(newMoveNumber);
         synchronizeWithBuilder();
        }
    });

    connect(_whiteOO, &QRadioButton::clicked, [this]() {
       bool newValue = _whiteOO->isChecked();
       _positionBuilder->setWhiteOO(newValue);
        synchronizeWithBuilder();
    });

    connect(_whiteOOO, &QRadioButton::clicked, [this]() {
       bool newValue = _whiteOOO->isChecked();
       _positionBuilder->setWhiteOOO(newValue);
        synchronizeWithBuilder();
    });

    connect(_blackOO, &QRadioButton::clicked, [this]() {
       bool newValue = _blackOO->isChecked();
       _positionBuilder->setBlackOO(newValue);
        synchronizeWithBuilder();
    });

    connect(_blackOOO, &QRadioButton::clicked, [this]() {
       bool newValue = _blackOOO->isChecked();
       _positionBuilder->setBlackOOO(newValue);
        synchronizeWithBuilder();
    });

    connect(_enPassantSquareFileCombo, qOverload<int>(&QComboBox::activated), [this](int index) {
        _positionBuilder->setEnPassantFile(index - 1);
        synchronizeWithBuilder();
    });

    connect(_fiftyMovesRuleValue, &QLineEdit::editingFinished, [this]() {
        bool conversionOk;
        int newFiftyMovesCount = _fiftyMovesRuleValue->text().toInt(&conversionOk);

        if (conversionOk) {
         _positionBuilder->setFiftyMovesRuleCount(newFiftyMovesCount);
         synchronizeWithBuilder();
        }
    });

    connect(_pasteFenButton, &QPushButton::clicked, [this]() {
        const QClipboard *clipboard = QApplication::clipboard();
        try {
            _positionBuilder->setFromFen(clipboard->text());
            synchronizeWithBuilder();
        } catch (loloof64::IllegalPositionException & /* e */) {

        }
    });

    connect(_copyFenButton, &QPushButton::clicked, [this]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(_positionBuilder->getFen());
    });

    connect(_validationButtons, &QDialogButtonBox::accepted, [this]() {
        close();
    });

    connect(_validationButtons, &QDialogButtonBox::rejected, [this]()
    {
        close();
    });

    synchronizeWithBuilder();

    setWindowTitle(tr("Position editor"));
    setModal(true);
}

PositionEditorDialog::~PositionEditorDialog() {
    delete _pasteFenButton;
    delete _copyFenButton;
    delete _fenButtonsLine;
    delete _fenValueValue;
    delete _fenValueLabel;
    delete _fenValueLineLayout;
    delete _fenOptionsLayout;
    delete _fenOptions;

    delete _fiftyMovesRuleValue;
    delete _fiftyMovesRuleLabel;
    delete _fiftyMovesRuleLayout;
    delete _enPassantSquareRankLabel;
    delete _enPassantSquareFileCombo;
    delete _enPassantLabel;
    delete _enPassantSquareLayout;
    delete _blackOOO;
    delete _blackOO;
    delete _whiteOOO;
    delete _whiteOO;
    delete _castlesGroupLayout;
    delete _castlesGroup;
    delete _advancedOptionsLayout;
    delete _advancedOptions;

    delete _moveNumberValue;
    delete _moveNumberLabel;
    delete _moveNumberLayout;
    delete _blackTurnButton;
    delete _whiteTurnButton;
    delete _playerTurnGroupLayout;
    delete _playerTurnGroup;
    delete _generalOptionsLayout;
    delete _generalOptions;
    delete _optionsZone;

    delete _blackKingButton;
    delete _blackQueenButton;
    delete _blackRookButton;
    delete _blackBishopButton;
    delete _blackKnightButton;
    delete _blackPawnButton;

    delete _whiteKingButton;
    delete _whiteQueenButton;
    delete _whiteRookButton;
    delete _whiteBishopButton;
    delete _whiteKnightButton;
    delete _whitePawnButton;

    delete _trashCanButton;

    delete _editorComponent;
    delete _validationButtons;

    delete _blackPiecesButtonsLine;
    delete _whitePiecesButtonsLine;

    delete _piecesButtonsLayout;
    delete _mainEditorZoneLayout;
    delete _mainEditorZone;
    delete _mainLayout;
}

void PositionEditorDialog::synchronizeWithBuilder() {
    _editorComponent->setFromFen(_positionBuilder->getFen());

    _whiteTurnButton->setChecked(_positionBuilder->isWhiteTurn());
    _blackTurnButton->setChecked(! _positionBuilder->isWhiteTurn());
    _moveNumberValue->setText(QString::number(_positionBuilder->getMoveNumber()));

    _whiteOO->setChecked(_positionBuilder->getWhiteOO());
    _whiteOOO->setChecked(_positionBuilder->getWhiteOOO());
    _blackOO->setChecked(_positionBuilder->getBlackOO());
    _blackOOO->setChecked(_positionBuilder->getBlackOOO());

    int enPassantFile = _positionBuilder->getEnPassantFile();
    if (enPassantFile >= 0) {
       _enPassantSquareFileCombo->setCurrentIndex(1+enPassantFile);
       _enPassantSquareRankLabel->setText(_positionBuilder->isWhiteTurn() ? "6" : "3");
    }
    else {
        _enPassantSquareFileCombo->setCurrentIndex(0);
        _enPassantSquareRankLabel->setText("");
    }

    _fiftyMovesRuleValue->setText(QString::number(_positionBuilder->getFiftyMovesRuleCount()));

    _fenValueValue->setText(_positionBuilder->getFen());
}
