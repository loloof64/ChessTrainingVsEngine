#include "settingsdialog.h"
#include <QFileDialog>
#include <QMessageBox>

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

    connect(_uciEngineChooserButton, &QPushButton::clicked, [this] {
        auto choosenFile = QFileDialog::getOpenFileName(this, tr("Choose engine"), QString(), tr("All files"));
        if ( ! choosenFile.isEmpty() ) {
            _uciEngineLineEdit->setText(choosenFile);
        }
    });

    _engineLineLayout->addWidget(_uciEngineLabel);
    _engineLineLayout->addWidget(_uciEngineLineEdit);
    _engineLineLayout->addWidget(_uciEngineChooserButton);

    _mainLayout->addLayout(_engineLineLayout);
    _mainLayout->addWidget(_validationButtons);

    connect(_validationButtons, &QDialogButtonBox::accepted, [this]() {
        if (_uciEngineLineEdit->text().isEmpty()) {
            QMessageBox::critical(this, tr("No engine choosen"), tr("You can't validate without choosing an UCI engine !"));
            return;
        }
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
