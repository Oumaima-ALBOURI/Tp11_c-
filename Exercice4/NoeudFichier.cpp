
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Classe abstraite NoeudFichier
class NoeudFichier {
protected:
    string nomFichier;

public:
    NoeudFichier(string n) {
        nomFichier = n;
    }

    string nom() const {
        return nomFichier;
    }

    virtual int taille() const = 0;

    virtual ~NoeudFichier() {}
};

// Classe Fichier
class Fichier : public NoeudFichier {
private:
    int tailleFichier;

public:
    Fichier(string n, int t) : NoeudFichier(n) {
        tailleFichier = t;
    }

    int taille() const override {
        return tailleFichier;
    }
};

// Classe Dossier
class Dossier : public NoeudFichier {
private:
    vector<NoeudFichier*> enfants;

public:
    Dossier(string n) : NoeudFichier(n) {}

    // Ajouter un fichier ou un sous-dossier
    void ajouter(NoeudFichier* element) {
        enfants.push_back(element);
    }

    // Calculer la taille totale du dossier
    int taille() const override {
        int total = 0;

        for (int i = 0; i < enfants.size(); i++) {
            total += enfants[i]->taille();
        }

        return total;
    }

    // Afficher le contenu du dossier
    void afficher() const {
        cout << "\nDossier : " << nom() << endl;

        for (int i = 0; i < enfants.size(); i++) {
            cout << enfants[i]->nom()
                 << " - Taille : "
                 << enfants[i]->taille() << " Ko" << endl;
        }
    }

    // Accéder aux enfants
    const vector<NoeudFichier*>& getEnfants() const {
        return enfants;
    }

    // Destructeur : libérer les enfants
    ~Dossier() {
        for (int i = 0; i < enfants.size(); i++) {
            delete enfants[i];
        }
    }
};

// Création récursive d'un dossier
Dossier* creerDossier() {
    string nom;
    int nombre, choix;

    cout << "\nDonner le nom du dossier : ";
    cin >> nom;

    Dossier* dossier = new Dossier(nom);

    cout << "Combien d'elements contient ce dossier ? ";
    cin >> nombre;

    for (int i = 0; i < nombre; i++) {
        cout << "\n1. Ajouter un fichier";
        cout << "\n2. Ajouter un sous-dossier";
        cout << "\nVotre choix : ";
        cin >> choix;

        if (choix == 1) {
            string nomF;
            int t;

            cout << "Nom du fichier : ";
            cin >> nomF;

            cout << "Taille du fichier (Ko) : ";
            cin >> t;

            dossier->ajouter(new Fichier(nomF, t));
        }
        else if (choix == 2) {
            dossier->ajouter(creerDossier());
        }
        else {
            cout << "Choix invalide !" << endl;
            i--;
        }
    }

    return dossier;
}

// Rechercher un dossier par son nom
Dossier* rechercherDossier(Dossier* dossier, string nom) {

    if (dossier->nom() == nom) {
        return dossier;
    }

    for (NoeudFichier* element : dossier->getEnfants()) {

        Dossier* sousDossier = dynamic_cast<Dossier*>(element);

        if (sousDossier != nullptr) {
            Dossier* resultat = rechercherDossier(sousDossier, nom);

            if (resultat != nullptr) {
                return resultat;
            }
        }
    }

    return nullptr;
}

// Programme principal
int main() {

    cout << "===== SYSTEME DE FICHIERS VIRTUEL =====" << endl;

    // Création de la structure
    Dossier* racine = creerDossier();

    // Affichage de la taille totale
    cout << "\nTaille totale du dossier racine : "
         << racine->taille() << " Ko" << endl;

    // Sélection d'un dossier
    string nomRecherche;

    cout << "\nDonner le nom du dossier a selectionner : ";
    cin >> nomRecherche;

    Dossier* selection = rechercherDossier(racine, nomRecherche);

    if (selection != nullptr) {
        cout << "\nDossier selectionne : " << selection->nom() << endl;
        cout << "Taille totale : " << selection->taille() << " Ko" << endl;

        selection->afficher();
    }
    else {
        cout << "Dossier introuvable !" << endl;
    }

    // Libération de la mémoire
    delete racine;

    return 0;
}
