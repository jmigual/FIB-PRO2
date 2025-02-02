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
    if (not retallat and not cels.es_buit())
    {
        estirar_recursiu(cels, max_id, tamany);
    }
}

void Organisme::estirar_recursiu(Arbre<Celula> &a, int &max_id, int &tam) 
{
    Arbre<Celula> a1, a2;
    Celula c = a.arrel();
    a.fills(a1, a2);
    if (a1.es_buit() and a2.es_buit())
    {
        tam += 2;
        Celula aux = c;
        Arbre<Celula> buit;
        
        // Plantem els dos arbres i ens estalviem cridar la funció
        // recursiva per poder duplicar només la cèl·lula arrel
        ++max_id;
        aux.id = max_id;
        
        a1.plantar(aux, buit, buit);
        
        ++max_id;
        aux.id = max_id;
        
        a2.plantar(aux, buit, buit);
        
    }
    else 
    {
        if (not a1.es_buit()) estirar_recursiu(a1, max_id, tam);
        if (not a2.es_buit()) estirar_recursiu(a2, max_id, tam);
    }
    a.plantar(c, a1, a2);
}

void Organisme::retallar_organisme() 
{
    if (tamany != 0 and not cels.es_buit())
    {
        retallat = true;
        int max = 0;
        retallar_recursiu(cels, tamany, max);
        max_id = max;
    }
}

void Organisme::retallar_recursiu(Arbre<Celula> &a, int &tam, int &max_id)
{
    Arbre<Celula> a1, a2;
    Celula c = a.arrel();
    a.fills(a1, a2);

    // Si algun dels dos fills no està buit vol dir que la cèl·lula encara
    // no s'ha d'eliminar. Si ja no té cap fill no tornem a plantar
    // l'arbre i haurem eliminat la cèl·lula.
    if(not(a1.es_buit()) or not(a2.es_buit())) 
    {
        if (c.id > max_id) max_id = c.id;
        if (not a1.es_buit()) retallar_recursiu(a1, tam, max_id);
        if (not a2.es_buit()) retallar_recursiu(a2, tam, max_id);
        a.plantar(c, a1, a2);
    }
    else --tam;
}

bool Organisme::reproduir_organisme(const Organisme &o1, const Organisme &o2)
{
    Arbre<Celula> a1 = o1.cels;
    Arbre<Celula> a2 = o2.cels;
    
    bool res = false;
    
    max_id = o1.max_id;
    tamany = 0;
    
    int tam_int = reproduir(cels, a1, a2, max_id, tamany);
    
    int comp = (o1.tamany + o2.tamany)/4;
    
    if(tam_int >= comp) 
    {
        res = true;
        max_id = busca_max(cels);
    }
    else 
    {
        cels.a_buit();
        max_id = 0;
        res = false;
    }
    return res;
}

int Organisme::reproduir(Arbre<Celula> &cels, Arbre<Celula> &a1,
                         Arbre<Celula> &a2, int &max_id, int &tamany) 
{
    int res = 0;
    if(not(a1.es_buit()) and not(a2.es_buit())) 
    {
        Celula c = a1.arrel();
        
        if(a2.arrel().activa) c.activa = true;

        Arbre<Celula> cels_e, cels_d;
        Arbre<Celula> a1_e, a1_d, a2_e, a2_d;
        
        a1.fills(a1_e, a1_d);
        a2.fills(a2_e, a2_d);
        
        res += reproduir(cels_e, a1_e, a2_e, max_id, tamany);
        res += reproduir(cels_d, a1_d, a2_d, max_id, tamany);
        ++res;
        ++tamany;
        
        cels.plantar(c, cels_e, cels_d);
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
    return res;
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
                ++tamany;
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

int Organisme::busca_max(Arbre<Celula> &cels)
{
    Celula c = cels.arrel();
    Arbre<Celula> a_e, a_d;
    cels.fills(a_e, a_d);
    
    int max, max_e, max_d;
    max = max_e = max_d = 0;
    
    if (not a_e.es_buit())
    {
        max_e = busca_max(a_e);
    }
    if (not a_d.es_buit())
    {
        max_d = busca_max(a_d);
    }
    
    // Busquem el màxim d'aquest subarbre, ha de ser l'ID de l'arrel o un dels
    // dos màxims dels fills
    if (max_e > max_d) max = max_e;
    else max = max_d;
    if (c.id > max) max = c.id;
    
    cels.plantar(c, a_e, a_d);
    return max;
}

/*********************
 *    CONSULTORES    *
 *********************/

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

