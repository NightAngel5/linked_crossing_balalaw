// mobile.h, Mohamed Yassine Toujani et Adam Belghith, V2
#ifndef MOBILE_H
#define MOBILE_H

#include <sstream>
#include <vector>
#include "tools.h"
#include "message.h"
#include "constantes.h"

class Mobile
{
public:
    Mobile(double x0, double y0, double a0, double d0);
    Mobile() = default;
    double get_x0() { return x0; }
    double get_y0() { return y0; }
    double get_a0() { return a0; }
    double get_d0() { return d0; }

protected:
    double x0, y0, a0, d0;
};

class Particule : public Mobile
{
public:
    Particule(double x0, double y0, double a0, double d0, unsigned c0);
    Particule() = default;
    bool lecture(std::istringstream &data);
    unsigned get_c0() { return c0; }
    void set_c0(unsigned x);
    void draw();
    Particule move();

private:
    unsigned c0;
};

class Faiseur : public Mobile
{
public:
    Faiseur(double x0, double y0, double a0, double d0,
            unsigned r0, unsigned nbe0);
    Faiseur() = default;
    bool lecture(std::istringstream &data, const std::vector<Faiseur> &V);
    std::vector<Cercle> constructionFaiseur() const;
    void draw();
    double get_r0() { return r0; }
    unsigned get_nbe0() { return nbe0; }
    void move();

private:
    double r0;
    unsigned nbe0;
};

bool collisionFaiseur(const Faiseur &F1, const std::vector<Faiseur> &V, bool epsil = true);

bool impact(std::vector<Cercle> v1, std::vector<Cercle> v2, size_t a, size_t b, bool epsil = true);

#endif