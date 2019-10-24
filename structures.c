#include <stdio.h>
#include <stdlib.h>

struct Bagage {
  int ticket;
  int poids;
  int priority;
  int depose;
  int embarque;
};

typedef struct {
  char nom[64];
  char prenom[64];
  struct Bagage bagages[2];
  int prioritaire;
  char numero_billet[11];
  char date_naissance[10];
  char numero_siege[64];
} Passager;

struct Vol {
  char heure_depart[64];
  char heure_arrivee[64];
  char destination[128];
  Passager passagers[1024];
  int places_reservees;
  int places_libres;
};
