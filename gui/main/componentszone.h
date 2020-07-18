#ifndef COMPONENTSZONE_H
#define COMPONENTSZONE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QFrame>
#include <QScrollArea>
#include <QListWidget>
#include <QPushButton>
#include <QList>
#include "../chessboard/chessboard.h"
#include "../history/moveshistoryfullcomponent.h"
#include "../../libs/chessx-pgn/database/pgndatabase.h"
#include "core/ucienginecommunication.h"

namespace loloof64 {
    class ComponentsZone : public QWidget
    {
        Q_OBJECT
    public:
        explicit ComponentsZone(QWidget *parent = nullptr);
        ~ComponentsZone();
        inline bool gameInProgress(){ return _chessBoard->gameInProgress(); }
        void setEnginePath(QString enginePath);

    public slots:
        void reverseBoard();

    private:
        QList<QString> _expectedMovesFanList;
        QHBoxLayout *_mainLayout;
        ChessBoard *_chessBoard;
        MovesHistoryFullComponent *_movesHistory;
        PgnDatabase *_pgnDatabase;
        UCIEngineCommunication * _engineCommunication;
        Game _currentGame;
        bool _isWhitePly;

        void handleMoveVerification(MoveCoordinates moveCoordinates, char promotion = 0);
        void makeComputerPlayNextMove();
        char promotionPieceToPromotionFen(Piece promotion) const;
        QString moveToMoveFan(Move moveId);
    };
}

#endif // COMPONENTSZONE_H
