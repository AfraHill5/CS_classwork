#include "Map.h"  // class template from problem 1

    class Point
    {
        public:
		
		bool operator!=(const Point& other)
		{
			return (this->x() > other.y());
		}
        Point(int x, int y) : m_x(x), m_y(y) {}
        Point() : m_x(0), m_y(0) {}
        double x() const { return m_x; }
        double y() const { return m_y; }
        private:
        double m_x;
        double m_y;
    };

int main()
{
	Map<int, double> mid;
	mid.insert(42, -1.25);         // OK
	Map<Point, int> mpi;
	mpi.insert(Point(40,10), 32);  // error!
}