#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"

static int n_giocatori = 0;

int array_giocatori[];
// puntatore all’array struct Giocatore che
// viene creato dinamicamente in base ai giocatori
static struct Giocatore *giocatori = NULL;
// quest da finire per vincere il gioco
static unsigned short quest_da_finire;

struct Stanza *stanza_inizio;

struct Stanza *lista_stanze;


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

      int arry_giocatori[n_giocatori];
      


        break;
      case 2:
        do{
          printf("inserisci il numero di quest totali:\n");
          scanf("%hu",&quest_da_finire);
          printf("%u",quest_da_finire);
          if((quest_da_finire <= 0)){
            printf("Numero non valido. riprova\n");
             while(getchar() != '\n');
          }
        } while(quest_da_finire <= 0);

        printf("\e[1;1h\]");
      break;
      case 3:
        //termina_gioco();
        printf("sgocciola\n");
      break;
    }
}
