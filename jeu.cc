#include "jeu.h"
using namespace std;

static Chaine chaine;
static vFaiseurs vfaiseurs;
static vParticules vparticules;
static etat etat_lecture;
static unsigned score, nbPart, nbFais, nbArtic;
static Mode mode;

Jeu::Jeu()
{
    etat_lecture = SCORE;
    vfaiseurs.clear();
    vparticules.clear();
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
            if (decodage_ligne(data) == false)
                exit(EXIT_FAILURE);
        }
        if (collisionAF()==true)
        {
            exit(EXIT_FAILURE);
        }
        cout<<message::success();
        exit(0);
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
            etat_lecture = (nbPart==0)?NBFAIS:PART;
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
    if (data >> nbFais)
    {
        etat_lecture = (nbFais==0)?NBARTIC:FAIS;;
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
        if (vfaiseurs.size() == nbFais)
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
        etat_lecture = (nbArtic==0)?MODE:ARTIC;
        return true;
    }
    return false;
}

bool decodage_artic(istringstream &data)
{
    if (chaine.lecture(data))
    {
        if (chaine.articulations().size()==nbArtic)
        {
            etat_lecture = MODE;
        }
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
        return true;
    }
    return false;
}


bool collisionAF()
{
    vector<Cart> v1(chaine.articulations());
    for (size_t i(0); i < vfaiseurs.size(); ++i)
    {
        vector<Cercle> v2(vfaiseurs[i].constructionFaiseur());
        if (intouch(v1,v2,i))
        {
            return true;
        }
    }
    return false;
}

bool intouch(vector<Cart>v1, vector<Cercle>v2, size_t a )
{
    if (v1.size()==0)
    {
        return false;
    }
    for (size_t i(0); i<v1.size(); ++i)
    {
        for (size_t j(0); j< v2.size(); ++j)
        {
            if (v2[j].inclusion(v1[i]))
            {
                cout<<message::chaine_articulation_collision(i,a,j);
                return true;
            }
        }
    }
    return false;
}
            