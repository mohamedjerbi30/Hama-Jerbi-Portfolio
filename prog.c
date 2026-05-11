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
#include <unistd.h>
#include <sys/wait.h>

#define MAX 256

/* Structure envoyée dans le tube */
typedef struct {
    pid_t pid;
    char  chaine[MAX];
} Message;

void creer_fils(int numero, int n, Message msg)
{
    if(numero > n) return;

    int tube[2];
    pipe(tube);

    if(fork() == 0) /* ===== FILS ===== */
    {
        Message recu;
        close(tube[1]);
        read(tube[0], &recu, sizeof(Message));
        close(tube[0]);

        if(numero == 1)
            printf("[FILS %d | pid=%d] Recu \"%s\" du PERE (pid=%d)\n",
                    numero, getpid(), recu.chaine, recu.pid);
        else
            printf("[FILS %d | pid=%d] Recu \"%s\" du fils %d (pid=%d)\n",
                    numero, getpid(), recu.chaine, numero-1, recu.pid);

        /* Préparer le message pour le fils suivant */
        Message suivant;
        suivant.pid = getpid();
        strcpy(suivant.chaine, recu.chaine);

        creer_fils(numero + 1, n, suivant);
        exit(0);
    }
    else /* ===== PÈRE / FILS QUI ENVOIE ===== */
    {
        close(tube[0]);
        write(tube[1], &msg, sizeof(Message));
        close(tube[1]);
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3) { fprintf(stderr,"Usage: %s <n> <chaine>\n", argv[0]); return 1; }

    Message msg;
    msg.pid = getpid();
    strcpy(msg.chaine, argv[2]);

    printf("[PERE | pid=%d] J'envoie \"%s\"\n\n", getpid(), argv[2]);

    creer_fils(1, atoi(argv[1]), msg);

    printf("\n[PERE] Fin.\n");
    return 0;
}
