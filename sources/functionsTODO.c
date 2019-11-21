#include <stdio.h>
#include <stdlib.h>
#include "structures.c"

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

  vol=(Vol*)malloc(n*sizeof(Vol));

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
  // heure d'arrivée, de départ, la destination, le nombre de place totales, visa ?
}

int main(void) {

  return 0;
}
