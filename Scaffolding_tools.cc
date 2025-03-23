#include <iostream>
#include "tools.h"
using namespace std;

int main(){
    Cart P1  (2, 0);
    Cart P2  (5, 6);
    Cart P3  (1, 1);
    Cart P4  (-2, -1);
    Cart CP1  (0, 0);
    Cart CP2  (4, 0);
    Cart CP3  (-1, 0);
    Cercle C1  (CP1, 3);
    Cercle C2  (CP2, 2);
    Cercle C3  (CP3, 1);
    Cercle C4  (P2, 1);
    Pol V1  (0.7, 0.);
    Pol V2  (1, M_PI / 3);
    Pol V3  (1, M_PI / 2);

    cout << "Norme de (5,6) = " << P2.norme() << endl
         << "(1,1) = ( norme = " << P3.toPol().norme << " , angle = " << P3.toPol().angle <<" )"<< endl
         << "(1, pi/3) = (" << V2.toCart().x << " ," << V2.toCart().y << " )" << endl
         << "Distance entre (2,0) et (5,6) = " << distance(P1, P2) << endl
         << "C3 est inclus dans C1 = " << C1.inclusion(C3) << endl
         << "C4 est inclus dans C1 = " << C1.inclusion(C4) << endl
         << "P2 inclus dans C1 = " << C1.inclusion(P2) << endl
         << "P1 inclus dans C1 = " << C1.inclusion(P1) << endl
         << "C2 intersecte C1 = " << intersection(C2, C1) << endl
         << "C3 intersecte C1 = " << intersection(C3, C1) << endl
         << "reflexion de (1,1) avec vecteur (1,pi/3) = (" << reflect(P3, V2, FORWARD).norme << " , " << reflect(P3, V2, FORWARD).angle << " )" << endl
         << "reflexion de (-2,-1) avec vecteur (1,pi/2) (BACKWARD) = (" << reflect(P4, V3, BACKWARD).norme << " , " << reflect(P4, V3, BACKWARD).angle << " )" << endl
         << "reflexion de (2,0) avec vecteur (0.7, angle=0) = (" << reflect(P1, V1, FORWARD).norme << " , " << reflect(P1, V1, FORWARD).angle << " )" << endl;

    return 0;
}