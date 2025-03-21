#ifndef TOOLS_H
#define TOOLS_H
#define _USE_MATH_DEFINES
#include <cmath>
constexpr double epsil_zero(0.5);
enum State
{
    FORWARD,
    BACKWARD
};

struct S2d {
    double x = 0.;
    double y = 0.;
};
struct Pol;
struct Cart
{
    S2d point;
    double x = point.x;
    double y = point.y;
    Pol toPol();
    double norme();
};
struct Pol
{
    S2d point; //x norme et y angle
    double norme = point.x;
    double angle = point.y;
    Cart toCart();
};


struct Cercle {
    Cart C;
    double R;
};

double angleNormalise(double angle);
double distance(Cart P1, Cart P2);
double distance(Pol P1, Pol P2);
double distance(Cart P1, Pol P2);
double distance(Pol P1, Cart P2);
bool inclusion (Cercle C1, Cart P);
bool inclusion (Cercle C1, Cercle C2);
bool intersection(Cercle C1, Cercle C2);
Pol reflect(Cart P, Pol V, State state);

#endif