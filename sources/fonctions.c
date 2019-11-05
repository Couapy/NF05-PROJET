#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structures.c" // TEMP: Remove


Vol vols[255];
int nb_vols = 0;


void genererBillet(Passager *passager) { // DONE
  int continuer = 0;
  float nb_rand;
  char billet[11];
  billet[0] = '\0'; // Condition pour rentrer dans la boucle

  while (billet[0] == '\0' || continuer == 1) {
    continuer = 0;

    for (int i = 0; i < 10; i++) {
      nb_rand = (float)rand()/RAND_MAX * 10.0;
      billet[i] = (int)nb_rand + '0';
    }
    billet[11] = '\0';

    int i = 0, j;
    while (i < nb_vols && continuer == 0) {
      j = 0;
      while (j < vols[i].places_reservees && continuer == 0) {
        if (vols[i].passagers[j]->billet == billet) {
          continuer = 1;
        }
        j++;
      }
      i++;
    }
  }

  strcpy(passager->billet, billet);
}

void saisirPassager(Passager *passager) { // FIX: scanf (\n is readen)
  char reponse[10];

  printf("Enregistrement des informations sur les passagers.\n");

  printf("Entrez le nom de votre passager : ");
  scanf(" %s", passager->nom);

  printf("Entrez le prenom de votre passager : ");
  scanf(" %s", passager->prenom);

  printf("Etes vous prioritaire ? (oui ou non) ");
  scanf(" %s", &reponse);

  if (strcmp(reponse, "oui") == 0) {
    passager->prioritaire = 0;
  } else {
    passager->prioritaire = 1;
  }

  printf("Indiquez votre date de naissance en format JJ/MM/AAAA : ");
  scanf(" %s", passager->date_naissance);
}

int ajouterPassager(Vol *vol) { // DONE
  Passager *passager = (Passager*)malloc(sizeof(Passager));

  //On génère le passager
  saisirPassager(passager);
  genererBillet(passager);

  // Les informations du passager sont montrés en une "jolie" phrase.
  printf("Date de naissance : %s\n", passager->date_naissance);
  printf("%s %s ne(e) le %s ", passager->nom, passager->prenom, passager->date_naissance);
  if (passager->prioritaire == 0){
    printf("est prioritaire.\n");
  } else {
    printf("n'est pas prioritaire.\n");
  }

  printf("Votre numero de billet : %s %c\n", passager->billet, passager->billet[10]);

  if (vol->places_libres > 0) {
    vol->passagers[vol->places_reservees] = passager;
    vol->places_libres -= 1;
    vol->places_reservees += 1;
    printf("[INFO]Ajout reussi du passager au vol\n");
    return 1;
  }

  return 0;
}

void engeristrerPassager(void) {
  // Entrer Nom ou numero de Billet
  char reponse[64];
  printf("Nom ou Numero de billet : ");
  gets(reponse);

  int i = 0, j, trouve = 0;
  while (trouve != 1) {
    j = 0;
  }
  // TODO: générer le boarding pass
  // TODO: générer les tickets bagages
    // if (priority == 1)
      // bagages_max = 2
  // TODO: afficher boarding pass

  // TODO: générer numéro de siège, OU le choisir, ET selon les places dispo
    //si la place existe dans l'avion
    //si aucun autre passager a deja la place
}

int main(void) {

  // Passager *passager = (Passager*)malloc(sizeof(Passager));
  // saisirPassager(passager);
  // genererBillet(passager);
  // printf("Billet numero : %s\n", passager->billet);

  Vol *vol = (Vol*)malloc(sizeof(Vol));
  vol->places_reservees = 3;
  vol->places_libres = 64;
  ajouterPassager(vol);

  return 0;
}
