#include "ucienginecommunication.h"

#include <QDebug>

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

            qDebug() << line;

            if (UCIEngineOptionSpin::canParse(line))
            {
                UCIEngineOptionSpin option(line);
                _spinOptions.insert(option.getName(), option);
            }
            if (line == "uciok") {
                _uciOk = true;
                setOptions();
            }
            if (line == "readyok") {
                _readyOk = true;
                emit isReady();
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
                                   "setoption name %s value %d\n",
                                   option.getName().toStdString().c_str(), option.getValue())
                               .toStdString().c_str());
    }
    if (_spinOptions.contains("Skill Level")) {
        auto option = _spinOptions["Skill Level"];
        option.setToMaximum();

        QString optionCommand;
        _relatedProcess->write(optionCommand.sprintf(
                                   "setoption name %s value %d\n",
                                   option.getName().toStdString().c_str(), option.getValue())
                               .toStdString().c_str());
    }
    _relatedProcess->write("isready\n");
}

void loloof64::UCIEngineCommunication::sendCommand(QString command)
{
    if (_readyOk)
    {
        QString cmd;
        _relatedProcess->write(cmd.sprintf("%s\n", command.toStdString().c_str()).toStdString().c_str());
    }
}
