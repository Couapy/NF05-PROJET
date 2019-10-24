#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.c"

int ajouterPassager(struct Vol *vol) {
  //TEMP : nécéssaire pour compiler sinon il y a une erreur !
  Passager *passager;
  char reponse[3];
  char naissance[11];

  printf("Enregistrement des informations sur les passagers.\n");
  printf("Entrez le nom de votre passager :\n");
  scanf("%c", &passager->nom);

  printf("Entrez le prénom de votre passager :\n");
  scanf("%c", &passager->prenom);

  printf("Êtes vous prioritaire ? (oui ou non)\n");
  scanf("%c", &reponse[]);

  if ( strcmp(reponse, "oui") == 0 ){
    passager->prioritaire = 0;
  }
  else {
      passager->prioritaire = 1;
  }

  printf("Indiquez votre date de naissance en format JJ/MM/AAAA:\n");
    fgets(naissance, 11);

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
