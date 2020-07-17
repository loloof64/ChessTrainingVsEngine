#include "uciengineoptionspin.h"

#include <QStringList>
#include <QRegExp>

bool loloof64::UCIEngineOptionSpin::canParse(QString optionString)
{
    auto parts = optionString.split(QRegExp("\\s+"));

    if (parts.size() < 5) return false;

    auto name = parts[2];
    auto type = parts[4];

    if (type != "spin") return false;

    return true;
}

loloof64::UCIEngineOptionSpin::UCIEngineOptionSpin(QString optionString)
{
    auto parts = optionString.split(' ');

    if (parts.size() < 5) throw QString("Not a spin option");

    _name = parts[2];
    auto type = parts[4];

    if (type != "spin") throw QString("Not a spin option");

    _default = parts[6].toInt();
    _min = parts[8].toInt();
    _max = parts[10].toInt();
    _current = _default;
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

int loloof64::UCIEngineOptionSpin::getCurrent() const
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
