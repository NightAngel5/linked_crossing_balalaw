// chaine.cc, Mohamed Yassine Toujani et Adam Belghith, V2
#include "chaine.h"
#include <iostream>

using namespace std;

// Reads and validates articulation points for the chain.
bool Chaine::lecture(std::istringstream &data)
{
    double x, y;
    if (data >> x >> y)
    {
        Cart art(x, y);
        if (!Cercle(r_max).inclusion(art))
        {
            cout << message::articulation_outside(x, y);
            return false;
        }
        else if (articulations_.size() == 0)
        {
            if (art.norme() < r_max - r_capture + epsil_zero)
            {
                cout << message::chaine_racine(x, y);
                return false;
            }
        }
        else if (distance(articulations_[articulations_.size() - 1],
                          art) > r_capture - epsil_zero)
        {
            cout << message::chaine_max_distance(articulations_.size() - 1);
            return false;
        }
        articulations_.push_back(art);
        return true;
    }
    else
    {
        return false;
    }
}

void Chaine::pointOppose()
{
    Pol P = opp(articulations_[0].toPol());
    P.point.x = r_max;
    point_opp = P.toCart();
}

// Returns the list of articulation points of the chain.
std::vector<Cart> Chaine::articulations()
{
    return articulations_;
}

void Chaine::draw()
{
    if (articulations_.size() > 0)
    {
        for (size_t i = 0; i < articulations_.size(); i++)
        {
            drawCircle(Cercle(r_viz, articulations_[i]), RED);
            if (i > 0)
            {
                drawLine(articulations_[i - 1], articulations_[i], RED);
            }
        }
        drawCircle(Cercle(r_capture, articulations_[articulations_.size() - 1]), RED);
        drawCircle(Cercle(r_viz, point_opp), BLACK);
    }
}

bool Chaine::tete_arrivee()
{
    return articulations_.size() && distance(articulations_[articulations_.size()], point_opp) < epsil_zero;
}
