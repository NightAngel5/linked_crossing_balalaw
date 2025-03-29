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
public:
    bool lecture(std::istringstream &data);
    
    std::vector<Cart> articulations();
};

#endif