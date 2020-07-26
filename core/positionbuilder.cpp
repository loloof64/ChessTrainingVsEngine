#include "positionbuilder.h"
#include <QStringList>
#include <cctype>

loloof64::PositionBuilder::PositionBuilder()
{
    const char NO_PIECE = ' ';
    for (auto row = 0; row < 8; row++) {
        for (auto col = 0; col < 8; col++) {
            _pieces[row][col] = NO_PIECE;
        }
    }
    setFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void loloof64::PositionBuilder::setFromFen(QString fen)
{
    const char NO_PIECE = ' ';
    const int ascii_0 = 48;
    const char ascii_3 = 51;
    const char ascii_6 = 54;
    const char ascii_lower_a = 97;
    const char ascii_lower_h = 104;

    QStringList parts = fen.split(" ");
    if (parts.size() < 6) {
        throw IllegalPositionException(QString::asprintf("%s : missing data", fen.toStdString().c_str()));
    }

    QString boardPart = parts[0];
    QString turnPart = parts[1];
    QString castlesPart = parts[2];
    QString enPassantPart = parts[3];
    QString fiftyMovesPart = parts[4];
    QString moveNumberPart = parts[5];

    QStringList boardLines = boardPart.split("/");
    if (boardLines.size() != 8) {
        throw IllegalPositionException(QString::asprintf("%s : do not have 8 pieces lines", fen.toStdString().c_str()));
    }
    auto currentRank = 7;
    for (auto it = boardLines.begin(); it != boardLines.end(); ++it) {
        const auto currentLine = *it;
        auto currentFile = 0;

        for (auto it2 = currentLine.begin(); it2 != currentLine.end(); ++it2) {
            const auto currentValue = *it2;
            auto isDigit = currentValue.isDigit();
            if (isDigit) {
                auto digit = currentValue.unicode() - ascii_0;
                for (auto time = 0; time < digit; time++) {
                    _pieces[currentRank][currentFile] = NO_PIECE;
                    ++currentFile;
                }
            }
            else {
                _pieces[currentRank][currentFile] = currentValue.toLatin1();
                ++currentFile;
            }
        }

        --currentRank;
    }

    if (turnPart != "w" && turnPart != "b") {
        QString errorMsg;
        throw IllegalPositionException(errorMsg.sprintf("%s : incorrect turn field", fen.toStdString().c_str()));
    }

    _whiteTurn = turnPart == "w";

    if (castlesPart != "-") {
        if (castlesPart.contains("K")) _castles.whiteOO = true;
        if (castlesPart.contains("Q")) _castles.whiteOOO = true;
        if (castlesPart.contains("k")) _castles.blackOO = true;
        if (castlesPart.contains("q")) _castles.blackOOO = true;
    }
    else {
        _castles.whiteOO = false;
        _castles.whiteOOO = false;
        _castles.blackOO = false;
        _castles.blackOOO = false;
    }

    if (enPassantPart != "-") {
        auto filePart = enPassantPart[0];
        auto fileAscii = filePart.unicode();
        auto notAFileChar = fileAscii < ascii_lower_a || fileAscii > ascii_lower_h;
        if (notAFileChar) {
            throw IllegalPositionException(QString::asprintf("%s : en-passant square has incorrect file", fen.toStdString().c_str()));
        }

        auto rankPart = enPassantPart[1];
        auto rankAscii = rankPart.unicode();
        auto incorrectRank = ((rankAscii != ascii_3) && !_whiteTurn) && ((rankAscii != ascii_6) && _whiteTurn);
        if (incorrectRank) {
            throw IllegalPositionException(QString::asprintf("%s : en-passant square has incorrect rank", fen.toStdString().c_str()));
        }

        _enPassantFile = fileAscii - ascii_lower_a;
    }
    else {
     _enPassantFile = -1;
    }

    bool fiftyMovesNumberOk;
    int fiftyMovesNumber = fiftyMovesPart.toInt(&fiftyMovesNumberOk);
    if (! fiftyMovesNumberOk) {
        throw IllegalPositionException(QString::asprintf("%s : fifty moves rule counter field is not a number", fen.toStdString().c_str()));
    }
    _fiftyMovesRuleCount = fiftyMovesNumber;

    bool moveNumberOk;
    int moveNumber = moveNumberPart.toInt(&moveNumberOk);
    if (! moveNumberOk) {
        throw IllegalPositionException(QString::asprintf("%s : move number field is not a number", fen.toStdString().c_str()));
    }
    _moveNumber = moveNumber;
}

QString loloof64::PositionBuilder::getFen() const
{
    QString result;
    const char NO_PIECE = ' ';
    const char ascii_lower_a = 97;

    for (auto rank = 7; rank >= 0; --rank) {
        auto holes = 0;
        for (auto file = 0; file < 8; ++file) {
            auto current = getPieceAtSquare(BoardSquare(file, rank));
            auto isEmpty = current == NO_PIECE;
            if (isEmpty) {
                ++holes;
            }
            else {
                if (holes > 0) {
                    result += QString::number(holes);
                }
                holes = 0;
                result += current;
            }
        }
        if (holes > 0) result += QString::number(holes);
        if (rank > 0) result += "/";
    }

    if (_whiteTurn) result += " w ";
    else result += " b ";

    if (_castles.whiteOO || _castles.whiteOOO || _castles.blackOO || _castles.blackOOO) {
        QString castlesStr;

        if (_castles.whiteOO) castlesStr += "K";
        if (_castles.whiteOOO) castlesStr += "Q";
        if (_castles.blackOO) castlesStr += "k";
        if (_castles.blackOOO) castlesStr += "q";

        result += castlesStr;
        result += " ";
    }
    else {
        result += "- ";
    }

    if (_enPassantFile >= 0) {
        QString enPassantStr;
        enPassantStr += static_cast<char>(ascii_lower_a + _enPassantFile);
        enPassantStr += _whiteTurn ? "6 " : "3 ";
        result += enPassantStr;
    }
    else {
        result += "- ";
    }

    result += QString::number(_fiftyMovesRuleCount);
    result += " ";
    result += QString::number(_moveNumber);

    return result;
}

void loloof64::PositionBuilder::setTurn(bool isWhiteTurn)
{
    _whiteTurn = isWhiteTurn;
}

bool loloof64::PositionBuilder::isWhiteTurn() const
{
    return _whiteTurn;
}


void loloof64::PositionBuilder::setPieceAtSquare(char piece, BoardSquare square)
{
    _pieces[square.getRank()][square.getFile()] = piece;
}

char loloof64::PositionBuilder::getPieceAtSquare(BoardSquare square) const
{
    return _pieces[square.getRank()][square.getFile()];
}

void loloof64::PositionBuilder::setWhiteOO(bool value) {
    _castles.whiteOO = value;
}

bool loloof64::PositionBuilder::getWhiteOO() const {
    return _castles.whiteOO;
}

void loloof64::PositionBuilder::setWhiteOOO(bool value) {
    _castles.whiteOOO = value;
}

bool loloof64::PositionBuilder::getWhiteOOO() const {
    return _castles.whiteOOO;
}

void loloof64::PositionBuilder::setBlackOO(bool value) {
    _castles.blackOO = value;
}

bool loloof64::PositionBuilder::getBlackOO() const {
    return _castles.blackOO;
}

void loloof64::PositionBuilder::setBlackOOO(bool value) {
    _castles.blackOOO = value;
}

bool loloof64::PositionBuilder::getBlackOOO() const {
    return _castles.blackOOO;
}


void loloof64::PositionBuilder::setEnPassantFile(int file) {
    _enPassantFile = file;
}

int loloof64::PositionBuilder::getEnPassantFile() const {
    return _enPassantFile;
}

void loloof64::PositionBuilder::setFiftyMovesRuleCount(int count) {
    _fiftyMovesRuleCount = count;
}

int loloof64::PositionBuilder::getFiftyMovesRuleCount() const {
    return _fiftyMovesRuleCount;
}

void loloof64::PositionBuilder::setMoveNumber(int number) {
    _moveNumber = number;
}

int loloof64::PositionBuilder::getMoveNumber() const {
    return _moveNumber;
}
