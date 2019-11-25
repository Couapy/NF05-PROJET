#include <stdio.h>
#include <stdlib.h>

void sauvegarder(void) {
  FILE *fvols = NULL, *fpassagers = NULL;
  char chemin_vols[64], chemin_passagers[64], nom_fichier[24];
  int nb_passagers;

  printf("\nNom de la sauvegarde : ");
  scanf("%s", nom_fichier);
  sprintf(chemin_vols, "data/%s_vols.txt", nom_fichier);
  sprintf(chemin_passagers, "data/%s_passagers.txt", nom_fichier);
  fvols = fopen(chemin_vols, "w+");
  fpassagers = fopen(chemin_passagers, "w+");

  /**
   * On enregistre les vols
   * puis les passagers
   */

  fprintf(fvols, "%d\n", nb_vols);
  for (int i = 0; i < nb_vols; i++) {
    nb_passagers += vols[i]->places_reservees;
    fprintf(fvols, "%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
     vols[i]->passagers[j].numero_vol,
     vols[i]->passagers[j].heure_depart,
     vols[i]->passagers[j].heure_arrivee,
     vols[i]->passagers[j].destination,
     vols[i]->passagers[j].places_reservees,
     vols[i]->passagers[j].places_libres,
     vols[i]->passagers[j].visa_requis,
     vols[i]->passagers[j].sieges_rangee,
     vols[i]->passagers[j].sieges_colonne
    );
  }

  fprintf(fvols, "%d\n", nb_passagers);
  for (int i = 0; i < nb_vols; i++) {
    for (int j = 0; i < vols[i]->places_reservees; j++) {
      fprintf(fpassagers, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%s\n%s\n%d\n%d\n"
                          "%d\n%d\n",
        vols[i]->passager[j].nom,
        vols[i]->passager[j].prenom,
        vols[i]->passager[j].nationalite,
        vols[i]->passager[j].visa,
        vols[i]->passager[j].frontiere,
        vols[i]->passager[j].securite,
        vols[i]->passager[j].nb_bagages,
        vols[i]->passager[j].prioritaire,
        vols[i]->passager[j].billet,
        vols[i]->passager[j].date_naissance,
        vols[i]->passager[j].siege.rangee,
        vols[i]->passager[j].siege.colonne,
        vols[i]->passager[j].enregistrer,
        vols[i]->passager[j].embarquer,
      );
      for (int k = 0; k < vols[i]->passagers[j].nb_bagages; k++) {
        fprintf(fpassagers, "%d %d ",
          vols[i]->passagers[j].bagages.ticket
          vols[i]->passagers[j].bagages.embarque,
        );
        fprintf(fpassagers, "\n");
      }
    }
  }

  fclose(fvols);
  fclose(fpassagers);
}

void charger(void) {

}


int main(void) {

  sauvegarder();

  return 0;
}
