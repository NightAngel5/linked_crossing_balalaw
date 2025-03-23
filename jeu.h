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

Chaine chaine;
static vFaiseurs vfaiseurs;
static vParticules vparticules;
static etat etat_lecture;
static unsigned score,nbPart,nbFais,nbArtic;
static Mode mode;
class Jeu
{
    public:
        Jeu();
        void lecture(std::string nom_fichier);
};
bool decodage_score(istringstream &data);
bool decodage_nbPart(istringstream &data);
bool decodage_part(istringstream &data);
bool decodage_nbFais(istringstream &data);
bool decodage_fais(istringstream &data);
bool decodage_nbArtic(istringstream &data);
bool decodage_artic(istringstream &data);
bool decodage_mode(istringstream &data);

#endif