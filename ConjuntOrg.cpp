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
    Rank = vector<OrganRank> (M);
    Rel = vector< list<ParFill> > (M);
	Aparellat = vector< vector<bool> > (M, vector<bool> (M));  
	tamany = 0;
}

ConjuntOrg::ConjuntOrg(const ConjuntOrg &c) 
{
	V = c.V;
	Rank = c.Rank;
    Rel = c.Rel;
    Aparellat = c.Aparellat;
	tamany = c.tamany;
}

ConjuntOrg::~ConjuntOrg() {}

/***********************
 *    MODIFICADORES    *
 ***********************/

void ConjuntOrg::afegir_organisme(const Organisme &o) 
{
	if (tamany == int(V.size())) cout << "ERROR 1: El conjunt esta ple" << endl;
	else {
		V[tamany] = o;
		++tamany;
	}
}

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

void ConjuntOrg::ranking() const 
{}

void ConjuntOrg::estat(int p) const
{
    V[i - 1].escriure_organisme();
}
