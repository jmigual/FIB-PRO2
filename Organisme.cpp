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
		else --tam;
	}
}

void Organisme::reproduir_organisme(const Organisme &o1, const Organisme &o2)
{
    Arbre<Celula> a1 = o1.cels;
    Arbre<Celula> a2 = o2.cels;
    
    max_id = o1.max_id;
    
    // Primer fem la intersecció
    reproduir(cels, a1, a2, max_id, tamany);
    
    
}

void Organisme::reproduir(Arbre<Celula> &cels, Arbre<Celula> &a1,
                          Arbre<Celula> &a2, int &max_id, int &tamany) 
{
    if(not(a1.es_buit()) and not(a2.es_buit())) {
        Celula c = a1.arrel();
        
        if(c.activa or a2.arrel().activa) c.activa = true;
        else c.activa = false;
        
        Arbre<Celula> cels_e, cels_d;
        Arbre<Celula> a1_e, a1_d, a2_e, a2_d;
        
        a1.fills(a1_e, a1_d);
        a2.fills(a2_e, a2_d);
        
        reproduir(cels_e, a1_e, a2_e, max_id, tamany);
        reproduir(cels_d, a1_d, a2_d, max_id, tamany);
        cels.plantar(c, cels_e, cels_d);
        ++tamany;
    }
    else if (a1.es_buit() and not(a2.es_buit())) {
        ++max_id;
        busca_activa_gran(cels, a2, max_id, tamany);
        if (cels.es_buit()) --max_id;
    }
    else if (not(a1.es_buit()) and a2.es_buit()) {
        busca_activa_petit(cels, a1, tamany);
    }
}

void Organisme::busca_activa_gran(Arbre<Celula> &cels, Arbre<Celula> &a,
                                  int &max_id, int &tamany)
{
    if (not a.es_buit()) {
        Celula c = a.arrel();
        Arbre<Celula> a_e, a_d;
        
        a.fills(a_e, a_d);
        
        if (a_e.es_buit() and a_d.es_buit()) {
            if (c.activa) {
                ++tamany;
                c.id = max_id;
                cels.plantar(c, a_e, a_d);
            }
        }
        else {
            Arbre<Celula> cels_e, cels_d;
            
            ++max_id;
            busca_activa_gran(cels_e, a_e, max_id, tamany);
            if (cels_e.es_buit()) --max_id;
            
            ++max_id;
            busca_activa_gran(cels_d, a_d, max_id, tamany);
            if (cels_d.es_buit()) --max_id;
            
            if (c.activa or not(cels_e.es_buit()) or not(cels_d.es_buit())) {
                ++tamany;
                
                c.id = max_id;
                cels.plantar(c, cels_e, cels_d);
            }
        }
    }
}

void Organisme::busca_activa_petit(Arbre<Celula> &cels, Arbre<Celula> &a, 
                                   int &tamany)
{
    if (not(a.es_buit())) {
        Celula c = a.arrel();
        Arbre<Celula> a_e, a_d;
        
        a.fills(a_e, a_d);
        
        if (a_e.es_buit() and a_d.es_buit()) {
            if (c.activa) {
                ++tamany;
                cels.plantar(c, a_e, a_d);
            }
        }
        else {
            Arbre<Celula> cels_e, cels_d;
            
            busca_activa_petit(cels_e, a_e, tamany);
            busca_activa_petit(cels_d, a_d, tamany);
            
            if (c.activa or not(cels_e.es_buit()) or not(cels_d.es_buit())) {
                ++tamany;
                
                cels.plantar(c, cels_e, cels_d);
            }
        }
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

int Organisme::tam_intersec_recursiu(Arbre<Celula> &a1, Arbre<Celula> &a2)
{
	int res = 0;

    // Evaluem per cada branca de l'arbre, si hi ha una arrel sumem 1
	// com que ho fem recursivament tots els resultats es van sumant fins
	// a obtenir el resultat de la intersecció
	if(not(a1.es_buit()) and not(a1.es_buit())) {
		++res;
        Arbre<Celula> a1_e, a1_d, a2_e, a2_d;
		a1.fills(a1_e, a1_d);
		a2.fills(a2_e, a2_d);
		res += tam_intersec_recursiu(a1_e, a2_e);
		res += tam_intersec_recursiu(a1_d, a2_d);
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

void Organisme::llegir_organisme(int marca)
{
    cels.a_buit();
    llegir_rec(cels, marca, max_id);
}

void Organisme::llegir_rec(Arbre<Celula> &cels, int marca, int &max_id)
{
    int x = readint();
    bool activa = true;//readbool();
    
    if (x != marca) {
        if (x > max_id) max_id = x;
        
        Arbre<Celula> a_e, a_d;
        
        llegir_rec(a_e, marca, max_id);
        llegir_rec(a_d, marca, max_id);
        
        Celula c;
        c.id = x;
        c.activa = activa;
        
        cels.plantar(c, a_e, a_d);
    }
    
}

void Organisme::escriure_organisme() const
{
    Arbre<Celula> a = cels;
    escriure_rec(a);
}

void Organisme::escriure_rec(Arbre<Celula> &cels)
{
    if (not cels.es_buit()) {
        Celula c = cels.arrel();
        
        cout << c.id << " ";
        if (c.activa) cout << "true";
        else cout << "false";
        cout << endl;
        
        Arbre<Celula> a_e, a_d;
        
        cels.fills(a_e, a_d);
        cout << "------------" << endl;
        escriure_rec(a_e);
        escriure_rec(a_d);
    }    
}
