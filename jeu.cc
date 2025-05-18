// jeu.cc, Mohamed Yassine Toujani et Adam Belghith, V2
#include "jeu.h"

using namespace std;

// Initializes the game state.
Jeu::Jeu()
{
    reset();
}

// Reads and processes game data from a file.
bool Jeu::lecture(std::string nom_fichier)
{
    reset();
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
                return false;
        }
        if (collisionAF() == true)
        {
            return false;
        }
        set_status();
        lecture_ok_ = true;
        cout << message::success();
        return true;
    }
    else
        return false;
}

void Jeu::set_status()
{
    if (score == 0)
    {
        status = LOST;
    }
    else if (chaine.fin())
    {
        status = WON;
        cout << "Bravo! Bien joué!" << endl;
    }
    else
    {
        status = ONGOING;
    }
}

bool Jeu::impasse_faiseur(size_t j)
{
    Cart P(vfaiseurs[j].get_x0(), vfaiseurs[j].get_y0());
    Pol vect(vfaiseurs[j].get_d0(), vfaiseurs[j].get_a0());
    P += vect;
    Cercle tete(vfaiseurs[j].get_r0(), P);
    for (size_t i = 0; i < vfaiseurs.size(); i++)
    {
        if (i == j)
            continue;
        for (auto k : vfaiseurs[i].constructionFaiseur())
        {
            if (intersection(tete, k))
            {
                return true;
            }
        }
    }
    return false;
}

// Decodes a line of game data based on the current reading state (etat_lecture).
bool Jeu::decodage_ligne(istringstream &data)
{
    switch (etat_lecture)
    {
    case SCORE: // Reads the initial score
        if (decodage_score(data) == false)
            return false;
        break;

    case NBPART: // Reads the number of particles
        if (decodage_nbPart(data) == false)
            return false;
        break;

    case PART: // Reads individual particle data
        if (decodage_part(data) == false)
            return false;
        break;

    case NBFAIS: // Reads the number of Faiseurs
        if (decodage_nbFais(data) == false)
            return false;
        break;

    case FAIS: // Reads individual Faiseur data
        if (decodage_fais(data) == false)
            return false;
        break;

    case NBARTIC: // Reads the number of articulations
        if (decodage_nbArtic(data) == false)
            return false;
        break;
    case ARTIC: // Reads individual articulation data
        if (decodage_artic(data) == false)
            return false;
        break;
    case MODE: // Reads the game mode
        if (decodage_mode(data) == false)
            return false;
        break;
    default:
        return false;
    }
    return true;
}

// Reads and validates the score value.
bool Jeu::decodage_score(istringstream &data)
{
    if (data >> score)
    {
        if (score <= 0 or score > score_max)
        {
            cout << message::score_outside(score);
            return false;
        }
        else
            etat_lecture = NBPART;
        return true;
    }
    return false;
}

// Reads and validates the number of particles.
bool Jeu::decodage_nbPart(istringstream &data)
{
    if (data >> nbPart)
    {
        if (nbPart < 0 or nbPart > nb_particule_max)
        {
            cout << message::nb_particule_outside(nbPart);
            return false;
        }
        else
            etat_lecture = (nbPart == 0) ? NBFAIS : PART;
        return true;
    }
    return false;
}

// Reads and adds a particle.
bool Jeu::decodage_part(istringstream &data)
{
    Particule x;
    if (x.lecture(data))
    {
        vparticules.push_back(x);
        if (vparticules.size() == nbPart)
        {
            etat_lecture = NBFAIS;
        }
        return true;
    }
    return false;
}

// Reads and validates the number of Faiseurs.
bool Jeu::decodage_nbFais(istringstream &data)
{
    if (data >> nbFais)
    {
        etat_lecture = (nbFais == 0) ? NBARTIC : FAIS;
        return true;
    }
    return false;
}

// Reads and adds a Faiseur.
bool Jeu::decodage_fais(istringstream &data)
{
    Faiseur x;
    if (x.lecture(data, vfaiseurs))
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

// Reads and validates the number of articulations.
bool Jeu::decodage_nbArtic(istringstream &data)
{
    if (data >> nbArtic)
    {
        etat_lecture = (nbArtic == 0) ? MODE : ARTIC;
        return true;
    }
    return false;
}

// Reads and adds an articulation.
bool Jeu::decodage_artic(istringstream &data)
{
    if (chaine.lecture(data))
    {
        if (chaine.articulations().size() == nbArtic)
        {
            racine_set = true;
            chaine.pointOppose();
            etat_lecture = MODE;
        }
        return true;
    }
    return false;
}

// Reads and sets the game mode.
bool Jeu::decodage_mode(istringstream &data)
{
    string x;
    if (data >> x)
    {
        if (x == "CONSTRUCTION")
        {
            mode = CONSTRUCTION;
        }
        else if (x == "GUIDAGE")
        {
            mode = GUIDAGE;
        }
        else
        {
            return false;
        }
        return true;
    }
    return false;
}

// Checks for collisions between articulations and Faiseurs.
bool Jeu::collisionAF()
{
    vector<Cart> v1(chaine.articulations());
    for (size_t i(0); i < vfaiseurs.size(); ++i)
    {
        vector<Cercle> v2(vfaiseurs[i].constructionFaiseur());
        if (intouch(v1, v2, i))
        {
            return true;
        }
    }
    return false;
}

// Checks for specific articulation-Faiseur collisions.
bool Jeu::intouch(const vector<Cart> &v1, const vector<Cercle> &v2, size_t a)
{
    if (v1.size() == 0)
    {
        return false;
    }
    for (size_t i(0); i < v1.size(); ++i)
    {
        for (size_t j(0); j < v2.size(); ++j)
        {
            if (v2[j].inclusion(v1[i]))
            {
                cout << message::chaine_articulation_collision(i, a, j);
                return true;
            }
        }
    }
    return false;
}

void Jeu::draw()
{
    drawCircle(Cercle(r_max, Cart(0, 0)), GREEN, 1);
    for (auto i : vfaiseurs)
    {
        i.draw();
    }
    for (auto i : vparticules)
    {
        i.draw();
        // code supplémentaire pour le dessin des lignes entre particules  
        // (utile pour le fichier de test 22)
        //for(auto j:vparticules){
        //    Cart P1(i.get_x0(),i.get_y0());
        //    Cart P2(j.get_x0(),j.get_y0());
        //    if (distance(P1,P2)<13)
        //    {
        //        drawLine(P1,P2,GREEN);
        //    }    
        //}
    }
    if (racine_set)
    {
        chaine.draw();
    }
    else
    {
        draw_starting_point();
    }
}

void Jeu::reset()
{
    etat_lecture = SCORE;
    vfaiseurs.clear();
    vparticules.clear();
    vparticules.reserve(nb_particule_max);
    score = 0;
    nbFais = 0;
    nbArtic = 0;
    nbPart = 0;
    racine_set = false;
    chaine.reset();
    mode = CONSTRUCTION;
    status = ONGOING;
    lecture_ok_ = false;
}
bool Jeu::lecture_ok()
{
    return lecture_ok_;
}

unsigned Jeu::get_score()
{
    return score;
}

unsigned Jeu::get_nb_part()
{
    return nbPart;
}

unsigned Jeu::get_nb_fais()
{
    return nbFais;
}

unsigned Jeu::get_nb_artic()
{
    return nbArtic;
}

vParticules Jeu::update_particules(){
    vParticules V;
    V.reserve(vparticules.size() * 2); // worst case: every particle splits
    for (size_t i = 0; i < vparticules.size(); ++i)
    {
        if (vparticules[i].get_c0() == time_to_split-1)
        {
            if (nbPart == nb_particule_max)
                nbPart -= 1;
            else if (nbPart < nb_particule_max)
            {
                double n(vparticules[i].get_a0() + delta_split);
                angleNormalise(n);
                V.emplace_back(Particule(vparticules[i].get_x0(),
                                         vparticules[i].get_y0(), n,
                                         vparticules[i].get_d0() * coef_split, 0)
                                   .move());
                V.back().set_c0(0);
                n = vparticules[i].get_a0() - delta_split;
                angleNormalise(n);
                V.emplace_back(Particule(vparticules[i].get_x0(),
                                         vparticules[i].get_y0(), n,
                                         vparticules[i].get_d0() * coef_split, 0)
                                   .move());
                V.back().set_c0(0);
                nbPart += 1;
            }
        }
        else
            V.push_back(vparticules[i].move());
    }
    return V;
}

void Jeu::draw_starting_point()
{
    Cart P(projection(Cart(xs, ys), Cercle(r_max)));
    drawCircle(Cercle(r_capture, P), RED);
    Pol M = opp(P.toPol());
    M.point.x = r_max;
    drawCircle(Cercle(r_viz, M.toCart()), BLACK, 0.7, PLEIN, BLACK);
}

void Jeu::updateJeu()
{
    // update particules
    
    vparticules = move(update_particules());

    // update faiseurs
    for (size_t i = 0; i < vfaiseurs.size(); ++i)
    {
        if (!impasse_faiseur(i))
        {
            vfaiseurs[i].move();
        }
    }

    // update score et statut
    score -= 1;
    set_status();
}

void Jeu::save(string file_name)
{
    ofstream fichier(file_name);
    if (!fichier)
    {
        cout << "Erreur lors de l'ouverture du fichier: " << file_name << endl;
        return;
    }
    fichier << score << endl
            << endl
            << nbPart << endl;
    for (auto i : vparticules)
    {
        fichier << "\t" << i.get_x0() << " " << i.get_y0() << " " << i.get_a0()
                << " " << i.get_d0() << " " << i.get_c0() << endl;
    }
    fichier << endl
            << nbFais << endl;
    for (auto i : vfaiseurs)
    {
        fichier << "\t" << i.get_x0() << " " << i.get_y0() << " " << i.get_a0()
                << " " << i.get_d0() << " " << i.get_r0() << " " << i.get_nbe0()
                << endl;
    }
    fichier << endl
            << nbArtic << endl;
    for (auto i : chaine.articulations())
    {
        fichier << "\t" << i.point.x << " " << i.point.y << endl;
    }
    fichier << endl
            << (mode == 0
                    ? "CONSTRUCTION"
                    : "GUIDAGE");
}
