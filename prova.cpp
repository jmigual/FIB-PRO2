#include "utils.PRO2"
#include "ConjuntOrg.hpp"
#include "Ranking.hpp"
#include "Organisme.hpp"


int main() {
    Organisme o;
    
    cout << "Entra l'organisme en PREORDRE" << endl;
    o.llegir_organisme(0);
    o.escriure_organisme();
}
