/**
 * @file structures.c
 * @author Marchand Mael & Calixte Axel
 * @brief Fichier comportant toutes les structures utilisées pour le projet
 * @version 1
 * @date 2019-12-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Comporte le numéro de ticket du bagage et si il a été embarqué
 */
typedef struct {
  int ticket; /*!< Ticket du bagage */
  int embarque; /*!< Booléen qui indique si le bagage est embarqué */
} Bagage;

/**
 * Associe un numéro de rangée et de colonne pour une place dans l'avion
 */
typedef struct {
  int rangee; /*!< numéro de rangée */
  int colonne; /*!< numéro de colonne */
} Siege;

/**
 * Structure de date, avec le jour, le mois et l'année
 */
typedef struct {
  int jour; /*!< entier pour le jour */
  int mois; /*!< entier pour le mois */
  int annee; /*!< entier pour l'année */
} Date;

/**
 * Comporte un entier pour l'heure et pour les minutes
 */
typedef struct {
  int heure; /*!< entier pour l'heure */
  int minutes; /*!< entier pour les minutes */
} Temps;

/**
 * Comporte le nom, prénom, la nationalité, le billet et des int bouléens pour
 * le bon fonctionnement du programme.
 * La structure pasager intègre aussi les structures Date, Siege et Bagage.
 */
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

/**
 * Comporte le numéro de vol, la destination, le nombre de places libres,
 * de places réservées, de colonnes et rangées (pour la taille de l'avion).
 * Vol intègre les structures de Date, Temps et Passager.
 */
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

/**
 * Permet d'associer un numéro à une fonction pour la console
 */
typedef struct {
  int fonction; /*!< entier de numéro de fonction */
  char commande[24]; /*!< chaines de caratères associées à leur entier de fonction*/
} Commande;
