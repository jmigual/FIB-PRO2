/** @file Ranking.cpp
    @brief Implementació de la classe Ranking
*/

#include "Ranking.hpp"

/***********************
 *    CONSTRUCTORES    *
 ***********************/

Ranking::Ranking(int M)
{
    Rank = vector<OrganRank> (M);
    Rel = vector< list<ParFill> > (M);
    tamany = 0;
}

/***********************
 *    MODIFICADORES    *
 ***********************/

void Ranking::afegir_fill(int pare1, int pare2, int fill)
{
    ParFill aux;
    list<ParFill>::iterator it;
    
    ++tamany;
    
    aux.parella = pare1;
    aux.fill = fill;
    it = Rel[pare1 - 1].end();
    Rel[pare1 - 1].insert(it, aux);

    aux.parella = pare2;
    it = Rel[pare2 - 1].end();
    Rel[pare2 - 1].insert(it, aux);
    
    // Aqui actualitzarem el vector Rank per generar el rànking
    // Primer afegim el fill a la última posició lliure del vector
    OrganRank f;
    f.id = fill;
    f.fills = 0;
    Rank[tamany] = f;
    // M'HE QUEDAT AUQÍ!!!!!!!!
    
}

/***************************
 *    ENTRADA / SORTIDA    *
 ***************************/

void Ranking::ranking() const
{}
