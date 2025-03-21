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
