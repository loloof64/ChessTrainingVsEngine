#ifndef GAMESELECTIONDIALOG_H
#define GAMESELECTIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QComboBox>
#include <QPushButton>
#include "gameselectionmainzone.h"

namespace loloof64
{
    class GameSelectionDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit GameSelectionDialog(QWidget *parent = nullptr);
        ~GameSelectionDialog();
        void setPgnDatabase(PgnDatabase *database);
        quint64 getSelectedGameIndex() const;

    signals:

    private:
        int _gamesCount;

        QVBoxLayout *_layout;
        QLabel *_gameIndexLabel;
        QLabel *_playersLabel;
        QLabel *_eventLabel;
        GameSelectionMainZone *_mainZone;
        QPushButton *_validateButton;

        QString _whitePlayerName;
        QString _blackPlayerName;
        QString _eventName;
        QString _eventDate;
        QString _eventSite;
    };
};

#endif // GAMESELECTIONDIALOG_H
