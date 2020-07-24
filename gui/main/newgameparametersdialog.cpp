#include "newgameparametersdialog.h"
#include <QMessageBox>

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

    _mustUseTimer = new QCheckBox(tr("Use time"));

    _playerTimerLine = new QHBoxLayout();
    _playerTimerLineLabel = new QLabel(tr("Player"));
    _playerMinutesVal = new QLineEdit();
    _playerMinutesVal->setAlignment(Qt::AlignmentFlag::AlignRight);
    _playerMinutesVal->setMaxLength(4);
    _playerMinutesLabel = new QLabel(tr("Minutes"));
    _playerSecondsVal = new QLineEdit();
    _playerSecondsVal->setAlignment(Qt::AlignmentFlag::AlignRight);
    _playerSecondsVal->setMaxLength(2);
    _playerSecondsLabel = new QLabel(tr("Seconds"));

    _mustUseAsymetricTiming = new QCheckBox(tr("Set different computer time"));

    _cpuTimerLine = new QHBoxLayout();
    _cpuTimerLineLabel = new QLabel(tr("Computer"));
    _cpuMinutesVal = new QLineEdit();
    _cpuMinutesVal->setAlignment(Qt::AlignmentFlag::AlignRight);
    _cpuMinutesVal->setMaxLength(4);
    _cpuMinutesLabel = new QLabel(tr("Minutes"));
    _cpuSecondsVal = new QLineEdit();
    _cpuSecondsVal->setAlignment(Qt::AlignmentFlag::AlignRight);
    _cpuSecondsVal->setMaxLength(2);
    _cpuSecondsLabel = new QLabel(tr("Seconds"));

    _validationButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    _cpuTimerLine->addWidget(_cpuTimerLineLabel);
    _cpuTimerLine->addStretch();
    _cpuTimerLine->addWidget(_cpuMinutesVal);
    _cpuTimerLine->addWidget(_cpuMinutesLabel);
    _cpuTimerLine->addStretch();
    _cpuTimerLine->addWidget(_cpuSecondsVal);
    _cpuTimerLine->addWidget(_cpuSecondsLabel);
    _cpuTimerLine->addStretch();

    _playerTimerLine->addWidget(_playerTimerLineLabel);
    _playerTimerLine->addStretch();
    _playerTimerLine->addWidget(_playerMinutesVal);
    _playerTimerLine->addWidget(_playerMinutesLabel);
    _playerTimerLine->addStretch();
    _playerTimerLine->addWidget(_playerSecondsVal);
    _playerTimerLine->addWidget(_playerSecondsLabel);
    _playerTimerLine->addStretch();

    _playerTypeSelectionLine->addWidget(_playerTypeSelectionLabel);
    _playerTypeSelectionLine->addWidget(_playerTypeSelectionCombo);
    _playerTypeSelectionLine->addStretch();

    _mainLayout->addWidget(_chessBoard);
    _mainLayout->addLayout(_playerTypeSelectionLine);
    _mainLayout->addWidget(_mustUseTimer);
    _mainLayout->addLayout(_playerTimerLine);
    _mainLayout->addWidget(_mustUseAsymetricTiming);
    _mainLayout->addLayout(_cpuTimerLine);
    _mainLayout->addWidget(_validationButtons);

    updateTimeComponentsVisibility();

    connect(_mustUseTimer, &QCheckBox::stateChanged, [this](int /*newState*/) {
        updateTimeComponentsVisibility();
    });

    connect(_mustUseAsymetricTiming, &QCheckBox::stateChanged, [this](int /*newState*/) {
       updateTimeComponentsVisibility();
    });

    connect(_validationButtons, &QDialogButtonBox::accepted, [this]() {
        auto timedGame = _mustUseTimer->isChecked();
        if (timedGame)
        {
            emitNewTimedGameRequest();
        }
        else
        {
            bool playerHasWhite = _playerTypeSelectionCombo->currentIndex() == 0;
            emit newGameRequest(_positionFen, playerHasWhite);
            close();
        }
    });

    connect(_validationButtons, &QDialogButtonBox::rejected, [this]() {
        close();
    });
}

NewGameParametersDialog::~NewGameParametersDialog()
{
    delete _validationButtons;

    delete _cpuSecondsLabel;
    delete _cpuSecondsVal;
    delete _cpuMinutesLabel;
    delete _cpuMinutesVal;
    delete _cpuTimerLineLabel;
    delete _cpuTimerLine;

    delete _mustUseAsymetricTiming;

    delete _playerSecondsLabel;
    delete _playerSecondsVal;
    delete _playerMinutesLabel;
    delete _playerMinutesVal;
    delete _playerTimerLineLabel;
    delete _playerTimerLine;

    delete _mustUseTimer;

    delete _playerTypeSelectionCombo;
    delete _playerTypeSelectionLabel;
    delete _playerTypeSelectionLine;
    delete _chessBoard;

    delete _mainLayout;
}

void NewGameParametersDialog::updateTimeComponentsVisibility()
{
    if (_mustUseTimer->isChecked())
    {
        _playerTimerLineLabel->setEnabled(true);
        _playerMinutesVal->setEnabled(true);
        _playerMinutesLabel->setEnabled(true);
        _playerSecondsVal->setEnabled(true);
        _playerSecondsLabel->setEnabled(true);
        _mustUseAsymetricTiming->setEnabled(true);
        if (_mustUseAsymetricTiming->isChecked())
        {
            _cpuTimerLineLabel->setEnabled(true);
            _cpuMinutesVal->setEnabled(true);
            _cpuMinutesLabel->setEnabled(true);
            _cpuSecondsVal->setEnabled(true);
            _cpuSecondsLabel->setEnabled(true);
        }
        else
        {
            _cpuTimerLineLabel->setEnabled(false);
            _cpuMinutesVal->setEnabled(false);
            _cpuMinutesLabel->setEnabled(false);
            _cpuSecondsVal->setEnabled(false);
            _cpuSecondsLabel->setEnabled(false);
        }
    }
    else
    {
        _playerTimerLineLabel->setEnabled(false);
        _playerMinutesVal->setEnabled(false);
        _playerMinutesLabel->setEnabled(false);
        _playerSecondsVal->setEnabled(false);
        _playerSecondsLabel->setEnabled(false);
        _mustUseAsymetricTiming->setEnabled(false);
        _cpuTimerLineLabel->setEnabled(false);
        _cpuMinutesVal->setEnabled(false);
        _cpuMinutesLabel->setEnabled(false);
        _cpuSecondsVal->setEnabled(false);
        _cpuSecondsLabel->setEnabled(false);
    }
}

void NewGameParametersDialog::emitNewTimedGameRequest()
{
    bool playerHasWhite = _playerTypeSelectionCombo->currentIndex() == 0;
    bool playerMinutesOk;
    auto playerMinutes = _playerMinutesVal->text().toInt(&playerMinutesOk);
    if (! playerMinutesOk || playerMinutes < 0) {
        QMessageBox::critical(this, tr("Time value error"), tr("Player minutes must be a positive number"));
        return;
    }

    bool playerSecondsOk;
    auto playerSeconds = _playerSecondsVal->text().toInt(&playerSecondsOk);
    if (! playerSecondsOk || playerSeconds < 0) {
        QMessageBox::critical(this, tr("Time value error"), tr("Player seconds must be a positive number"));
        return;
    }

    auto isAsymetricalTime = _mustUseAsymetricTiming->isChecked();
    if (isAsymetricalTime)
    {
        bool computerMinutesOk;
        auto computerMinutes = _cpuMinutesVal->text().toInt(&computerMinutesOk);
        if (! computerMinutesOk || computerMinutes < 0) {
            QMessageBox::critical(this, tr("Time value error"), tr("Computer minutes must be a positive number"));
            return;
        }

        bool computerSecondsOk;
        auto computerSeconds = _cpuSecondsVal->text().toInt(&computerSecondsOk);
        if (! computerSecondsOk || computerSeconds < 0) {
            QMessageBox::critical(this, tr("Time value error"), tr("Computer seconds must be a positive number"));
            return;
        }

        int totalPlayerTimeSeconds = playerMinutes * 60 + playerSeconds;
        int totalPlayerTimeMs = totalPlayerTimeSeconds * 1000;

        int totalComputerTimeSeconds = computerMinutes * 60 + computerSeconds;
        int totalComputerTimeMs = totalComputerTimeSeconds * 1000;

        int whiteTimeMs = playerHasWhite ? totalPlayerTimeMs : totalComputerTimeMs;
        int blackTimeMs = playerHasWhite ? totalComputerTimeMs : totalPlayerTimeMs;

        emit newTimedGameRequest(_positionFen, playerHasWhite, whiteTimeMs, blackTimeMs);
    }
    else
    {
        int totalTimeSeconds = playerMinutes * 60 + playerSeconds;
        int totalTimeMs = totalTimeSeconds * 1000;

        emit newTimedGameRequest(_positionFen, playerHasWhite, totalTimeMs, totalTimeMs);
    }

    close();
}
