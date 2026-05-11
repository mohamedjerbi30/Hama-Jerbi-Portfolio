/*
 * ============================================================
 *  TP - Gestion des Processus sous UNIX
 *  Ecole Nationale d'Ingenieurs de Tunis
 *  Module : Administration & Programmation Systeme
 * ============================================================
 *
 *  Ce fichier contient deux exercices :
 *
 *  EXERCICE 1 : Pere qui controle son fils via un tube
 *               - s : le fils fait un sleep de 5 secondes
 *               - r : le fils affiche qu'il travaille
 *               - q : le fils se termine, le pere quitte
 *
 *  EXERCICE 2 : Chaine de N fils
 *               - Le pere cree le fils 1 et lui envoie une chaine
 *               - Chaque fils cree le suivant et lui transmet la chaine
 *               - Chaque fils affiche de qui il a recu la chaine
 *
 *  Compilation : gcc -Wall -o tp tp_processus.c
 *  Execution   :
 *        Exercice 1 : ./tp 1
 *        Exercice 2 : ./tp 2 <n_fils> <chaine>
 *        Exemple    : ./tp 2 3 "Bonjour"
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* ============================================================
 *  CONSTANTES
 * ============================================================ */
#define MAX 256   /* Taille maximale de la chaine */


/* ============================================================
 *  EXERCICE 1 : Pere controleur de fils via un tube
 * ============================================================
 *
 *  Schema de communication :
 *
 *  PERE                   TUBE                  FILS
 *  ----                   ----                  ----
 *  scanf()                                    (bloque sur read)
 *  write(tube[1], &c, 1) ──────────────────>  read(tube[0], &c, 1)
 *                                              if s → sleep(5)
 *                                              if r → affiche "Je travaille"
 *                                              if q → exit(0)
 *  wait(NULL) <─────────── fils termine
 *
 * ============================================================ */
void exercice1(void)
{
    int  tube[2];  /* tube[0]=lecture  tube[1]=ecriture */
    char c;        /* commande tapee par l'utilisateur  */

    /* --- Creer le tube AVANT le fork --- */
    pipe(tube);

    switch(fork())
    {
        /* ------ Erreur de creation ------ */
        case -1:
            perror("Erreur fork");
            exit(1);

        /* ------ FILS : lit les commandes depuis le tube ------ */
        case 0:
            close(tube[1]);  /* le fils n'ecrit pas dans le tube */

            printf("[FILS  | pid=%d] Je suis pret, j'attends les commandes...\n",
                    getpid());

            /*
             * Boucle d'attente :
             * read() bloque jusqu'a ce que le pere envoie une commande
             */
            while(read(tube[0], &c, 1) > 0)
            {
                if(c == 's')
                {
                    printf("[FILS  | pid=%d] Je fais un sleep de 5 secondes...\n", getpid());
                    sleep(5);
                    printf("[FILS  | pid=%d] Reveil ! Je suis pret.\n", getpid());
                }
                if(c == 'r')
                {
                    printf("[FILS  | pid=%d] Je travaille !\n", getpid());
                }
                if(c == 'q')
                {
                    printf("[FILS  | pid=%d] Je me termine. Bye !\n", getpid());
                    close(tube[0]);
                    exit(0);  /* terminaison normale du fils */
                }
            }

            close(tube[0]);
            exit(0);

        /* ------ PERE : envoie les commandes via le tube ------ */
        default:
            close(tube[0]);  /* le pere n'lit pas depuis le tube */

            printf("[PERE  | pid=%d] Fils cree avec succes.\n", getpid());
            printf("---------------------------------------------\n");
            printf("Commandes : s=Sleep | r=Redemarrer | q=Quitter\n");
            printf("---------------------------------------------\n");

            while(1)
            {
                printf("Commande > ");
                fflush(stdout);    /* forcer l'affichage immediat */
                scanf(" %c", &c);  /* lire une commande depuis stdin */

                /* Envoyer la commande au fils via le tube */
                write(tube[1], &c, 1);

                /* Si quitter : attendre la fin du fils et sortir */
                if(c == 'q')
                {
                    wait(NULL);  /* pere attend la mort du fils */
                    close(tube[1]);
                    printf("[PERE  | pid=%d] Fils termine. Fin du programme.\n",
                            getpid());
                    return;
                }
            }
    }
}


/* ============================================================
 *  EXERCICE 2 : Chaine de N fils
 * ============================================================
 *
 *  Schema de creation et communication :
 *
 *  PERE (pid=100)
 *    │  cree FILS1 via tube0
 *    │  envoie {pid=100, "Bonjour"} dans tube0
 *    │
 *    └──> FILS1 (pid=101) : recu "Bonjour" du PERE (100)
 *           │  cree FILS2 via tube1
 *           │  envoie {pid=101, "Bonjour"} dans tube1
 *           │
 *           └──> FILS2 (pid=102) : recu "Bonjour" du fils 1 (101)
 *                  │  cree FILS3 via tube2
 *                  │  envoie {pid=102, "Bonjour"} dans tube2
 *                  │
 *                  └──> FILS3 (pid=103) : recu "Bonjour" du fils 2 (102)
 *
 * ============================================================ */

/*
 * Structure Message :
 * On regroupe le pid et la chaine dans une seule structure
 * pour n'avoir qu'un seul write() et un seul read()
 */
typedef struct {
    pid_t pid;        /* pid de l'expediteur       */
    char  chaine[MAX];/* chaine a faire circuler   */
} Message;

/*
 * creer_fils() : fonction recursive
 *
 * Parametres :
 *   numero : numero du fils a creer (1, 2, 3, ...)
 *   n      : nombre total de fils a creer
 *   msg    : message a envoyer au fils (pid + chaine)
 */
void creer_fils(int numero, int n, Message msg)
{
    /* Cas de base : tous les fils ont ete crees */
    if(numero > n) return;

    int tube[2];  /* tube local pour ce fils uniquement */
    pipe(tube);

    if(fork() == 0) /* ------ FILS numero ------ */
    {
        Message recu;    /* message recu depuis le tube   */
        Message suivant; /* message a envoyer au suivant  */

        close(tube[1]);  /* le fils ne fait que lire      */

        /* Lire le message du pere/fils precedent */
        read(tube[0], &recu, sizeof(Message));
        close(tube[0]);

        /* Afficher le message recu */
        if(numero == 1)
            printf("[FILS %d | pid=%d] Recu \"%s\" du PERE    (pid=%d)\n",
                    numero, getpid(), recu.chaine, recu.pid);
        else
            printf("[FILS %d | pid=%d] Recu \"%s\" du fils %d (pid=%d)\n",
                    numero, getpid(), recu.chaine, numero-1, recu.pid);

        fflush(stdout);

        /* Preparer le message pour le fils suivant */
        suivant.pid = getpid();
        strcpy(suivant.chaine, recu.chaine);

        /* Creer le fils suivant et lui envoyer la chaine */
        creer_fils(numero + 1, n, suivant);

        exit(0);  /* terminaison normale du fils */
    }
    else /* ------ PERE ou FILS QUI ENVOIE ------ */
    {
        close(tube[0]);  /* l'expediteur n'a pas besoin de lire */

        /* Envoyer le message au fils qu'on vient de creer */
        write(tube[1], &msg, sizeof(Message));
        close(tube[1]);

        wait(NULL);  /* attendre que le fils termine */
    }
}

void exercice2(int argc, char *argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "Usage : %s 2 <n_fils> <chaine>\n", argv[0]);
        fprintf(stderr, "Exemple : %s 2 3 \"Bonjour\"\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[2]);
    if(n <= 0)
    {
        fprintf(stderr, "Erreur : n_fils doit etre > 0\n");
        exit(1);
    }

    /* Preparer le message initial du pere */
    Message msg;
    msg.pid = getpid();
    strcpy(msg.chaine, argv[3]);

    printf("[PERE  | pid=%d] J'envoie \"%s\" a %d fils\n\n",
            getpid(), argv[3], n);
    fflush(stdout);

    /* Lancer la chaine de fils */
    creer_fils(1, n, msg);

    printf("\n[PERE  | pid=%d] Tous les fils ont termine. Fin.\n", getpid());
}


/* ============================================================
 *  MAIN : choisir l'exercice a executer
 * ============================================================ */
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage :\n");
        fprintf(stderr, "  Exercice 1 : %s 1\n", argv[0]);
        fprintf(stderr, "  Exercice 2 : %s 2 <n_fils> <chaine>\n", argv[0]);
        return 1;
    }

    int choix = atoi(argv[1]);

    printf("============================================\n");

    if(choix == 1)
    {
        printf("  EXERCICE 1 : Pere controleur de fils\n");
        printf("============================================\n\n");
        exercice1();
    }
    else if(choix == 2)
    {
        printf("  EXERCICE 2 : Chaine de N fils\n");
        printf("============================================\n\n");
        exercice2(argc, argv);
    }
    else
    {
        fprintf(stderr, "Choix invalide ! Utilisez 1 ou 2.\n");
        return 1;
    }

    return 0;
}
