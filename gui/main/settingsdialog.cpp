#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent): QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint)
{
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(10);

    _engineLineLayout = new QHBoxLayout();
    _engineLineLayout->setSpacing(10);

    _validationButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    _uciEngineLabel = new QLabel(tr("UCI engine"), this);
    _uciEngineLineEdit = new QLineEdit(this);
    _uciEngineChooserButton = new QPushButton(tr("Choose engine ..."), this);

    _engineLineLayout->addWidget(_uciEngineLabel);
    _engineLineLayout->addWidget(_uciEngineLineEdit);
    _engineLineLayout->addWidget(_uciEngineChooserButton);

    _mainLayout->addLayout(_engineLineLayout);
    _mainLayout->addWidget(_validationButtons);

    connect(_validationButtons, &QDialogButtonBox::accepted, [this]() {
        close();
    });

    connect(_validationButtons, &QDialogButtonBox::rejected, [this]() {
        close();
    });

    setWindowTitle(tr("Settings"));
    setModal(true);
}

SettingsDialog::~SettingsDialog() {
    delete _uciEngineChooserButton;
    delete _uciEngineLineEdit;
    delete _uciEngineLabel;

    delete _validationButtons;
    delete _engineLineLayout;
    delete _mainLayout;
}
