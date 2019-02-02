#ifndef FIREARRAY_H
#define FIREARRAY_H

#include <QImage>

//!
//! \brief The FireArray class - this class is based on the original algorithm to generate the Doom fire effect.
//!
class FireArray
{
public:
    FireArray();
    ~FireArray();

public:
    QPixmap update();

private:
    void doFire();
    void spreadFire(int src);

private:
    //!
    //! \brief _fire_pixels - this array indexes the image pixels to each rgb color
    //!
    int* _fire_pixels;

    //!
    //! \brief _buffer - the image to be painted with coordinates of rgb colors from the fire pixels
    //!
    QImage* _buffer;

};
#endif // FIREARRAY_H
