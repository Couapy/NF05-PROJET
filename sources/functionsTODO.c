int passerFrontieres(void) {
  printf("Vérification des documents:\n");
  if (passager->billet[0] != "\0"){
    printf("Votre billet est bien le numéro :\n%%s", passager->billet);
    if (passager->pass != "\0"){ TODO: BOARDING PASS 
      if (passager->bagage[0] != 0){
        printf("Vous avez bien %d bagages avec vous.\n", passager->bagage[0]);
        printf("Vous etes de nationalitee : %s et vous vous rendez à %s.\n", passager->nationalite, vol->destination);
          if(vol->visa_requis == 1){
            printf("Montrez votre VISA s'il vous plait :\n 0 - si vous ne l'avez pas \n 1 - si vous l'avez\n");
            scanf("%d", &passager->visa);
            if (passager->visa == 1){
              passager->frontiere = 1;
            }
            else {
              passager->frontiere = 1;
            }
        }
        else {
          passager->frontiere = 0;
        }
      }
      else {
        passager->frontiere = 0;
      }
    }
    else {
      passager->frontiere = 0;
    }
  }
  else {
    passager->frontiere = 0;
  }

  return 0;
}

int visaRequis(char destination[]) {
  //Trouver les pays qui ont besoin d'un VISA, ou pas

  return 0;
}

int passerSecurite(void) {
  // règles sur les liquides pour le bagage en main
  // règles sur les objets à prendre en cabine ?
  // afficher les objets à retirer des bagages
  return 1 || 0;
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
