#ifndef POSITIONEDITOR_H
#define POSITIONEDITOR_H

#include <QWidget>
#include <QString>
#include "../../core/positionbuilder.h"
#include "../../core/adapters/thcposition.h"

namespace loloof64 {
    class PositionEditor : public QWidget
    {
        Q_OBJECT
    public:
        explicit PositionEditor(int cellsSize, QWidget *parent = nullptr);
        virtual ~PositionEditor() override;

        void setFromFen(QString positionValue);

    private:
        int _cellsSize;
        loloof64::ThcPosition _position;

        void paintEvent(QPaintEvent *event) override;
    };
}
#endif // POSITIONEDITOR_H
