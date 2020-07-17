#include "uciengineoptionspin.h"

#include <QStringList>
#include <QRegExp>

bool loloof64::UCIEngineOptionSpin::canParse(QString optionString)
{
    auto parts = optionString.split(QRegExp("\\s+"));

    for (auto it = parts.begin(); it != parts.end(); ++it)
    {
        auto current = *it;
        if (current == "spin") return true;
    }

    return false;
}

loloof64::UCIEngineOptionSpin::UCIEngineOptionSpin(QString optionString)
{
    auto parts = optionString.split(' ');
    QString currentParsing;
    QString currentParsingType;

    for (auto it = parts.begin(); it != parts.end(); ++it)
    {
        auto currentPart = *it;

        if (currentPart == "name" || currentPart == "type" || currentPart == "default"
                || currentPart == "default" || currentPart == "min" || currentPart == "max")
        {
            currentParsingType = currentPart;
            if (currentPart == "name") currentParsing = QString();
            continue;
        }

        if (currentParsingType == "name")
        {
            _name += currentPart + " ";
        }
        else if (currentParsingType == "default")
        {
            _default = QString(currentPart).toInt();
            _current = _default;
        }
        else if (currentParsingType == "min")
        {
            _min = QString(currentPart).toInt();
        }
        else if (currentParsingType == "max")
        {
            _max = QString(currentPart).toInt();
        }
    }

    _name = _name.trimmed();
}

void loloof64::UCIEngineOptionSpin::setToDefault()
{
    _current = _default;
}

void loloof64::UCIEngineOptionSpin::setToMinimum()
{
    _current = _min;
}

void loloof64::UCIEngineOptionSpin::setToMaximum()
{
    _current = _max;
}

void loloof64::UCIEngineOptionSpin::setToValue(int value)
{
    if (value < _min) value = _min;
    if (value > _max) value = _max;
    _current = value;
}

QString loloof64::UCIEngineOptionSpin::getName() const
{
    return _name;
}

int loloof64::UCIEngineOptionSpin::getValue() const
{
    return _current;
}

int loloof64::UCIEngineOptionSpin::getDefault() const
{
    return _default;
}

int loloof64::UCIEngineOptionSpin::getMinimum() const
{
    return _min;
}

int loloof64::UCIEngineOptionSpin::getMaximum() const
{
    return _max;
}
