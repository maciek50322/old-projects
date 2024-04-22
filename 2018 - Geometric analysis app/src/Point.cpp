#include "Point.h"

const double pi=3.1415926535897932384626535897832384626433832795;

Point::Point() {
}
Point::Point(double newx, double newy) {
    x=newx;
    y=newy;
}

double Point::getDistance(Point& p) {
    return sqrt( pow(x-p.x, 2) + pow(y-p.y, 2) );
}

double Point::getAngle(Point& p1, Point& p2) {
    double cnd=getDistance(p1)*getDistance(p2);
    if ( cnd*p1.getDistance(p2)==0 ) return 0;
    return acos( ( (p1.x-x)*(p2.x-x) + (p1.y-y)*(p2.y-y) )/( cnd ) )*180/pi;
}
double Point::getArea(Point& p1, Point& p2) {
    double area=0.5*((p1.x-x)*(p2.y-y)-(p1.y-y)*(p2.x-x));
    return area<0 ? -area : area;
}

void Point::setDistance(Point& p, double dist, bool ev) {
    double cnd=getDistance(p);
    if (cnd==0) {
        if (!ev) y=p.y+dist;
        else     y=p.y-dist;
    } else {
        double k=dist/cnd;
        if (!ev) {
            x=p.x+k*(x-p.x);
            y=p.y+k*(y-p.y);
        } else {
            x=p.x-k*(x-p.x);
            y=p.y-k*(y-p.y);
        }
    }
}

void Point::setAngleC(Point& p1, Point& p2, double angl, bool ev) {
    while (angl>=180) angl-=180;
    while (angl<=-180) angl+=180;
    if (angl<0) {
        ev=!ev;
    }

    double cangl=cos(angl/180*pi);
    double a=getDistance(p1), c=p2.getDistance(p1), cnd=4*a*a*cangl*cangl-4*a*a+4*c*c;
    if (a==0 || c==0) {
        //impossible
    } else if (cnd<0) {
        //impossible , a>c
    } else if (cnd>=0) {  //change position of this
        double b, sgamma=(p2.x-p1.x)/c, cgamma=(p2.y-p1.y)/c;

        if (a>c) b=(2*a*cangl-sqrt(cnd))/2;
        else     b=(2*a*cangl+sqrt(cnd))/2;

        double cbeta=(a*a+c*c-b*b)/(2*a*c), sbeta=sqrt(1-cbeta*cbeta);

        if (!ev) {
            x=p1.x+a*(sgamma*cbeta+sbeta*cgamma);
            y=p1.y+a*(cgamma*cbeta-sgamma*sbeta);
        } else {
            x=p1.x+a*(sgamma*cbeta-sbeta*cgamma);
            y=p1.y+a*(cgamma*cbeta+sgamma*sbeta);
        }
    }
}
void Point::setAngleL(Point& p1, Point& p2, double angl) {
    bool ev=false;
    while (angl>=180) angl-=180;
    while (angl<=-180) angl+=180;

    if (angl==0) {
        setDistance(p1, 0);
    } else {

        double ptp=p1.getAngle(*this, p2);
        if (ptp>90)  {
            ptp=180-ptp;
            ev=true;
        }

        double b=p1.getDistance(p2);
        double a=b*sin( ptp/180*pi )/sin(angl/180*pi);
        double c=sqrt( pow(a, 2)+pow(b, 2)+2*a*b*cos( (ptp+angl)/180*pi ) );
        if (!ev)
            setDistance(p1, c);
        else setDistance(p1, -c);
    }
}
void Point::setAngleS(Point& p1, Point& p2, double angl) {
    while (angl>=180) angl-=180;
    while (angl<=-180) angl+=180;

    //ev done by math

    if (getDistance(p1)>0) {
        double sa=sin( angl/180*pi ), ca=cos( angl/180*pi );
        double vx=getDistance(p2)/getDistance(p1)*((p1.x-x)*ca-(p1.y-y)*sa);
        double vy=getDistance(p2)/getDistance(p1)*((p1.x-x)*sa+(p1.y-y)*ca);

        p2.x=x+vx;
        p2.y=y+vy;

    }
}

Point::~Point() {
}
