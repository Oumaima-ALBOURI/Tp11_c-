
#include <iostream>
using namespace std;

// Classe abstraite Paiement
class Paiement {
public:
    virtual void effectuerPaiement(double montant) = 0;

    virtual ~Paiement() {}
};

// Classe PaiementCarte
class PaiementCarte : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant
             << " DH par carte bancaire." << endl;
    }
};

// Classe PaiementEspece
class PaiementEspece : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant
             << " DH en especes." << endl;
    }
};

// Fonction principale
int main() {

    // Tableau de pointeurs
    Paiement* paiements[4];

    // Création des objets
    paiements[0] = new PaiementCarte();
    paiements[1] = new PaiementEspece();
    paiements[2] = new PaiementCarte();
    paiements[3] = new PaiementEspece();

    // Montants des paiements
    double montants[4] = {200, 150, 500, 100};

    // Simulation des paiements
    cout << "===== SIMULATION DES PAIEMENTS =====" << endl;

    for (int i = 0; i < 4; i++) {
        paiements[i]->effectuerPaiement(montants[i]);
    }

    // Libération de la mémoire
    for (int i = 0; i < 4; i++) {
        delete paiements[i];
    }

    return 0;
}
