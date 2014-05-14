/** @file Organisme.cpp
	@brief Implementació de la classe Organisme
*/
#include "Organisme.hpp"
#include <cmath>

/***********************
 *    CONSTRUCTORES    *
 ***********************/

Organisme::Organisme() 
{
    tamany = 0;
    max_id = 0;
    retallat = false;
    cels.a_buit();
}

Organisme::~Organisme() 
{}


/***********************
 *    MODIFICADORES    *
 ***********************/

void Organisme::estirar_organisme() 
{
	if (not retallat and not cels.es_buit()) {
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
    if (a.es_buit()) 
    {
        ++max_id;
        ++tam;
        
        c.id = max_id;
        
        a.plantar(c, a1, a2);
    }
    else 
    {
        c = a.arrel();
        a.fills(a1, a2);
        estirar_recursiu(a1, max_id, c, tam);
        estirar_recursiu(a2, max_id, c, tam);
        a.plantar(c, a1, a2);
    }
}

void Organisme::retallar_organisme() 
{
    if (tamany != 0)
    {
        retallat = true;
        
        Celula c = cels.arrel();
        Arbre<Celula> a1, a2;
        cels.fills(a1, a2);
        int max = 0;
        
		if(a1.es_buit() and a2.es_buit()) tamany = 0;
		else 
        {
            retallar_recursiu(a1, tamany, max);
            retallar_recursiu(a2, tamany, max);
            cels.plantar(c, a1, a2);
            max_id = max;
		}

    }
}

void Organisme::retallar_recursiu(Arbre<Celula> &a, int &tam, int &max_id)
{
	if(not a.es_buit()) 
    {
        Arbre<Celula> a1, a2;
		Celula c = a.arrel();
		a.fills(a1, a2);

		// Si algun dels dos fills no està buit vol dir que la cèl·lula encara
        // no s'ha d'eliminar. Si ja no té cap fill no tornem a plantar
        // l'arbre i haurem eliminat la cèl·lula.
		if(not(a1.es_buit() and a2.es_buit())) 
        {
            if (max_id < c.id) max_id = c.id;
            retallar_recursiu(a1, tam, max_id);
            retallar_recursiu(a2, tam, max_id);
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
    if(not(a1.es_buit()) and not(a2.es_buit())) 
    {
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
    else if (a1.es_buit() and not(a2.es_buit())) 
    {
        ++max_id;
        busca_activa_gran(cels, a2, max_id, tamany);
        if (cels.es_buit()) --max_id;
    }
    else if (not(a1.es_buit()) and a2.es_buit()) 
    {
        busca_activa_petit(cels, a1, tamany);
    }
}

void Organisme::busca_activa_gran(Arbre<Celula> &cels, Arbre<Celula> &a,
                                  int &max_id, int &tamany)
{
    if (not a.es_buit()) 
    {
        Celula c = a.arrel();
        Arbre<Celula> a_e, a_d;
        
        a.fills(a_e, a_d);

        if (a_e.es_buit() and a_d.es_buit()) 
        {
            if (c.activa) 
            {
                ++tamany;
                c.id = max_id;
                cels.plantar(c, a_e, a_d);
            }
        }
        else
        {
            ++tamany;
            c.id = max_id;

            Arbre<Celula> cels_e, cels_d;
            
            ++max_id;
            busca_activa_gran(cels_e, a_e, max_id, tamany);
            if (cels_e.es_buit()) --max_id;
            
            ++max_id;
            busca_activa_gran(cels_d, a_d, max_id, tamany);
            if (cels_d.es_buit()) --max_id;
            
            if (c.activa or not(cels_e.es_buit()) or not(cels_d.es_buit())) 
            {
                cels.plantar(c, cels_e, cels_d);
            }
        }
    }
}

void Organisme::busca_activa_petit(Arbre<Celula> &cels, Arbre<Celula> &a, 
                                   int &tamany)
{
    if (not(a.es_buit())) 
    {
        Celula c = a.arrel();
        Arbre<Celula> a_e, a_d;
        
        a.fills(a_e, a_d);
        
        if (a_e.es_buit() and a_d.es_buit()) 
        {
            if (c.activa) 
            {
                ++tamany;
                cels.plantar(c, a_e, a_d);
            }
        }
        else 
        {
            Arbre<Celula> cels_e, cels_d;
            
            busca_activa_petit(cels_e, a_e, tamany);
            busca_activa_petit(cels_d, a_d, tamany);
            
            if (c.activa or not(cels_e.es_buit()) or not(cels_d.es_buit())) 
            {
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

    Arbre<Celula> a_a = cels;
    Arbre<Celula> a_b = o.cels;
    
    return (tam_intersec_recursiu(a_a, a_b) >= comp);
}

int Organisme::tam_intersec_recursiu(Arbre<Celula> &a1, Arbre<Celula> &a2)
{
	int res = 0;

    // Evaluem per cada branca de l'arbre, si hi ha una arrel sumem 1
	// com que ho fem recursivament tots els resultats es van sumant fins
	// a obtenir el resultat de la intersecció
	if(not(a1.es_buit()) and not(a2.es_buit())) 
    {
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
	return (tamany == 0); 
}

/***************************
 *    ENTRADA / SORTIDA    *
 ***************************/

void Organisme::llegir_organisme(int marca)
{
    if (not cels.es_buit()) cout << "L'organisme no és buit!" << endl;
    else llegir_rec(cels, marca, max_id, tamany);
}

void Organisme::llegir_rec(Arbre<Celula> &cels, int marca, int &max_id,
                           int &tamany)
{
    int x = readint();
    
    if (x != marca) 
    {
        bool activa = readbool();
        
        ++tamany;
        if (x > max_id) max_id = x;
        
        Arbre<Celula> a_e, a_d;
        
        llegir_rec(a_e, marca, max_id, tamany);
        llegir_rec(a_d, marca, max_id, tamany);
        
        Celula c;
        c.id = x;
        c.activa = activa;
        
        cels.plantar(c, a_e, a_d);
    }
    
}

void Organisme::escriure_organisme() const
{
    if (cels.es_buit()) cout << "0 " << endl;
    else 
    {
        Arbre<Celula> a = cels;
        escriure_rec(a);
        cout << endl;
    }
}

void Organisme::escriure_rec(Arbre<Celula> &cels)
{
    Celula c = cels.arrel();   
    Arbre<Celula> a_e, a_d;
    
    cels.fills(a_e, a_d);

    /* ESCRITURA EN PREORDRE
    cout << " " << c.id;
    if (c.activa) cout << " 1";
    else cout << " -1";
    if (not a_e.es_buit()) escriure_rec(a_e);
    else cout << " 0";
    if (not a_d.es_buit()) escriure_rec(a_d);
    else cout << " 0";
    */


    // Escrivim a la branca esquerra si no està buida
    if (not a_e.es_buit()) escriure_rec(a_e);
    else cout << "0 ";
    
    // Escrivim l'arrel
    cout << c.id << " ";
    if (c.activa) cout << "1 ";
    else cout << "-1 ";
    
    // Escrivim la branca dreta si no està buida
    if (not a_d.es_buit()) escriure_rec(a_d);   
    else cout << "0 ";
}

// DIBUIXAR L'ARBRE

void Organisme::escriure_bonic() const
{
    cout << endl << "----Arbre de celules----" << endl << endl;
    Arbre<Celula> a = cels;
    int h = tamany_arbre(a);
    vector< vector<Celula> > m(h + 1, vector<Celula> ());
    
    int pot = 1;
    for (int i = 0; i <= h; ++i) 
    {
        Celula c;
        c.id = 0;
        m[i] = vector<Celula> (pot, c);
        pot *= 2;
    }
    
    vector<int> ultimpos(h + 1, 0);
    int haux = 0;
    conv_matriu(a, m, haux, ultimpos, h);
    escriure_bonic_rec(m);
    cout << "------------------------" << endl;
}

int Organisme::tamany_arbre(Arbre<Celula> &a)
{
    int h = 1;
    if (a.es_buit()) return 0;
    else {
        Celula c = a.arrel();
        Arbre<Celula> a1, a2;
        a.fills(a1, a2);
        int h1 = tamany_arbre(a1);
        int h2 = tamany_arbre(a2);
        
        a.plantar(c, a1, a2);
        
        if (h1 > h2) h += h1;
        else h += h2;
    }
    return h;
}

void Organisme::conv_matriu(Arbre<Celula> &a, vector< vector<Celula> > &m, 
                              int h, vector<int> &ultimpos, int hmax) 
{
    if (not a.es_buit()) {
        Celula c = a.arrel();
        m[h][ultimpos[h]] = c;
        ++ultimpos[h];
        Arbre<Celula> a1, a2;
        a.fills(a1, a2);
        conv_matriu(a1, m, h+1, ultimpos, hmax);
        conv_matriu(a2, m, h+1, ultimpos, hmax);
        a.plantar(c, a1, a2);
    }
    else {
        ++ultimpos[h];
        ++h;
        int espais = 2;
        while (h < hmax) {
            ultimpos[h] += espais;
            espais *= 2;
            ++h;
        }
    }
}

void Organisme::escriure_bonic_rec(const vector< vector<Celula> > &m)
{
    int n = m.size() - 1;
    int espaientreelements = 3*pow(2, n - 1);
    int espaiinicial = espaientreelements/2;
    int espaientrebarres = espaiinicial/2;
    int espaientrebranques =  3*espaientrebarres;
    int strideespaiinicial = espaientrebarres/2;
    for (int i = 0; i < n; ++i) {
        if (n - i == 3) espaiinicial = 6;
        else if (n - i == 2) espaiinicial = 3;
        else if (n - i == 1) espaiinicial = 1;
        espais(espaiinicial - 1);
        espaiinicial -= strideespaiinicial;
        for (int j = 0; j < int(m[i].size()); ++j) {
            escriu_elem(m[i][j]);
            int sumadigits = 0;
            if (j%2 == 0 and not es_buida(m[i][j])) {
                sumadigits += ndigits(es_activa(m[i][j]), id(m[i][j])) - 1;
                if (j+1 < int(m[i].size())) {
                    sumadigits += ndigits(es_activa(m[i][j+1]), id(m[i][j+1])) - 1;
                }
            }
            if (n - i == 1) {
                if (j%2 == 0) espaientreelements = 4;
                else espaientreelements = 2;
            }
            espais(espaientreelements - 1 - sumadigits);
        }
        cout << endl;
        if (n - i == 3) espaiinicial = 4;
        else if (n - i == 2) espaiinicial = 2;
        espais(espaiinicial - 1);
        espaiinicial -= strideespaiinicial;
        int j = 0;
        for (int k = 0; k < int(m[i].size()); ++k) {
            if (not es_buida(m[i + 1][j])) cout << '/';
            else cout << ' ';
            ++j;
            if (n - i == 2) espaientrebarres = 2;
            else if (n - i == 3) espaientrebarres = 4;
            espais(espaientrebarres - 1);
            if (not es_buida(m[i + 1][j])) cout << '\\';
            else cout << ' ';
            ++j;
            if (n - i == 3) espaientrebranques = 8;
            else if (n - i == 2) espaientrebranques = 4;
            espais(espaientrebranques - 1);
        }
        cout << endl;
        strideespaiinicial /= 2;
        espaientrebarres /= 2;
        espaientrebranques /= 2;
        espaientreelements /= 2;
    }
}

void Organisme::espais(int n)
{
    for (int i = 0; i < n; ++i) cout << " ";
}

void Organisme::escriu_elem(const Celula &c)
{
    if (c.activa) cout << "!";
    cout << c.id;
}

bool Organisme::es_buida(const Celula &c)
{
    return c.id == 0;
}
bool Organisme::es_activa(const Celula &c)
{
    return c.activa;
}
int Organisme::id(const Celula &c)
{
    return c.id;
}
int Organisme::ndigits(bool es_activa, int n) {
    if (n < 10 and es_activa) return 1;
    else if (n < 10) return 2;
    else return 1 + ndigits(es_activa, n/10);
}


/*





   !8
  /  \
 8    !8 8 8 8 8 8 8


*/
