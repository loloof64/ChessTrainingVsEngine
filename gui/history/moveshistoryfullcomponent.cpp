#include "moveshistoryfullcomponent.h"

loloof64::MovesHistoryFullComponent::MovesHistoryFullComponent(QWidget *parent): QWidget(parent)
{
    _mainLayout = new QVBoxLayout(this);
    _buttonsZone = new MovesHistoryButtons(this);
    _mainZoneScrollArea = new QScrollArea(this);
    _historyZone = new MovesHistory();

    setLayout(_mainLayout);
    _mainLayout->addWidget(_buttonsZone);
    _mainLayout->addWidget(_mainZoneScrollArea);

    _mainZoneScrollArea->setWidget(_historyZone);
    _mainZoneScrollArea->setWidgetResizable( true );
}

loloof64::MovesHistoryFullComponent::~MovesHistoryFullComponent()
{
    delete _historyZone;
    delete _mainZoneScrollArea;
    delete _buttonsZone;
    delete _mainLayout;
}

void loloof64::MovesHistoryFullComponent::newGame(QString startPosition)
{
    _historyZone->newGame(startPosition);
}

void loloof64::MovesHistoryFullComponent::addHistoryItem(HistoryItem item, bool gameFinished)
{
    _historyZone->addHistoryItem(item, gameFinished);
}

loloof64::MovesHistory* loloof64::MovesHistoryFullComponent::getMovesHistoryMainComponent() const
{
    return _historyZone;
}

loloof64::MovesHistoryButtons* loloof64::MovesHistoryFullComponent::getButtonsZone() const
{
    return _buttonsZone;
}

void loloof64::MovesHistoryFullComponent::commitHistoryNodeSelection()
{
    _historyZone->commitHistoryNodeSelection();
}
