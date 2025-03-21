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
typedef S2d Cart; //x l'abscisse et y l'ordonnée
typedef S2d Pol; //x la norme et y l'angle
struct Cercle {
    S2d C;
    double R;
};
double norme(Cart P);
Cart conversion(Pol P);
Pol conversion(Cart P);
double distance(Cart P1, Cart P2);
double distance(Pol P1, Pol P2);
double distance(Cart P1, Pol P2);
double distance(Pol P1, Cart P2);
bool inclusion (Cercle C1, Cart P);
bool inclusion (Cercle C1, Cercle C2);
bool intersection(Cercle C1, Cercle C2);
Cart reflect(Cart P, Pol V, State state);