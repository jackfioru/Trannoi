#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"

  int main(void){
    int scelta = 0;
    int contatore = 0;
//////////////////// MENU //////////////////////
    do{
      system("clear");
      printf("\t\tTrannoi\n\n\t\tMenù\n\n1) Imposta gioco\n\n2) GIoca\n\n3) Termina gioco\n");
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
          break;
        case 2:
          gioca();
        break;
        case 3:
          termina_gioco();
          printf("sgocciola\n");
        break;
      }

  }
