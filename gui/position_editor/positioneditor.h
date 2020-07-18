#ifndef POSITIONEDITOR_H
#define POSITIONEDITOR_H

#include <QWidget>
#include "../../core/IPosition.h"

namespace loloof64 {
    class PositionEditor : public QWidget
    {
        Q_OBJECT
    public:
        explicit PositionEditor(int cellsSize, QWidget *parent = nullptr);
        virtual ~PositionEditor() override;

    signals:

    public slots:

    private:
        int _cellsSize;
        IPosition *_relatedPosition;

        void paintEvent(QPaintEvent *event) override;
    };
}
#endif // POSITIONEDITOR_H
