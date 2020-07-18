#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>

class SettingsDialog : public QDialog
{
        Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    QVBoxLayout * _mainLayout;
    QHBoxLayout * _engineLineLayout;
    QDialogButtonBox * _validationButtons;

    QLabel * _uciEngineLabel;
    QLineEdit * _uciEngineLineEdit;
    QPushButton * _uciEngineChooserButton;
};

#endif // SETTINGSDIALOG_H
