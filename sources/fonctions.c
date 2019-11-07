#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structures.c" // TEMP: Remove

// Variable globales
Vol vols[255];
int nb_vols = 0;
int last_id_bagage = 0;


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

void saisirPassager(Passager *passager) { // DONE
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

  passager->billet[0] = '\0';
  passager->bagages[0].ticket = 0;
}

int ajouterPassager(Vol *vol) { // DONE
  Passager *passager = (Passager*)malloc(sizeof(Passager));

  //On génère le passager
  saisirPassager(passager);
  genererBillet(passager);

  // Les informations du passager sont montrés en une "jolie" phrase.
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

/**
 * Trouve un passager selon un Nom ou un Numero de billet
 * @return  Passager*
 */
Passager* trouverPassager(void) {
  char reponse[64];
  printf("Nom ou Numero de billet : ");
  gets(reponse);

  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      if (strcmp(reponse, vols[i].passagers[j]->nom) == 0 || strcmp(reponse, vols[i].passagers[j]->billet)) {
        return vols[i].passagers[j];
      }
    }
  }
}

/**
 * Trouve le vol d'un passager
 * @param  passager Passager*
 * @return          Passager*
 */
Vol* trouverVol(Passager *passager) {
  Vol vol*;
  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      if (strcmp(passager->billet, vols[i].passagers[j]->billet) == 0) {
        return &vol[i];
      }
    }
  }
}

/**
 * Permet d'enregistrer les bagages d'un passager lors de son Enregistrement
 * @param [name] [description]
 */
void enregistrerBagages(Passager passager*) {
  int nb_bagages = 3, nb_bagages_max = 1;
  if (passager->prioritaire == 1) {
    nb_bagages_max = 2;
  }

  while (nb_bagages > nb_bagages_max) {
    printf("Combien de bagages avez-vous ? (%d maximum)", nb_bagages_max);
    scanf(" %d", nb_bagages);
  }

  passager->nb_bagages = nb_bagages;
  for (int i = 0; i < passager->nb_bagages; i++) {
    last_id_bagage++;
    passager->bagages[i].ticket = last_id_bagage;
    passager->bagages[i].embarque = 0;
  }
}

/**
 * Permet d'afficher le boarding pass
 * @param passager Passager*
 * @param vol    Vol*
 */
void afficherBoardingPass(Passager passager*, Vol *vol) {

}

/**
 * Permet de choisir un siège parmi les siège libres
 * @param passager [description]
 */
void choisirSiege(Passager *passager) {
  char choix[15];
  printf("Voulez-vous choisir votre siege ? (oui ou non) ");
  scanf(" %d", choix);

  if (strcmp(choix, "oui") == 0) {
    printf("Quelle est la place que vous voulez ? ");
    scanf("");
  }
  // TODO: générer numéro de siège, OU le choisir, ET selon les places dispo
  // si la place existe dans l'avion
  // si aucun autre passager a deja la place
}

void engeristrerPassager(void) {
  Passager *passager = trouverPassager();
  Vol *vol = trouverVol(passager);

  enregistrerBagages(passager);
  choisirSiege(passager);

  passager->boardingPass = 1;
  afficherBoardingPass(passager, vol);
}

int main(void) {

  // Passager *passager = (Passager*)malloc(sizeof(Passager));
  // saisirPassager(passager);
  // genererBillet(passager);
  // printf("Billet numero : %s\n", passager->billet);

  // Vol *vol = (Vol*)malloc(sizeof(Vol));
  // vol->places_reservees = 3;
  // vol->places_libres = 64;
  // ajouterPassager(vol);

  return 0;
}
