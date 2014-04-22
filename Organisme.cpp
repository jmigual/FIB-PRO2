/** @file Organisme.cpp
	@brief Implementació de la classe Organisme
*/
#include "Organisme.hpp"

Organisme::Organisme() 
{
	fills = 0;
	tamany = 0;
}

Organisme::Organisme(const Organisme &o) 
{
	fills = o.fills;
	tamany = o.tamany;
	arbre = o.arbre;
}

Organisme::~Organisme() {}

void Organisme::estirar_organisme() 
{
	Celula c = arbre.arrel();
	Arbre<Celula> a1, a2;
	arbre.fills(a1, a2);
	estirar_recursiu(a1, max_id, c, tamany);
	estirar_recursiu(a2, max_id, c, tamany);
	arbre.plantar(c, a1, a2);
}

void Organisme::estirar_recursiu(Arbre<Celula> &a, int &max_id, Celula c, 
int &tam) 
{
	if (a.es_buit()) {
		if (not c.dividida) {
			++max_id;
			++tam;
			c.id = max_id;
			c.dividida = false;
			Arbre<Celula> a1;
			a.plantar(c, a1, a1);
		}
	}
	else {
		Celula c = a.arrel();
		Arbre<Celula> a1, a2;
		a.fills(a1, a2);
		estirar_recursiu(a1, max_id, c, tam);
		estirar_recursiu(a2, max_id, c, tam);
		c.dividida = true;
		a.plantar(c, a1, a2);
	}
}

void Organisme::retallar_organisme() 
{
	if (not mort) {
		Celula c = arbre.arrel();
		Arbre<Celula> a1, a2;
		arbre.fills(a1, a2);
		if(a1.es_buit() and a2.es_buit()) {
			mort = true;
			tamany = 0;
		}
		else {
			retallar_recursiu(a1, tamany);
			retallar_recursiu(a2, tamany);
			arbre.plantar(c, a1, a2);
		}
	}
}

void Organisme::retallar_recursiu(Arbre<Celula> &a, int &tam) 
{
	if(not a.es_buit()) {
		Arbre<Celula> a1, a2;
		Celula c = a.arrel();
		a.fills(a1, a2);

		// Si algun dels dos fills no està buit vol dir que la cèl·lula encara
		// no s'ha d'eliminar. Si ja no té cap fill no tornem a plantar
		// l'arbre i haurem eliminat la cèl·lula.
		if(not(a1.es_buit() and a2.es_buit())) {
			retallar_recursiu(a1, tam);
			retallar_recursiu(a2, tam);
			a.plantar(c, a1, a2);
		}
		else {
			--tam;
		}
	}
}

void Organisme::afegir_fill() 
{
	++fills;
}

int Organisme::consultar_fills() const 
{
	return fills;
}

bool Organisme::compatibles(const Organisme &o) const 
{
	int comp = (tamany + o.tamany)/4;

	Arbre<Celula> aA = arbre;
	Arbre<Celula> aB = o.arbre;
	// Variable amb la que es mirarà el tamany de l'intersecció
	int intersec = intersec_recursiu(aA, aB);
	return intersec >= comp;
}

int Organisme::intersec_recursiu(Arbre<Celula> &aA, Arbre<Celula> &aB) 
{
	int res = 0;

	// Evaluem per cada branca de l'arbre, si hi ha una arrel sumem 1
	// com que ho fem recursivament tots els resultats es van sumant fins
	// a obtenir el resultat de la intersecció
	if(not(aA.es_buit()) and not(aB.es_buit())) {
		++res;
		Arbre<Celula> aA1, aA2, aB1, aB2;
		aA.fills(aA1, aA2);
		aB.fills(aB1, aB2);
		res += intersec_recursiu(aA1, aB1);
		res += intersec_recursiu(aA2, aB2);
	}
	return res;
}

Organisme Organisme::reproduir_organisme(const Organisme &o) const 
{
	Organisme res;
    return res;
}

int Organisme::consultar_tamany() const 
{
	return tamany;
}

bool Organisme::es_mort() const 
{ 
	return mort; 
}
