#include "gameselectiondialog.h"

loloof64::GameSelectionDialog::GameSelectionDialog(QWidget *parent) : QDialog(parent)
{
    _layout = new QVBoxLayout();
    _layout->setSpacing(20);

    _gameIndexLabel = new QLabel();
    _playersLabel = new QLabel();
    _eventLabel = new QLabel();

    _mainZone = new GameSelectionMainZone(this);

    _validateButton = new QPushButton(tr("Validate"), this);

    _layout->addWidget(_gameIndexLabel);
    _layout->addWidget(_mainZone);
    _layout->addWidget(_playersLabel);
    _layout->addWidget(_eventLabel);
    _layout->addWidget(_validateButton);

    _layout->setAlignment(_gameIndexLabel, Qt::AlignHCenter);
    _layout->setAlignment(_mainZone, Qt::AlignHCenter);
    _layout->setAlignment(_playersLabel, Qt::AlignHCenter);
    _layout->setAlignment(_eventLabel, Qt::AlignHCenter);
    _layout->setAlignment(_validateButton, Qt::AlignHCenter);

    setLayout(_layout);

    connect(_mainZone, &GameSelectionMainZone::gameIndexChanged, this, [this](quint64 selectedIndex)
    {
        _gameIndexLabel->setText(QString("%1 / %2").arg(selectedIndex + 1).arg(_gamesCount));
    });

    connect(_mainZone, &GameSelectionMainZone::whitePlayerChanged, this, [this](QString name)
    {
        _whitePlayerName = name;
        auto whiteName = _whitePlayerName;
        if (whiteName.isEmpty()) whiteName = QString(tr("Unknown"));

        auto blackName = _blackPlayerName;
        if (blackName.isEmpty()) blackName = QString(tr("Unknown"));

        _playersLabel->setText(QString("%1 / %2").arg(whiteName).arg(blackName));
    });

    connect(_mainZone, &GameSelectionMainZone::blackPlayerChanged, this, [this](QString name)
    {
        _blackPlayerName = name;
        auto whiteName = _whitePlayerName;
        if (whiteName.isEmpty()) whiteName = QString(tr("Unknown"));

        auto blackName = _blackPlayerName;
        if (blackName.isEmpty()) blackName = QString(tr("Unknown"));

        _playersLabel->setText(QString("%1 / %2").arg(whiteName).arg(blackName));
    });

    connect(_mainZone, &GameSelectionMainZone::gameDateChanged, this, [this](QString date)
    {
        _eventDate = date;
        auto newDate = date;
        if (newDate.isEmpty()) newDate = QString(tr("Unknown"));

        auto newEventName = _eventName;
        if (newEventName.isEmpty()) newEventName = QString(tr("Unknown"));

        auto newSite = _eventSite;
        if (newSite.isEmpty()) newSite = QString(tr("Unknown"));

        _eventLabel->setText(QString("%1 - %2 (%3)").arg(newEventName).arg(newSite).arg(newDate));
    });

    connect(_mainZone, &GameSelectionMainZone::gameEventChanged, this, [this](QString event)
    {
        _eventName = event;
        auto newDate = _eventDate;
        if (newDate.isEmpty()) newDate = QString(tr("Unknown"));

        auto newEventName = _eventName;
        if (newEventName.isEmpty()) newEventName = QString(tr("Unknown"));

        auto newSite = _eventSite;
        if (newSite.isEmpty()) newSite = QString(tr("Unknown"));

        _eventLabel->setText(QString("%1 - %2 (%3)").arg(newEventName).arg(newSite).arg(newDate));
    });

    connect(_mainZone, &GameSelectionMainZone::gameSiteChanged, this, [this](QString site)
    {
        _eventSite = site;
        auto newDate = _eventDate;
        if (newDate.isEmpty()) newDate = QString(tr("Unknown"));

        auto newEventName = _eventName;
        if (newEventName.isEmpty()) newEventName = QString(tr("Unknown"));

        auto newSite = _eventSite;
        if (newSite.isEmpty()) newSite = QString(tr("Unknown"));

        _eventLabel->setText(QString("%1 - %2 (%3)").arg(newEventName).arg(newSite).arg(newDate));
    });

    connect(_validateButton, &QPushButton::clicked, this, [this]()
    {
        accept();
    });

    setModal(true);
}

loloof64::GameSelectionDialog::~GameSelectionDialog()
{
    delete _validateButton;

    delete _mainZone;

    delete _eventLabel;
    delete _playersLabel;
    delete _gameIndexLabel;
    delete _layout;
}

void loloof64::GameSelectionDialog::setPgnDatabase(PgnDatabase *database)
{
    _mainZone->setPgnDatabase(database);
    _gamesCount = static_cast<int>(database->count());

    _gameIndexLabel->setText(QString("%1 / %2").arg(1).arg(_gamesCount));
}

quint64 loloof64::GameSelectionDialog::getSelectedGameIndex() const
{
    return _mainZone->getSelectedGameIndex();
}
