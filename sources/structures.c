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
  char nom[64]; //!< Nom du passager
  char prenom[64]; //!< Prénom du passager
  char nationalite[25]; //!< Nationalité du passager
  int visa; //!< 1 si le passager a un VISA, sinon c'est 0
  int frontiere; //!< 1 si le passager a passé la frontière
  int securite; //!<v 1 si le passager a passé la securite
  Bagage bagages[2]; //!< Tableau de bagages du passager
  int nb_bagages; //!< Nombre de bagages
  int prioritaire; //!< 1 si le passager est prioritaire
  unsigned long billet; //!< Le numéro de billet
  Date date_naissance; //!< La date de naissance
  Siege siege; //!< Le siège
  int enregistrer; //!< 1 si le passager s'est enregistré, sinon c'est 0
  int embarquer; //!< 1 si le passager est embarqué, sinon c'est 0
} Passager;

/**
 * Comporte le numéro de vol, la destination, le nombre de places libres,
 * de places réservées, de colonnes et rangées (pour la taille de l'avion).
 * Vol intègre les structures de Date, Temps et Passager.
 */
typedef struct {
  char numero_vol[8]; //!< Le numéro du vol
  char destination[128]; //!< La destination de du vol
  Date date; //!< La date du vol
  Temps heure_depart; //!< Heure de départ
  Temps heure_arrivee; //!< Heure d'arrivée
  int visa_requis; //!< 1 si un VISA est requis, 0 sinon
  int places_reservees; //!< Nombre de places réservées, ou simplement le nombre de passager dans le vol
  int places_libres; //!< Le nombre de places libres dans
  Passager *passagers[1024]; //!< Tableau de passagers
  int sieges_rangee; //!< Nombre de sièges par rangée
  int sieges_colonne; //!< Nombre de sièges par colonne
} Vol;

/**
 * Permet d'associer un numéro à une fonction pour la console
 */
typedef struct {
  int fonction; /*!< entier de numéro de fonction */
  char commande[24]; /*!< chaines de caratères associées à leur entier de fonction*/
} Commande;
