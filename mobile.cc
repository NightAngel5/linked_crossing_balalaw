#include "mobile.h"
#include <iostream>
using namespace std;


bool Particule::lecture(istringstream& data)
{
    if(data >> x0 >> y0 >> a0 >> d0 >> c0)  // lecture des attributs avec succès
	{
        if (Cercle(r_max).inclusion(Cart(x0,y0)))
        {
            cout<<message::particule_outside(x0,y0);
            std ::exit(EXIT_FAILURE); 
            return false;
        } else if  (!(-M_PI<=a0 && a0<=M_PI))
        {
            angleNormalise(a0);
        } else if (!(0<=d0 && d0<=d_max))
        {
            cout<<message::mobile_displacement(d0);
            std ::exit(EXIT_FAILURE);
            return false;
        } else if (!(0<=c0 && c0<time_to_split))
        {cout<<message::particule_counter(c0);
            std ::exit(EXIT_FAILURE);
            return false;
        }
        return true;
    } else
        return false;
	
}


bool Faiseur::lecture(istringstream &data, const vFaiseurs& V)
{
    if(data >> x0 >> y0 >> a0 >> d0 >> r0 >> nbe0)  // lecture des attributs avec succès
	{
        if (Cercle(r_max).inclusion(Cart(x0,y0)))
        {
            cout<<message::faiseur_outside(x0,y0);
            std ::exit(EXIT_FAILURE); 
            return false;
        } else if  (!(-M_PI<=a0 && a0<=M_PI))
        {
            angleNormalise(a0);
        } else if (!(0<=d0 && d0<=d_max))
        {
            cout<<message::mobile_displacement(d0);
            std ::exit(EXIT_FAILURE);
            return false;
        }else if (!(r_min_faiseur<=r0 && r0<=r_max_faiseur))
        {   cout<<message::faiseur_radius(r0);
            std ::exit(EXIT_FAILURE);
            return false;
        } else if (nbe0<=0)
        {   cout<<message::faiseur_nbe(nbe0);
            std ::exit(EXIT_FAILURE);
            return false;
        }
        if (!V.size()){
            if (collisionFaiseur(*this,V)){
                exit(EXIT_FAILURE);
            }
        }
        return true;
    } else
        return false;

}

std::vector<Cercle> Faiseur::constructionFaiseur() const
{   std::vector<Cercle> v1;
    Cart c(x0,y0);
    Pol pas (d0,a0);
    Pol pas1(opp(pas));
    for (unsigned i(0); i<nbe0 ; ++i)
    {
        if (Cercle(r_max).inclusion(Cercle(r0,c+pas1)))
        {
            v1.push_back(Cercle(r0,c+pas1));
            c+=pas1;
        }else
            pas1=reflect(c,pas,BACKWARD);
            pas=opp(pas);
            v1.push_back(Cercle(r0,c+pas1));
            c+=pas1;
    }
    return v1;
}

bool collisionFaiseur(const Faiseur & F1, const vFaiseurs V)
{
    std::vector<Cercle> v1(F1.constructionFaiseur());
    for (size_t i(0); i<V.size(); ++i)
    {
        std::vector<Cercle> v2(V[i].constructionFaiseur());
        if (impact(v1,v2))
        {
            return false;
        }
    }
    return true;
}

bool impact(std::vector<Cercle> v1, std::vector<Cercle> v2)
{
    for (size_t i(0); i<v1.size(); ++i)
    {
        for (size_t j(0); j<v2.size(); ++j)
        {
            if (intersection(v1[i],v2[j]))
            {
                return true;
            }
        }
    }
    return false;
}
