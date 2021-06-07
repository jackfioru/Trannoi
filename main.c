
#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"

  int main(){
    int scelta = 0;
    //int contatore = 0;
    system("clear");
//////////////////// MENU //////////////////////
    do{
      printf("\t\tTrannoi\n\n\t\tMenù\n\n1) Imposta gioco\n\n2) Gioca\n\n3) Termina gioco\n\n");
      scanf("%d",&scelta);
      //printf("valore : %d\n", scelta);
      if(scelta != 1 && scelta != 2 && scelta != 3){
        system("clear");
        printf("\nNumero non valido. riprova\n\n");
         while(getchar() != '\n');
      }
      //contatore++;
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
        break;
      }

  }
