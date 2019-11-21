#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int ticket;
  int embarque;
} Bagage;

typedef struct {
  int rangee;
  int colonne;
} Siege;

typedef struct {
  char nom[64];
  char prenom[64];
  char nationalite[25];
  int visa;
  int frontiere; // a passé la frontière : 1
  int securite; // après avoir passer la securite : 1
  Bagage bagages[2];
  int nb_bagages;
  int prioritaire;
  char billet[11];
  char date_naissance[24];
  Siege siege;
  int enregistrer; // boarding pass enregistré
  int embarquer;
} Passager;

typedef struct {
  char heure_depart[64];
  char heure_arrivee[64];
  char destination[128];
  Passager *passagers[1024];
  int places_reservees;
  int places_libres;
  int visa_requis;
  int sieges_rangee;
  int sieges_colonne;
} Vol;
