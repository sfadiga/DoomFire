
#include "firetable.h"
#include "doomfire.h"

#include <QPixmap>
#include <QRandomGenerator>

FireTable::FireTable()
{
    _buffer = new QImage(FIRE_WIDTH, FIRE_HEIGHT, QImage::Format_Indexed8);

    _fire_pixels = new int*[FIRE_WIDTH]();

    for(int i = 0; i < FIRE_WIDTH ; i++)
    {
        _fire_pixels[i] = new int[FIRE_HEIGHT]();
        for(int j = 0; j < FIRE_HEIGHT; j++)
        {
            if (j == FIRE_HEIGHT - 1)
                _fire_pixels[i][j] = 36;
            else
                _fire_pixels[i][j] = 0;
        }
    }

   // populate the image color table
   for(int i = 0; i < 38; i++)
   {
       _buffer->setColor(i, FIRE_PALETTE[i]);
   }
}

FireTable::~FireTable()
{
    for(int i = 0; i < FIRE_WIDTH; i++)
    {
        delete _fire_pixels[i];
    }
    delete _fire_pixels;
    delete _buffer;
}

void FireTable::doFire()
{
    for(int x = 0 ; x < FIRE_WIDTH ; x++)
    {
        for (int y = 1 ; y < FIRE_HEIGHT ; y++)
        {
            spreadFire(x, y);
        }
    }
}

void FireTable::spreadFire(int x, int y)
{
    // create the random index and use it to spread in x direction
    int rnd_index = QRandomGenerator::global()->bounded(4);
    int nx = x - rnd_index + 1;
    if (nx < 0 || nx > FIRE_WIDTH - 1) // safe guards for the x position
        nx = x;

    int pixel = _fire_pixels[x][y]; // use the current value to propagate further
    if(pixel == 0)
    {
        _fire_pixels[x][y-1] = 0;
    }
    else
    {   // uses the random index to go to a cooler position in the palette
        _fire_pixels[nx][y-1] = pixel - (rnd_index & 1);
    }
}

QPixmap FireTable::update()
{
    doFire();
    for(int h = 0 ; h < FIRE_HEIGHT ; h++)
    {
        for(int w = 0 ; w < FIRE_WIDTH ; w++)
        {
            int i = _fire_pixels[w][h];
            _buffer->setPixel(w, h, i);
        }
    }
    return QPixmap::fromImage(*_buffer);
}
