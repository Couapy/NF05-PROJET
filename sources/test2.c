#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int entier;
  char string[64];
} Test;

int main(void) {
  // char tab[10];
  //
  // printf("Entrez une string : ");
  // fgets(tab, 10, stdin);
  // printf("Vous avez entre : %s\n", tab);

  Test *test;

  printf("Entrez un entier : ");
  scanf(" %d", test->entier);
  // fgets(test->string, 64, stdin);
  printf("Vous avez entre : %d\n", test->entier);

  return 0;
}
