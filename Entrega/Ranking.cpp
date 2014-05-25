/** @file Ranking.cpp
    @brief Implementació de la classe Ranking
*/

#include "Ranking.hpp"
#include <algorithm>

/***********************
 *    CONSTRUCTORES    *
 ***********************/

Ranking::Ranking(int M, int tam)
{
    Rank = vector<OrganRank> (M);
    Rel = vector< list<ParFill> > (M);
    tamany = tam;
    for (int i = 0; i < tam; ++i) Rank[i].id = i;
}

/***********************
 *    MODIFICADORES    *
 ***********************/

void Ranking::afegir_fill(int pare1, int pare2, int fill)
{
    ParFill aux;
    list<ParFill>::iterator it;
    
    // Afegim el pare2 a la llista del pare1
    aux.parella = pare2;
    aux.fill = fill;
    it = Rel[pare1].end();
    Rel[pare1].insert(it, aux);

    // Afegim el pare1 a la llista del pare2
    aux.parella = pare1;
    it = Rel[pare2].end();
    Rel[pare2].insert(it, aux);
    
    modificat = true;
    ++tamany;
}

bool Ranking::comp_rank(const OrganRank &a, const OrganRank &b)
{
    if (a.fills > b.fills) return true;
    else if (a.fills == b.fills) return a.id < b.id;
    else return false;    
}

/***************************
 *    ENTRADA / SORTIDA    *
 ***************************/

void Ranking::ranking()
{
    if (modificat)
    {
        modificat = false;
        for (int i = 0; i < tamany; ++i)
        {
            Rank[i].id = i;
            Rank[i].fills = Rel[i].size();
        }
        sort(Rank.begin(), Rank.begin() + tamany, comp_rank); 
    }
    for (int i = 0; i < tamany; ++i)
    {
        cout << Rank[i].id + 1 << " :";
        
        list<ParFill>::const_iterator it = Rel[Rank[i].id].begin();
        while (it != Rel[Rank[i].id].end()) 
        {
            cout << " " << (*it).parella + 1 << " " << (*it).fill + 1;
            ++it;
        }
        cout << endl;
    }
}
