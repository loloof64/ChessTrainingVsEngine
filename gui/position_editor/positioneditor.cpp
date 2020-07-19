#include "positioneditor.h"
#include "../../core/adapters/thcposition.h"
#include "../../core/IPosition.h"
#include <cmath>
#include <QPainter>
#include <QSvgRenderer>

loloof64::PositionEditor::PositionEditor(int cellsSize, QWidget *parent) : QWidget(parent), _cellsSize(cellsSize)
{
    _relatedPosition = new ThcPosition();
    setMinimumSize(9*cellsSize, 9*cellsSize);
    setMaximumSize(9*cellsSize, 9*cellsSize);
}

void loloof64::PositionEditor::paintEvent(QPaintEvent * /*event*/)
{
    const auto wholeSize = 9 * _cellsSize;
    const auto colsIndexes = QVector<int>{0,1,2,3,4,5,6,7};
    const auto rowsIndexes = QVector<int>{0,1,2,3,4,5,6,7};

    const auto backgroundColor = QColor(108, 93, 167);
    const auto whiteCellsColor = QColor(255, 206, 158);
    const auto blackCellsColor = QColor(209, 139, 71);

    QPainter painter(this);

    // painting background
    painter.fillRect(0, 0, wholeSize, wholeSize, backgroundColor);

    // painting cells
    for (auto row: rowsIndexes)
    {
        for (auto col: colsIndexes)
        {
            const auto file = col;
            const auto rank = 7-row;

            // draw cell
            const auto isWhiteCell = (row+col) %2 == 0;
            const auto x = int(floor(_cellsSize * (0.5 + col)));
            const auto y = int(floor(_cellsSize * (0.5 + row)));
            auto cellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

            painter.fillRect(x, y, _cellsSize, _cellsSize, cellColor);

            // draw piece
            const auto pieceValue = _relatedPosition->getPieceFenAt(file, rank);

            const auto notAnEmptyPiece = QVector<char>{
                'P', 'N', 'B', 'R', 'Q', 'K',
                'p', 'n', 'b', 'r', 'q', 'k'
            }.contains(pieceValue);

            if (notAnEmptyPiece)
            {
                auto resourceName = QString(":/chess_vectors/");
                resourceName += IPosition::pieceFenToPieceImageReference(pieceValue);
                QSvgRenderer pieceImage{resourceName};

                pieceImage.render(&painter, QRect(x, y, _cellsSize, _cellsSize));
            }

        }
    }

    // painting coordinates
    const auto fontSize = _cellsSize * 0.3;
    const auto coordinatesColor = QColor(255, 199, 0);
    auto font = QFont();
    font.setPointSizeF(fontSize);
    font.setWeight(QFont::Bold);
    painter.setFont(font);
    painter.setPen(QPen(coordinatesColor));

    const auto ascii_a = 65;
    const auto ascii_1 = 49;

    for (auto col: colsIndexes)
    {
        const auto file = col;
        const auto letter = static_cast<char>(ascii_a + file);

        const auto x = int(floor(_cellsSize * (0.85 + col)));
        const auto y1 = int(floor(_cellsSize * 0.4));
        const auto y2 = int(floor(_cellsSize * 8.9));

        painter.drawText(x, y1, QString(letter));
        painter.drawText(x, y2, QString(letter));
    }

    for (auto row: rowsIndexes)
    {
        const auto rank = 7-row;
        const auto digit = static_cast<char>(ascii_1 + rank);

        const auto x1 = int(floor(_cellsSize * 0.12));
        const auto x2 = int(floor(_cellsSize * 8.62));
        const auto y = int(floor(_cellsSize * (1.2 + row)));

        painter.drawText(x1, y, QString(digit));
        painter.drawText(x2, y, QString(digit));
    }
}

loloof64::PositionEditor::~PositionEditor()
{
    delete _relatedPosition;
}
