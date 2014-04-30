/** @file Organisme.cpp
	@brief Implementació de la classe Organisme
*/
#include "Organisme.hpp"

/***********************
 *    CONSTRUCTORES    *
 ***********************/

Organisme::Organisme() 
{
    Arbre<Celula> a1, a2;
    Celula c;
    c.id = 1;
    c.activa = true;
    tamany = 1;
    max_id = 1;
	mort = false;
    retallat = false;

    cels.plantar(c, a1, a2);
}

Organisme::~Organisme() {}


/***********************
 *    MODIFICADORES    *
 ***********************/

void Organisme::estirar_organisme() 
{
	if (not retallat) {
        Celula c = cels.arrel();
        Arbre<Celula> a1, a2;
        cels.fills(a1, a2);
		estirar_recursiu(a1, max_id, c, tamany);
		estirar_recursiu(a2, max_id, c, tamany);
        cels.plantar(c, a1, a2);
	}
}

void Organisme::estirar_recursiu(Arbre<Celula> &a, int &max_id, Celula c,
                                 int &tam) 
{
    Arbre<Celula> a1, a2;
    if (a.es_buit()) {
        ++max_id;
        ++tam;
        
        c.id = max_id;
        
        a.plantar(c, a1, a2);
    }
    else {
        c = a.arrel();
        a.fills(a1, a2);
        estirar_recursiu(a1, max_id, c, tam);
        estirar_recursiu(a2, max_id, c, tam);
        a.plantar(c, a1, a2);
    }
}

void Organisme::retallar_organisme() 
{
	if (not mort) {
        retallat = true;
        
        Celula c = cels.arrel();
        Arbre<Celula> a1, a2;
        cels.fills(a1, a2);
        
		if(a1.es_buit() and a2.es_buit()) {
			mort = true;
			tamany = 0;
		}
		else {
			retallar_recursiu(a1, tamany);
			retallar_recursiu(a2, tamany);
            cels.plantar(c, a1, a2);
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

void Organisme::reproduir_organisme(const Organisme &o1, const Organisme &o2)
{
    Arbre<Celula> a1 = o1.cels;
    Arbre<Celula> a2 = o2.cels;
    
    max_id = o1.max_id;
    
    // Primer fem la intersecció
    reproduir(cels, a1, a2, max_1, max_id);
    
}

void Organisme::reproduir(Arbre<Celula> &cels, Arbre<Celula> &a1,
                          Arbre<Celula> &a2, int &max_1, int &max_id) 
{
    if(not(a1.es_buit()) and not(a2.es_buit())) {
        Celula c = a1.arrel();
        
        if(c.activa or a2.arrel().activa) c.activa = true;
        else c.activa = false;
        
        Arbre<Celula> cels_e, cels_d;
        Arbre<Celula> a1_e, a1_d, a2_e, a2_d;
        
        a1.fills(a1_e, a1_d);
        a2.fills(a2_e, a2_d);
        
        reproduir(cels_e, a1_e, a2_e, max_id);
        reproduir(cels_d, a1_d, a2_d, max_id);
        cels.plantar(c, cels_e, cels_d);
    }
    else if (a1.es_buit() and not(a2.es_buit())) {
        Arbre<Celula> cels_e, cels_d;
        Arbre<Celula> a2_e, a2_d;
        
        a2.fills(a2_e, a2_d);
        if (hi_ha_activa(cels_e, a2_e, max_id))
    }
}


/*********************
 *    CONSULTORES    *
 *********************/

bool Organisme::compatibles(const Organisme &o) const 
{
	int comp = (tamany + o.tamany)/4;

    Arbre<Celula> aA = cels;
    Arbre<Celula> aB = o.cels;
    
    return (tam_intersec_recursiu(aA, aB) >= comp);
}

int Organisme::tam_intersec_recursiu(Arbre<Celula> &aA, Arbre<Celula> &aB)
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

int Organisme::consultar_tamany() const 
{
	return tamany;
}

bool Organisme::es_mort() const 
{ 
	return mort; 
}

/***************************
 *    ENTRADA / SORTIDA    *
 ***************************/

void Organisme::llegir_organisme()
{}

void Organisme::escriure_organisme() const
{}
