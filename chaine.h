// chaine.h, Mohamed Yassine Toujani et Adam Belghith, V2
#ifndef CHAINE_H
#define CHAINE_H

#include "tools.h"
#include "message.h"
#include "constantes.h"
#include <sstream>
#include <vector>

class Chaine
{
private:
    std::vector<Cart> articulations_;
    Cart point_opp;

public:
    bool lecture(std::istringstream &data);
    void pointOppose();
    std::vector<Cart> articulations();
    void draw();
    bool tete_arrivee();
    void reset();
};

#endif