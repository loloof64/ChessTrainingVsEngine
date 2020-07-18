#include "positioneditordialog.h"

#include <QHeaderView>
#include <QIcon>

PositionEditorDialog::PositionEditorDialog(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint)
{
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(10);

    _whitePiecesButtonsLine = new QHBoxLayout();
    _whitePiecesButtonsLine->setSpacing(10);

    _blackPiecesButtonsLine = new QHBoxLayout();
    _blackPiecesButtonsLine->setSpacing(10);

    _validationButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    _editorComponent = new loloof64::PositionEditor(45, this);

    _trashCanButton = new QPushButton();
    _trashCanButton->setIcon(QIcon(":/icons/trashCan.svg"));

    _whitePawnButton = new QPushButton();
    _whitePawnButton->setIcon(QIcon(":/chess_vectors/pl.svg"));

    _whiteKnightButton = new QPushButton();
    _whiteKnightButton->setIcon(QIcon(":/chess_vectors/nl.svg"));

    _whiteBishopButton = new QPushButton();
    _whiteBishopButton->setIcon(QIcon(":/chess_vectors/bl.svg"));

    _whiteRookButton = new QPushButton();
    _whiteRookButton->setIcon(QIcon(":/chess_vectors/rl.svg"));

    _whiteQueenButton = new QPushButton();
    _whiteQueenButton->setIcon(QIcon(":/chess_vectors/ql.svg"));

    _whiteKingButton = new QPushButton();
    _whiteKingButton->setIcon(QIcon(":/chess_vectors/kl.svg"));

    _blackPawnButton = new QPushButton();
    _blackPawnButton->setIcon(QIcon(":/chess_vectors/pd.svg"));

    _blackKnightButton = new QPushButton();
    _blackKnightButton->setIcon(QIcon(":/chess_vectors/nd.svg"));

    _blackBishopButton = new QPushButton();
    _blackBishopButton->setIcon(QIcon(":/chess_vectors/bd.svg"));

    _blackRookButton = new QPushButton();
    _blackRookButton->setIcon(QIcon(":/chess_vectors/rd.svg"));

    _blackQueenButton = new QPushButton();
    _blackQueenButton->setIcon(QIcon(":/chess_vectors/qd.svg"));

    _blackKingButton = new QPushButton();
    _blackKingButton->setIcon(QIcon(":/chess_vectors/kd.svg"));

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

    _mainLayout->addWidget(_editorComponent);
    _mainLayout->addWidget(_trashCanButton);
    _mainLayout->addLayout(_whitePiecesButtonsLine);
    _mainLayout->addLayout(_blackPiecesButtonsLine);
    _mainLayout->addWidget(_validationButtons);

    connect(_validationButtons, &QDialogButtonBox::accepted, [this]() {
        close();
    });

    connect(_validationButtons, &QDialogButtonBox::rejected, [this]()
    {
        close();
    });

    setWindowTitle(tr("Position editor"));
    setModal(true);
}

PositionEditorDialog::~PositionEditorDialog() {
    delete _trashCanButton;

    delete _editorComponent;
    delete _validationButtons;

    delete _blackPiecesButtonsLine;
    delete _whitePiecesButtonsLine;
    delete _mainLayout;
}
