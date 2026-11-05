
#include <iostream>
#include <vector>
using namespace std;

// Classe abstraite Animal
class Animal {
public:

    // Methode virtuelle pure
    virtual void crier() const = 0;

    // Methode concrete (non abstraite)
    void info() const {
        cout << "Je suis un animal." << endl;
    }

    // Destructeur virtuel
    virtual ~Animal() {}
};

// Classe Chien
class Chien : public Animal {
public:
    void crier() const override {
        cout << "Wouf !" << endl;
    }
};

// Classe Chat
class Chat : public Animal {
public:
    void crier() const override {
        cout << "Miaou !" << endl;
    }
};

// Classe Vache
class Vache : public Animal {
public:
    void crier() const override {
        cout << "Meuh !" << endl;
    }
};

// Programme principal
int main() {

    // Vecteur de pointeurs vers Animal
    vector<Animal*> animaux;

    // Creation des objets
    animaux.push_back(new Chien());
    animaux.push_back(new Chat());
    animaux.push_back(new Vache());

    // Parcours du vecteur
    cout << "===== GESTION DES ANIMAUX =====" << endl;

    for (int i = 0; i < animaux.size(); i++) {

        animaux[i]->info();

        animaux[i]->crier();

        cout << "------------------" << endl;
    }

    // Liberation de la memoire
    for (int i = 0; i < animaux.size(); i++) {
        delete animaux[i];
    }

    return 0;
}
