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

int passerSecurite(void) {
  printf("La securite n'accepte pas de produits liquides de plus de 100mL ou d'objets contondants.");
  printf("En avez-vous en votre possession ?\n - 0 pour oui\n -1 pour non\n");
  scanf("%d", &passager->interdit);

  if (passager->interdit == 1){
    printf("Vous venez de passer la securite.");
    passager->securite = 1;
  } 
  else{
    passager->securite = 0;
    printf("Vous ne pouvez pas passer la securite.\n");
  }
  return 0;
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