#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char *seme;
    float valore;
    int isMatta;
} Carta;

char *semi[4] = {"Spade", "Coppe", "Bastoni", "Denari"};

Carta pesca_carta(int *mazzo) {
    int numero_random = 0;
    do {
        numero_random = rand() % 40;
    } while (mazzo[numero_random] == 1);
    mazzo[numero_random] = 1;
    Carta carta;
    carta.isMatta = 0;
    carta.seme = semi[numero_random / 10];
    int valore = numero_random % 10 + 1;
    if (numero_random == 39) {
        carta.isMatta = 1;
    }
    if (valore < 8) {
        carta.valore = valore;

    } else {
        carta.valore = 0.5;
    }

    return carta;
}
float turno_giocatore(int *mazzo) {
    float punteggio = 0;
    char scelta;
    printf("Turno del giocatore\n");
    do {
        Carta carta = pesca_carta(mazzo);
        if (carta.isMatta == 1) {
            printf("Hai pescato la matta! \n Scegli un valore da assegnarle(1-7 o 0,5):");
            scanf("%f", &carta.valore);
        }
        punteggio += carta.valore;
        printf("Hai pescato: %s %.1f\n", carta.seme, carta.valore);
        printf("Punteggio attuale: %.1f\n", punteggio);
        if (punteggio > 7.5) {
            printf("Hai sballato!");
            return punteggio;
        }
        printf("Vuoi pescare un'altra carta? (s/n): ");
        scanf(" %c", &scelta);
    } while (scelta == 's' || scelta == 'S');
    return punteggio;
}

float turno_banco(int *mazzo) {
    float punteggio = 0;

    printf("Turno del banco\n");

    while (punteggio < 5.5) {
        Carta carta = pesca_carta(mazzo);
        punteggio += carta.valore;
        printf("Il banco pesca: %s %.1f\n", carta.seme, carta.valore);
        printf("Punteggio del banco: %.1f\n", punteggio);

        if (punteggio > 7.5) {
            printf("Il banco ha sballato! Punteggio: %.1f\n", punteggio);
            return punteggio;
        }
    }

    printf("Il banco si ferma con: %.1f\n", punteggio);
    return punteggio;
}
int main() {
    int mazzo[40] = {0};
    srand(time(NULL));

    printf("Benvenuto al gioco del 7 e mezzo con la Matta!\n");

    float punteggio_giocatore = turno_giocatore(mazzo);
    if (punteggio_giocatore > 7.5) {
        printf("Hai perso! Il banco vince.\n");
        return 0;
    }

    float punteggio_banco = turno_banco(mazzo);

    if (punteggio_banco > 7.5) {
        printf("Il banco ha sballato! Tu vinci con %.1f punti.\n", punteggio_giocatore);
    } else if (punteggio_giocatore > punteggio_banco) {
        printf("Hai vinto! Il tuo punteggio è %.1f, il punteggio del banco è %.1f.\n", punteggio_giocatore, punteggio_banco);
    } else if (punteggio_giocatore < punteggio_banco) {
        printf("Il banco vince! Il suo punteggio è %.1f, il tuo punteggio è %.1f.\n", punteggio_banco, punteggio_giocatore);
    } else {
        printf("Pareggio! Il tuo punteggio è %.1f, quello del banco è %.1f.\n", punteggio_giocatore, punteggio_banco);
    }

    return 0;
}