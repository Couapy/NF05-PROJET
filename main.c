#include <stdio.h>
#include "structures.c"
#include "fonctions.c"

/**
 * register
 * ticket bagages + boarding pass
 * depot bagages
 * frontière
 * sécurité
 * embarquement
 */

int main(void) {
  char commande[64];
  while (strcmp(commande, "quitter") != 0) {
    printf("Sys> ");
    gets(commande);

    if (commande == "ajouter") {
      
    } else {
      // Aide
      printf("ajouter\n");
    }
    printf("\n");
  }

  return 0;
}
