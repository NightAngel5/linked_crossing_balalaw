#include "tools.h"
using namespace std;

double norme(Cart P)
{
    return sqrt((P.x) *(P.x) + (P.y) *(P.y));
}

Cart conversion(Pol P)
{
    Cart M = {P.x * cos(P.y), P.x * sin(P.y)};
    return M;
}

Pol conversion(Cart P)
{
    Pol M = {norme(P), atan2(P.x, P.y)};
    return M;
}

double distance(Cart P1, Cart P2)
{
    return sqrt(pow((P1.x) - (P2.x), 2) + pow((P1.y) - (P2.y), 2));
}

double distance(Pol P1, Pol P2)
{
    return distance(conversion(P1), conversion(P2));
}

double distance(Cart P1, Pol P2)
{
    return distance(P1, conversion(P2));
}

double distance(Pol P1, Cart P2)
{
    return distance(P1, conversion(P2));
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
    if (distance(C1.C, C2.C)<C2.R+C1.R+epsil_zero) {
        return true;
    } else {
        return false;
    }
}

Cart reflect(Cart P, Pol V, State state)
{
    if (state=BACKWARD)
    {
        V.y = -V.y;
    }
    Cart V1 = conversion(V);
    Cart R = {P.x + V1.x, P.y + V1.y};
    double alpha = V.y;
    double beta = atan2(R.y, R.x);
    double alpha_prime = M_PI + 2 * beta - alpha;
    Cart V2 = {V.x * cos(alpha_prime), V.x * sin(alpha_prime)};
    Cart Reflechi = {R.x + V2.x, R.y + V2.y};
    return Reflechi;
}
