#include "ucienginecommunication.h"

//////////////////////////
#include <QDebug>
//////////////////////////

loloof64::UCIEngineCommunication::UCIEngineCommunication(QString executablePath)
{
    _relatedProcess = new QProcess();
    connect(_relatedProcess, &QProcess::readyRead,
            [this]()
    {
        auto stdOutputBytes = _relatedProcess->readAllStandardOutput();
        auto stdOutput = QString::fromStdString(stdOutputBytes.toStdString());
        auto stdOutputLines = stdOutput.split('\n');

        for (auto it = stdOutputLines.begin(); it != stdOutputLines.end(); ++it)
        {
            auto line = *it;
            /////////////////////
            qDebug() << line;
            /////////////////////
            if (UCIEngineOptionSpin::canParse(line)) _spinOptions.append(UCIEngineOptionSpin(line));
        }

        ////////////////////////////////////////
        for (auto it = _spinOptions.begin(); it != _spinOptions.end(); ++it)
        {
            qDebug() << QString("Spin option ") << QString(it->getName()) << " : " <<
                         QString::number(it->getCurrent()) << "([" <<
                         QString::number(it->getMinimum()) << ", " <<
                         QString::number(it->getMaximum()) << "; " <<
                         QString::number(it->getDefault()) << "])";
        }
        ////////////////////////////////////////
    });

    _relatedProcess->start(executablePath);
    _relatedProcess->write("uci\n");
}


loloof64::UCIEngineCommunication::~UCIEngineCommunication() {
    if (_relatedProcess != nullptr) {
        _relatedProcess->close();
    }

    delete _relatedProcess;
}

void loloof64::UCIEngineCommunication::close() {
    if (_relatedProcess != nullptr) {
        _relatedProcess->close();
    }
}
