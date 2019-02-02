#ifndef FIRETABLE_H
#define FIRETABLE_H

#include <QImage>

//!
//! \brief The FireTable class - this class is uses a table index of RGP colors and a image buffer to generate the Doom fire effect.
//!]
class FireTable
{
public:
    FireTable();
    ~FireTable();

public:
    QPixmap update();

private:
    //!
    //! \brief _fire_pixels - this table maps the image pixels to each rgb color
    //!
    int** _fire_pixels;

    //!
    //! \brief _buffer - the image to be painted with coordinates of rgb colors from the table above
    //!
    QImage* _buffer;

};

#endif // FIRETABLE_H
