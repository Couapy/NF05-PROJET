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
  int jour;
  int mois;
  int annee;
} Date;

typedef struct {
  int heure;
  int minutes;
} Temps;

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
  unsigned long billet;
  Date date_naissance;
  Siege siege;
  int enregistrer; // boarding pass enregistré
  int embarquer;
} Passager;

typedef struct {
  char numero_vol[8];
  char destination[128];
  Date date;
  Temps heure_depart;
  Temps heure_arrivee;
  int visa_requis;
  int places_reservees;
  int places_libres;
  Passager *passagers[1024];
  int sieges_rangee;
  int sieges_colonne;
} Vol;

typedef struct {
  int fonction;
  char commande[24];
} Commande;
