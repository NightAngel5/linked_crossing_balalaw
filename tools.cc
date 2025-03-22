#include "tools.h"
using namespace std;

double Cart::norme() const
{
    return sqrt((point.x) *(point.x) + (point.y) *(point.y));
}

Pol::Pol(double norme, double angle):point({norme,angle})
{
}

Cart Pol::toCart() const
{
    Cart M(norme * cos(angle), norme * sin(angle));
    return M;
}

Cart::Cart(double x, double y):point({x,y})
{
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
    return sqrt(pow((P1.x) - (P2.x), 2) + pow((P1.y) - (P2.y), 2));
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
bool inclusion (Cercle C1, Cart P){
    if (distance(C1.C, P)<C1.R-epsil_zero) {
        return true;
    } else {
        return false;
    }
}

bool inclusion (Cercle C1, Cercle C2){
    if (distance(C1.C, C2.C)<C2.R-C1.R-epsil_zero) {
        return true;
    } else {
        return false;
    }
}

bool intersection(Cercle C1, Cercle C2){
    if (inclusion(C1,C2) || inclusion(C2,C1) || distance(C1.C, C2.C)>=C2.R+C1.R+epsil_zero) {
        return false;
    } else {
        return true;
    }
}

Pol reflect(Cart P, Pol V, State state)
{
    if (state==BACKWARD)
    {
        V.angle = V.angle + M_PI;
    }
    double alpha = V.angle;
    double beta = atan2(P.y, P.x);
    double alpha_prime = M_PI + 2 * beta - alpha;
    angleNormalise(alpha_prime);
    Pol Reflechi (V.norme, alpha_prime);
    return Reflechi;
}

Cart &operator+=(Cart &a, const Pol &b)
{
    Cart m = b.toCart();
    a.point.x += m.x;
    a.point.y += m.y;
    return a;
}
