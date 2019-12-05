#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "structures.c"
#define VOLS_MAX 255

Vol vols[VOLS_MAX];
int nb_vols = 0;
int last_id_bagage = 0;

/**
 * Trouve un passager selon un Nom ou un Numero de billet
 * @return  Passager*
 */
Passager* trouverPassager(void) {
  char reponse[64];
  unsigned long billet = 0;
  while (1) {
    printf("\nNom ou Numero de billet : ");
    scanf(" %s", reponse);
    sscanf(reponse, "%d", &billet);
    for (int i = 0; i < nb_vols; i++) {
      for (int j = 0; j < vols[i].places_reservees; j++) {
        if (strcmp(reponse, vols[i].passagers[j]->nom) == 0 ||
            billet == vols[i].passagers[j]->billet) {
          printf(
            "[INFO] %s %s #%010lu a ete selectionne\n",
            vols[i].passagers[j]->nom,
            vols[i].passagers[j]->prenom,
            vols[i].passagers[j]->billet
          );
          return vols[i].passagers[j];
        }
      }
    }
    printf("\a[ERROR] Nous n'avons pas trouve le passager\n");
  }
}

/**
 * Trouve le vol d'un passager
 * @param  passager Passager*
 * @return          Passager*
 */
Vol* trouverVol(Passager *passager) {
  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      if (passager->billet == vols[i].passagers[j]->billet) {
        return &vols[i];
      }
    }
  }
}

/**
 * Permet d'afficher tous les vols
 */
void afficherVols(void) {
  printf("\nVoici la liste des vols :\n");
  for (int i = 0; i < nb_vols; i++) {
    printf("[%d] %s, %d passagers\n", i+1, vols[i].destination, vols[i].places_reservees);
  }
  printf("%d vols affiches\n\n", nb_vols);
}

/**
* Affiche les informations d'un passager
*/
void afficherPassager(Passager *passager) {
  printf("\n  %s %s est %s\n", passager->nom, passager->prenom, passager->nationalite);
  printf("  Billet : %010lu\n", passager->billet);
  printf("  Naissance : %s\n", passager->date_naissance);
  printf("  Prioritaire : %d\n", passager->prioritaire);
  printf("  Bagages : %d\n", passager->nb_bagages);
  printf("  VISA : %d\n", passager->visa);
  printf("  Frontiere : %d\n", passager->frontiere);
  printf("  Securite : %d\n", passager->securite);
  printf("  Siege : %c%02d\n", passager->siege.rangee + '@', passager->siege.colonne);
  printf("  Enregistre : %d\n", passager->enregistrer);
  printf("  Embarquer : %d\n", passager->embarquer);
  for (int i = 0; i < passager->nb_bagages; i++) {
    printf("    Bagage#%d \n", passager->bagages[i].ticket);
  }
  printf("    ");
}

/**
 * Permet de sélectionner un vol
 * @return  Vol*
 */
Vol* selectionnerVol(void) {
  int numero;

  afficherVols();
  do {
    printf("Entrez le numero du vol : ");
    scanf(" %d", &numero);
  } while(numero > nb_vols);

  return &vols[numero-1];
}

/**
 * Fonction qui génère un billet à un passager
 * @param passager Passager*
 */
void genererBillet(Passager *passager) {
  int continuer = 1;
  unsigned long billet = 0;
  float nb_rand;

  while (continuer == 1) {
    continuer = 0;

    billet = (float)rand()/RAND_MAX * pow(10, 10);

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

  passager->billet = billet;
}

/**
 * Saisie d'un passager par l'utilisateur
 * @param passager Passager*
 */
void saisirPassager(Passager *passager) {
  char reponse[10];

  printf("\nEntrez le nom du passager : ");
  scanf(" %s", passager->nom);
  printf("Entrez le prenom du passager : ");
  scanf(" %s", passager->prenom);
  printf("Nationalite du passager : ");
  scanf(" %s", passager->nationalite);
  printf("Est-il prioritaire ? (1 - oui ou 0 - non) ");
  scanf(" %d", &passager->prioritaire);
  printf("Indiquez sa date de naissance en format JJ/MM/AAAA : ");
  scanf(" %s", passager->date_naissance);

  passager->billet = 0;
  passager->nb_bagages = 0;
  passager->bagages[0].ticket = 0;
  passager->bagages[1].ticket = 0;
  passager->enregistrer = 0;
  passager->embarquer = 0;
  passager->visa = 0;
  passager->frontiere = 0;
  passager->securite = 0;
  passager->siege.rangee = -1;
  passager->siege.colonne = -1;
}

/**
 * On ajoute un passager à un vol
 * @param  vol Vol*
 */
void ajouterPassager(void) {
  if (nb_vols > 0) {
    Vol *vol = selectionnerVol();
    if (vol->places_libres > 0) {
      Passager *passager = (Passager*)malloc(sizeof(Passager));

      //On génère le passager
      saisirPassager(passager);
      genererBillet(passager);

      // Les informations du passager sont montrés en une "jolie" phrase.
      printf("%s %s ne(e) le %s ", passager->nom, passager->prenom, passager->date_naissance);
      if (passager->prioritaire == 1){
        printf("est prioritaire.\n");
      } else {
        printf("n'est pas prioritaire.\n");
      }

      printf("Votre numero de billet : %010lu\n", passager->billet);

      vol->passagers[vol->places_reservees] = passager;
      vol->places_libres -= 1;
      vol->places_reservees += 1;
      printf("[INFO] Ajout reussi du passager au vol\n\n");
    } else {
      printf("\a[ERROR] Il n'y a plus de places sur le vol\n\n");
    }
  } else {
    printf("\n\a[ERROR] Il n'y pas encore de vol enregistre\n\n");
  }
}

/**
 * Permet d'enregistrer les bagages d'un passager lors de son Enregistrement
 * @param [name] [description]
 */
void enregistrerBagages(Passager *passager) {
  int nb_bagages, nb_bagages_max = 1;
  if (passager->prioritaire == 1) {
    nb_bagages_max = 2;
  }
  nb_bagages = nb_bagages_max + 1;

  printf("\n[INFO] Vous avez le droit a %d bagages maximum\n", nb_bagages_max);
  while (nb_bagages > nb_bagages_max) {
    printf("Combien de bagages avez-vous ? ");
    scanf(" %d", &nb_bagages);
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
  printf("  Carte d'embarquement:\n\n");
  printf(
    "  M/Mme %s %s\n"
    "  Priorite: %d\n"
    "  Numero billet: %lu\n",
    passager->nom,
    passager->prenom,
    passager->prioritaire,
    passager->billet
  );
  printf(
    "  Vol numero: %s a destination de %s depuis Paris\n"
    "  Depart: %s / Arrivee prevue a : %s\n",
    vol->numero_vol,
    vol->destination,
    vol->heure_depart,
    vol->heure_arrivee
  );
}

/**
 * Permet de savoir si une place est libre dans un vol
 * @param  place Siege
 * @param  vol   Vol
 * @return       int
 */
int placeLibre(Siege *place, Vol *vol) {
  char place_max[4];
  char string_place[4];
  sprintf(place_max, "%c%d", place->rangee + '@', vol->sieges_colonne);
  sprintf(string_place, "%c%d", place->rangee + '@', place->colonne);

  if (1 > place->rangee || place->rangee > vol->sieges_rangee ||
  1 > place->colonne || place->colonne > vol->sieges_colonne) {
    return 0;
  }

  if (strcmp(string_place, "A1") > 0 && strcmp(string_place, place_max) < 0) {
    int i = 0, pastrouve = 1;
    while (i < vol->places_reservees && pastrouve == 1) {
      if (vol->passagers[i]->siege.rangee == place->rangee &&
        vol->passagers[i]->siege.colonne == place->colonne) {
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
    scanf(" %s", choix);
    if (strcmp(choix, "oui") == 0) {
      printf("Quelle est la place que vous voulez ?\n");
      printf("[INFO] 1 < Rangee < %d et 1 < Colonne < %d\n", vol->sieges_rangee, vol->sieges_colonne);
      printf("  > Rangee numero : ");
      scanf(" %d", &place.rangee);
      printf("  > Colonne numero : ");
      scanf(" %d", &place.colonne);
      if (placeLibre(&place, vol)) {
        passager->siege = place;
        printf("[INFO] Votre place est la %c%02d\n", '@' + place.rangee, place.colonne);
        return 1;
      }
      printf("\a[ERROR] La place est deja attribuee ou non valide\n");
    } else {
      do {
        place.rangee = ((float)rand()/RAND_MAX) * vol->sieges_rangee;
        place.colonne = ((float)rand()/RAND_MAX) * vol->sieges_colonne;
        printf("Rangee = %d, Colonne = %d\n", place.rangee, place.colonne);
      } while (!placeLibre(&place, vol));
      passager->siege = place;
      printf("[INFO] Votre place est la %c%02d\n", '@' + place.rangee, place.colonne);
      return 1;
    }
  }
}

/**
 * On enregistre un passager sur son vol
 */
void engeristrerPassager(void) {
  if (nb_vols > 0) {
    int personne = 0, i = 0;
    while (personne == 0 && i < nb_vols) {
      if (vols[i].places_reservees > 0) {
        personne = 1;
      }
      i++;
    }
    if (personne == 1) {
      Passager *passager = trouverPassager();
      if (passager->enregistrer == 0) {
        Vol *vol = trouverVol(passager);

        enregistrerBagages(passager);
        choisirSiege(passager, vol);

        passager->enregistrer = 1;
        afficherBoardingPass(passager, vol);
        printf("\n[SUCCESS] Le passager est enregistre\n\n");
      } else {
        printf("\n\a[ERROR] Le passager s'est deja enregistre\n\n");
      }
    } else {
      printf("\n\a[ERROR] Il n'y a aucun passager sur les vols\n\n");
    }
  } else {
    printf("\n\a[ERROR] Aucun vol existe\n\n");
  }
}

/**
 * Faire passer la frontière pour un passager
 * @param  passager Passager*
 * @param  vol      Vol*
 * @return          boolean
 */
void passerFrontieres(void) {
  Passager *passager = trouverPassager();
  Vol *vol = trouverVol(passager);
  if (passager->frontiere == 0) {
    if (passager->enregistrer == 1) {
      int bagages_enregistres = 1;
      for (int i = 0; i < passager->nb_bagages; i++) {
        if (passager->bagages[i].ticket == 0) {
          bagages_enregistres = 0;
        }
      }
      if (bagages_enregistres == 1) {
        printf("[INFO] Le numero de billet est : %010lu\n", passager->billet);
        printf("[INFO] Le passager a %d bagages\n", passager->bagages[0]);
        printf("[INFO] Le passager est %s se rend a %s\n",
          passager->nationalite, vol->destination);
        if (vol->visa_requis == 1) {
          printf("[INFO] Le passager a besoin de VISA\n");
          printf("Montrez votre VISA s'il vous plait :\n 0 - si vous ne l'avez "
          "pas \n 1 - si vous l'avez\n > ");
          scanf(" %d", &passager->visa);
          if (passager->visa == 1) {
            printf("[INFO] Tous les papiers sont en regle\n");
            passager->frontiere = 1;
          } else {
            printf("\a[ERROR] Le passager ne possede pas de VISA\n");
          }
        } else {
          printf("[INFO] Le passager n'a pas besoin de VISA\n");
          passager->frontiere = 1;
        }
        if (passager->frontiere == 1) {
          printf("[SUCCES] Le passager a passe la frontiere\n\n");
        }
      } else {
        printf("\n\a[ERROR] Le passager n'a pas depose ses bagages\n");
      }
    } else {
      printf("\n\a[ERROR] Le passager ne s'est pas enregistre\n\n");
    }
  } else {
    printf("\n\a[ERROR] Le passager a deja passe la frontiere\n\n");
  }
}

/**
 * Passe un passager à la frontière
 * @param  passager Passager*
 * @return          int
 */
void passerSecurite(void) {
  int interdit, reponse;
  Passager *passager = trouverPassager();
  FILE *fichier = NULL;
  char ch;

  printf("Voulez-vous afficher la liste des objets interdits en cabine ?\n - 0 pour non\n - 1 pour oui\n > ");
  scanf("%d", &reponse);

  if (reponse == 1){
    fichier = fopen("interdit.txt", "r");
    if(fichier == NULL){
      printf("Impossible d'ouvrir le fichier. Verifiez qu'il existe et que vous pouvez le lire.\n");
    }
    else {
      printf("\n");
      do{
        ch = fgetc(fichier);
        putchar(ch);
      }
      while(ch != EOF);
      printf("\n");
      fclose(fichier);
    }
  }

  printf("Avez-vous des objets interdits en votre possession ?\n - 0 pour non\n - 1 pour oui\n > ");
  scanf("%d", &interdit);

  if (interdit == 1){
    printf("\a[ERROR] Vous ne pouvez pas passer la securite.\n\n");
    passager->securite = 0;
  } else{
    printf("[SUCCESS]Vous venez de passer la securite.\n\n");
    passager->securite = 1;
  }
}

/**
 * Fonction qui permet d'embarquer un passager
 * @return  [description]
 */
int embarquement(void) {
  Passager *passager = trouverPassager();
  Vol *vol = trouverVol(passager);

  if (passager->securite != 1) {
    printf("\a[ERROR] Le passager n'a pas passe la securite\n\n");
    return 0;
  }
  if (passager->frontiere != 1) {
    printf("\a[ERROR] Le passager n'a pas passe la frontiere\n\n");
    return 0;
  }

  if (passager->prioritaire == 1) {
    passager->embarquer = 1;
    printf("[SUCCESS] Vous avez embarqué.\n\n");
    return 1;
  }

  for (int i = 0; i < vol->places_reservees ; i++) {
    if (vol->passagers[i]->prioritaire == 1 && vol->passagers[i]->embarquer == 0){
      printf("\a[ERROR] Vous ne passerez pas. Il reste des passagers prioritaires à embarquer.\n");
      return 0;
    }
  }

  printf("[SUCCESS] Vous avez embarqué.\n\n");
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

/**
 * Permet  de faire decoller un avion
 * @return  int
 */
int decoller(void) {
  if (nb_vols > 0) {
    Vol *vol = selectionnerVol();
    int non_enregistre = 0;

    for (int i = 0; i < vol->places_reservees; i++) {
      if (vol->passagers[i]->enregistrer == 1) {
        if (vol->passagers[i]->embarquer == 0)
        {
          printf("\a[ERROR]Un passager n'a pas embarque.\n");
          return 0;
        }
        for (int i = 0; i < vol->passagers[i]->nb_bagages; i++)
        {
          if (vol->passagers[i]->bagages[i].embarque == 0) {
            printf("\a[ERROR] Un passager n'a pas embarquer ses bagages\n");
            return 0;
          }
        }
      } else {
        non_enregistre++;
      }
    }

    if (non_enregistre > 0) {
      printf("[INFO] %d passagers ne se sont pas enregistres\n", non_enregistre);
    } else {
      printf("[INFO] Tous les passagers sont embarques\n");
    }

    // On cherche l'indice du vol dans le tableau vols pour le retirer
    int i = 0, trouve = 0;
    while (i < nb_vols && trouve == 0) {
      if (strcmp(vols[i].numero_vol, vol->numero_vol) == 0) {
        trouve = 1;
        for (int j = i; j < nb_vols-1; j++) {
          vols[j] = vol[j+1];
        }
      }
      i++;
    }
    nb_vols--;

    printf("[SUCCESS] L'avion va maintenant decoller.\nBon vol a tous!\n\n");
    return 1;
  } else {
    printf("\n\a[ERROR] Il n'y pas encore de vol enregistre\n\n");
    return 0;
  }
}

/**
 * Génération du numéro du vol aléatoirement
 * @param numero Numéro de Vol généré
 */
void genererNumeroVol(char *numero) {
  int numero1, numero2, numero3;
  numero1 = 26.0 * ((float)rand()/RAND_MAX) + 'A';
  numero2 = 26.0 * ((float)rand()/RAND_MAX) + 'A';
  do {
    numero3 = 10000.0 * ((float)rand()/RAND_MAX);
  } while (numero3 == 10000);
  sprintf(numero, "%c%c%04d", numero1, numero2, numero3);
}

/**
 * Permet de creer un vol
 */
void ajouterVol(void){
  Vol *vol = &vols[nb_vols];
  nb_vols++;

  printf("\nQuelle est la destination du vol ? ");
  scanf(" %s", vol->destination);
  printf("Choisissez votre heure de depart ? ");
  scanf(" %s", vol->heure_depart);
  printf("Choisissez votre heure d'arrivee ? ");
  scanf(" %s", vol->heure_arrivee);
  printf("Combien voulez-vous de sieges sur une rangee ? ");
  scanf(" %d", &vol->sieges_rangee);
  printf("Combien voulez-vous de sieges sur une colonne ? ");
  scanf(" %d", &vol->sieges_colonne);

  vol->places_libres = vol->sieges_colonne * vol->sieges_rangee;
  printf("Votre vol comprend %d places libres au total.\n", vol->places_libres);

  printf("Est-ce que les passagers ont besoin d'un VISA pour se rendre dans la "
  "destination prevue par le vol ?\n - 0 pour non\n - 1 pour oui\n  > ");
  scanf(" %d", &vol->visa_requis);

  genererNumeroVol(vol->numero_vol);

  printf("[INFO] Le numero de vol est le %s\n", vol->numero_vol);
  printf("[SUCCESS] Le vol a bien ete ajoute\n\n");
}

/**
 * Affiche le menu de l'aide
 */
void afficherAide(void) {
  printf("\n"
  "Bienvenue dans l'aide !\n"
  "Vous pouvez saisir les commandes, mais aussi le numero correspondant\n"
  "Voici les commandes disponibles :\n\n"
  "[1]   ajouter vol           : Ajouter un vol\n"
  "[2]   ajouter passager      : Ajouter un passager a un vol\n"
  "[3]   enregistrer           : Enregistrer un passage sur vol\n"
  "[4]   passer frontiere      : Passer un passager a un la frontiere\n"
  "[5]   passager securite     : Passer un passager a la securite\n"
  "[6]   desposer bagages      : Deposer les bagages d'un passager\n"
  "[7]   embarquer             : Embarquer un passager\n"
  "[8]   decoller              : Faire decoller un avion\n\n"
  "[11]  afficher vols         : Afficher tous les vols\n"
  "[12]  afficher info vol     : Afficher les informations d'un vol\n\n"
  "[21]  sauvegarder           : Sauvegarder l'instance\n"
  "[21]  restaurer             : Restaurer l'instance\n\n"
  "[99]  ping                  : Ping ???\n\n"
  "[0]   aide                  : Afficher l'aide\n"
  "[100] fermer                : Fermer le programme\n\n");
}

/**
 * Afficher les infromations d'un vol
 */
void afficherInfoVol(void) {
  if (nb_vols > 0) {
    Vol *vol = selectionnerVol();
    printf("\nDestination : %s\n", vol->destination);
    printf("Heure de depart : %s\n", vol->heure_depart);
    printf("Heure d'arrivee : %s\n", vol->heure_arrivee);
    printf("Nombre de passager : %d\n", vol->places_reservees);
    printf("Nombre de places libres : %d\n", vol->places_libres);
    printf("VISA requis : ");
    if (vol->visa_requis) {
      printf("oui\n\n");
    } else {
      printf("non\n\n");
    }
    printf("Liste des passagers :\n");
    for (int i = 0; i < vol->places_reservees; i++) {
      afficherPassager(vol->passagers[i]);
    }
    printf("\n");
  } else {
    printf("\n\a[ERROR] Il n'y pas encore de vol enregistre\n\n");
  }
}

/**
 * Sauvegarder l'instance du programme en cours
 */
void sauvegarder(void) {
  FILE *fvols = NULL, *fpassagers = NULL;
  char chemin_vols[64], chemin_passagers[64], nom_fichier[24];

  printf("\nNom de la sauvegarde : ");
  scanf("%s", nom_fichier);
  sprintf(chemin_vols, "data/%s_vols.txt", nom_fichier);
  sprintf(chemin_passagers, "data/%s_passagers.txt", nom_fichier);
  fvols = fopen(chemin_vols, "w+");
  fpassagers = fopen(chemin_passagers, "w+");

  fprintf(fvols, "%d\n", nb_vols);
  fprintf(fvols, "%d\n", last_id_bagage);
  for (int i = 0; i < nb_vols; i++) {
    fprintf(fvols, "%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n\n",
     vols[i].numero_vol,
     vols[i].heure_depart,
     vols[i].heure_arrivee,
     vols[i].destination,
     vols[i].places_reservees,
     vols[i].places_libres,
     vols[i].visa_requis,
     vols[i].sieges_rangee,
     vols[i].sieges_colonne
    );
  }

  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      fprintf(fpassagers, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%lu\n%s\n%d\n%d\n"
                          "%d\n%d\n\n",
        vols[i].passagers[j]->nom,
        vols[i].passagers[j]->prenom,
        vols[i].passagers[j]->nationalite,
        vols[i].passagers[j]->visa,
        vols[i].passagers[j]->frontiere,
        vols[i].passagers[j]->securite,
        vols[i].passagers[j]->nb_bagages,
        vols[i].passagers[j]->prioritaire,
        vols[i].passagers[j]->billet,
        vols[i].passagers[j]->date_naissance,
        vols[i].passagers[j]->siege.rangee,
        vols[i].passagers[j]->siege.colonne,
        vols[i].passagers[j]->enregistrer,
        vols[i].passagers[j]->embarquer
      );
      for (int k = 0; k < vols[i].passagers[j]->nb_bagages; k++) {
        fprintf(fpassagers, "%d %d ",
          vols[i].passagers[j]->bagages[k].ticket,
          vols[i].passagers[j]->bagages[k].embarque
        );
        fprintf(fpassagers, "\n");
      }
    }
  }

  fclose(fvols);
  fclose(fpassagers);

  printf("[SUCCESS] La sauvegarde a ete effectuee\n\n");
}

/**
 * Permet de restaurer une instance à partir d'un fichier
 */
void restaurer(void) {
  FILE *fvols = NULL, *fpassagers = NULL;
  char chemin_vols[64], chemin_passagers[64], nom_fichier[24];

  printf("\nNom de la sauvegarde : ");
  scanf("%s", nom_fichier);
  sprintf(chemin_vols, "data/%s_vols.txt", nom_fichier);
  sprintf(chemin_passagers, "data/%s_passagers.txt", nom_fichier);
  fvols = fopen(chemin_vols, "r");
  fpassagers = fopen(chemin_passagers, "r");

  if (fvols != 0 && fpassagers != 0) {
    fscanf(fvols, "%d\n", &nb_vols);
    fscanf(fvols, "%d\n", &last_id_bagage);
    printf("\n[INFO] Il y a %d vols a charger\n", nb_vols);
    for (int i = 0; i < nb_vols; i++) {
      fscanf(fvols, "%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n\n",
       vols[i].numero_vol,
       vols[i].heure_depart,
       vols[i].heure_arrivee,
       vols[i].destination,
       &vols[i].places_reservees,
       &vols[i].places_libres,
       &vols[i].visa_requis,
       &vols[i].sieges_rangee,
       &vols[i].sieges_colonne
      );
    }
    printf("[INFO] Les vols ont ete charges\n");
    fclose(fvols);

    for (int i = 0; i < nb_vols; i++) {
      for (int j = 0; j < vols[i].places_reservees; j++) {
        vols[i].passagers[j] =(Passager*)malloc(sizeof(Passager));
        fscanf(fpassagers, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%lu\n%s\n%d\n%d\n"
                           "%d\n%d\n\n",
          vols[i].passagers[j]->nom,
          vols[i].passagers[j]->prenom,
          vols[i].passagers[j]->nationalite,
          &vols[i].passagers[j]->visa,
          &vols[i].passagers[j]->frontiere,
          &vols[i].passagers[j]->securite,
          &vols[i].passagers[j]->nb_bagages,
          &vols[i].passagers[j]->prioritaire,
          &vols[i].passagers[j]->billet,
          vols[i].passagers[j]->date_naissance,
          &vols[i].passagers[j]->siege.rangee,
          &vols[i].passagers[j]->siege.colonne,
          &vols[i].passagers[j]->enregistrer,
          &vols[i].passagers[j]->embarquer
        );
        for (int k = 0; k < vols[i].passagers[j]->nb_bagages; k++) {
          fscanf(fpassagers, "%d %d ",
            &vols[i].passagers[j]->bagages[k].ticket,
            &vols[i].passagers[j]->bagages[k].embarque
          );
        }
      }
    }
    printf("[INFO] Les passagers ont ete charges\n");
    fclose(fpassagers);

    printf("[SUCCESS] La sauvegarde a ete chargee\n\n");
  } else {
    printf("\a[ERROR] Impossible de trouver la sauvegarde\n\n");
  }
}

/**
 * Libère les pointeurs passagers stockés dans chaque vol
 */
void fermer(void) {
  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      free(vols[i].passagers[j]);
    }
  }
  printf("\n>> Au plaisir de vous revoir\n");
}

/**
 * Pong ?
 */
void ping(void) {
  printf("\n  PONG ! \n\n");
}

int main(void) {
  srand(time(NULL));
  char commande[64];
  int fonction, choix_commande, nb_commandes, i;
  Commande commandes[] = {
    { 1, "ajouter vol" },
    { 2, "ajouter passager" },
    { 3, "enregistrer" },
    { 4, "passer frontiere" },
    { 5, "passer securite" },
    { 6, "deposer bagages" },
    { 7, "embarquement" },
    { 8, "decoller" },
    { 0, "aide" },
    { 11, "afficher vols" },
    { 12, "afficher info vol" },
    { 21, "sauvegarder" },
    { 22, "restaurer" },
    { 99, "ping" },
    { 100, "fermer" }
  };
  nb_commandes = sizeof(commandes) / sizeof(commandes[0]);

  printf("Bienvenue a Paris-Charles-De-Guaule !!\n");
  printf("Pour obtenir de l'aide, tapez 'aide'\n\n");

  while (1) {
    printf("operateur@tourDeControle:~$ ");
    choix_commande = 0;
    i = 0;
    while (1) {
      scanf("%c", &commande[i]);
      if (commande[i] == '\n') {
        if (i == 0) {
          continue;
        }
        commande[i] = '\0';
        break;
      }
      i++;
    }

    for (int i = 0; i < nb_commandes; i++) {
      if (strcmp(commande, commandes[i].commande) == 0) {
        fonction = commandes[i].fonction;
        choix_commande = 1;
      }
    }

    if (choix_commande == 0) {
      fonction = -1;
      if ('0' < commande[0] && commande[0] < '9') {
        sscanf(commande, " %d", &fonction);
      }
    }

    switch (fonction) {
      case 1: ajouterVol(); break;
      case 2: ajouterPassager(); break;
      case 3: engeristrerPassager(); break;
      case 4: passerFrontieres(); break;
      case 5: passerSecurite(); break;
      case 6: deposerBagages(); break;
      case 7: embarquement(); break;
      case 8: decoller(); break;
      case 0: afficherAide(); break;
      case 11: afficherVols(); break;
      case 12: afficherInfoVol(); break;
      case 21: sauvegarder(); break;
      case 22: restaurer(); break;
      case 99: ping(); break;
      case 100: fermer(); return 0;
      default:
        printf("\nLa commande n'a pas ete reconnue, vous pouvez consulter l'aide en"
        " tapant 'aide'\n\n");
    }
  }
}
