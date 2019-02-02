#ifndef DOOMFIRE_H
#define DOOMFIRE_H

#include <QWidget>
#include <QTimer>


static const int FIRE_WIDTH =  320;
static const int FIRE_HEIGHT = 168;
static const int MS_UPDATE = 32;

// a array of Red Green Blue values , from black -> white, passing throug red yellow organge, mimics the
// heat being produced (fire source as white) to the complete cooldown (black)
static const QRgb FIRE_PALETTE[] = {
    qRgb(0x07,0x07,0x07),qRgb(0x1F,0x07,0x07),qRgb(0x2F,0x0F,0x07),qRgb(0x47,0x0F,0x07),qRgb(0x57,0x17,0x07),
    qRgb(0x67,0x1F,0x07),qRgb(0x77,0x1F,0x07),qRgb(0x8F,0x27,0x07),qRgb(0x9F,0x2F,0x07),qRgb(0xAF,0x3F,0x07),
    qRgb(0xBF,0x47,0x07),qRgb(0xC7,0x47,0x07),qRgb(0xDF,0x4F,0x07),qRgb(0xDF,0x57,0x07),qRgb(0xDF,0x57,0x07),
    qRgb(0xD7,0x5F,0x07),qRgb(0xD7,0x5F,0x07),qRgb(0xD7,0x67,0x0F),qRgb(0xCF,0x6F,0x0F),qRgb(0xCF,0x77,0x0F),
    qRgb(0xCF,0x7F,0x0F),qRgb(0xCF,0x87,0x17),qRgb(0xC7,0x87,0x17),qRgb(0xC7,0x8F,0x17),qRgb(0xC7,0x97,0x1F),
    qRgb(0xBF,0x9F,0x1F),qRgb(0xBF,0x9F,0x1F),qRgb(0xBF,0xA7,0x27),qRgb(0xBF,0xA7,0x27),qRgb(0xBF,0xAF,0x2F),
    qRgb(0xB7,0xAF,0x2F),qRgb(0xB7,0xB7,0x2F),qRgb(0xB7,0xB7,0x37),qRgb(0xCF,0xCF,0x6F),qRgb(0xDF,0xDF,0x9F),
    qRgb(0xEF,0xEF,0xC7),qRgb(0xFF,0xFF,0xFF)
};

namespace Ui {
class DoomFire;
}

class FireTable;
class FireArray;

//!
//! \brief The DoomFire class - the idea of this tests came from here: http://fabiensanglard.net/doom_fire_psx/
//!
//! I implemented Fabien's version of the code and tryied (or still trying to) implement my own, with a index structure as a table
//! so the application displays the two versions side by side to compare results
//!
class DoomFire : public QWidget
{
    Q_OBJECT

public:
    explicit DoomFire(QWidget *parent = nullptr);
    ~DoomFire();

private slots:
    void update();

private:
    Ui::DoomFire *ui;

    //!
    //! \brief _timer - the event timer to control animation loop
    //!
    QTimer* _timer;

    //!
    //! \brief _table - a structure that represents the index as a table and maps to the actual image (based on a color index table)
    //!
    FireTable* _table;

    //!
    //! \brief _array - the data structure used as index , from the original algorithm
    //!
    FireArray* _array;

};

#endif // DOOMFIRE_H
