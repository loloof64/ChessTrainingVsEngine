#include "settingsdialog.h"
#include "../../libs/mini-yaml/Yaml.hpp"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent): QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint), _fileChooserDir(QString())
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
        auto choosenFile = QFileDialog::getOpenFileName(this, tr("Choose engine"), _fileChooserDir);
        if ( ! choosenFile.isEmpty() ) {
            _uciEngineLineEdit->setText(choosenFile);
            _fileChooserDir = QDir(choosenFile).absolutePath();
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

        serializeOptionFile();
        close();
    });

    connect(_validationButtons, &QDialogButtonBox::rejected, [this]()
    {
        close();
    });

    loadOptionsFile();

    setWindowTitle(tr("Settings"));
    setModal(true);
}

SettingsDialog::~SettingsDialog()
{
    delete _uciEngineChooserButton;
    delete _uciEngineLineEdit;
    delete _uciEngineLabel;

    delete _validationButtons;
    delete _engineLineLayout;
    delete _mainLayout;
}


void SettingsDialog::serializeOptionFile()
{
    Yaml::Node root;

    try
    {
        auto newEnginePath = _uciEngineLineEdit->text();
        root["uci_engine"] = newEnginePath.toStdString();
        auto filePath = QDir::toNativeSeparators(QDir::homePath() + "/ChessTrainingVsEngine.yml");
        Yaml::Serialize(root, filePath.toStdString().c_str());

        emit enginePathChanged(newEnginePath);
    }
    catch (Yaml::OperationException &ex)
    {
        std::cerr << ex.Message() << std::endl;
        QMessageBox::critical(this, tr("Saving error"), tr("Failed to save configuration file !"));
    }
}

void SettingsDialog::loadOptionsFile()
{
    try {
        Yaml::Node root;
        auto filePath = QDir::toNativeSeparators(QDir::homePath() + "/ChessTrainingVsEngine.yml");
        Yaml::Parse(root, filePath.toStdString().c_str());

        auto uciEnginePath = QString::fromStdString(root["uci_engine"].As<std::string>());
        _uciEngineLineEdit->setText(uciEnginePath);
        _fileChooserDir = QDir(uciEnginePath).absolutePath();
    }
    catch (Yaml::OperationException &ex) {
        std::cerr << ex.Message() << std::endl;
        QMessageBox::critical(this, tr("Loading error"), tr("No configuration file !"));
    }
    catch (Yaml::ParsingException &ex) {
        std::cerr << ex.Message() << std::endl;
        QMessageBox::critical(this, tr("Loading error"), tr("Failed reading configuration file !"));
    }
}
