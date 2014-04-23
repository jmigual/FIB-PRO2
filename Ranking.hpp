/**	@file Ranking.hpp
 *  @brief Especificaci√≥ de la classe Ranking
 */
#ifndef RANKING_HPP
#define RANKING_HPP

#include <list>
#include <vector>
#include "utils.PRO2"


/** @class Ranking
 *  @brief Classe Ranking per poder imprimir el ranking dels organismes
 */
class Ranking {
private:

    /** @struct OrganRank
     *  @brief Tipus de dades per poder fer el r√ nking
     */
    struct OrganRank
    {
        /** @var id
         *  @brief Identificador de l'organisme
         */
        int id;

        /** @var fills
         *  @brief N√∫mero de fills que ha tingut l'organisme
         */
        int fills;
    };

    /** @struct ParFill
     *  @brief Estructura per poder saber quins fills ha tingut un organisme i
     *  amb qui els ha tingut
     */
    struct ParFill
    {
        /** @var parella
         *  @brief Retorna l'identificador del pare
         */
        int parella;

        /** @var fill
         *  @brief Retorna l'identificador del fill
         */
        int fill;
    };
    
    /** @brief Vector que utilitzarem per generar i guardar el r√ nking */
    vector<OrganRank> Rank;

    /** @brief Vector per saber quins fills ha tingut cada organisme i amb qui
     *  els ha tingut
     */
    vector< list<ParFill> > Rel;

public:

    /***********************
     *    CONSTRUCTORES    *
     ***********************/

    /** @brief Constructora per defecte
     *  \pre Cert
     *  \post Es crea un ranking de tamany 'M'
     */
    Ranking(int M);

    /***********************
     *    MODIFICADORES    *
     ***********************/

    /** @brief Modificadora que afegeix els pares de un organisme per poder
     *  fer el r√ nking
     *  \pre Cert
     *  \post S'han afegit l'ID dels pares i dels fills al Ranking
     */
    void afegir_fill(int pare1, int pare2, int fill);

    /***************************
     *    ENTRADA / SORTIDA    *
     ***************************/

    /** @brief Funci√≥ que imprimeix el r√ nking
     *  \pre Hi ha com a m√≠nim un organisme
     *  \post Pel can√ l est√ ndard de sortida s'ha impr√®s el r√ nking de
     *  reproducci√≥ dels organismes
     */
    void ranking() const;
};

#endif // RANKING_HPP
