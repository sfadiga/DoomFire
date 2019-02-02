#include "doomfire.h"
#include "ui_doomfire.h"

#include <QDebug>
#include <QPixmap>

#include "firetable.h"
#include "firearray.h"

DoomFire::DoomFire(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoomFire)
{
    ui->setupUi(this);
    this->setMinimumSize(FIRE_WIDTH + 5, FIRE_HEIGHT + 5);

    _table = new FireTable();
    _array = new FireArray();
    _timer = new QTimer();

    connect(_timer, &QTimer::timeout, this, &DoomFire::update);
    _timer->start(MS_UPDATE);
}

void DoomFire::update()
{
    ui->image_place_holder_1->setPixmap(_table->update());
    ui->image_place_holder_2->setPixmap(_array->update());
}

DoomFire::~DoomFire()
{
    delete ui;
    delete _table;
    delete _array;
}
