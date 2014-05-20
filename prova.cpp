#include "utils.PRO2"
#include "ConjuntOrg.hpp"
#include "Ranking.hpp"
#include "Organisme.hpp"


int main() {
    Organisme o1, o2;
    
    cout << "Entra l'organisme 1 en PREORDRE" << endl;
    o1.llegir_organisme(0);
    o1.escriure_organisme();
    
    cout << "Entra l'organisme 2 en PREORDRE" << endl;
    o2.llegir_organisme(0);
    o2.escriure_organisme();
    
    
    cout << "FILL" << endl;
    Organisme fill;
    fill.reproduir_organisme(o1, o2);
    fill.escriure_organisme();
}
