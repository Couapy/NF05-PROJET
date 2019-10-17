#include <stdio.h>
#include <string.h>

struct Bagage {
  int ticket;
  int poids;
  int priority;
  int depose;
  int embarque;
};

struct Passager {
  char nom[64];
  char prenom[64];
  struct Bagage bagages[2];
  int prioritaire;
  char numero_billet[128];
  char date_naissance[64];
  char numero_siege[64];
};

struct Vol {
  char heure_depart[64];
  char heure_arrivee[64];
  char destination[128];
  struct Passager passagers[1024];
  int places_reservees;
  int places_libres;
};


/**
 * register
 * ticket bagages + boarding pass
 * depot bagages
 * frontière
 * sécurité
 * embarquement
 */


int ajouterPassager(struct Vol *vol) {
  //TEMP : nécéssaire pour compiler sinon il y a une erreur !
  struct Passager passager;
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
  // règles sur les liquides pour le bagage en main
  // règles sur les objets à prendre en cabine ?
  // afficher les objets à retirer des bagages
  return 1 || 0;
}

int embarquement(void) {
  //Embarquer d'abord les passagers prioritaires
  // Tant qu'il reste un passager prioritaire non embarqué, ne pas embarquer les autres passagers
}

int passagerPrioriatireNonEmbarquer(void) {
  return 0 || 1;
}

int chargerBagages(void) {
  return 0 || 1;
}

int peutDecoller(void) {
  // V´erifier que l’avion peut d´ecoller en v´erifiant que tous les passagers enregistr´es ont
  // embarqu´e et que tous les bagages sont charg´es.

  return 0 || 1;
}

int main(void) {
  char commande[64];
  // while (strcomp(commande, "quitter") == 1) {
  //   printf("Sys> ");
  //   gets(commande);
  // }

  return 0;
}
