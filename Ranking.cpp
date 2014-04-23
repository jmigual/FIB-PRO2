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
}

/***********************
 *    MODIFICADORES    *
 ***********************/

void Ranking::afegir_fill(int pare1, int pare2, int fill)
{
    ParFill aux;
    list<ParFill>::iterator it;

    aux.parella = pare1;
    aux.fill = fill;
    it = Rel[pare1 - 1].end();
    Rel[pare1 - 1].insert(it, aux);

    aux.parella = pare2;
    it = Rel[pare2 - 1].end();
    Rel[pare2 - 1].insert(it, aux);
}

