#include "ucienginecommunication.h"

//////////////////////////
#include <iostream>
//////////////////////////

loloof64::UCIEngineCommunication::UCIEngineCommunication(QString executablePath)
{
    _relatedProcess = new QProcess();
    connect(_relatedProcess, &QProcess::readyRead,
            [this]()
    {
        auto stdOutputBytes = _relatedProcess->readAllStandardOutput();
        auto stdOutput = QString::fromStdString(stdOutputBytes.toStdString());

        //////////////////////////////////////////////
        std::cout << stdOutput.toStdString() << std::endl;
        //////////////////////////////////////////////
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
