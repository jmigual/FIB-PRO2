/** 
	@mainpage Pràctica de PRO2: Reproducció al laboratori
	En aquesta pràctica de PRO2 s'utilitza el disseny modular per a la
	interacció amb organismes de manera que puguin créixer, decréixer, 
	reproduir-se i morir especificat per l'usuari del programa. S'utilitza la
	classe <em>Organisme</em> i <em>ConjuntOrg</em>. També 
*/
/**	@file main.cpp
	@brief Programa principal per a la pràctica
*/

#include <iostream>
#include <stack>
#include "Organisme.hpp"
#include "ConjuntOrg.hpp"
#include "Ranking.hpp"
using namespace std;

#define MARCA -1

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
    Ranking Rank(M);

    // Cridem la funicó per llegir un conjunt d'organismes de la classe
    // ConjuntOrg
    Conj.llegir();

	// Variable per seleccionar la opció d'entrada
	int x;

	/* 	Variable de tipus int que quan sigui diferent de '0' farà
		acabar l'experiment, un número diferent de 0 indicarà el motiu pel
		qual s'acaba l'experiment:
		- 1 => Tots els organismes han mort
		- 2 => S'ha arribat al límit d'organismes
		- 3 => S'ha donat per finalitzat l'experiment manualment  */
	int fi = 0;
    cin >> x;
	while (x != MARCA and fi == 0) {
		// Opció per estirar un conjunt d'organismes
        if (x == 1) {
            int a = readint();

			while(a != MARCA) {
                Conj.estirar(a);
				cin >> a;
            }
		}

		// Opció per retallar un conjunt d'organismes
        else if (x == 2) {
            int a = readint();

			while(a != MARCA) {
                Conj.retallar(a);
				cin >> a;
            }
            if (Conj.morts()) fi = 1;
		}

		// Aplicar una ronda de reproducció a TOTS els organismes, actualitzar
		// el rànking i imprimir els fills nascuts a la ronda
		else if (x == 3) {
            int fills;
            if (not Conj.reproduir(RANKING, fills)) fi = 2;
            cout << fills << endl;
		}

		// Obtenir el rànking de reproducció dels organismes 
		else if (x == 4) {
            Rank.ranking();
		}

		// Consultar l'estat d'un subconjunt d'organismes 
        else if (x == 5) {
            int a = readint();

            while(a != MARCA) {
                Conj.estat(a);
                cin >> a;
            }
		}
        cin >> x;
	}

    // Instruccions per a la fi del programa
    if (fi == 1) {
        cout << "FI: Tots els organismes han mort" << endl;
    }
    if (fi == 2) {
        Rank.ranking();
        Conj.escriure_ultims(fills);
    }
}
