/**	@file Ranking.hpp
 *  @brief Especificació de la classe Ranking
 */
#ifndef RANKING_HPP
#define RANKING_HPP

#include <list>
#include <vector>


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
    /** @var parella
     *  @brief Retorna l'identificador del pare
     */
    int parella;

    /** @var fill
     *  @brief Retorna l'identificador del fill
     */
    int fill;
};

/**********************************************************/

/** @class Ranking
 *  @brief Classe Ranking per poder imprimir el ranking dels organismes
 */
class Ranking {
private:

    /** @brief Vector que utilitzarem per generar i guardar el rànking */
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
     *  fer el rànking
     *  \pre Cert
     *  \post S'han afegit l'ID dels pares i dels fills al Ranking
     */
    void afegir_fill(int pare1, int pare1, int fill);

    /***************************
     *    ENTRADA / SORTIDA    *
     ***************************/

    /** @brief Funció que imprimeix el rànking
     *  \pre Hi ha com a mínim un organisme
     *  \post Pel canàl estàndard de sortida s'ha imprès el rànking de
     *  reproducció dels organismes
     */
    void ranking() const;
};

#endif // RANKING_HPP
