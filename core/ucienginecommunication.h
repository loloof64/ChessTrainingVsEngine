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
        UCIEngineCommunication(QString executablePath);
        ~UCIEngineCommunication();
        void close();
        void sendCommand(QString command);

    signals:
        void isReady();
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
