#ifndef MOBILE_H
#define MOBILE_H
#include <sstream>
#include <vector>
#include "tools.h"
#include "message.h"
#include "constantes.h"


class Particule {
public:                                 
    bool lecture(std::istringstream &data);     
private:
    double x0,y0,a0,d0;
    unsigned c0;                   
};


class Faiseur {
    public:                                
        bool lecture(std::istringstream &data, const std::vector<Faiseur>& V);
        std::vector<Cercle> constructionFaiseur() const;    
    private:
        double x0,y0,a0,d0,r0;
        unsigned nbe0;           
    };
    
typedef std::vector<Faiseur> vFaiseurs;
typedef std::vector<Particule> vParticules;


bool collisionFaiseur(const Faiseur& F1, const vFaiseurs& V );
bool impact(std::vector<Cercle> v1, std::vector<Cercle> v2, size_t a, size_t b);




#endif