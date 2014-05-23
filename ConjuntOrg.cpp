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
    // Vector que és true si un organisme ha estat escollit per tal d'evitar
    // posar a reproduir dos organismes i que un d'ells ja s'estigui
    // aparellant en aquesta ronda
    vector<bool> Escollit(tamany, false);
    
    // Ens indicarà el número d'organismes que hi ha que es poden reproduir
    int num = tamany;
    
    // Posem a '0' la variable fills per si de cas té algun altre valor
    fills = 0;
    
    // Variable que ens servirà per saber si la reproducció s'ha pogut fer
    // correctament, en cas contrari la variable serà 'false'
    bool hi_cap = true;
    
    int i = 0;
    while (i < num and hi_cap)
    {
        if (not Escollit[i] and not V[i].es_mort()) 
        {
            bool candidat = false;
            int j = i + 1;
            while (j < num and not candidat)
            {
                if (not Aparellat[i][j] and not Escollit[j] and
                        not V[j].es_mort()) candidat = true;
                else ++j;
            }
            if (candidat)
            {
                Escollit[i] = Escollit[j] = true;
                Aparellat[i][j] = Aparellat[j][i] = true;
                
                // Sabem que l'identificador 'i' serà sempre més petit 
                // que l'id 'j' ja que és una de les condicions
                // d'inicialització
                // cout << "i: " << i+1 << " j: " << j+1 << endl;
                if(V[tamany].reproduir_organisme(V[i], V[j])) 
                {
                    Rank.afegir_fill(i, j, tamany);
                    ++tamany;
                    ++fills;
                    
                    // Si després de la ronda de reproducció ja no hi cap cap
                    // més organisme posem 'hi_cap' a 'false'
                    if (tamany == int(V.size())) hi_cap = false;
                }
            }            
        }
        ++i;
    }
    Rank.actualitzar();
    return hi_cap;
}

/*********************
 *    CONSULTORES    *
 *********************/

int ConjuntOrg::vius() const
{ 
    int cont = 0;
    
    for (int i = 0; i < tamany; ++i) 
    {
        if (not V[i].es_mort()) ++cont;
    } 
    
    return cont;
}

bool ConjuntOrg::morts() const
{
	bool mort = true;
	for (int i = 0; i < tamany; ++i) if (not V[i].es_mort()) mort = false;
	return mort;
}

int ConjuntOrg::consultar_tamany() const
{
    return tamany;
}

/***************************
 *    ENTRADA / SORTIDA    *
 ***************************/

void ConjuntOrg::llegir(int N, int marca)
{
    for (int i = 0; i< N; ++i) 
    {
        V[i].llegir_organisme(marca);
    }
    tamany = N;
}

void ConjuntOrg::escriure_ultims(int n)
{
    for (int i = tamany - n; i < tamany; ++i)
    {
        cout << i + 1 << " : ";
        V[i].escriure_organisme();
        V[i].escriure_bonic();
    }
}

void ConjuntOrg::estat(int p) const
{
    if (p <= tamany) 
    {
        cout << p << " : ";
        V[p - 1].escriure_organisme(); 
        V[p - 1].escriure_bonic();   
    }
}
