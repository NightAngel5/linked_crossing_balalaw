// mobile.cc, Mohamed Yassine Toujani et Adam Belghith, V2
#include "mobile.h"
#include <iostream>

using namespace std;

Mobile::Mobile(double x0, double y0, double a0, double d0)
    : x0(x0), y0(y0), a0(a0), d0(d0) {}
Particule::Particule(double x0, double y0, double a0, double d0, unsigned c0)
    : Mobile(x0, y0, a0, d0), c0(c0) {}
// Reads and validates attributes for a particle.
bool Particule::lecture(istringstream &data)
{
    if (data >> x0 >> y0 >> a0 >> d0 >> c0) // lecture des attributs avec succès
    {
        if (!Cercle(r_max).inclusion(Cart(x0, y0),false))
        {
            cout << message::particule_outside(x0, y0);
            return false;
        }
        else if (!(0 <= d0 && d0 <= d_max))
        {
            cout << message::mobile_displacement(d0);
            return false;
        }
        else if (!(0 <= c0 && c0 < time_to_split))
        {
            cout << message::particule_counter(c0);
            return false;
        }
        angleNormalise(a0);
        return true;
    }
    else
        return false;
}

void Particule::set_c0(unsigned x)
{
    if (!(0 <= x && x < time_to_split))
    {
        cout << message::particule_counter(x);
    }
    else
        c0 = x;
}

void Particule::draw()
{
    drawCircle(Cercle(r_viz, x0, y0), GREEN, 0.7, PLEIN, CYAN);
}

Particule Particule::move()
{
    Cart P(x0, y0);
    Pol vect(d0, a0);
    if (!Cercle(r_max).inclusion(P+vect))
    {
        vect = reflect(P, vect, FORWARD);
    }
    P += vect;
    return Particule(P.point.x, P.point.y, vect.point.y, vect.point.x, c0 + 1);
}

Faiseur::Faiseur(double x0, double y0, double a0,
                 double d0, unsigned r0, unsigned nbe0)
    : Mobile(x0, y0, a0, d0), r0(r0), nbe0(nbe0) {}
// Reads and validates attributes for a Faiseur + checking for collisions.
bool Faiseur::lecture(istringstream &data, const std::vector<Faiseur> &V)
{
    if (data >> x0 >> y0 >> a0 >> d0 >> r0 >> nbe0) // lecture des attributs
    {                                               // avec succès
        if (!Cercle(r_max).inclusion(Cercle(r0, x0, y0),false))
        {
            cout << message::faiseur_outside(x0, y0);
            return false;
        }
        else if (!(0 <= d0 && d0 <= d_max))
        {
            cout << message::mobile_displacement(d0);
            return false;
        }
        else if (!(r_min_faiseur <= r0 && r0 <= r_max_faiseur))
        {
            cout << message::faiseur_radius(r0);
            return false;
        }
        else if (nbe0 <= 0)
        {
            cout << message::faiseur_nbe(nbe0);
            return false;
        }
        angleNormalise(a0);
        if (V.size() > 0)
        {
            if (collisionFaiseur(*this, V,false))
                return false;
        }
        return true;
    }
    else
        return false;
}

// Constructs the faiseurs's circles based on the head.
std::vector<Cercle> Faiseur::constructionFaiseur() const
{
    vector<Cercle> v1;
    v1.push_back(Cercle(r0, x0, y0));
    Cart c(x0, y0);
    Pol pas(d0, a0);
    Pol pas1(opp(pas));

    for (unsigned i(0); i < nbe0; ++i)
    {
        if (!Cercle(r_max).inclusion(Cercle(r0, c + pas1)))
        {
            pas1 = reflect(c, pas, BACKWARD);
            pas = opp(pas1);
        }
        v1.push_back(Cercle(r0, c + pas1));
        c += pas1;
    }
    return v1;
}

void Faiseur::draw()
{
    std::vector<Cercle> v(constructionFaiseur());
    for (unsigned i(0); i <= nbe0; ++i)
    {
        drawCircle(v[i], BLUE, 0.7);
    }
}

void Faiseur::move()
{
    Cart P(x0, y0);
    Pol vect(d0, a0);
    if (!Cercle(r_max).inclusion(Cercle(r0, (P + vect))))
    {
        vect = reflect(P, vect, FORWARD);
    }
    P += vect;
    x0 = P.point.x;
    y0 = P.point.y;
    d0 = vect.point.x;
    a0 = vect.point.y;
}

// Checks if a Faiseur collides with any other Faiseur in a list.
bool collisionFaiseur(const Faiseur &F1, const std::vector<Faiseur> &V, bool epsil)
{
    std::vector<Cercle> v1(F1.constructionFaiseur());
    for (size_t i(0); i < V.size(); ++i)
    {
        std::vector<Cercle> v2(V[i].constructionFaiseur());
        if (impact(v1, v2, i, V.size()))
        {
            return true;
        }
    }
    return false;
}

// Determines if two sets of circles (representing Faiseurs) intersect.
bool impact(std::vector<Cercle> v1, std::vector<Cercle> v2, size_t id1, size_t id2, bool epsil)
{
    for (size_t i(0); i < v1.size(); ++i)
    {
        for (size_t j(0); j < v2.size(); ++j)
        {
            if (intersection(v1[i], v2[j],epsil))
            {
                cout << message::faiseur_element_collision(id1, j, id2, i);
                return true;
            }
        }
    }
    return false;
}
