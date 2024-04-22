#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
    public:
        double x, y;
        Point();
        Point(double newx, double newy);

        double getDistance(Point& p);
        double getAngle(Point& p1, Point& p2); // get 0<=angle<=180 [degrees] of |p1,this,p2|
        double getArea(Point& p1, Point& p2);

        void setDistance(Point& p, double dist, bool ev=false); // save direction p to this, change position of this point
        void setAngleC(Point& p1, Point& p2, double angl, bool ev=false); // save distance p1 to this, change position of this
        void setAngleL(Point& p1, Point& p2, double angl);   //save this on this-p1 line
        void setAngleS(Point& p1, Point& p2, double angl);   //save distance this to p2, change position of p2



        ~Point();

};

#endif // POINT_H
