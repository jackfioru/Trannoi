#include <stdio.h>
#include "gamelib.h"

/* è un puntatore all’array distruct Giocatore
 che viene creato dinamicamente in base a quanti
giocatori si vogliono nel gioco (4-10)*/
struct Giocatore* giocatori;

// numero di quest da finire per vincere il gioco da parte degli astronauti
unsigned short quest_da_finire;

//iene memorizzata la prima stanza, dalla quale iniziano a giocare tutti i giocatori presenti
struct Stanza* stanza_inizio;

/* contiene il puntatore alla stanza di inizio,
 e che rappresenta la lista di tutte le struct Stanza create durante il gioco,
  una dopo l’altra in ordine di creazione.
  Questa lista serve come appoggio per scorrere tutte le stanze,
   per esempio per trovare quelle con le botole.*/
struct Stanza* lista_stanze;

void imposta_gioco(){
  int scelta = 0;
  printf("\t\tTRANNOI\n");
//////////////////// IMPOSTAZIONI //////////////////////
  do{
    printf("Scegli il numero di giocatori da 4 a 10 :\n");
    scanf("%d",&scelta);
    //printf("valore : %d\n", scelta);
    if((scelta < 4)&&(scelta > 10)){
      printf("Numero non valido. riprova\n");
       while(getchar() != '\n');
      }
    }
}

void main() {}
