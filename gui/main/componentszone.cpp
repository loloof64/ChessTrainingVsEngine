#include "componentszone.h"
#include "../../core/adapters/thcposition.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QTimer>

loloof64::ComponentsZone::ComponentsZone(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setSpacing(20);
    _chessBoard = new ChessBoard(45, this);
    _movesHistory = new MovesHistoryFullComponent(this);
    _pgnDatabase = new PgnDatabase(false);
    _engineCommunication = nullptr;

    QFont font;
    font.setPointSize(20);

    _mainLayout->addWidget(_chessBoard);
    _mainLayout->addWidget(_movesHistory);
    setLayout(_mainLayout);
    resize(600, 540);

    connect(_chessBoard, &loloof64::ChessBoard::moveDoneAsFan,
            [this](QString moveFan, QString newPositionFen, MoveCoordinates lastMove, bool gameFinished)
    {
        _movesHistory->addHistoryItem(HistoryItem(moveFan, newPositionFen, lastMove), gameFinished);
    });
    connect(_movesHistory->getMovesHistoryMainComponent(), &loloof64::MovesHistory::requestPositionOnBoard,
            [this](HistoryItem item)
    {
       const auto validated = _chessBoard->setPosition(item);
       if (validated)
       {
           _movesHistory->commitHistoryNodeSelection();
       }
    });
    connect(_chessBoard, &loloof64::ChessBoard::externalTurn,
            [this](QString /*currentPosition*/)
    {
        makeComputerPlayNextMove();
    });
    connect(_chessBoard, &loloof64::ChessBoard::moveDoneAsSan,
            [this](QString moveSan, QString /*newPositionFen*/, MoveCoordinates moveCoordinates, bool /*gameFinished*/)
    {
        const auto stdMoveSan = moveSan.toStdString();
        char promotion = 0;
        const auto equalSignPos = stdMoveSan.find("=");
        if (equalSignPos != std::string::npos) {
            const auto promotionPart = stdMoveSan.substr(equalSignPos+1);
            promotion = promotionPart[0];
        }
        handleMoveVerification(moveCoordinates, promotion);
    });

    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestFirstPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoFirstPosition(); });
    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestLastPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoLastPosition(); });
    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestPreviousPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoPreviousPosition(); });
    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestNextPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoNextPosition(); });
}

loloof64::ComponentsZone::~ComponentsZone()
{
    if (_engineCommunication != nullptr) {
        _engineCommunication->close();
        delete _engineCommunication;
    }

    if (_pgnDatabase != nullptr)
    {
        _pgnDatabase->close();
        delete _pgnDatabase;
        _pgnDatabase = nullptr;
    }
    delete _movesHistory;
    delete _chessBoard;
    delete _mainLayout;
}

void loloof64::ComponentsZone::setEnginePath(QString enginePath)
{
    if (_engineCommunication != nullptr) {
        _engineCommunication->close();
        delete _engineCommunication;
    }

    _engineCommunication = new UCIEngineCommunication();
    _engineCommunication->setExecutablePath(enginePath);

    connect(_engineCommunication, &loloof64::UCIEngineCommunication::computedBestMove, [this](QString bestMove) {
        reactToEngineMoveIfPossible(bestMove);
    });

    connect(_engineCommunication, &UCIEngineCommunication::isNotReady, [this]() {
        emit engineNotReady();
    });

    connect(_engineCommunication, &UCIEngineCommunication::isReady, [this]() {
        emit engineReady();
    });
}

void loloof64::ComponentsZone::reverseBoard()
{
    _chessBoard->reverse();
}

void loloof64::ComponentsZone::handleMoveVerification(MoveCoordinates moveCoordinates, char promotion)
{
    const auto whiteTurnBeforeMove = ! _chessBoard->isWhiteTurn();
    const auto externalPlayerTurn = (whiteTurnBeforeMove && (_chessBoard->getWhitePlayerType() == PlayerType::EXTERNAL)) ||
            (!whiteTurnBeforeMove && (_chessBoard->getBlackPlayerType() == PlayerType::EXTERNAL));

    if (externalPlayerTurn) {
        return;
    }
    else {
        auto promotionPiece = PieceType::None;
        const auto fromSquare = SquareFromRankAndFile((unsigned char) moveCoordinates.startRank, (unsigned char) moveCoordinates.startFile);
        const auto toSquare = SquareFromRankAndFile((unsigned char) moveCoordinates.endRank, (unsigned char) moveCoordinates.endFile);
        switch (promotion) {
        case 'Q':
        case 'q':
            promotionPiece = PieceType::Queen;
            break;
        case 'R':
        case 'r':
            promotionPiece = PieceType::Rook;
            break;
        case 'B':
        case 'b':
            promotionPiece = PieceType::Bishop;
            break;
        case 'N':
        case 'n':
            promotionPiece = PieceType::Knight;
            break;
        }
    }
}

void loloof64::ComponentsZone::makeComputerPlayNextMove()
{
    if (!gameInProgress()) return;
    const auto whiteTurn = _chessBoard->isWhiteTurn();
    const auto isExternalTurn = (whiteTurn && _chessBoard->getWhitePlayerType() == PlayerType::EXTERNAL) ||
            (!whiteTurn && _chessBoard->getBlackPlayerType() == PlayerType::EXTERNAL);
    if (!isExternalTurn) return;

    QString uciPositionCommand("position fen ");
    uciPositionCommand += _chessBoard->getCurrentPosition();
    _engineCommunication->sendCommand(uciPositionCommand);

    _engineCommunication->sendCommand("go movetime 1000");
}

char loloof64::ComponentsZone::promotionPieceToPromotionFen(Piece promotion) const
{
    char promotionFen = 0;

    switch (promotion) {
    case Piece::WhiteQueen: promotionFen = 'Q'; break;
    case Piece::BlackQueen: promotionFen = 'q'; break;
    case Piece::WhiteRook: promotionFen = 'R'; break;
    case Piece::BlackRook: promotionFen = 'r'; break;
    case Piece::WhiteBishop: promotionFen = 'B'; break;
    case Piece::BlackBishop: promotionFen = 'b'; break;
    case Piece::WhiteKnight: promotionFen = 'N'; break;
    case Piece::BlackKnight: promotionFen = 'n'; break;
    default: ;
    }

    return promotionFen;
}

QString loloof64::ComponentsZone::moveToMoveFan(Move move)
{
    const auto startFile = move.from() % 8;
    const auto startRank = move.from() / 8;
    const auto endFile = move.to() % 8;
    const auto endRank = move.to() / 8;

    char nextMovePromotionFen = 0;
    if (move.isPromotion())
    {
        const auto promotion = move.promotedPiece();
        nextMovePromotionFen = promotionPieceToPromotionFen(promotion);
    }
    const auto moveFan = _chessBoard->getMoveFan(startFile, startRank, endFile, endRank, nextMovePromotionFen);
    return moveFan;
}

void loloof64::ComponentsZone::startNewGame(QString positionFen, bool playerHasWhite)
{
    _movesHistory->newGame(positionFen);
    _chessBoard->setWhitePlayerType(playerHasWhite ? loloof64::PlayerType::HUMAN : loloof64::PlayerType::EXTERNAL);
    _chessBoard->setBlackPlayerType(playerHasWhite ? loloof64::PlayerType::EXTERNAL : loloof64::PlayerType::HUMAN);

    _chessBoard->newGame(positionFen);
}

void loloof64::ComponentsZone::reactToEngineMoveIfPossible(QString bestMove)
{
    const auto ascii_lower_a = 97;
    const auto ascii_1 = 49;

    const auto startFile = bestMove[0].toLatin1() - ascii_lower_a;
    const auto startRank = bestMove[1].toLatin1() - ascii_1;
    const auto endFile = bestMove[2].toLatin1() - ascii_lower_a;
    const auto endRank = bestMove[3].toLatin1() - ascii_1;
    const auto isPromotion = bestMove.size() >= 5;

    if (isPromotion)
    {
        const auto promotion = bestMove[4].toLatin1();
        _chessBoard->playMove(startFile, startRank, endFile, endRank, promotion);
    }
    else {
        _chessBoard->playMove(startFile, startRank, endFile, endRank);
    }
}
