#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int ticket;
  int depose;
  int embarque;
} Bagage;

typedef struct {
  char nom[64];
  char prenom[64];
  Bagage bagages[2];
  int prioritaire;
  char billet[11];
  char date_naissance[24];
  char numero_siege[64];
} Passager;

typedef struct {
  char heure_depart[64];
  char heure_arrivee[64];
  char destination[128];
  Passager *passagers[1024];
  int places_reservees;
  int places_libres;
} Vol;
