#ifndef POSITIONBUILDER_H
#define POSITIONBUILDER_H

#include <QString>
#include "IPosition.h"

namespace loloof64 {
    struct BoardSquare {
        int file, rank;
        BoardSquare(int file, int rank): file(file), rank(rank) {}

        int getFile() const {return file;}
        int getRank() const {return rank;}
    };

    struct Castles {
        bool whiteOO;
        bool whiteOOO;
        bool blackOO;
        bool blackOOO;

        Castles(bool whiteOO, bool whiteOOO, bool blackOO, bool blackOOO):
            whiteOO(whiteOO), whiteOOO(whiteOOO), blackOO(blackOO), blackOOO(blackOOO) {}
        Castles():
            whiteOO(false), whiteOOO(false), blackOO(false), blackOOO(false){}
    };

    class PositionBuilder
    {
    public:
        PositionBuilder();
        void setFromFen(QString fen);
        void setTurn(bool isWhiteTurn);
        void setPieceAtSquare(char piece, BoardSquare square);
        void setWhiteOO(bool value);
        void setWhiteOOO(bool value);
        void setBlackOO(bool value);
        void setBlackOOO(bool value);
        void setEnPassantFile(int file);
        void setFiftyMovesRuleCount(int count);
        void setMoveNumber(int number);

        QString getFen() const;
        bool isWhiteTurn() const;
        char getPieceAtSquare(BoardSquare square) const;
        bool getWhiteOO() const;
        bool getWhiteOOO() const;
        bool getBlackOO() const;
        bool getBlackOOO() const;
        int getEnPassantFile() const;
        int getFiftyMovesRuleCount() const;
        int getMoveNumber() const;

    private:
        bool _whiteTurn = false;
        char _pieces[8][8];
        Castles _castles;
        int _enPassantFile = -1;
        int _fiftyMovesRuleCount = 0;
        int _moveNumber = 0;
    };
}
#endif // POSITIONBUILDER_H
