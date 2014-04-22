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
using namespace std;

#define MARCA 0

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

	// Entrem tots els organismes i els afegim al conjunt d'organismes
	for (int i = 0; i < N; ++i) {
		Organisme o;
		o.llegir_organisme();
		Conj.afegir_organisme(o);
	}

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
			stack<int> P;
			int a;
			cin >> a;
			while(a != MARCA) {
				P.push(a);
				cin >> a;
			}
			Conj.estirar(P);
		}

		// Opció per retallar un conjunt d'organismes
		else if (x == 2) {
			stack<int> P;
			int a;
			cin >> a;
			while(a != MARCA) {
				P.push(a);
				cin >> a;
			}
			Conj.retallar(P);
		}

		// Aplicar una ronda de reproducció a TOTS els organismes, actualitzar
		// el rànking i imprimir els fills nascuts a la ronda
		else if (x == 3) {
			if (not Conj.reproduir()) fi = 2;
		}

		// Obtenir el rànking de reproducció dels organismes 
		else if (x == 4) {
			Conj.ranking();
		}

		// Consultar l'estat d'un subconjunt d'organismes 
		else if (x == 5) {
			stack<int> P;
			int a;
			cin >> a;
			while(a != MARCA) P.push(a);
			Conj.estat(P);
		}
        cin >> x;
	}
}
