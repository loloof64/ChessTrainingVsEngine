#ifndef UCIENGINECOMMUNICATION_H
#define UCIENGINECOMMUNICATION_H

#include "uciengineoptionspin.h"

#include <QObject>
#include <QProcess>
#include <QString>
#include <QMap>

namespace loloof64 {
    class UCIEngineCommunication : public QObject
    {
        Q_OBJECT

    public:
        UCIEngineCommunication();
        ~UCIEngineCommunication();
        void close();
        void sendCommand(QString command);
        void setExecutablePath(QString executablePath);

    signals:
        void isReady();
        void isNotReady();
        void computedBestMove(QString moveString);

    private:
        QProcess * _relatedProcess;
        bool _uciOk;
        bool _readyOk;
        QMap<QString, UCIEngineOptionSpin> _spinOptions;
        void setOptions();
    };
}

#endif // UCIENGINECOMMUNICATION_H
