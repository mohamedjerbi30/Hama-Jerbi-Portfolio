#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int tube[2];
    char c;
    pipe(tube);

    switch(fork())
    {
        case -1:
            perror("fork"); return 1;

        case 0: /* ===== FILS ===== */
            close(tube[1]);
            while(read(tube[0], &c, 1) > 0)
            {
                if(c == 's') { printf("[FILS] Sleep...\n"); sleep(5); printf("[FILS] Reveil!\n"); }
                if(c == 'r') { printf("[FILS] Je travaille!\n"); }
                if(c == 'q') { printf("[FILS] Bye!\n"); exit(0); }
            }
            break;

        default: /* ===== PÈRE ===== */
            close(tube[0]);
            printf("Commandes : s=sleep | r=redemarrer | q=quitter\n");
            while(1)
            {
                printf("Commande > "); fflush(stdout);
                scanf(" %c", &c);
                write(tube[1], &c, 1);
                if(c == 'q') { wait(NULL); return 0; }
            }
    }
    return 0;
}
/*ex2*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 256

void creer_fils(int numero, int n, char *chaine, pid_t pid_expediteur)
{
    /* Cas de base : on a créé tous les fils */
    if(numero > n) return;

    int tube[2];
    pipe(tube);

    if(fork() == 0) /* ===== FILS numero ===== */
    {
        char buffer[MAX];
        pid_t expediteur;

        /* Lire la chaine depuis le père */
        close(tube[1]);
        read(tube[0], &expediteur, sizeof(pid_t));
        read(tube[0], buffer, MAX);
        close(tube[0]);

        /* Afficher */
        if(numero == 1)
            printf("[FILS %d | pid=%d] Recu \"%s\" du PERE (pid=%d)\n",
                    numero, getpid(), buffer, expediteur);
        else
            printf("[FILS %d | pid=%d] Recu \"%s\" du fils %d (pid=%d)\n",
                    numero, getpid(), buffer, numero-1, expediteur);

        /* Créer le fils suivant et lui envoyer la chaine */
        creer_fils(numero + 1, n, buffer, getpid());

        exit(0);
    }
    else /* ===== PÈRE ou FILS qui envoie ===== */
    {
        /* Envoyer la chaine au fils qu'on vient de créer */
        pid_t moi = getpid();
        close(tube[0]);
        write(tube[1], &moi,   sizeof(pid_t));
        write(tube[1], chaine, MAX);
        close(tube[1]);

        wait(NULL); /* Attendre le fils qu'on vient de créer */
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3) { fprintf(stderr,"Usage: %s <n> <chaine>\n", argv[0]); return 1; }

    int n        = atoi(argv[1]);
    char *chaine = argv[2];

    printf("[PERE | pid=%d] J'envoie \"%s\"\n\n", getpid(), chaine);

    creer_fils(1, n, chaine, getpid());

    printf("\n[PERE] Fin.\n");
    return 0;
}
