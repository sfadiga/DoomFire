
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
}


QPixmap FireTable::update()
{
    for(int x = 0 ; x < FIRE_WIDTH; x++)
    {
        for (int y = (FIRE_HEIGHT - 2); y > 0; y--) // skip the first line (always white)
        {
            //int rand_index = (qrand() * 3) & 3;
            int rand_index = QRandomGenerator::global()->bounded(3);
            int dst = x - rand_index + 1;
            if(dst < 1)
                dst = 1;

            int index = _fire_pixels[FIRE_WIDTH - dst][y+1] - (rand_index & 1);
            if(index < 0)
                index = 0;

            _fire_pixels[x][y] = index;
            _buffer->setPixel(x, y, static_cast<uint>(index));
        }
    }
    return QPixmap::fromImage(*_buffer);
}
