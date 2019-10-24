#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void genererBillet(Passager *passager) {
  char billet[11];
  int continuer;
  float nb_rand;

  while (billet == 0 || continuer == 1) {
    continuer = 0;

    for (int i = 0; i < 13; i++) {
      nb_rand = (float)rand()/RAND_MAX * 10.0;
      billet[i] = (int)nb_rand + '0';$
    }
    billet[10] = '\0';

    int i = 0, j;
    while (i < nb_vols && continuer == 0) {
      j = 0;
      while (j < vols[i].places_reservees && continuer == 0) {
        if (vols[i].passagers[j].numero_billet == billet) {
          continuer = 1;
        }
        j++;
      }
      i++;
    }
  }

  passager->numero_billet = billet;
}

void genererBillet(void) {




}

int ajouterPassager(struct Vol *vol) {
  struct Passager passager;
  // TODO: créer passsager
  // TODO: générer n°billet
  // TODO: afficher toutes les informations
  if (vol->places_libres > 0) {
    vol->passagers[vol->places_reservees] = passager;
    vol->places_libres -= 1;
    vol->places_reservees += 1;
    printf("[INFO]Ajout reussi du passager au vol\n");
    return 1;
  }
  return 0;
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
