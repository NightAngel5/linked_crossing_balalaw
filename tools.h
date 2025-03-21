#include <cmath>
constexpr double epsil_zero(0.5);

struct S2d {
    double x = 0.;
    double y = 0.;
};
typedef S2d Cart; //x l'abscisse et y l'ordonnée
typedef S2d Pol; //x la norme et y l'angle

double norme(Cart P);
Cart conversion(Pol P);
Pol conversion(Cart P);
double distance(Cart P1, Cart P2);
double distance(Pol P1, Pol P2);
double distance(Cart P1, Pol P2);
double distance(Pol P1, Cart P2);
