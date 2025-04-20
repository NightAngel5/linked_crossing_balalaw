// tools.cc, Mohamed Yassine Toujani et Adam Belghith, V3
#include "tools.h"

using namespace std;

Cart::Cart(double x, double y)
{
    point.x = x;
    point.y = y;
}

Pol Cart::toPol() const
{
    Pol M(norme(), atan2(point.y, point.x));
    return M;
}

// Converts Cartesian coordinates to polar coordinates.
double Cart::norme() const
{
    return sqrt((point.x) * (point.x) + (point.y) * (point.y));
}

Pol::Pol(double norme, double angle)
{
    point.x = norme;
    point.y = angle;
}

// Converts Polar coordinates to Cartesian coordinates.
Cart Pol::toCart() const
{
    Cart M(point.x * cos(point.y), point.x * sin(point.y));
    return M;
}

Cercle::Cercle(double R, Cart C) : C(C), R(R)
{
}

Cercle::Cercle(double R, double x, double y) : R(R), C(x, y)
{
}

// Checks if a Cartesian point is inside the circle.
bool Cercle::inclusion(const Cart &P) const
{
    if (distance(C, P) < R - epsil_zero)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks if a circle is entirely inside another circle.
bool Cercle::inclusion(const Cercle &C1) const
{
    if (distance(C, C1.C) < R - C1.R - epsil_zero)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Normalizes an angle to the range [-π, π].
void angleNormalise(double &angle)
{
    while (angle < -M_PI)
    {
        angle += 2 * M_PI;
    }
    while (angle > M_PI)
    {
        angle -= 2 * M_PI;
    }
}

// Computes the Euclidean distance between two Cartesian points.
double distance(const Cart &P1, const Cart &P2)
{
    return sqrt(pow((P1.point.x) - (P2.point.x), 2) + pow((P1.point.y) - (P2.point.y), 2));
}

double distance(const Pol &P1, const Pol &P2)
{
    return distance(P1.toCart(), P2.toCart());
}

double distance(const Cart &P1, const Pol &P2)
{
    return distance(P1, P2.toCart());
}

double distance(const Pol &P1, const Cart &P2)
{
    return distance(P2, P1);
}

// Checks if two circles intersect.
bool intersection(Cercle C1, Cercle C2)
{
    if (distance(C1.C, C2.C) >= C2.R + C1.R + epsil_zero)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Computes the reflection of a vector relative to a point with an optional state adjustment.
Pol reflect(Cart P, Pol V, State state)
{
    if (state == BACKWARD)
    {
        V.point.y = V.point.y + M_PI;
    }
    double alpha = V.point.y;
    double beta = atan2(P.point.y, P.point.x);
    double alpha_prime = M_PI + 2 * beta - alpha;
    angleNormalise(alpha_prime);
    Pol Reflechi(V.point.x, alpha_prime);
    return Reflechi;
}

Cart &operator+=(Cart &a, const Pol &b)
{
    Cart m = b.toCart();
    a.point.x += m.point.x;
    a.point.y += m.point.y;
    return a;
}

Cart operator+(Cart a, const Pol &b)
{
    return a += b;
}

// Computes the opposite of a polar vector by flipping its angle.
Pol opp(const Pol &p)
{
    double alpha(p.point.y + M_PI);
    angleNormalise(alpha);
    return Pol(p.point.x, alpha);
}

void drawCircle(Cercle C, Color C1, double width, Remplissage Remp, Color C2)
{
    draw_circle(C.C.point.x, C.C.point.y, C.R, width, C1, Remp, C2);
}
