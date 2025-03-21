#include <cmath>
constexpr double epsil_zero(0.5);

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

bool inclusion (Cercle C1, Cart P);
bool inclusion (Cercle C1, Cercle C2);
bool intersection(Cercle C1, Cercle C2);
