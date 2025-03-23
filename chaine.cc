#include "chaine.h"
#include <iostream>

using namespace std;

bool Chaine::lecture(std::istringstream &data)
{
    double x, y;
    if (data>>x>>y)
    {
        Cart art(x, y);
        cout<<art.point.x<<" "<<art.point.y;
        if (!Cercle(r_max).inclusion(art))
        {
            cout << message::articulation_outside(x, y);
            exit(EXIT_FAILURE);
        }
        else if (articulations_.size() == 0){
            if (art.norme() < r_max - r_capture + epsil_zero)
            {
                cout << message::chaine_racine(x, y);
                exit(EXIT_FAILURE);
            }  
        }else if(distance(articulations_[articulations_.size()-1],art)>r_capture-epsil_zero){
            cout << message::chaine_max_distance(articulations_.size() - 1);
            exit(EXIT_FAILURE);
        }
        articulations_.push_back(art);
        return true;
    }
    else{
        return false;
    }
    
}

std::vector<Cart> Chaine::articulations()
{
    return articulations_;
}
