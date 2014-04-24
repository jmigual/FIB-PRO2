/** @file ConjuntOrg.cpp
	@brief Implementació de la classe ConjuntOrg
*/
#include "ConjuntOrg.hpp"
#include <algorithm>

/***********************
 *    CONSTRUCTORES    *
 ***********************/

ConjuntOrg::ConjuntOrg(int M) {
	V = vector<Organisme> (M);
	Aparellat = vector< vector<bool> > (M, vector<bool> (M));  
	tamany = 0;

    //Posem true a la diagonal per tal que no s'aparelli mai am si mateix
    for (int i = 0; i < M; ++i) Aparellat[i][i] = true;
}

ConjuntOrg::ConjuntOrg(const ConjuntOrg &c) 
{
	V = c.V;
    Aparellat = c.Aparellat;
	tamany = c.tamany;
}

ConjuntOrg::~ConjuntOrg() {}

/***********************
 *    MODIFICADORES    *
 ***********************/

void ConjuntOrg::estirar(int p)
{
    V[p - 1].estirar_organisme();
}

void ConjuntOrg::retallar(int p)
{
    V[p - 1].retallar_organisme();
}

bool ConjuntOrg::reproduir(Ranking &Rank, int &fills)
{
    vector<bool> Escollit(tamany, false);
    for (int i = 0; i < tamany; ++i)
    {
        if (not Escollit[i]) 
        {
            bool candidat = false;
            int j = 0;
            while (j < tamany and not candidat)
            {
                if (not Aparellat[i][j]) candidat = true;
                else ++j;
            }
            if (candidat and V[i].compatibles(V[j]) {
				Organisme o;
				o.reproduir_organisme(V[i], V[j])
            
        }
    }
    return true;
}

/*********************
 *    CONSULTORES    *
 *********************/

int ConjuntOrg::consultar_tamany() const
{ return tamany; }

bool ConjuntOrg::morts() const
{
	bool mort = true;
	for (int i = 0; i < tamany; ++i) if (not V[i].es_mort()) mort = false;
	return mort;
}

/***************************
 *    ENTRADA / SORTIDA    *
 ***************************/

void ConjuntOrg::escriure_ultims(int n)
{

}

void ConjuntOrg::llegir()
{}

void ConjuntOrg::estat(int p) const
{
    V[p - 1].escriure_organisme();
}
