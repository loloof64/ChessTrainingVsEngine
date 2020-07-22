#ifndef MOVESHISTORY_H
#define MOVESHISTORY_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include "../../core/IPosition.h"
#include "../../libs/FlowLayout/flowlayout.h"

namespace loloof64 {
    class MovesHistory : public QWidget
    {
        Q_OBJECT
    public:
        explicit MovesHistory(QWidget *parent = nullptr);
        ~MovesHistory();
        void newGame(QString startPosition);
        void addHistoryItem(HistoryItem item, bool gameFinished = false);

    signals:
        void requestPositionOnBoard(HistoryItem item);

    protected:
      virtual void paintEvent(QPaintEvent* ) override;
    private:
        int _itemToHighlightIndex = -1;
        QString _startPosition = "";
        bool _blackToMoveFirst = false;
        bool _nextMoveIsForBlack = false;
        int _moveNumber = 1;
        FlowLayout * _mainLayout;
        QVector<QWidget *> _widgetsItems;
        QVector<HistoryItem> _dataItems;
        void clearMoves();
        void addMoveComponent(QPushButton *moveComponent, bool gameFinished = false);
        QLabel *buildMoveNumber();
        void updateItemHighlightingTo(int newItemToHighlightIndex);
    };
}

#endif // MOVESHISTORY_H
