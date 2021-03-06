#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"

  int main(void){
    int scelta = 0;
    int contatore = 0;
    printf("\t\tTRANNOI\n");
//////////////////// MENU //////////////////////
    do{
      printf("\t\tMenu:\n");
      printf("1)Imposta Gioco\t\t");
      printf("2)Gioca\t\t");
      printf("3)Termina Gioco\n");
      scanf("%d",&scelta);
      //printf("valore : %d\n", scelta);
      if(scelta != 1 && scelta != 2 && scelta != 3){
        printf("Numero non valido. riprova\n");
         while(getchar() != '\n');
      }
      contatore++;
    } while((scelta != 1 && scelta != 2 && scelta != 3));

      switch (scelta){
        case 1:
          imposta_gioco();
          //printf("lezzo\n");
          break;
        case 2:
          //gioca();
          printf("penzola\n");
        break;
        case 3:
          //termina_gioco();
          printf("sgocciola\n");
        break;
      }

  }
