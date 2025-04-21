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
    Mobile(double x0,double y0,double a0,double d0);
    unsigned get_x0() { return x0; }
    void set_x0(unsigned x) { x0=x; }
    unsigned get_y0() { return y0; }
    void set_y0(unsigned y) { y0=y; }
    unsigned get_a0() { return a0; }
    void set_a0(unsigned a) { a0=a; }
    unsigned get_d0() { return d0; }
    void set_d0(unsigned d) { d0=d; }
protected:
    double x0,y0,a0,d0;
};

class Particule: public Mobile
{
public:                    
    Particule(double x0,double y0,double a0,double d0,unsigned c0);           
    bool lecture(std::istringstream &data);
    unsigned get_c0() { return c0; }
    void set_c0(unsigned x) { c0=x; }
    void draw();  
private:
    unsigned c0;                   
};


class Faiseur: public Mobile 
{
public:   
    Faiseur(double x0,double y0,double a0,double d0,unsigned r0, unsigned nbe0);                             
    bool lecture(std::istringstream &data, const std::vector<Faiseur>& V);
    std::vector<Cercle> constructionFaiseur() const;  
    void draw(); 
    unsigned get_r0() { return r0; }
    void set_c0(unsigned x) { r0=x; } 
private:
    double r0;
    unsigned nbe0;           
};

bool collisionFaiseur(const Faiseur &F1, const std::vector<Faiseur> &V);

bool impact(std::vector<Cercle> v1, std::vector<Cercle> v2, size_t a, size_t b);

#endif