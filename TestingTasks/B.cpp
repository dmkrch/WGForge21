#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
    double x;
    double y;
    double z;
};

struct Flatness {
    double A;
    double B;
    double C;
    double D;  
};

const double MY_PI = acos(-1.0);

void MakeFlatnessWithThreePoints(const Point& p1, const Point& p2, const Point& p3, Flatness& f) {
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double z1 = p1.z;
    double z2 = p2.z;
    double z3 = p3.z;

    f.A = y1 *(z2 - z3) + y2 *(z3 - z1) + y3* (z1 - z2);
    f.B = z1 *(x2 - x3) + z2 *(x3 - x1) + z3 *(x1 - x2); 
    f.C = x1 *(y2 - y3) + x2 *(y3 - y1) + x3 *(y1 - y2);
    f.D = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
}

void PrintFlatness(Flatness& f) {
    std::cout << f.A << "x + " << f.B << "y + " << f.C << "z + " << f.D << std::endl;
}

double GetAngleBetweenFlatnesses(Flatness& f1, Flatness& f2) {
    double cosA;
    cosA = fabs(f1.A*f2.A + f1.B*f2.B + f1.C*f2.C) /
        (sqrt(f1.A*f1.A + f1.B*f1.B + f1.C*f1.C) * sqrt(f2.A*f2.A + f2.B*f2.B + f2.C*f2.C));
    
    return acos(cosA);
}

int GetPointArea(Point& p) {
    if (p.x>=0 && p.y<=0)
        return 1;
    else if (p.x<0 && p.y<0)
        return 2;
    else if (p.x<=0 && p.y>=0)
        return 3;
    else if (p.x>0 && p.y>0)
        return 4;
}

double GetFixForAngleBetweenFlatnesses(Point& p) {
    int area = GetPointArea(p);

    switch(area) {
    case 1:
        return 0.0;
    case 2:
        return MY_PI / 2.0;
    case 3:
        return MY_PI;  
    case 4:
        return 3.0*MY_PI/2.0;
    }
}


int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(8);


    double r = 0;
    double h = 0;
    std::cin >> r >> h;

    // r - radius of cone
    // h - height of cone

    // 2 points that we input
    Point p1;
    Point p2;

    std::cin >> p1.x >> p1.y >> p1.z;
    std::cin >> p2.x >> p2.y >> p2.z;

    // creating 0,0,0, and 0,0,h points
    Point p0 = {0.0, 0.0, 0.0};
    Point ph = {0.0, 0.0, static_cast<double>(h)};

    if (p1.z==0 && p2.z==0) {
        double answer = sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) + (p2.z-p1.z)*(p2.z-p1.z));
        std::cout << answer;
    }
    else {
        // creating 2 flatnesses flatness{x,y,z 0,0,0, 0,0,h}

        Flatness f1;
        MakeFlatnessWithThreePoints(p1, p0, ph, f1);

        Flatness f2;
        MakeFlatnessWithThreePoints(p2, p0, ph, f2);

        // creating flatness y=0
        Flatness fy0;
        MakeFlatnessWithThreePoints(Point{1, 0, 0}, Point{0, 0, 0}, Point{0, 0, 1}, fy0);

        // getting angle between f1, fy0
        // getting angle between f2, fy0
        double a1 = GetAngleBetweenFlatnesses(f1, fy0) + GetFixForAngleBetweenFlatnesses(p1);
        double a2 = GetAngleBetweenFlatnesses(f2, fy0) + GetFixForAngleBetweenFlatnesses(p2);

        std::cout << a1 * 180 / MY_PI << std::endl;
        std::cout << a2 * 180 / MY_PI << std::endl;

        return 0;

        double da = fabs(a2-a1);
        if (da > MY_PI)
            da = 2.0 * MY_PI - da;

        double l = sqrt(r*r+h*h);
        double fi = da * r / l;

        double dist1 = l * (1 - p1.z/h);
        double dist2 = l * (1 - p2.z/h);

        double answer = sqrt(dist1*dist1 + dist2*dist2 - 2.0*dist1*dist2*cos(fi));
        std::cout << answer;
    }

    return 0;
}