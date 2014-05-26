/** 
	@mainpage Pràctica de PRO2: Reproducció al laboratori
	En aquesta pràctica de PRO2 s'utilitza el disseny modular per a la
	interacció amb organismes de manera que puguin créixer, decréixer, 
    reproduir-se i morir especificat per l'usuari del programa. S'utilitza les
    classes <em>Organisme</em>, <em>ConjuntOrg</em> i <em>Ranking</em>.
*/
/**	@file main.cpp
	@brief Programa principal per a la pràctica
*/

#include "utils.PRO2"
#include "Organisme.hpp"
#include "ConjuntOrg.hpp"
#include "Ranking.hpp"
using namespace std;

/** @brief Marca que utilitzarem per saber quan s'acaba l'experiment */
#define MARCA -6

/** @brief Marca que s'utilitzarà per saber quan acaba un arbre a l'hora
 *  d'introduir l'arbre d'un organisme
 */
#define MARCA_ORG 0

/**	@brief Programa principal de la <em>Pràctica de PRO2</em>.
*/
int main() 
{
	// M És el màxim històric permés
	// N És el nombre d'organismes inicials
	int N, M;
	cin >> N >> M;

	// Conjunt que ens permetrà guardar tots els organismes existents
	ConjuntOrg Conj(M);
    Ranking Rank(M, N);
    
    // Cridem la funicó per llegir un conjunt d'organismes de la classe
    // ConjuntOrg
    Conj.llegir(N, MARCA_ORG);

	// Variable per seleccionar la opció d'entrada
	int x;

	/* 	Variable de tipus int que quan sigui diferent de '0' farà
		acabar l'experiment, un número diferent de 0 indicarà el motiu pel
		qual s'acaba l'experiment:
		- 1 => Tots els organismes han mort
		- 2 => S'ha arribat al límit d'organismes  */
	int fi = 0;
    int fills;
    cin >> x;
	while (x != MARCA and fi == 0) {
		// Opció per estirar un conjunt d'organismes
        if (x == -1) {
            int a;
            
            cin >> a;
            for (int i = 0; i < a; ++i) {
                int b;
                cin >> b;
                Conj.estirar(b);
            }
		}

		// Opció per retallar un conjunt d'organismes
        else if (x == -2) {
            int a;
            
            cin >> a;
            for (int i = 0; i < a; ++i) {
                int b;
                cin >> b;
                Conj.retallar(b);
            }
            if (Conj.morts()) fi = 1;
		}

		// Aplicar una ronda de reproducció a TOTS els organismes, actualitzar
		// el rànking i imprimir els fills nascuts a la ronda
		else if (x == -3) {
            cout << "RONDA DE EMPAREJAMIENTOS" << endl;
            
            if (not Conj.reproduir(Rank, fills)) {
            	fi = 2;
            }
            cout << "Nuevos organismos : " << fills << endl;
            cout << endl;
		}

		// Obtenir el rànking de reproducció dels organismes 
		else if (x == -4) {
            cout << "RANKING" << endl;
            Rank.ranking();
            cout << endl;
		}

		// Consultar l'estat d'un subconjunt d'organismes 
        else if (x == -5) {
            int a;
            cin >> a;
            
            cout << "ORGANISMOS" << endl;
            
            for (int i = 0; i < a; ++i) {
                int b;
                cin >> b;
                Conj.estat(b);
            }
            cout << endl;
		}
        cin >> x;
	}
    cout << "FIN" << endl;
    cout << endl;
    cout << "Organismos en total : " << Conj.consultar_tamany() << endl;
    cout << "Organismos vivos : " << Conj.vius() << endl;
    
    // Instruccions per a la fi del programa quan s'ha arribat al límit del
    // conjunt
    if (fi == 2) {
        cout << endl;
        cout << "ORGANISMOS" << endl;
        Conj.escriure_ultims(fills);
        
        cout << endl;
        
        cout << "RANKING" << endl;
        Rank.ranking();
    }
}
