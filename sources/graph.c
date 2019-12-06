#include <stdio.h>
#include <stdlib.h>

void afficherPourcentage(float pourcentage, int longueur) {
  printf("[");
  for (int i = 0; i < longueur * (int)pourcentage/100; i++) {
    printf("=");
  }
  for (int i = 0; i < longueur - longueur * (int)pourcentage/100; i++) {
    printf(" ");
  }
  printf("] %.2f%%\n", pourcentage);
}

int main(void) {
  
  for (float i = 0; i <= 100; i += 5.5) {
    printf("Taux de remplissage : ");
    afficherPourcentage(i, 50);
  }
  for (float i = 0; i <= 100; i += 5) {
    printf("Taux de remplissage : ");
    afficherPourcentage(i, 70);
  }

  return 0;
}
