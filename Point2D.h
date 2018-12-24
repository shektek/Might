#ifndef POINT2D_H
#define POINT2D_H

/* Really just a wrapper for two coordinates
 *
 */
class Point2D
{
	public:
		short x;
		short y;

		Point2D();
		Point2D(const Point2D &other);
		Point2D(short xcoord, short ycoord);
		~Point2D();

		Point2D &operator=(const Point2D &other);
        bool operator==(const Point2D &other);
};

#endif
