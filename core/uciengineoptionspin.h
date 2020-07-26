#ifndef UCIENGINEOPTIONSPIN_H
#define UCIENGINEOPTIONSPIN_H

#include <QString>

namespace loloof64 {
    class UCIEngineOptionSpin
    {
    public:
        static bool canParse(QString optionString);
        UCIEngineOptionSpin(QString optionString = "        ");
        void setToMinimum();
        void setToMaximum();
        void setToDefault();
        void setToValue(int value);
        QString getName() const;
        int getValue() const;
        int getDefault() const;
        int getMinimum() const;
        int getMaximum() const;
    private:
        QString _name;
        int _default;
        int _min;
        int _max;
        int _current;
    };
}

#endif // UCIENGINEOPTIONSPIN_H
