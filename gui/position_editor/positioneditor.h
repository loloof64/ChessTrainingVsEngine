#ifndef POSITIONEDITOR_H
#define POSITIONEDITOR_H

#include <QWidget>
#include <QString>
#include <QMouseEvent>
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
        void setCurrentEditingPiece(char pieceFen);

    signals:
        void cellSelected(int file, int rank);

    private:
        int _cellsSize;
        loloof64::ThcPosition _position;

        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
    };
}
#endif // POSITIONEDITOR_H
