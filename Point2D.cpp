#include "Point2D.h"

Point2D::Point2D()
{
	x = 0;
	y = 0;
}

Point2D::Point2D(const Point2D &other)
{
	x = other.x;
	y = other.y;
}

Point2D::Point2D(short xcoord, short ycoord)
{
	x = xcoord;
	y = ycoord;
}

Point2D::~Point2D()
{
	x = 0;
	y = 0;
}

Point2D &Point2D::operator=(const Point2D &other)
{
	x = other.x;
	y = other.y;
	return *this;
}

bool Point2D::operator==( const Point2D &other)
{
    return (this->x == other.x && this->y == other.y);
}
