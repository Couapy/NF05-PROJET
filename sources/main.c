#include <stdio.h>
#include "structures.c"
#include "fonctions.c"

Vol vols[255];
int nb_vols = 0;

int main(void) {
  char commande[24] = { "\0" };
  int nb_commandes = 8, i, selection;
  char commandes[][24] = {
    "ajouterVol",
    "ajouterPassager",
    "engeristrerPassager",
    "passerFrontieres",
    "passerSecurite",
    "deposerBagages",
    "embarquer",
    "decoller"
  };
  int fonctions[] = {
    &ajouterVol,
    &ajouterPassager,
    &engeristrerPassager,
    &passerFrontieres,
    &passerSecurite,
    &deposerBagages,
    &embarquer,
    &decoller
  };
  printf("Pour obtenir de l'aide, tapez 'help'\n\n");

  while (1) {
    printf("\n>");
    scanf(" %s", commande);
    if (strcmp(commande, "exit")) {
      return 0;
    }

    i = 0;
    selection = -1;
    while (i < nb_commandes && selection != -1) {
      if (strcmp(commande, commandes[i]) == 0) {
        selection = i;
      }
      i++;
    }

    if (selection < 0) {
      printf("La commande n'a pas été reconnue, vous pouvez consulter l'aide en"
      " tapant 'help'\n");
    }
    else {
      fonctions[selection]();
    }
  }
}
