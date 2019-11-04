#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nom[20];
    char prenom[20];
    char adresse[20];
    int numeroDeCompte;
    float solde;
} Client;

void saisieClient (Client *p, int i) {
    printf("\n\n\n\t\t\tClient N° %d\n\n", i + 1);
    printf ("Nom : ");
    scanf ("%s", p->nom);
    printf ("Prenom : ");
    scanf ("%s", p->prenom);
    printf ("Adresse : ");
    scanf ("%s", p->adresse);
    printf ("Numero de compte : ");
    scanf ("%d", & p->numeroDeCompte);
    printf ("Solde : ");
    scanf ("%f", & p->solde);
}

int main(void) {
  Client *client;

  saisieClient(client, 0);

  return 0;
}
