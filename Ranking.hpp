/**	@file Ranking.hpp
 *  @brief Especificació de la classe Ranking
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
     *  @brief Estructura que conté l'identificador d'un organisme i el
     *  nombre de fills que ha tingut
     */
    struct OrganRank
    {
        /** @var id
         *  @brief Identificador de l'organisme
         */
        int id;

        /** @var fills
         *  @brief Nombre de fills que ha tingut l'organisme
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
    
    /** @brief Vector que utilitzarem per generar i guardar el rànking */
    vector<OrganRank> Rank;

    /** @brief Vector per saber quins fills ha tingut cada organisme i amb qui
     *  els ha tingut
     */
    vector< list<ParFill> > Rel;
    
    /** @brief Variable que utilitzarem per saber el nombre d'elements vàlids
     *  que hi ha als vectors
     */
    int tamany;
    
    /** @brief Variable que ens indica si el rànking ha estat modificat i
     *  necessitarem tornar a generar-lo.
     */
    bool modificat;
    
    /** @brief Funció booleana que ens dona les condicions per ordenar el 
     *  rànking
     */
    static bool comp_rank(const OrganRank &a, const OrganRank &b);

public:

    /***********************
     *    CONSTRUCTORES    *
     ***********************/
    
    /** @brief Constructora que afegeix un nombre d'organismes per defecte
     *  \pre 0 <= n < M
     *  \post Al rànking s'hi contemplen 'n' organismes
     */
    Ranking(int M, int n);

    /***********************
     *    MODIFICADORES    *
     ***********************/

    /** @brief Modificadora que afegeix els pares de un organisme per poder
     *  fer el rànking
     *  \pre Cert.
     *  \post S'han afegit l'ID dels pares i del fill que han tingut al P.I. i
     *  al rànking s'hi contempla un organisme més.
     */
    void afegir_fill(int pare1, int pare2, int fill);
    
    /** @brief Genera de nou el vector Rank i l'ordena
     *  \pre Cert
     *  \post Rànking ha estat regenerat.
     */
    //void actualitzar();
    

    /***************************
     *    ENTRADA / SORTIDA    *
     ***************************/

    /** @brief Funció que imprimeix el rànking
     *  \pre S'ha cridat la funció 'afegir_fill' del P.I. com a mínim un cop
     *  \post Pel canal estàndard de sortida s'ha imprés el rànking de
     *  reproducció dels organismes
     */
    void ranking();
};

#endif // RANKING_HPP
