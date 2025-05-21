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
private:
    Chaine chaine;
    vFaiseurs vfaiseurs;
    vParticules vparticules;
    etat etat_lecture;
    unsigned score, nbPart, nbFais, nbArtic;
    Mode mode;
    bool lecture_ok_;
    double xs, ys;
    bool racine_set;

    Status status;

    bool decodage_ligne(std::istringstream &data);

    bool decodage_score(std::istringstream &data);

    bool decodage_nbPart(std::istringstream &data);

    bool decodage_part(std::istringstream &data);

    bool decodage_nbFais(std::istringstream &data);

    bool decodage_fais(std::istringstream &data);

    bool decodage_nbArtic(std::istringstream &data);

    bool decodage_artic(std::istringstream &data);

    bool decodage_mode(std::istringstream &data);

    bool collisionAF(bool epsil = true);

    bool intouch(const std::vector<Cart> &v1,
                 const std::vector<Cercle> &v2, size_t a,
                 bool epsil = true);

    bool impasse_faiseur(size_t j);
    vParticules update_particules();
    void draw_starting_point();

public:
    void set_xs(double x) { xs = x; }
    void set_ys(double y) { ys = y; }
    Mode get_mode() { return mode; }
    Status get_status() { return status; }
    Jeu();
    bool lecture(std::string nom_fichier);
    void updateJeu();
    void draw();
    void reset();
    bool lecture_ok();
    unsigned get_score();
    unsigned get_nb_part();
    unsigned get_nb_fais();
    unsigned get_nb_artic();
    void save(std::string);
    void set_mode(Mode m) { mode = m; }
    void capture();
};

#endif