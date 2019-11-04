#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.c"

Vol vols[255];
int nb_vols = 0;

void genererBillet(Passager *passager) {
  int continuer;
  float nb_rand;
  char billet[11];
  billet[11] = '\0';

  printf("Generation du billet en cours...\n");

  while (billet[0] == '\0' || continuer == 1) {
    continuer = 0;

    for (int i = 0; i < 13; i++) {
      nb_rand = (float)rand()/RAND_MAX * 10.0;
      billet[i] = (int)nb_rand + '0';
    }
    billet[10] = '\0';

    int i = 0, j;
    while (i < nb_vols && continuer == 0) {
      j = 0;
      while (j < vols[i].places_reservees && continuer == 0) {
        if (vols[i].passagers[j].billet == billet) {
          continuer = 1;
        }
        j++;
      }
      i++;
    }
  }

  printf("Generation du billet terminee.\n");
  printf("Recopiage en cours... \n");

  passager->billet = billet;

  // strcpy(billet, passager->billet);

  // for (int i = 0; i < 11; i++) {
  //   passager->numero_billet[i] = billet[i];
  // }

  printf("Recopiage termine \n");
}

int main(void) {

  Passager *passager;
  genererBillet(passager);
  printf("%c", passager->billet[0]);
  printf("Le billet est : %s\n", passager->billet);

  return 0;
}
