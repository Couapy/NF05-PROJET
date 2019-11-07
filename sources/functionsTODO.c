#include <stdio.h>
#include <stdlib.h>
#include "structures.c"

int passerFrontieres(Passager *passager, Vol *vol) {
  printf("Vérification des documents:\n");
  if (passager->billet[0] != '\0'){
    printf("Votre billet est bien le numéro : %s\n", passager->billet);
    if (passager->enregistrer == 1) {
      if (passager->bagages[0].ticket != 0) {
        printf("Vous avez bien %d bagages avec vous.\n", passager->bagages[0]);
        printf("Vous etes de nationalitee : %s et vous vous rendez à %s.\n", passager->nationalite, vol->destination);
          if (vol->visa_requis == 1) {
            printf("Montrez votre VISA s'il vous plait :\n 0 - si vous ne l'avez pas \n 1 - si vous l'avez\n");
            scanf("%d", &passager->visa);
            if (passager->visa == 1){
              passager->frontiere = 1;
            } else {
              passager->frontiere = 0;
            }
        } else {
          passager->frontiere = 0;
        }
      } else {
        passager->frontiere = 0;
      }
    } else {
      passager->frontiere = 0;
    }
  } else {
    passager->frontiere = 0;
  }

  return passager->frontiere;
}

int passerSecurite(Passager *passager) {
  printf("La securite n'accepte pas de produits liquides de plus de 100mL ou d'objets contondants.");
  printf("En avez-vous en votre possession ?\n - 0 pour oui\n -1 pour non\n");
  scanf("%d", &passager->interdit);

  if (passager->interdit == 1){
    printf("Vous venez de passer la securite.");
    passager->securite = 1;
  }
  else{
    printf("Vous ne pouvez pas passer la securite.\n");
    passager->securite = 0;
  }
  return passager->securite;
}

int embarquement(void) {
  //Embarquer d'abord les passagers prioritaires
  // Tant qu'il reste un passager prioritaire non embarqué, ne pas embarquer les autres passagers
}

int passagerPrioriatireNonEmbarquer(void) {
  return 0 || 1;
}

int chargerBagages(void) {
  return 0 || 1;
}

int peutDecoller(void) {
  // V´erifier que l’avion peut d´ecoller en v´erifiant que tous les passagers enregistr´es ont
  // embarqu´e et que tous les bagages sont charg´es.

  return 0 || 1;
}

int creerVol(void){
    // heure d'arrivée, de départ, la destination, le nombre de place totales, visa ?
}

int main(void) {

  return 0;
}
