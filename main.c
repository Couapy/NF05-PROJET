#include <stdio.h>

struct Passager {
  char nom[64];
  char prenom[64];
  Bagage bagages[2];
  int prioritaire = 0;
  char numero_billet[128];
  char date_naissance[64];
  char numero_siege[64];
};

struct Bagage {
  int ticket;
  int poids = 0;
  int priority = 0;
  int depose = 0;
  int embarque = 0;
};

struct Vol {
  char heure_depart[64];
  char heure_arrivee[64];
  char destination[128];
  Passager passagers[1024];
  int places_reservees = 0;
  int places_libres = 1024;
};


/**
 * register
 * ticket bagages + boarding pass
 * depot bagages
 * frontière
 * sécurité
 * embarquement
 */


int ajouterPassager(Vol *vol) {
  // TODO: créer passsager
  // TODO: générer n°billet
  // TODO: afficher toutes les informations
  if (vol->places_libres > 0) {
    vol->passagers[vol->places_reservees] = passager;
    vol->places_libres -= 1;
    vol->places_reservees += 1;
    printf("[INFO]Ajout reussi du passager au vol\n");
    return 0;
  }
  return 1;
}

void engeristrer(char nom[], char billet[]) {
  // TODO: générer le boarding pass
  // TODO: générer les tickets bagages
    // if (priority == 1)
      // bagages_max = 2
  // TODO: afficher boarding pass

  // TODO: générer numéro de siège, OU le choisir, ET selon les places dispo
    //si la place existe dans l'avion
    //si aucun autre passager a deja la place
}

int passerFrontieres(void) {

  // Si toutes les conditions sont OK pour rejoindre la destination
    // engeristré ?
    // a son boarding pass ET ses tickets de bagages
  // Afficher
    // Nationalité
    // Destination
    // A besoin d'un visa ?

  return 0 || 1;
}

int visaRequis(char destination[]) {
  //Trouver les pays qui ont besoin d'un VISA, ou pas

  return 0;
}

int passerSecurite(void) {

}

int main(void) {

  return 0;
}
