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
    
    int i = 0;
    
    /* INV: 0 <= i <= num, hi_cap = "hi ha espai per com a mínim un organisme
       més al vector 'V' que és on es guarden tots els organismes."
     */
    while (i < num and tamany != int(V.size()))
    {
        if (not Escollit[i] and not V[i].es_mort()) 
        {
            bool candidat = false;
            int j = i + 1;
            
            /* INV: i+1 <= j <= num, candidat = "s'ha trobat una parella V[j] 
               per a l'organisme V[i], tamany != V.size()"
             */
            while (j < num and not candidat)
            {
                if (not Escollit[j] and not V[j].es_mort() and
                    not Aparellat[i][j]) 
                {
                    candidat = true;
                    Escollit[i] = Escollit[j] = true;
                    Aparellat[i][j] = Aparellat[j][i] = true;
                }
                else ++j;
            }
            if (candidat)
            {
                
                // Sabem que l'identificador 'i' serà sempre més petit 
                // que l'id 'j' ja que és una de les condicions
                // d'inicialització
                if(V[tamany].reproduir_organisme(V[i], V[j])) 
                {
                    Rank.afegir_fill(i, j, tamany);
                    ++tamany;
                    ++fills;
                }
            }            
        }
        ++i;
    }
    return tamany != int(V.size());
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
    }
}

void ConjuntOrg::estat(int p) const
{
    if (p <= tamany) 
    {
        cout << p << " : ";
        V[p - 1].escriure_organisme(); 
    }
}
