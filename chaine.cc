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

Cart Chaine::get_point_opp() const
{
    return point_opp;
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
                drawLine(articulations_[i - 1], articulations_[i], RED, 1.2);
            }
        }
        drawCircle(Cercle(r_capture, articulations_[articulations_.size() - 1]),
                          RED);
        drawCircle(Cercle(r_viz, point_opp), BLACK, 0.7, PLEIN, BLACK);
    }
}

void Chaine::reset()
{
    articulations_.clear();
    point_opp = Cart(0, 0);
}

bool Chaine::fin()
{
    return Cercle(r_capture, articulations_.back()).inclusion(point_opp);
}

void Chaine::guidage(double xs, double ys)
{ 
    Cart but_inter(projection(Cart(xs, ys), Cercle(r_capture, articulations_.back())));
    bool ok = Cercle(r_max).inclusion(but_inter);
    vector<Cart> copy(articulations());
    if (ok)
    {
        copy.back() = but_inter;
        for (size_t i = articulations_.size() - 1; i > 0; i--)
        {
            Pol v((copy[i] - copy[i - 1]).toPol());
            v.point.x = distance(articulations_[i], articulations_[i - 1]);
            copy[i - 1] = copy[i] + v;
            ok = Cercle(r_max).inclusion(copy[i - 1]);
            if (!ok)
            {
                break;
            }
        }
        copy.front() = articulations_.front();
        if (ok)
        {
            for (size_t i = 0; i < articulations_.size() - 1; i++)
            {
                Pol v((copy[i + 1] - copy[i]).toPol());
                v.point.x = distance(articulations_[i + 1], articulations_[i]);
                copy[i + 1] = copy[i] + v;
                ok = Cercle(r_max).inclusion(copy[i + 1]);
                if (!ok)
                {
                    break;
                }
            }
        }
    }
    if (ok)
    {
        articulations_ = move(copy);
    }
}
