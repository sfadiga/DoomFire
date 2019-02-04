#include "firearray.h"
#include "doomfire.h"

#include <QPixmap>
#include <QRandomGenerator>


FireArray::FireArray()
{
    _buffer = new QImage(FIRE_WIDTH, FIRE_HEIGHT, QImage::Format_Indexed8);

    _fire_pixels = new int[FIRE_WIDTH * FIRE_HEIGHT]();

    // from original algorithm:
    // lower-left is at array index zero and upper right is at index FIRE_HEIGHT * FIRE_WIDTH - 1.
    // but in Qt case the upper-left is at index zero (due to Qt coordinate system) and upper right os at index FIRE_WIDHT - 1.

    // Set whole screen to 0 (color: 0x07,0x07,0x07)
    for(int i = 0; i < FIRE_WIDTH * FIRE_HEIGHT; i++)
    {
        _fire_pixels[i] = 0;
    }

    for(int i = 0; i < FIRE_WIDTH; i++)
    {
        _fire_pixels[(FIRE_HEIGHT - 1) * FIRE_WIDTH + i] = 36;
    }

    // populate the image color table
    for(int i = 0; i < 38; i++)
    {
        _buffer->setColor(i, FIRE_PALETTE[i]);
    }

}

FireArray::~FireArray()
{
    delete _fire_pixels;
    delete _buffer;
}

void FireArray::spreadFire(int src)
{
    int pixel = _fire_pixels[src];
    if(pixel == 0)
    {
        _fire_pixels[src - FIRE_WIDTH] = 0;
    }
    else
    {
        //int rnd_index = (qrand() * 3) & 3; //using Qt modern random generator instead of qrand
        int rnd_index = QRandomGenerator::global()->bounded(4);
        int dst = src - rnd_index + 1;
        _fire_pixels[dst - FIRE_WIDTH ] = pixel - (rnd_index & 1);
    }
}

void FireArray::doFire()
{
    for(int x = 0 ; x < FIRE_WIDTH ; x++)
    {
        for (int y = 1 ; y < FIRE_HEIGHT ; y++)
        {
            spreadFire(y * FIRE_WIDTH + x);
        }
    }
}

QPixmap FireArray::update()
{
    doFire();
    for(int h = 0 ; h < FIRE_HEIGHT ; h++)
    {
        for(int w = 0 ; w < FIRE_WIDTH ; w++)
        {
            int i = _fire_pixels[h * FIRE_WIDTH + w];
            _buffer->setPixel(w, h, i);
        }
    }
    return QPixmap::fromImage(*_buffer);
}
