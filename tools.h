// tools.h, Mohamed Yassine Toujani et Adam Belghith, V3
#ifndef TOOLS_H
#define TOOLS_H
#define _USE_MATH_DEFINES

#include <cmath>
#include "graphic.h"

constexpr double epsil_zero(0.5);

enum State
{
    FORWARD,
    BACKWARD
};

struct S2d
{
    double x = 0.;
    double y = 0.;
};
struct Pol;
struct Cart
{
    S2d point;

    Cart(double x = 0, double y = 0);

    Pol toPol() const;

    double norme() const;
};
struct Pol
{
    S2d point; // x norme et y angle

    Pol(double norme, double angle);

    Cart toCart() const;
};

struct Cercle
{
    Cercle(double R, Cart C = Cart(0., 0.));

    Cercle(double R, double x, double y);

    Cart C;
    double R;

    bool inclusion(const Cart &P) const;

    bool inclusion(const Cercle &C1) const;
};

void angleNormalise(double &angle);

double distance(const Cart &P1, const Cart &P2);

double distance(const Pol &P1, const Pol &P2);

double distance(const Cart &P1, const Pol &P2);

double distance(const Pol &P1, const Cart &P2);

bool intersection(Cercle C1, Cercle C2);

Pol reflect(Cart P, Pol V, State state);

Cart &operator+=(Cart &a, const Pol &b);

Cart operator+(Cart a, const Pol &b);

Pol opp(const Pol &p);

void drawCircle(Cercle C, Color C1, double width = 0.7,
                Remplissage Remp = VIDE, Color C2 = WHITE);

void drawLine(Cart C1, Cart C2, Color C, double width = 0.7);

#endif