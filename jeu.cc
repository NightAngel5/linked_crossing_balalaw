#include "jeu.h"
using namespace std;

Jeu::Jeu()
{
    etat_lecture = SCORE;
    vFaiseurs.clear();
    vParticules.clear();
    score = 0;
    nbFais = 0;
    nbArtic = 0;
    nbPart = 0;
    mode = CONSTRUCTION;
}

void Jeu::lecture(std::string nom_fichier)
{
    ifstream fichier(nom_fichier);
    if (!fichier.fail())
    {
        string line;
        while (getline(fichier >> ws, line))
        {
            if (line[0] == '#')
                continue;
            istringstream data(line);
            if (decodage_ligne(data) == false) // détection d'erreur simple
                exit(EXIT_FAILURE);
        }
    }
    else
        exit(EXIT_FAILURE);
}

bool decodage_ligne(istringstream &data)
{
    switch (etat_lecture)
    {
    case SCORE: // lecture du nombre de livreurs
        if (decodage_score(data) == false)
            return false;
        break;

    case NBPART: // ajout dans le vector en cas de succès
        if (decodage_nbPart(data) == false)
            return false;
        break;

    case PART: // lecture du nombre de véhicules
        if (decodage_part(data) == false)
            return false;
        break;

    case NBFAIS: // ajout dans le vector en cas de succès
        if (decodage_nbFais(data) == false)
            return false;
        break;

    case FAIS: // lecture du nombre de livraisons
        if (decodage_fais(data) == false)
            return false;
        break;

    case NBARTIC: // ajout dans le vector en cas de succès
        if (decodage_nbArtic(data) == false)
            return false;
        break;
    case ARTIC: // ajout dans le vector en cas de succès
        if (decodage_artic(data) == false)
            return false;
        break;
    case MODE: // ajout dans le vector en cas de succès
        if (decodage_mode(data) == false)
            return false;
        break;
    default:
        return false;
    }
    return true;
}

bool decodage_score(istringstream &data)
{
    if (data >> score)
    {
        if (score<=0 or score>score_max)
        {
            cout << message::score_outside(score);
            return false;
        }else
            etat_lecture = NBPART;
            return true;
    }
    return false;
}

bool decodage_nbPart(istringstream &data)
{
    if (data >> nbPart)
    {
        if (nbPart < 0 or nbPart > nb_particule_max)
        {
            cout << message::nb_particule_outside(nbPart);
            return false;
        }
        else
            etat_lecture = PART;
            return true;
    }
    return false;
}

bool decodage_part(istringstream &data)
{
    Particule x;
    if (x.lecture(data))
    {
        vparticules.push_back(x);
        if (vparticules.size()==nbPart)
        {
            etat_lecture = NBFAIS;
        }
        return true;
    }
    return false;
}
bool decodage_nbFais(istringstream &data)
{
    if (data >> nbPart)
    {
        etat_lecture = FAIS;
        return true;
    }
    return false;
}

bool decodage_fais(istringstream &data)
{
    Faiseur x;
    if (x.lecture(data,vfaiseurs))
    {
        vfaiseurs.push_back(x);
        if (vparticules.size() == nbFais)
        {
            etat_lecture = NBARTIC;
        }
        return true;
    }
    return false;
}

bool decodage_nbArtic(istringstream &data)
{
    if (data >> nbArtic)
    {
        etat_lecture = ARTIC;
        return true;
    }
    return false;
}

bool decodage_artic(istringstream &data)
{
    if (chaine.lecture(data))
    {
        etat_lecture = MODE;
        return true;
    }
    return false;
}

bool decodage_mode(istringstream &data)
{
    string x;
    if (data >> x)
    {
        if (x=="CONSTRUCTION")
        {
            mode = CONSTRUCTION;
        }
        else if (x=="GUIDAGE")
        {
            mode = GUIDAGE;
        }else{
            return false;
        }
        etat_lecture = ARTIC;
        return true;
    }
    return false;
}
