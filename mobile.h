// mobile.h, Mohamed Yassine Toujani et Adam Belghith, V2
#ifndef MOBILE_H
#define MOBILE_H

#include <sstream>
#include <vector>
#include "tools.h"
#include "message.h"
#include "constantes.h"

class mobile
{
protected:
    double x0, y0, a0, d0;
};

class Particule : public mobile
{
public:
    bool lecture(std::istringstream &data);
    void draw();
    Particule move();

private:
    unsigned c0;
};

class Faiseur : public mobile
{
public:
    bool lecture(std::istringstream &data, const std::vector<Faiseur> &V);
    std::vector<Cercle> constructionFaiseur() const;
    void draw();
    void move();

private:
    double r0;
    unsigned nbe0;
};

bool collisionFaiseur(const Faiseur &F1, const std::vector<Faiseur> &V);

bool impact(std::vector<Cercle> v1, std::vector<Cercle> v2, size_t a, size_t b);

#endif