#ifndef RANKING_HPP
#define RANKING_HPP

#include <list>
#include "utils.PRO2"

/** @struct OrganRank
    @brief Tipus de dades per poder fer el rànking
*/
struct OrganRank
{
    /** @var id
        @brief Identificador de l'organisme
    */
    int id;

    /** @var fills
        @brief Número de fills que ha tingut l'organisme
    */
    int fills;
};

/**********************************************************/

/** @struct ParFill
    @brief Estructura per poder saber quins fills ha tingut un organisme i amb
    qui els ha tingut
*/
struct ParFill
{
    /** @var pare
        @brief Retorna l'identificador del pare
    */
    int pare;

    /** @var fill
        @brief Retorna l'identificador del fill
    */
    int fill;
};

/**********************************************************/

class Ranking {
private:

    /** @brief Vector que utilitzarem per generar i guardar el rànking */
    vector<OrganRank> Rank;

    /** @brief Vector per saber quins fills ha tingut cada organisme i amb qui
        els ha tingut */
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
};

#endif // RANKING_HPP
