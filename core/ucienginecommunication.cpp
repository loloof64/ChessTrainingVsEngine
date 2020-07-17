#include "ucienginecommunication.h"

/////////////////////////////////
#include <QDebug>
/////////////////////////////////

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

            if (UCIEngineOptionSpin::canParse(line))
            {
                UCIEngineOptionSpin option(line);
                /////////////////////////////
                qDebug() << "SPIN " << option.getName() << "[" << option.getValue() << " | " << option.getDefault() << " | " <<
                            option.getMinimum() << ", " << option.getMaximum() << "]";
                /////////////////////////////
                _spinOptions.insert(option.getName(), option);
            }
            if (line == "uciok") {
                _uciOk = true;
                setOptions();
            }
        }
    });

    _relatedProcess->start(executablePath);
    _relatedProcess->write("uci\n");
}


loloof64::UCIEngineCommunication::~UCIEngineCommunication()
{
    if (_relatedProcess != nullptr) {
        _relatedProcess->close();
    }

    delete _relatedProcess;
}

void loloof64::UCIEngineCommunication::close()
{
    if (_relatedProcess != nullptr) {
        _relatedProcess->close();
    }
}

void loloof64::UCIEngineCommunication::setOptions()
{
    if (_spinOptions.contains("UCI_Elo")) {
        auto option = _spinOptions["UCI_Elo"];
        option.setToMaximum();

        QString optionCommand;
        _relatedProcess->write(optionCommand.sprintf(
                                   "setoption name %s value %d",
                                   option.getName().toStdString().c_str(), option.getValue())
                               .toStdString().c_str());
    }
    if (_spinOptions.contains("Skill Level")) {
        auto option = _spinOptions["Skill Level"];
        option.setToMaximum();

        QString optionCommand;
        _relatedProcess->write(optionCommand.sprintf(
                                   "setoption name %s value %d",
                                   option.getName().toStdString().c_str(), option.getValue())
                               .toStdString().c_str());
    }
    _relatedProcess->write("isready\n");
}
