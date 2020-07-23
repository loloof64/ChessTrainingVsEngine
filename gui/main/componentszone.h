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
#include "gametimer.h"

namespace loloof64 {
    class ComponentsZone : public QWidget
    {
        Q_OBJECT
    public:
        explicit ComponentsZone(QWidget *parent = nullptr);
        ~ComponentsZone();
        inline bool gameInProgress(){ return _chessBoard->gameInProgress(); }
        void setEnginePath(QString enginePath);
        void startNewGame(QString positionFen, bool playerHasWhite);
        void startNewTimedGame(QString positionFen, bool playerHasWhite, int whiteTimeMs, int blackTimeMs);

    public slots:
        void reverseBoard();

    signals:
        void engineReady();
        void engineNotReady();

    private:
        QList<QString> _expectedMovesFanList;
        QVBoxLayout * _boardAndTimerLayout;
        QHBoxLayout * _timerLayout;
        QHBoxLayout * _chessBoardLayout;
        QHBoxLayout *_mainLayout;
        GameTimer * _gameTimer;
        ChessBoard *_chessBoard;
        MovesHistoryFullComponent *_movesHistory;
        PgnDatabase *_pgnDatabase;
        UCIEngineCommunication * _engineCommunication;
        Game _currentGame;
        bool _isWhitePly;

        void makeComputerPlayNextMove();
        char promotionPieceToPromotionFen(Piece promotion) const;
        QString moveToMoveFan(Move moveId);
        void reactToEngineMoveIfPossible(QString bestMove);
    };
}

#endif // COMPONENTSZONE_H
