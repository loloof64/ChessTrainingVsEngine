#ifndef UCIENGINECOMMUNICATION_H
#define UCIENGINECOMMUNICATION_H

#include <QObject>
#include <QProcess>
#include <QString>

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
    };
}

#endif // UCIENGINECOMMUNICATION_H
