/** @file ConjuntOrg.hpp
	@brief Especificació de la classe ConjuntOrg
*/
#ifndef CONJUNTORG_HPP
#define CONJUNTORG_HPP

#include <list>
#include <vector>
#include "Organisme.hpp"
#include "Ranking.hpp"

/** @class ConjuntOrg
	@brief És un conjunt d'organismes
*/
class ConjuntOrg 
{
private:
	/** @brief Vector on es guardaran tots els organismes */
	vector<Organisme> V;

	/** @brief Matriu que ens dirà quins organismes s'han aparellat i amb qui
		ho han fet */
	vector< vector<bool> > Aparellat;

	/** @brief Variable que ens dona el número de organismes que hi ha al
		vector */
	int tamany;
public:
    /***********************
     *    CONSTRUCTORES    *
     ***********************/

	/**	@brief Constructora per defecte
		<p>S'executa automàticament al declarar un conjunt</p>
		\pre M ha de ser un nombre enter més gran que '0'
		\post El resultat és un conjunt d'organismes de tamany M però buit
	*/
	ConjuntOrg(int M);

	/** @brief Constructora per còpia
		\pre Cert
		\post El paràmetre implícit passa a ser igual al afegit a la funció
	*/
	ConjuntOrg(const ConjuntOrg &C);

	/** @brief Destructora per defecte
        <p>Esborra automàticament l'objecte al sortir d'un àmbit de
        visibilitat</p> */
	~ConjuntOrg();

    /***********************
     *    MODIFICADORES    *
     ***********************/

	/** @brief Modificadora per estirar un subconjunt d'organismes
		\pre Es passa una pila amb identificadors d'organismes vàlids
		\post Els organismes que tenen l'identificador de la pila han estat 
		estirats
	*/
    void estirar(int p);

	/** @brief Modificadora per retallar un subconjunt d'organismes
		\pre Es passa una pila amb identificadors d'organismes vàlids
		\post Els organismes amb l'identificador de la pila han estat
		retallats
	*/
    void retallar(int p);

	/** @brief Modificadora que fa una ronda de reproducció dels organismes
		<p>Si la reproducció no s'ha pogut realitzar correctament es retorna
		un booleà 'false', en cas contrari retorna 'true'</p>
		\pre Cert
		\post Tots els organismes que poden s'han reproduit un cop com a màxim
		a més a més s'imprimeixen els fills nous de la ronda
	*/
    bool reproduir(Ranking &rank, int &fills);

    /*********************
     *    CONSULTORES    *
     *********************/

	/** @brief Consultora que retorna el nombre d'organismes del conjunt
		\pre Cert
		\post Es retorna el nombre d'organismes (vius o morts) que hi ha al
		conjunt
	*/
	int consultar_tamany() const;

	/** @brief Consultora que ens diu si els organismes estan morts
		<p>Si tots els organismes del Conjunt estan morts es retorna <em>
		true</em> i en cas contrari es retorna <em>false</em>
		\pre Cert
		\post Es retorna un booleà amb l'estat dels organismes
	*/
	bool morts() const;

    /***************************
     *    ENTRADA / SORTIDA    *
     ***************************/
    /** @brief Escriu els últims 'n' elements del conjutn
    	\pre Hi ha com a mínim 'n' elemnts
    	\post Pel canal estàndard de sortida s'escriuen els 'n' últims
    	elements
    */
    void escriure_ultims(int n);
    /** @brief Llegeix un conjunt d'organismes
        \pre Cert
        \post Es llegeixen els organismes inicials del conjunt
    */
    void llegir();

	/** @brief Imprimeix l'estat d'un subconjunt d'organismes
		\pre Cert
		\post S'imprimeix l'estat de cada organisme que es passa a la pila
	*/
    void estat(int p) const;
};

#endif

