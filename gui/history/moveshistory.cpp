#include "moveshistory.h"
#include <QLabel>
#include <QHeaderView>
#include <QFont>
#include <QPushButton>
#include <string>
#include <QPainter>

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new FlowLayout(this, 10, 10, 10);
    setLayout(_mainLayout);

    setStyleSheet("background-color: white");
    setMinimumSize(360, 400);
}

loloof64::MovesHistory::~MovesHistory()
{
    clearMoves();
    delete _mainLayout;
}

void loloof64::MovesHistory::newGame(QString startPosition)
{
    _itemToHighlightIndex = -1;
    _startPosition = startPosition;
    clearMoves();

    const auto parts = startPosition.split(" ");
    auto moveNumberPart = parts[5];
    _blackToMoveFirst = parts[1] == "b";
    _nextMoveIsForBlack = _blackToMoveFirst;

    _moveNumber = std::stoi(moveNumberPart.toStdString());
    auto moveNumberComponent = buildMoveNumber();
    _mainLayout->addWidget(moveNumberComponent);
    _widgetsItems.push_back(moveNumberComponent);

    updateItemHighlightingTo(0);
}

void loloof64::MovesHistory::addHistoryItem(HistoryItem item, bool gameFinished)
{
    auto moveButton = new QPushButton(item.moveFan, this);
    //moveButton->setFlat(true);
    moveButton->setStyleSheet("margin: 0px 5px; font-size: 22px;");
    moveButton->setFont(QFont("Free Serif"));

    connect(moveButton, &QPushButton::clicked, [this, item](){
        emit requestPositionOnBoard(item);
    });

    _dataItems.push_back(item);
    addMoveComponent(moveButton, gameFinished);
}

void loloof64::MovesHistory::clearMoves()
{

    for (auto it = _widgetsItems.rbegin(); it != _widgetsItems.rend(); ++it )
    {
        if (*it != nullptr)
        {
            delete *it;
            *it = nullptr;
        }
    }
    _widgetsItems.clear();
    _dataItems.clear();
}

void loloof64::MovesHistory::addMoveComponent(QPushButton *moveComponent, bool gameFinished)
{
   auto needToAddMoveNumber =  (_blackToMoveFirst && ! _nextMoveIsForBlack && _mainLayout->count() > 1)
            || (! _blackToMoveFirst && _nextMoveIsForBlack && _mainLayout->count() > 1);
   _mainLayout->addWidget(moveComponent);
   _widgetsItems.push_back(moveComponent);
   updateItemHighlightingTo(_widgetsItems.size() - 1);

   if (needToAddMoveNumber && !gameFinished)
   {
       _moveNumber++;

       auto *numberComponent = buildMoveNumber();
       _mainLayout->addWidget(numberComponent);
       _widgetsItems.push_back(numberComponent);
   }

   _nextMoveIsForBlack = ! _nextMoveIsForBlack;
}

QLabel* loloof64::MovesHistory::buildMoveNumber()
{
    auto numberText = QString(std::to_string(_moveNumber).c_str());
    numberText += ".";
    auto isFirstMoveAndForBlack = _blackToMoveFirst && _mainLayout->count() == 0;
    if (isFirstMoveAndForBlack) numberText += "..";

    auto *numberComponent = new QLabel{numberText, this};
    auto font = QFont();
    font.setPixelSize(22);
    font.setFamily("Free Serif");
    numberComponent->setFont(font);

    return numberComponent;
}

void loloof64::MovesHistory::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void loloof64::MovesHistory::updateItemHighlightingTo(int newItemToHighlightIndex)
{
    // Clearing current highlighting if necessary
    if (_itemToHighlightIndex >= 0)
    {
        auto wigdetToUpdate = _widgetsItems[_itemToHighlightIndex];
        wigdetToUpdate->setStyleSheet("QPushButton { background-color: transparent; margin: 0px 5px; font-size: 22px; }");
    }

    _itemToHighlightIndex = newItemToHighlightIndex;

    // Setting current highlighting if possible
    if (_itemToHighlightIndex >= 0)
    {
        auto wigdetToUpdate = _widgetsItems[_itemToHighlightIndex];
        wigdetToUpdate->setStyleSheet("QPushButton { background-color: #70d123; margin: 0px 5px; font-size: 22px; }");
    }
}
