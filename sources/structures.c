#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int ticket;
  int embarque;
} Bagage;

typedef struct {
  char nom[64];
  char prenom[64];
  char nationalite[25];
  int visa;
  int frontiere;
  int interdit; // pour passer la sécurité
  int securite; // après avoir passer la securite : 1 
  Bagage bagages[2];
  int nb_bagages;
  int prioritaire;
  char billet[11];
  char date_naissance[24];
  char numero_siege[64];
  int enregistrer;
} Passager;

typedef struct {
  char heure_depart[64];
  char heure_arrivee[64];
  char destination[128];
  Passager *passagers[1024];
  int places_reservees;
  int places_libres;
  int visa_requis;
} Vol;
