#include "positioneditordialog.h"

#include <QHeaderView>
#include <QIcon>

PositionEditorDialog::PositionEditorDialog(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint)
{
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(10);

    _mainEditorZone = new QHBoxLayout();
    _mainEditorZone->setSpacing(10);

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

    _piecesButtonsLayout->addWidget(_trashCanButton);
    _piecesButtonsLayout->addLayout(_whitePiecesButtonsLine);
    _piecesButtonsLayout->addLayout(_blackPiecesButtonsLine);

    _mainEditorZone->addWidget(_editorComponent);
    _mainEditorZone->addLayout(_piecesButtonsLayout);

    _mainLayout->addLayout(_mainEditorZone);
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

    delete _piecesButtonsLayout;
    delete _mainEditorZone;
    delete _mainLayout;
}
