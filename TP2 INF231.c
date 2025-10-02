#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <local.h>
#include <windows.h>


typedef struct simple_noeud {
    int valeur;
    struct simple_noeud *suivant;
} SimpleNoeud;

typedef struct double_noeud {
    int valeur;
    struct double_noeud *precedent;
    struct double_noeud *suivant;
} DoubleNoeud;


void afficher_liste_simple(SimpleNoeud *tete) {
    SimpleNoeud *courant = tete;
    printf("Liste simple: ");
    while (courant != NULL) {
        printf("%d -> ", courant->valeur);
        courant = courant->suivant;
    }
    printf("NULL\n");
}

void afficher_liste_double(DoubleNoeud *tete) {
    DoubleNoeud *courant = tete;
    printf("Liste double: ");
    while (courant != NULL) {
        printf("%d <-> ", courant->valeur);
        courant = courant->suivant;
    }
    printf("NULL\n");
}

void afficher_liste_simple_circulaire(SimpleNoeud *queue) {
    if (queue == NULL) {
        printf("Liste simple circulaire: Vide\n");
        return;
    }
    SimpleNoeud *tete = queue->suivant;
    SimpleNoeud *courant = tete;
    printf("Liste simple circulaire: ");
    do {
        printf("%d -> ", courant->valeur);
        courant = courant->suivant;
    } while (courant != tete);
    printf("(retour à %d)\n", tete->valeur);
}

void afficher_liste_double_circulaire(DoubleNoeud *tete) {
    if (tete == NULL) {
        printf("Liste double circulaire: Vide\n");
        return;
    }
    DoubleNoeud *courant = tete;
    printf("Liste double circulaire: ");
    do {
        printf("%d <-> ", courant->valeur);
        courant = courant->suivant;
    } while (courant != tete);
    printf("(retour à %d)\n", tete->valeur);
}


void supprimer_toutes_occurrences(SimpleNoeud **tete, int element_a_supprimer) {
    SimpleNoeud *courant = *tete;
    SimpleNoeud *precedent = NULL;

    while (courant != NULL && courant->valeur == element_a_supprimer) {
        *tete = courant->suivant;
        SimpleNoeud *a_supprimer = courant;
        courant = courant->suivant;
        free(a_supprimer);
    }

    if (courant == NULL) return;

    precedent = courant;
    courant = courant->suivant;

    while (courant != NULL) {
        if (courant->valeur == element_a_supprimer) {
            precedent->suivant = courant->suivant;
            SimpleNoeud *a_supprimer = courant;
            courant = courant->suivant;
            free(a_supprimer);
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}


void insertion_simple_triee(SimpleNoeud **tete, int nouvelle_valeur) {
    SimpleNoeud *nouveau_noeud = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    if (nouveau_noeud == NULL) { perror("Échec d'allocation mémoire"); return; }
    nouveau_noeud->valeur = nouvelle_valeur;
    nouveau_noeud->suivant = NULL;

    SimpleNoeud *courant = *tete;
    SimpleNoeud *precedent = NULL;

    if (*tete == NULL || nouvelle_valeur < (*tete)->valeur) {
        nouveau_noeud->suivant = *tete;
        *tete = nouveau_noeud;
        return;
    }

    while (courant != NULL && courant->valeur < nouvelle_valeur) {
        precedent = courant;
        courant = courant->suivant;
    }

    nouveau_noeud->suivant = courant;
    precedent->suivant = nouveau_noeud;
}


void insertion_double_triee(DoubleNoeud **tete, int nouvelle_valeur) {
    DoubleNoeud *nouveau_noeud = (DoubleNoeud *)malloc(sizeof(DoubleNoeud));
    if (nouveau_noeud == NULL) { perror("Échec d'allocation mémoire"); return; }
    nouveau_noeud->valeur = nouvelle_valeur;
    nouveau_noeud->precedent = NULL;
    nouveau_noeud->suivant = NULL;

    DoubleNoeud *courant = *tete;

    if (*tete == NULL || nouvelle_valeur < (*tete)->valeur) {
        nouveau_noeud->suivant = *tete;
        if (*tete != NULL) {
            (*tete)->precedent = nouveau_noeud;
        }
        *tete = nouveau_noeud;
        return;
    }

    while (courant != NULL && courant->valeur < nouvelle_valeur) {
        courant = courant->suivant;
    }

    if (courant == NULL) {
        DoubleNoeud *precedent = *tete;
        while (precedent->suivant != NULL) {
            precedent = precedent->suivant;
        }
        precedent->suivant = nouveau_noeud;
        nouveau_noeud->precedent = precedent;
    } else {
        nouveau_noeud->precedent = courant->precedent;
        nouveau_noeud->suivant = courant;
        courant->precedent->suivant = nouveau_noeud;
        courant->precedent = nouveau_noeud;
    }
}

void insertion_circulaire_simple_tete(SimpleNoeud **queue, int nouvelle_valeur) {
    SimpleNoeud *nouveau_noeud = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    if (nouveau_noeud == NULL) { perror("Échec d'allocation mémoire"); return; }
    nouveau_noeud->valeur = nouvelle_valeur;

    if (*queue == NULL) { // Liste vide
        nouveau_noeud->suivant = nouveau_noeud;
        *queue = nouveau_noeud;
    } else {
        nouveau_noeud->suivant = (*queue)->suivant;
        (*queue)->suivant = nouveau_noeud;
    }
}

void insertion_circulaire_simple_queue(SimpleNoeud **queue, int nouvelle_valeur) {
    SimpleNoeud *nouveau_noeud = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    if (nouveau_noeud == NULL) { perror("Échec d'allocation mémoire"); return; }
    nouveau_noeud->valeur = nouvelle_valeur;

    if (*queue == NULL) {
        nouveau_noeud->suivant = nouveau_noeud;
        *queue = nouveau_noeud;
    } else {
        nouveau_noeud->suivant = (*queue)->suivant;
        (*queue)->suivant = nouveau_noeud;
        *queue = nouveau_noeud;
    }
}


void insertion_circulaire_double_tete(DoubleNoeud **tete, int nouvelle_valeur) {
    DoubleNoeud *nouveau_noeud = (DoubleNoeud *)malloc(sizeof(DoubleNoeud));
    if (nouveau_noeud == NULL) { perror("Échec d'allocation mémoire"); return; }
    nouveau_noeud->valeur = nouvelle_valeur;

    if (*tete == NULL) {
        nouveau_noeud->suivant = nouveau_noeud;
        nouveau_noeud->precedent = nouveau_noeud;
        *tete = nouveau_noeud;
    } else {
        DoubleNoeud *queue = (*tete)->precedent;

        nouveau_noeud->suivant = *tete;
        nouveau_noeud->precedent = queue;

        (*tete)->precedent = nouveau_noeud;
        queue->suivant = nouveau_noeud;

        *tete = nouveau_noeud;
    }
}

void insertion_circulaire_double_queue(DoubleNoeud **tete, int nouvelle_valeur) {
    DoubleNoeud *nouveau_noeud = (DoubleNoeud *)malloc(sizeof(DoubleNoeud));
    if (nouveau_noeud == NULL) { perror("Échec d'allocation mémoire"); return; }
    nouveau_noeud->valeur = nouvelle_valeur;

    if (*tete == NULL) {
        nouveau_noeud->suivant = nouveau_noeud;
        nouveau_noeud->precedent = nouveau_noeud;
        *tete = nouveau_noeud;
    } else {
        DoubleNoeud *queue = (*tete)->precedent;

        nouveau_noeud->suivant = *tete;
        nouveau_noeud->precedent = queue;

        (*tete)->precedent = nouveau_noeud;
        queue->suivant = nouveau_noeud;

    }
}


int main() {
    setlocale(LC_ALL,"French");
    setConsoleOutputCp(Cp_UTF8);
    printf("========================================================\n");
    printf("      Démonstration des opérations sur Listes Chaînées\n");
    printf("========================================================\n\n");

    printf("--- 1. Suppression de toutes les occurrences (Liste Simple) ---\n");
    SimpleNoeud *liste1 = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    liste1->valeur = 5;
    liste1->suivant = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    liste1->suivant->valeur = 10;
    liste1->suivant->suivant = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    liste1->suivant->suivant->valeur = 5;
    liste1->suivant->suivant->suivant = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    liste1->suivant->suivant->suivant->valeur = 20;
    liste1->suivant->suivant->suivant->suivant = (SimpleNoeud *)malloc(sizeof(SimpleNoeud));
    liste1->suivant->suivant->suivant->suivant->valeur = 5;
    liste1->suivant->suivant->suivant->suivant->suivant = NULL;

    afficher_liste_simple(liste1);
    int val_suppr = 5;
    printf("Suppression de toutes les occurrences de %d...\n", val_suppr);
    supprimer_toutes_occurrences(&liste1, val_suppr);
    afficher_liste_simple(liste1);
    printf("\n");

    printf("--- 2. Insertion dans une liste simplement chaînée triée ---\n");
    SimpleNoeud *liste2 = NULL;
    insertion_simple_triee(&liste2, 20);
    insertion_simple_triee(&liste2, 5);
    insertion_simple_triee(&liste2, 15);
    insertion_simple_triee(&liste2, 10);
    printf("Liste après insertions: ");
    afficher_liste_simple(liste2);
    printf("\n");

    printf("--- 3. Insertion dans une liste doublement chaînée triée ---\n");
    DoubleNoeud *liste3 = NULL;
    insertion_double_triee(&liste3, 22);
    insertion_double_triee(&liste3, 7);
    insertion_double_triee(&liste3, 17);
    insertion_double_triee(&liste3, 12);
    printf("Liste après insertions: ");
    afficher_liste_double(liste3);
    printf("\n");

    printf("--- 4. Insertion dans une liste simplement chaînée circulaire ---\n");
    SimpleNoeud *liste4_queue = NULL;
    insertion_circulaire_simple_queue(&liste4_queue, 10);
    insertion_circulaire_simple_tete(&liste4_queue, 5);
    insertion_circulaire_simple_queue(&liste4_queue, 15);
    printf("Liste après insertions: ");
    afficher_liste_simple_circulaire(liste4_queue);
    printf("\n");

    printf("--- 5. Insertion dans une liste doublement chaînée circulaire ---\n");
    DoubleNoeud *liste5_tete = NULL;
    insertion_circulaire_double_tete(&liste5_tete, 30);
    insertion_circulaire_double_queue(&liste5_tete, 50);
    insertion_circulaire_double_tete(&liste5_tete, 20);
    printf("Liste après insertions: ");
    afficher_liste_double_circulaire(liste5_tete);
    printf("\n");

    return 0;
}
