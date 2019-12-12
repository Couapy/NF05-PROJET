/**
 * @file projet.c
 * @author Marchand Mael & Calixte Axel
 * @brief Projet de Gestion des Passagers d'un Aéroport
 * @version 1
 * @date 2019-12-12
 *
 * @copyright Copyright (c) 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "structures.c"
/**
 * @def VOLS_MAX
 * @brief Constante du maximum de vols
 */
#define VOLS_MAX 255


Vol vols[VOLS_MAX]; /** Tableau de tout les vols **/
int nb_vols = 0; /** Nombre de vols enregistrés en mémoire **/
int last_id_bagage = 0; /** Dernier numéro de ticket bagage délivré **/

// TODO: Demander le passeport
// TODO: Commenter le code

/**
 * Permet de saisir une date
 * @param date La date à écrire
 */
void saisirDate(Date *date){
  printf(" > Jour (format JJ) : ");
  scanf("%d", &date->jour);
  printf(" > Mois (format MM) : ");
  scanf("%d", &date->mois);
  printf(" > Annee (format AAAA) : ");
  scanf("%d", &date->annee);
}

/**
 * Permet de saisir un horaire
 * @param temps L'horaire à saisir
 */
void saisirTemps(Temps *temps){
  printf(" > Heure : ");
  scanf("%d", &temps->heure);
  printf(" > Minutes : ");
  scanf("%d", &temps->minutes);
}

/**
 * Trouve un passager selon un Nom ou un Numero de billet
 * @return  Le passager sélectionner
 */
Passager* trouverPassager(void) {
  char reponse[64];
  unsigned long billet = 0;
  int nb_passagers, id_passager, vol_passager, selection;
  while (1) {
    printf("\nNom ou Numero de billet : ");
    scanf(" %s", reponse);
    sscanf(reponse, "%ld", &billet);
    nb_passagers = 0;
    for (int i = 0; i < nb_vols; i++) {
      for (int j = 0; j < vols[i].places_reservees; j++) {
        if (strcmp(reponse, vols[i].passagers[j]->nom) == 0 ||
            billet == vols[i].passagers[j]->billet) {
          id_passager = j;
          vol_passager = i;
          nb_passagers += 1;
        }
      }
    }
    if (nb_passagers == 1) {
      printf(
        "[INFO] %s %s #%010lu a ete selectionne\n",
        vols[vol_passager].passagers[id_passager]->nom,
        vols[vol_passager].passagers[id_passager]->prenom,
        vols[vol_passager].passagers[id_passager]->billet
      );
      return vols[vol_passager].passagers[id_passager];
    } else if (nb_passagers > 1) {
      printf("[INFO] Il y a plusieurs passagers qui ont le meme nom\n\n");
      nb_passagers = 0;
      for (int i = 0; i < nb_vols; i++) {
        for (int j = 0; j < vols[i].places_reservees; j++) {
          if (strcmp(reponse, vols[i].passagers[j]->nom) == 0) {
            nb_passagers += 1;
            printf(
              "[%d] %s %s #%010lu > %s\n",
              nb_passagers,
              vols[i].passagers[j]->nom,
              vols[i].passagers[j]->prenom,
              vols[i].passagers[j]->billet,
              vols[i].destination
            );
          }
        }
      }
      printf("Quelle est le numero de la personne que vous recherchez ? ");
      scanf("%d", &selection);
      nb_passagers = 0;
      for (int i = 0; i < nb_vols; i++) {
        for (int j = 0; j < vols[i].places_reservees; j++) {
          if (strcmp(reponse, vols[i].passagers[j]->nom) == 0 ||
              billet == vols[i].passagers[j]->billet) {
            nb_passagers += 1;
            if (selection == nb_passagers) {
              printf(
                "[INFO] %s %s #%010lu a ete selectionne\n",
                vols[vol_passager].passagers[id_passager]->nom,
                vols[vol_passager].passagers[id_passager]->prenom,
                vols[vol_passager].passagers[id_passager]->billet
              );
              return vols[i].passagers[j];
            }
          }
        }
      }
    }
    printf("\a[ERROR] Nous n'avons pas trouve le passager\n");
  }
}

/**
 * Trouve le vol d'un passager à oar
 * @param  passager Le passager
 * @return          Le vol du passager
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
 * @param passager Passager à afficher
 */
void afficherPassager(Passager *passager) {
  printf("\n  %s %s est %s\n", passager->nom, passager->prenom, passager->nationalite);
  printf("  Billet : %010lu\n", passager->billet);
  printf("  Naissance : %d/%d/%d\n", passager->date_naissance.jour, passager->date_naissance.mois, passager->date_naissance.annee);
  printf("  Prioritaire : %d\n", passager->prioritaire);
  printf("  Bagages : %d\n", passager->nb_bagages);
  printf("  VISA : %d\n", passager->visa);
  printf("  Frontiere : %d\n", passager->frontiere);
  printf("  Securite : %d\n", passager->securite);
  if (passager->siege.rangee != -1 && passager->siege.colonne != -1) {
    printf("  Siege : %c%02d\n", passager->siege.rangee + '@', passager->siege.colonne);
  } else {
    printf("  Siege : N/A\n");
  }
  printf("  Enregistre : %d\n", passager->enregistrer);
  printf("  Embarquer : %d\n", passager->embarquer);
  for (int i = 0; i < passager->nb_bagages; i++) {
    printf("    Bagage#%d \n", passager->bagages[i].ticket);
  }
  printf("    ");
}

/**
 * Permet de sélectionner un vol
 * @return  Le vol sélectionné
 */
Vol* selectionnerVol(void) {
  if (nb_vols == 1) {
    printf("\n[INFO] %s est l'unique vol\n", vols[0].numero_vol);
    return &vols[0];
  } else {
    int numero;

    afficherVols();
    do {
      printf("Entrez le numero du vol : ");
      scanf(" %d", &numero);
    } while(numero > nb_vols);

    return &vols[numero-1];
  }
}

/**
 * Fonction qui génère un billet à un passager
 * @param passager Le passager sans billet
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
 * @param passager Le passager à saisir
 */
void saisirPassager(Passager *passager) {
  printf("\nEntrez le nom du passager : ");
  scanf(" %s", passager->nom);
  printf("Entrez le prenom du passager : ");
  scanf(" %s", passager->prenom);
  printf("Nationalite du passager : ");
  scanf(" %s", passager->nationalite);
  printf("Est-il prioritaire ? (1 - oui ou 0 - non) ");
  scanf(" %d", &passager->prioritaire);
  printf("Indiquez sa date de naissance : \n");
  saisirDate(&passager->date_naissance);

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
 */
void ajouterPassager(void) {
  if (nb_vols > 0) {
    Vol *vol = selectionnerVol();
    if (vol->places_libres > 0) {
      Passager *passager = (Passager*)malloc(sizeof(Passager));

      //On génère le passager
      saisirPassager(passager);
      genererBillet(passager);

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
 * @param passager Le passafer qui doit enregistrer ses bagages
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
    passager->bagages[i].embarque = 1;
  }
}

/**
 * Permet d'afficher le boarding pass
 * @param passager Le passager
 * @param vol      Le vol du passager
 */
void afficherBoardingPass(Passager *passager, Vol *vol) {
  printf("Carte d'embarquement:\n\n");
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
    "  Depart: %dh%d / Arrivee prevue a : %dh%d\n",
    vol->numero_vol,
    vol->destination,
    vol->heure_depart.heure, vol->heure_depart.minutes,
    vol->heure_arrivee.heure, vol->heure_arrivee.minutes
  );
}

/**
 * Permet de savoir si une place est libre dans un vol
 * @param  place Siège à tester
 * @param  vol   Vol dans lequel on va vérifier qu'il est libre
 * @return       1 pour un succes ou 0 pour un échec
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
 * @param passager Passager qui doit choisir son siège
 * @return         1 pour un succes ou 0 pour un échec
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
      } while (!placeLibre(&place, vol));
      passager->siege = place;
      printf("[INFO] Votre place est la %c%02d\n", '@' + place.rangee, place.colonne);
      return 1;
    }
  }
}

/**
 * Permet d'enregistrer un passager sur son vol
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
 */
void passerFrontieres(void) {
  Passager *passager = trouverPassager();
  Vol *vol = trouverVol(passager);
  if (passager->frontiere == 0) {
    if (passager->enregistrer == 1) {
      printf("[INFO] Le numero de billet est : %010lu\n", passager->billet);
      printf("[INFO] Le passager a %d bagages\n", passager->nb_bagages);
      printf("[INFO] Le passager est %s se rend a %s\n",
        passager->nationalite, vol->destination);
      if (vol->visa_requis == 1) {
        printf("[INFO] Le passager a besoin de VISA\n");
        printf("Montrez votre VISA s'il vous plait :\n 0 - si vous ne l'avez "
        "pas \n 1 - si vous l'avez\n > ");
        scanf(" %d", &passager->visa);
        if (passager->visa == 1) {
          printf("[INFO] Tous les papiers sont en regle\n\n");
          passager->frontiere = 1;
        } else {
          printf("\a[ERROR] Le passager ne possede pas de VISA\n\n");
        }
      } else {
        printf("[INFO] Le passager n'a pas besoin de VISA\n\n");
        passager->frontiere = 1;
      }
      if (passager->frontiere == 1) {
        printf("[SUCCESS] Le passager a passe la frontiere\n\n");
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
 */
void passerSecurite(void) {
  Passager *passager = trouverPassager();
  if (passager->frontiere == 1) {
    if (passager->securite == 0) {
      int interdit, reponse;
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
    } else {
      printf("\n\a[ERROR] Le passager a deja passe la securite\n\n");
    }
  } else {
    printf("\n\a[ERROR] Le passager n'a pas passe la frontiere\n\n");
  }
}

/**
 * Embarquement d'un passager
 * @return  1 pour un succes ou 0 pour un échec
 */
int embarquement(void) {
  Passager *passager = trouverPassager();
  Vol *vol = trouverVol(passager);

  if (passager->frontiere != 1) {
    printf("\n\a[ERROR] Le passager n'a pas passe la frontiere\n\n");
    return 0;
  }
  if (passager->securite != 1) {
    printf("\n\a[ERROR] Le passager n'a pas passe la securite\n\n");
    return 0;
  }

  if (passager->prioritaire != 1) {
    for (int i = 0; i < vol->places_reservees ; i++) {
      if (vol->passagers[i]->enregistrer == 1 &&
          vol->passagers[i]->prioritaire == 1 &&
          vol->passagers[i]->embarquer == 0) {
        printf("\n\a[ERROR] Vous ne passerez pas. Il reste des passagers prioritaires à embarquer.\n\n");
        return 0;
      }
    }
  }

  passager->embarquer = 1;
  printf("\n[SUCCESS] Vous avez embarque.\n\n");
  return 1;
}

/**
 * Permet de faire decoller un avion
 * @return  1 pour un succes ou 0 pour un échec
 */
int decoller(void) {
  if (nb_vols > 0) {
    Vol *vol = selectionnerVol();
    int non_enregistre = 0;

    for (int i = 0; i < vol->places_reservees; i++) {
      if (vol->passagers[i]->enregistrer == 1) {
        if (vol->passagers[i]->embarquer == 0) {
          printf("\a[ERROR]Un passager n'a pas embarque.\n\n");
          return 0;
        }
        for (int j = 0; j < vol->passagers[i]->nb_bagages; j++) {
          if (vol->passagers[i]->bagages[j].embarque == 0) {
            printf(
              "\a[ERROR] %s %s n'a pas embarque ses bagages\n\n",
              vol->passagers[i]->nom,
              vol->passagers[i]->prenom
            );
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

  printf("\nQuelle est la date du vol ?\n");
  saisirDate(&vol->date);
  printf("Le vol est le %d/%d/%d", vol->date.jour, vol->date.mois, vol->date.annee);
  printf("\nQuelle est la destination du vol ? ");
  scanf(" %s", vol->destination);
  printf("Choisissez votre heure de depart ?\n");
  saisirTemps(&vol->heure_depart);
  printf("Choisissez votre heure d'arrivee ?\n");
  saisirTemps(&vol->heure_arrivee);
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
  "[6]   embarquer             : Embarquer un passager\n"
  "[7]   decoller              : Faire decoller un avion\n\n"
  "[11]  afficher vols         : Afficher tous les vols\n"
  "[12]  afficher info vol     : Afficher les informations d'un vol\n\n"
  "[21]  sauvegarder           : Sauvegarder l'instance\n"
  "[21]  restaurer             : Restaurer l'instance\n\n"
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
    printf("Heure de depart : %dh%d\n", vol->heure_depart.heure, vol->heure_depart.minutes);
    printf("Heure d'arrivee : %dh%d\n", vol->heure_arrivee.heure, vol->heure_arrivee.minutes);
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
 * @return  1 pour un succes ou 0 pour un échec
 */
int sauvegarder(void) {
  FILE *fvols = NULL, *fpassagers = NULL;
  char chemin_vols[64], chemin_passagers[64], nom_fichier[24];

  printf("\nNom de la sauvegarde : ");
  scanf("%s", nom_fichier);
  sprintf(chemin_vols, "data/%s_vols.txt", nom_fichier);
  sprintf(chemin_passagers, "data/%s_passagers.txt", nom_fichier);
  fvols = fopen(chemin_vols, "w+");
  fpassagers = fopen(chemin_passagers, "w+");

  if (fvols == NULL || fpassagers == NULL) {
    printf("\a[ERROR] Impossible de créer la sauvegarde\n\n");
    return 0;
  }

  // On enregistre les données de chaque vols sauf les passagers
  printf("[INFO] Enregistrement des vols en cours...\n");
  fprintf(fvols, "%d\n", nb_vols);
  fprintf(fvols, "%d\n", last_id_bagage);
  for (int i = 0; i < nb_vols; i++) {
    fprintf(fvols, "%s\n", vols[i].numero_vol);
    fprintf(fvols, "%s\n", vols[i].destination);
    fprintf(
      fvols,
      "%d/%d/%d\n",
      vols[i].date.jour,
      vols[i].date.mois,
      vols[i].date.annee
    );
    fprintf(
      fvols,
      "%dH%d\n",
      vols[i].heure_depart.heure,
      vols[i].heure_depart.minutes
    );
    fprintf(
      fvols,
      "%dH%d\n",
      vols[i].heure_arrivee.heure,
      vols[i].heure_arrivee.minutes
    );
    fprintf(fvols, "%d\n", vols[i].visa_requis);
    fprintf(fvols, "%d\n", vols[i].places_reservees);
    fprintf(fvols, "%d\n", vols[i].places_libres);
    fprintf(fvols, "%d\n", vols[i].sieges_rangee);
    fprintf(fvols, "%d\n", vols[i].sieges_colonne);
  }

  // On enregistre tout les passagers de chaque vols
  printf("[INFO] Enregistrement des passagers en cours...\n");
  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      fprintf(fpassagers, "%s\n", vols[i].passagers[j]->nom);
      fprintf(fpassagers, "%s\n", vols[i].passagers[j]->prenom);
      fprintf(fpassagers, "%s\n", vols[i].passagers[j]->nationalite);
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->visa);
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->frontiere);
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->securite);
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->nb_bagages);
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->prioritaire);
      fprintf(fpassagers, "%010lu\n", vols[i].passagers[j]->billet);
      fprintf(
        fpassagers,
        "%d/%d/%d\n",
        vols[i].passagers[j]->date_naissance.jour,
        vols[i].passagers[j]->date_naissance.mois,
        vols[i].passagers[j]->date_naissance.annee
      );
      fprintf(
        fpassagers,
        "%d %d\n",
        vols[i].passagers[j]->siege.rangee,
        vols[i].passagers[j]->siege.colonne
      );
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->enregistrer);
      fprintf(fpassagers, "%d\n", vols[i].passagers[j]->embarquer);
      for (int k = 0; k < vols[i].passagers[j]->nb_bagages; k++) {
        fprintf(fpassagers, "%d %d ",
          vols[i].passagers[j]->bagages[k].ticket,
          vols[i].passagers[j]->bagages[k].embarque
        );
      }
      fprintf(fpassagers, "\n\n");
    }
  }

  fclose(fvols);
  fclose(fpassagers);

  printf("[SUCCESS] La sauvegarde a ete effectuee\n\n");
  return 1;
}

/**
 * Permet de restaurer une instance à partir d'un fichier
 * @return  1 pour un succes ou 0 pour un échec
 */
int restaurer(void) {
  FILE *fvols = NULL, *fpassagers = NULL;
  char chemin_vols[64], chemin_passagers[64], nom_fichier[24];

  printf("\nNom de la sauvegarde : ");
  scanf("%s", nom_fichier);
  sprintf(chemin_vols, "data/%s_vols.txt", nom_fichier);
  sprintf(chemin_passagers, "data/%s_passagers.txt", nom_fichier);
  fvols = fopen(chemin_vols, "r");
  fpassagers = fopen(chemin_passagers, "r");

  if (fvols == NULL || fpassagers == NULL) {
    printf("\a[ERROR] Impossible d'ouvrir la sauvegarde\n\n");
    return 0;
  }

  // On restaure les données de chaque vols sauf les passagers
  printf("[INFO] Restauration des vols en cours...\n");
  fscanf(fvols, "%d\n", &nb_vols);
  fscanf(fvols, "%d\n", &last_id_bagage);
  for (int i = 0; i < nb_vols; i++) {
    fscanf(fvols, "%s\n", vols[i].numero_vol);
    fscanf(fvols, "%s\n", vols[i].destination);
    fscanf(
      fvols,
      "%d/%d/%d\n",
      &vols[i].date.jour,
      &vols[i].date.mois,
      &vols[i].date.annee
    );
    fscanf(
      fvols,
      "%dH%d\n",
      &vols[i].heure_depart.heure,
      &vols[i].heure_depart.minutes
    );
    fscanf(
      fvols,
      "%dH%d\n",
      &vols[i].heure_arrivee.heure,
      &vols[i].heure_arrivee.minutes
    );
    fscanf(fvols, "%d\n", &vols[i].visa_requis);
    fscanf(fvols, "%d\n", &vols[i].places_reservees);
    fscanf(fvols, "%d\n", &vols[i].places_libres);
    fscanf(fvols, "%d\n", &vols[i].sieges_rangee);
    fscanf(fvols, "%d\n", &vols[i].sieges_colonne);
  }

  // On restaure tout les passagers de chaque vols
  printf("[INFO] Restauration des passagers en cours...\n");
  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; j < vols[i].places_reservees; j++) {
      vols[i].passagers[j] = (Passager*)malloc(sizeof(Passager));
      fscanf(fpassagers, "%s\n", vols[i].passagers[j]->nom);
      fscanf(fpassagers, "%s\n", vols[i].passagers[j]->prenom);
      fscanf(fpassagers, "%s\n", vols[i].passagers[j]->nationalite);
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->visa);
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->frontiere);
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->securite);
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->nb_bagages);
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->prioritaire);
      fscanf(fpassagers, "%010lu\n", &vols[i].passagers[j]->billet);
      fscanf(
        fpassagers,
        "%d/%d/%d\n",
        &vols[i].passagers[j]->date_naissance.jour,
        &vols[i].passagers[j]->date_naissance.mois,
        &vols[i].passagers[j]->date_naissance.annee
      );
      fscanf(
        fpassagers,
        "%d %d\n",
        &vols[i].passagers[j]->siege.rangee,
        &vols[i].passagers[j]->siege.colonne
      );
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->enregistrer);
      fscanf(fpassagers, "%d\n", &vols[i].passagers[j]->embarquer);
      for (int k = 0; k < vols[i].passagers[j]->nb_bagages; k++) {
        fscanf(fpassagers, "%d %d ",
          &vols[i].passagers[j]->bagages[k].ticket,
          &vols[i].passagers[j]->bagages[k].embarque
        );
      }
    }
  }

  fclose(fvols);
  fclose(fpassagers);

  printf("[SUCCESS] La restauration a ete effectuee\n\n");
  return 1;
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
* @brief Fonction principale du projet
 *
 * Gestion de la partie console avec laquelle l'utilisateur intéragit
 *
 * @return int
 */
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
    { 6, "embarquer" },
    { 7, "decoller" },
    { 0, "aide" },
    { 11, "afficher vols" },
    { 12, "afficher info vol" },
    { 21, "sauvegarder" },
    { 22, "restaurer" },
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
      case 6: embarquement(); break;
      case 7: decoller(); break;
      case 0: afficherAide(); break;
      case 11: afficherVols(); break;
      case 12: afficherInfoVol(); break;
      case 21: sauvegarder(); break;
      case 22: restaurer(); break;
      case 100: fermer(); return 0;
      default:
        printf("\nLa commande n'a pas ete reconnue, vous pouvez consulter l'aide en"
        " tapant 'aide'\n\n");
    }
  }
}
