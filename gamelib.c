#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

static int n_giocatori = 0;

static int v_giocatori[];
// puntatore all’array struct Giocatore che
// viene creato dinamicamente in base ai giocatori
static struct Giocatore *giocatori = NULL;
// quest da finire per vincere il gioco
static unsigned short quest_da_finire;

struct Stanza *stanza_inizio;

struct Stanza *lista_stanze;
time_t t;

// questa funzione imposta il numero dei giocatori, la tipologia
// e il numero di quest da completare
// Inoltre crea anche la stanza iniziale del gioco
void imposta_gioco(){
  int scelta = 0;
  do{
    printf("\t\tImpostazioni\n");
    printf("1)Imposta Giocatori\t\t");
    printf("2)Imposta numero di quest\t\t");
    printf("3)Termina Gioco\n");
    scanf("%d",&scelta);
    if(scelta != 1 && scelta != 2 && scelta != 3){
      printf("Numero non valido. riprova\n");
       while(getchar() != '\n');
    }
  } while((scelta != 1 && scelta != 2 && scelta != 3));

    switch (scelta){
      case 1:
        do{
          printf("Assegnazione casuale dei ruoli (astronauta / impostore)\n");
          printf("inserisci il numero di giocatori (4-10):\n");
          scanf("%d",&n_giocatori);
          if((n_giocatori < 4 || n_giocatori > 10)){
            printf("Numero non valido. riprova\n");
             while(getchar() != '\n');
          }
        } while((n_giocatori < 4 || n_giocatori > 10));

      srand((unsigned)time(&t));

      v_giocatori[n_giocatori];
      int vettore_temporaneo[10];

      for (int i = 0; i < 10; i++) {     // fill array

        vettore_temporaneo[i]=i;
        //printf("%d\t",vettore_temporaneo[i]);
      }
      printf("\n");
      for (int i = 0; i < 10; i++) {    // shuffle array
        int scambio = vettore_temporaneo[i];
        int indiceRand = rand() % 10;

        vettore_temporaneo[i] = vettore_temporaneo[indiceRand];
        vettore_temporaneo[indiceRand] = scambio;
      }
      for (int i = 0; i < n_giocatori; i++){
        v_giocatori[i]=vettore_temporaneo[i];
        printf("%d\t",v_giocatori[i]);
      }

      for(int i = 0;i<n_giocatori;i++){
        switch(v_giocatori[i]){
          case 0:
            printf("ROSSO\n");
          break;
          case 1:
            printf("BLU\n");
          break;
          case 2:
            printf("VERDE\n");
          break;
          case 3:
            printf("GIALLO\n");
          break;
          case 4:
            printf("ARANCIONE\n");
          break;
          case 5:
            printf("NERO\n");
          break;
          case 6:
            printf("ROSA\n");
          break;
          case 7:
            printf("VIOLA\n");
          break;
          case 8:
            printf("CELESTE\n");
          break;
          case 9:
            printf("GRIGIO\n");
          break;
        }
      }
        break;

      case 2:
        do{
          printf("inserisci il numero di quest totali:\n");
          scanf("%hu",&quest_da_finire);
          if((quest_da_finire <= 0)){
            printf("Numero non valido. riprova\n");
             while(getchar() != '\n');
          }
        } while(quest_da_finire <= 0);

      break;
      case 3:
        printf("sgocciola\n");
      break;
    }
    //printf("leggi sto messaggio\n");
}
void termina_gioco(){
  exit(0);

}
