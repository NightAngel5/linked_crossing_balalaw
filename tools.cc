#include "tools.h"
using namespace std;

double Cart::norme() const
{
    return sqrt((point.x) *(point.x) + (point.y) *(point.y));
}

Pol::Pol(double norme, double angle)
{
    point.x=norme;
    point.y=angle;
}

Cart Pol::toCart() const
{
    Cart M(point.x * cos(point.y), point.x * sin(point.y));
    return M;
}

Cart::Cart(double x, double y) {
    point.x = x;
    point.y = y;
}


Pol Cart::toPol() const
{
    Pol M(norme(), atan2(point.y, point.x));
    return M;
}
void angleNormalise(double &angle)
{
    while (angle<-M_PI)
    {
        angle += 2 * M_PI;
    }
    while (angle>M_PI)
    {
        angle -= 2 * M_PI;
    }
}

double distance(const Cart &P1, const Cart& P2)
{
    return sqrt(pow((P1.point.x) - (P2.point.x), 2) + pow((P1.point.y) - (P2.point.y), 2));
}

double distance(const Pol &P1,const Pol& P2)
{
    return distance(P1.toCart(), P2.toCart());
}

double distance(const Cart& P1,const Pol& P2)
{
    return distance(P1, P2.toCart());
}

double distance(const Pol& P1, const Cart& P2)
{
    return distance(P1.toCart(), P2);
}
Cercle::Cercle(double R, Cart C) : C(C), R(R)
{
}
Cercle::Cercle(double R, double x, double y) : R(R),C(x,y)
{
}
const bool Cercle::inclusion(const Cart &P)
{
    if (distance(C, P) < R-epsil_zero) {
        return true;
    } else {
        return false;
    }
}

const bool Cercle::inclusion (const Cercle& C1){
    if (distance(C, C1.C)<R-C1.R-epsil_zero) {
        return true;
    } else {
        return false;
    }
}

bool intersection(Cercle C1, Cercle C2){
    if (distance(C1.C, C2.C)>=C2.R+C1.R+epsil_zero) {
        return false;
    } else {
        return true;
    }
}

Pol reflect(Cart P, Pol V, State state)
{
    if (state==BACKWARD)
    {
        V.point.y = V.point.y + M_PI;
    }
    double alpha = V.point.y;
    double beta = atan2(P.point.y, P.point.x);
    double alpha_prime = M_PI + 2 * beta - alpha;
    angleNormalise(alpha_prime);
    Pol Reflechi (V.point.x, alpha_prime);
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

Pol opp(const Pol &p)
{
    double alpha(p.point.y + M_PI);
    angleNormalise(alpha);
    return Pol(p.point.x,alpha);
}
