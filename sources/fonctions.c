#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structures.c" // TEMP: Remove

// Variable globales
Vol vols[255];
int nb_vols = 0;
int last_id_bagage = 0;

/**
 * Fonction qui génère un billet à un passager
 * @param passager Passager*
 */
void genererBillet(Passager *passager) {
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

/**
 * Saisie d'un passager par l'utilisateur
 * @param passager Passager*
 */
void saisirPassager(Passager *passager) {
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

/**
 * On ajoute un passager à un vol
 * @param  vol Vol*
 */
void ajouterPassager(Vol *vol) { // DONE
  if (vol->places_libres > 0) {
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

    vol->passagers[vol->places_reservees] = passager;
    vol->places_libres -= 1;
    vol->places_reservees += 1;
    printf("[INFO]Ajout reussi du passager au vol\n");
  } else {
    printf("[ERROR] Il n'y a plus de places sur le vol");
  }
}

/**
 * Trouve un passager selon un Nom ou un Numero de billet
 * @return  Passager*
 */
Passager* trouverPassager(void) {
  char reponse[64];
  while (1) {
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
}

/**
 * Trouve le vol d'un passager
 * @param  passager Passager*
 * @return          Passager*
 */
Vol* trouverVol(Passager *passager) {
  Vol *vol;
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
void enregistrerBagages(Passager *passager) {
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
void afficherBoardingPass(Passager *passager, Vol *vol) {
  // TODO: afficher boardingPass
}

/**
 * Permet de savoir si une place est libre dans un vol
 * @param  place Siege
 * @param  vol   Vol
 * @return       int
 */
int placeLibre(Siege *place, Vol *vol) {
  char place_max[4];
  sprintf(place_max, "%d%c", place->rangee, vol->sieges_colonne + '@');

  if (1 >= place.rangee || place.rangee >= vol->sieges_rangee) {
    return 0;
  }

  if (strcmp(place, "1A") > 0 && strcmp(place, place_max) < 0) {
    int i = 0, pastrouve = 1;
    while (i < vol->places_reservees && pastrouve == 1) {
      if (vol->passagers[i].siege.rangee == place.rangee && vol->passagers[i].siege.colonne == place.colonne) {
        pastrouve = 0;
      }
      i++;
    }
    return pastrouve;
  }
  return 1;
}

/**
 * Permet de choisir un siège parmi les siège libres
 * @param passager [description]
 */
int choisirSiege(Passager *passager, Vol *vol) {
  char choix[15];
  Siege place;
  while (1) {
    printf("Voulez-vous choisir votre siege ? (oui ou non) ");
    scanf(" %d", choix);
    if (strcmp(choix, "oui") == 0) {
      printf("Quelle est la place que vous voulez ?\n");
      printf("  > Rangee numero : ");
      scanf(" %d", &place.rangee);
      printf("  > Colonne numero : ");
      scanf(" %d", &place.colonne);
      if (placeLibre(place, vol)) {
        passager->siege = place;
      }
    } else {
      do {
        place = {
          (rand()/RAND_MAX) * vol->siege_rangee,
          (rand()/RAND_MAX) * vol->siege_colonne
        };
      } while (!placeLibre(place, vol));
      passager->siege = place;
      return 1;
    }
  }
}

/**
 * On enregistre un passager sur son vol
 */
void engeristrerPassager(void) {
  Passager *passager = trouverPassager();
  Vol *vol = trouverVol(passager);

  enregistrerBagages(passager);
  choisirSiege(passager, vol);

  passager->enregistrer = 1;
  afficherBoardingPass(passager, vol);
}

/**
 * Faire passer la frontière pour un passager
 * @param  passager Passager*
 * @param  vol      Vol*
 * @return          boolean
 */
int passerFrontieres(Passager *passager, Vol *vol) {
  passager->frontiere = 0;
  printf("Vérification des documents:\n");

  if (passager->billet[0] != '\0') {
    printf("Votre billet est bien le numéro : %s\n", passager->billet);
    if (passager->enregistrer == 1) {
      if (passager->bagages[0].ticket != 0) {
        printf("Vous avez bien %d bagages avec vous.\n", passager->bagages[0]);
        printf("Vous etes de nationalitee : %s et vous vous rendez à %s.\n", passager->nationalite, vol->destination);
        if (vol->visa_requis == 1) {
          printf("Montrez votre VISA s'il vous plait :\n 0 - si vous ne l'avez pas \n 1 - si vous l'avez\n");
          scanf("%d", &passager->visa);
          if (passager->visa == 1) {
            passager->frontiere = 1;
          }
        } else {
          passager->frontiere = 1;
        }
      }
    }
  }

  return passager->frontiere;
}

/**
 * Passe un passager à la frontière
 * @param  passager Passager*
 * @return          int
 */
int passerSecurite(Passager *passager) {
  int interdit;
  printf("La securite n'accepte pas de produits liquides de plus de 100mL ou d'objets contondants.");
  printf("En avez-vous en votre possession ?\n - 0 pour non\n -1 pour oui\n");
  scanf("%d", &interdit);

  if (interdit == 1){
    printf("Vous ne pouvez pas passer la securite.\n");
    passager->securite = 0;
  } else{
    printf("Vous venez de passer la securite.");
    passager->securite = 1;
  }
  return passager->securite;
}

/**
 * Fonction qui permet d'embarquer un passager
 * @return  [description]
 */
int embarquement(void) {
  Passager *passager = trouverPassager();

  if (passager->prioritaire == 1) {
    passager->embarquer = 1;
    printf("[SUCCESS] Vous avez embarqué.");
    return 1;
  }

  for (int i = 0; i < vol->places_reservees ; i++) {
      if (vol->passagers[i].prioritaire == 1 && vol->passager[i].embarquer == 0){
        printf("[ERROR] Vous ne passerez pas. Il reste des passagers prioritaires à embarquer.\n");
        return 0;
      }
  }
  printf("[SUCCES] Vous avez embarqué.");
  return 1;
}

/**
 * Permet de déposer les bagages d'un passager
 */
void deposerBagages(void) {
  Passager *passager = trouverPassager();
  for (int i = 0; i < passager->nb_bagages; i++) {
    passager->bagages[i].embarque = 1;
  }
}

int peutDecoller(void) {
  for (int i = 0; i < vol->places_reservees; i++)
  {
    if (vol->passager[i].enregistrer == 1) {
      if (vol->passager[i].embarquer == 0)
      {
        printf("[ERROR]Un passager n'a pas embarqué.\n");
        return 0;
      }
      for (int i = 0; i < vol->passager[i].nb_bagages; i++)
      {
        if (vol->passager[i].bagages[i].embarque == 0) {
          printf("[ERROR] Un passager n'a pas emarquer ses bagages\n");
          return 0;
        }
      }
    }
  }
  printf("[SUCCES] L'avion va maintenant décoller.\n Bon vol à tous!\n");
  return 1;
}

int creerVol(void){
  Vol *vol;
  int n; // nécessaire pour ajouter plus qu'un unique vol en utilisant une seule fois la fonction

  printf("Bienvenue dans l'espace de creation d'un vol");

  vol = (Vol*)malloc(n*sizeof(Vol));

  printf("Nous allons creer un vol depuis l'aeroport vers une destination.\n Ou voulez-vous vous rendre ?\n");
  scanf("%s", vol->destination);
  printf("Choisissez votre heure de depart :\n");
  scanf("%s", vol->heure_depart);
  printf("Choisissez votre heure d'arrivee :\n");
  scanf("%s", vol->heure_arrivee);
  printf("Combien voulez-vous de sieges sur une rangee ?\n");
  scanf("%d", &vol->siege_rangee);
  printf("Combien voulez-vous de sieges sur une rangee ?\n");
  scanf("%d", vol->siege_colonne);

  vol->places_libres = vol->siege_colonne * vol->siege_rangee;
  printf("Votre vol comprend %d places libres au total.\n", vol->places_libres);

  printf("Est-ce que les passagers ont besoin d'un VISA pour se rendre dans la destination prevue par le vol ?\n - 0 pour non\n - 1 pour oui");
  scanf("%d", &vol->visa_requis);
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
