// jeu.h, Mohamed Yassine Toujani et Adam Belghith, V2
#ifndef JEU_H
#define JEU_H

#include <fstream>
#include <iostream>
#include <string>
#include "tools.h"
#include "mobile.h"
#include "chaine.h"
#include "message.h"
#include "constantes.h"

typedef std::vector<Faiseur> vFaiseurs;
typedef std::vector<Particule> vParticules;

enum Status
{
    ONGOING,
    WON,
    LOST
};

enum etat
{
    SCORE,
    NBPART,
    PART,
    NBFAIS,
    FAIS,
    NBARTIC,
    ARTIC,
    MODE
};

class Jeu
{
public:
    Jeu();
    void lecture(std::string nom_fichier);
};

bool decodage_ligne(std::istringstream &data);

bool decodage_score(std::istringstream &data);

bool decodage_nbPart(std::istringstream &data);

bool decodage_part(std::istringstream & data);

bool decodage_nbFais(std::istringstream &data);

bool decodage_fais(std::istringstream &data);

bool decodage_nbArtic(std::istringstream &data);

bool decodage_artic(std::istringstream &data);

bool decodage_mode(std::istringstream &data);

bool collisionAF();

bool intouch(std::vector<Cart> v1, std::vector<Cercle> v2, size_t a );
#endif