/** @file ConjuntOrg.hpp
	@brief Especificació de la classe ConjuntOrg
*/
#ifndef CONJUNT_ORG
#define CONJUNT_ORG

#include <stack>
#include <list>
#include <vector>
#include "Organisme.hpp"
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

/** @class ConjuntOrg
	@brief És un conjunt d'organismes
*/
class ConjuntOrg 
{
private:
	/** @brief Vector on es guardaran tots els organismes */
	vector<Organisme> V;
	/** @brief Vector que utilitzarem per generar i guardar el rànking */
	vector<OrganRank> Rank;
    /** @brief Vector per saber quins fills ha tingut cada organisme i amb qui
        els ha tingut */
    vector< list<ParFill> > Rel;
	/** @brief Matriu que ens dirà quins organismes s'han aparellat i amb qui
		ho han fet */
	vector< vector<bool> > Aparellat;
	/** @brief Variable que ens dona el número de organismes que hi ha al
		vector */
	int tamany;
public:
	/**********************
	*    CONSTRUCTORES    *
	**********************/

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

		Esborra automàticament l'objecte al sortir d'un àmbit de visibilitat
	*/
	~ConjuntOrg();

	/**********************
	*    MODIFICADORES    *
	**********************/

	/** @brief Modificadora per afegir un organisme al conjunt
		\pre El conjunt no està ple
		\post L'organisme 'o' ha estat afegit al conjunt
	*/
	void afegir_organisme(const Organisme &o);
	/** @brief Modificadora per estirar un subconjunt d'organismes
		\pre Es passa una pila amb identificadors d'organismes vàlids
		\post Els organismes que tenen l'identificador de la pila han estat 
		estirats
	*/
	void estirar(stack<int> &P);
	/** @brief Modificadora per retallar un subconjunt d'organismes
		\pre Es passa una pila amb identificadors d'organismes vàlids
		\post Els organismes amb l'identificador de la pila han estat
		retallats
	*/
	void retallar(stack<int> &P);
	/** @brief Modificadora que fa una ronda de reproducció dels organismes
		<p>Si la reproducció no s'ha pogut realitzar correctament es retorna
		un booleà 'false', en cas contrari retorna 'true'</p>
		\pre Cert
		\post Tots els organismes que poden s'han reproduit un cop com a màxim
		a més a més s'imprimeixen els fills nous de la ronda
	*/
	bool reproduir();

	/********************
	*    CONSULTORES    *
	********************/

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

	/**************************
	*    ENTRADA / SORTIDA    *
	**************************/

	/** @brief Imprimeix el rànking dels organismes
		\pre Cert
		\post S'imprimeix per el canal estàndard de sortida el rànking de la 
		reproducció dels organismes
	*/
	void ranking() const;
	/** @brief Imprimeix l'estat d'un subconjunt d'organismes
		\pre Cert
		\post S'imprimeix l'estat de cada organisme que es passa a la pila
	*/
	void estat(stack<int> &P) const;
};

#endif

