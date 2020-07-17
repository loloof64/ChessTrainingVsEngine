#ifndef UCIENGINECOMMUNICATION_H
#define UCIENGINECOMMUNICATION_H

#include "uciengineoptionspin.h"

#include <QObject>
#include <QProcess>
#include <QString>
#include <QVector>

namespace loloof64 {
    class UCIEngineCommunication : public QObject
    {
        Q_OBJECT

    public:
        UCIEngineCommunication(QString executablePath);
        ~UCIEngineCommunication();
        void close();
    private:
        QProcess * _relatedProcess;
        QVector<UCIEngineOptionSpin> _spinOptions;
    };
}

#endif // UCIENGINECOMMUNICATION_H
