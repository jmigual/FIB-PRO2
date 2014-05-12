/**	@file Organisme.hpp
	@brief Especificació de la classe Organisme
*/
#ifndef ORGANISME_HPP
#define ORGANISME_HPP

#include "Arbre.hpp"

/**	@class Organisme
	@brief És un conjunt de cèl·lules posades en un arbre
*/
class Organisme 
{    
private:

    /**	@struct Celula
     *  @brief Element bàsic de cada organisme té un identificador i un estat
     *  (activa o passiva).       
     */
    struct Celula
    {
        /** @var id
         *  @brief És el número que identifica la cèl·lula 	
         */
        int id;
        /** @var activa
         *  @brief Booleà que indica si la cèl·lula és activa o no ('true' si 
         *  és activa i 'false' si no ho és
         */
        bool activa;
    };

	/** @brief Arbre on estan guardades totes les cèl·lules de l'organisme */
    Arbre<Celula> cels;

	/** @brief Variable que ens indica si un organisme ha estat retallat
	 *  'true' si s'ha retallat 'false' si no s'ha fet.
	 */
    bool retallat;

	/** @brief Variable que indica el tamany de l'organisme */
	int tamany;

	/**	@brief Identificador màxim de les cèl·lules de l'organisme */
	int max_id;

    /**	@brief Funció recursiva per estirar un organisme
     *  \pre 'c' és una cèl·lula vàlida, max_id està inicialitzat i no
     *  \post Totes les cèl·lules que no s'havien dividit s'han dividit
	 */
	static void estirar_recursiu(Arbre<Celula> &a, int &max_id, Celula c,
    int &tamany);

	/** @brief Funció per retallar l'arbre d'un organisme
	 *  \pre L'organisme no està mort
	 *  \post Totes les cèl·lules que no tenen cap filla han estat eliminades
	 */
    static void retallar_recursiu(Arbre<Celula> &a, int &tamany, int &max_id);

	/** @brief Funció per calcular el tamany de la intersecció de dos arbres
	 *  de manera recursiva
	 *  \pre Cert
	 *  \post Retorna el nombre d'elements de l'arbre resultant de la
	 *  intersecció dels dos arbres 'a1' i 'a2'
	 */
	static int tam_intersec_recursiu(Arbre<Celula> &a1, Arbre<Celula> &a2);
    
    /** @brief Funció que afegeix l'arbre intersecció de dos arbres de
     *  organismes a l'àrbre 'cels'
     *  \pre Cert
     *  \post L'arbre cels ha passat a tenir la intersecció dels arbres dels
     *  dos organismes
     */
    static void reproduir(Arbre<Celula> &cels, Arbre<Celula> &a1, 
                          Arbre<Celula> &a2, int &max_id, int &tamany);
    
    /** @brief Funció que busca si hi ha una cèl·lula activa a l'arbre 'a' i 
     *  si la troba l'afegeix a 'cels' incrementant max_id en el procés de
     *  fer-ho i tamany, per conectar la cèl·lula ho fa mitjançant les que 
     *  hi hagi pel camí, siguin actives o passives.
     *  \pre max_id i tamany són enters majors que 0
     *  \post Les cèl·lules actives de l'arbre 'a' han estat afegides a
     *  l'arbre 'cels' en la mateixa posició i també s'ha incrementat 'max_id'
     *  i 'tamany'.
     */
    static void busca_activa_gran(Arbre<Celula> &cels, Arbre<Celula> &a,
                                  int &max_id, int &tamany);
    /** @brief Funció que busca si hi ha una cèl·lula activa a l'arbre 'a' i 
     *  si la troba l'afegeix a 'cels' conectant-la amb les cèl·lules que
     *  siguin necessàries siguin passives o actives.
     *  \pre Tamany és un enter major que 0
     *  \post Si 'a' conté una cèl·lula activa, aquesta ha passat a formar
     *  part de 'cels' en la mateixa posició en la que ho està a 'a'
     */
    static void busca_activa_petit(Arbre<Celula> &cels, Arbre<Celula> &a,
                                   int &tamany);
    
    /** @brief Funció recursiva que ens permetrà llegir l'arbre de cèl·lules
     *  d'un organisme.
     *  \pre A marca hi ha un enter que ens dona una marca per saber quan
     *  s'acaba la introducció de dades. Al canal estàndard d'entrada hi ha
     *  totes les cèl·lules que es volen introduir a l'arbre en preordre.
     *  \post 'cels' ha passat a estar tal i com s'ha especificat pel canal
     *  estàndard d'entrada.
     */
    static void llegir_rec(Arbre<Celula> &cels, int marca, int &max_id,
                           int &tamany);
    
    /** @brief Funció recursiva que escriurà un arbre de forma recursiva
     *  \pre 'cels' no és un arbre buit.
     *  \post L'arbre 'cels' s'ha escrit pel canal estàndard de sortida en 
     *  preordre
     */
    static void escriure_rec(Arbre<Celula> &cels);

public: 
    /***********************
     *    CONSTRUCTORES    *
     ***********************/

    /**	@brief Constructora per defecte
     *  <p>S'executa automàticament al declarar un organisme</p>
     *
     *  \pre Cert
     *  \post El resultat és amb una cèl·lula activa i tamany '0'
     */
	Organisme();

	/** @brief Destructora per defecte */
	~Organisme();

    /***********************
     *    MODIFICADORES    *
     ***********************/

    /**	@brief Modificadora que fa créixer l'organisme
     *  \pre L'organisme ha de tenir una cèl·lula o més
     *  \post Fisiona totes les cèl·lules de l'organisme que no s'hagin
     *  fisionat
     */
	void estirar_organisme();

	/** @brief Modificadora que elimina totes les cèl·lules que no tenen cap
	 *  fill
	 *  \pre L'organisme ha de tenir una cèl·lula o més
	 *  \post Totes les cèl·lules que no tenien cap fill han estat eliminades
	*/
	void retallar_organisme();

    /** @brief Modificadora que modifica l'organisme implícit per tal que
     *  es converteixi en un fill dels altres dos organismes
     *  \pre 'o1' i 'o2' han de ser dos organismes que no estiguin morts i
     *  han de ser compatibles entre ells, l'id de 'o1' és més
     *  petit que l'id de 'o2'
     *  \post L'organisme implícit ha passat a ser un organisme que és fill
     *  de 'o1' i 'o2'
     */
    void reproduir_organisme(const Organisme &o1, const Organisme &o2);


    /*********************
     *    CONSULTORES    *
     *********************/

    /** @brief Consultora que retorna si dos organismes són compatibles o no
     *  \pre Cert
     *  \post Retorna un booleà que és 'true' si són compatibles i 'false' si
     *  no ho són
     */
	bool compatibles(const Organisme &o) const;

    /** @brief Consultora que retorna el tamany de l'organisme
     *  \pre Cert
     *  \post Retorna un int amb el tamany de l'organisme
     */
	int consultar_tamany() const;

    /** @brief Consultora que ens diu si el paràmetre implícit està mort
     *  \pre Cert
     *  \post Retorna un booleà que és 'true' si el paràmetre implícit és mort
     */
	bool es_mort() const;


    /***************************
     *    ENTRADA / SORTIDA    *
     ***************************/

    /**	@brief Funció per llegir un organisme
     *  \pre A la variable 'marca' es passa la marca que s'utilitzarà per
     *  saber el final de l'entrada
     *  \post El paràmetre implícit ha passat a ser tal i com se li han donat
     *  pel canal estàndard d'entrada. El que hi havia abans en aquest
     *  organisme ha estat eliminat.
     */
	void llegir_organisme(int marca);

    /** @brief Funció per escriure un organisme
     *  \pre L'organisme no ha d'estar mort
     *  \post Escriu l'arbre que forma l'organisme, no s'escriu si les
     *  cèl·lules són actives o passives
     */
	void escriure_organisme() const;
};

#endif
