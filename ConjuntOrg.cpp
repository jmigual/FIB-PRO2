/** @file ConjuntOrg.cpp
	@brief Implementació de la classe ConjuntOrg
*/
#include "ConjuntOrg.hpp"
#include <algorithm>

ConjuntOrg::ConjuntOrg(int M) {
	V = vector<Organisme> (M);
    Rank = vector<OrganRank> (M);
    Rel = vector< stack<ParFill> > (M);
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

void ConjuntOrg::afegir_organisme(const Organisme &o) 
{
	if (tamany == int(V.size())) cout << "ERROR 1: El conjunt esta ple" << endl;
	else {
		V[tamany] = o;
		++tamany;
	}
}

void ConjuntOrg::estirar(stack<int> &P) 
{
	while (not P.empty()) {
		int x = P.top();
		V[x - 1].estirar_organisme();
		P.pop();
	}
}

void ConjuntOrg::retallar(stack<int> &P) 
{
	while(not P.empty()) {
		int x = P.top();
		V[x - 1].retallar_organisme();
		P.pop();
	}
}

bool ConjuntOrg::reproduir() 
{
    return true;    
}

int ConjuntOrg::consultar_tamany() const
{ return tamany; }

bool ConjuntOrg::morts() const
{
	bool mort = true;
	for (int i = 0; i < tamany; ++i) if (not V[i].es_mort()) mort = false;
	return mort;
}

void ConjuntOrg::ranking() const 
{}

void ConjuntOrg::estat(stack<int> &P) const
{}
