#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

static int n_giocatori = 0;
static int n_impostori = 0;
// quest da finire per vincere il gioco
static unsigned short quest_da_finire = 0;
// questa variabile serve per controllare se il gioco e' stato impostato
static int setted = 0;
// puntatore all’array struct Giocatore che
// viene creato dinamicamente in base ai giocatori
static struct Giocatore * giocatori = NULL;


static struct Stanza * stanza_inizio = NULL;
static struct Stanza * lista_stanze = NULL;
static void creazione_giocatori();
static void imposta_impostori();
static void imposta_quest();
static void crea_stanza_inizio();
static void assegna_stato_stanza(struct Stanza *new_stanza);
static void stampa_giocatori();
static void turno(int id);
static void avanza(int id);
//static void esegui_quest();
//static void chiamata_emergenza();
//static void uccidi_astonauta();
//static void usa_botola();
//static void sabotaggio();
const char* getNomeGiocatore(enum Nome_giocatore nome);


time_t t;

void imposta_gioco()
{
  /* Questa funzione contiene il menu delle impostazioni, indispenzabile per il gioco
     perche permette di impostare il numero dei giocatori, le quest che gli astronauti
     dovranno eseguire per completare il gioco e la creazione dell stanaza iniziale.
     Inoltre una volta impostato il gioco potremmo visualizzare i giocatori con il relativo
     ruolo. */


  int scelta = 0;   // varibile per lettura
  system("clear");
  do
  {
    printf("\t\tTrannoi\n\n\t\tImpostazioni\n\n1) Imposta Giocatori\n\n2) Stampa Giocatori\n\n3) Indietro\n\n");
    scanf("%d", & scelta);
      if (scelta != 1 && scelta != 2 && scelta != 3)
      {
        system("clear");
        printf("\nNumero non valido. riprova\n");
        while (getchar() != '\n');
      }
  } while ((scelta != 1 && scelta != 2 && scelta != 3)); // lettura input da tastiera
  switch (scelta)
    {
      case 1:
        if(setted == 1)   // la variabile setted permette di verificare se il gioco era gia
        {                 // stato impostato in precedenza. In caso positivo eliminare i precedenti settaggi
          free(giocatori);
          free(stanza_inizio);
        }
        creazione_giocatori();
        imposta_quest();
        imposta_impostori();
        crea_stanza_inizio();
        assegna_stato_stanza(stanza_inizio);
        setted = 1; // dichiaro di aver impostato il gioco
        imposta_gioco();
        break;
      case 2:
        stampa_giocatori();
        imposta_gioco();
        break;
      case 3:
        main();
        break;
    }


}

void creazione_giocatori()
{
  /* Questo algoritmo mi permette di creare il numero, in ordine casuale,
     di giocatori richiesto ed inserirli nell'array struct Giocatore* giocatori */
  do
  {
    printf("\nInserisci il numero di giocatori (4-10): ");
    scanf("%d", & n_giocatori);
      if ((n_giocatori < 4 || n_giocatori > 10))
      {
        system("clear");
        printf("\nNumero non valido. riprova\n");
        while (getchar() != '\n');
      }
  } while ((n_giocatori < 4 || n_giocatori > 10)); // lettura da tastiera
  // allocamento TO FIX (migliorare commento)
  giocatori = calloc(n_giocatori, sizeof( * giocatori));

  if (giocatori == NULL)
  {
    printf("Errore di allocazione\n");
    exit(0);
  }

//////////////////////// CREAZIONE GIOCATORI ////////////////////////////////
  /* Questo algoritmo crea un array di 10 elementi e viene riempito in ordine
     crescente da 0 a 9, per poi venre mescolato in un ciclo for */
  srand(time(0));
  int v_giocatori[n_giocatori];
  int vettore_temporaneo[10];

  for (int i = 0; i < 10; i++)
    vettore_temporaneo[i] = i;

  for (int i = 0; i < 10; i++)
  {
    // salvo il valore attuale dell' array nella variabile scambio
    int scambio = vettore_temporaneo[i];
    // creo un indice randomico che prende posizioni di celle casuali dell'array
    int indiceRand = rand() % 10;
    // scambio i valori
    vettore_temporaneo[i] = vettore_temporaneo[indiceRand];
    vettore_temporaneo[indiceRand] = scambio;
  }
  // ridimensiono l'array in base ai giocatori
  for (int i = 0; i < n_giocatori; i++)
    v_giocatori[i] = vettore_temporaneo[i];

    //inserisco i giocatori nella struttura
  for(int i = 0; i < n_giocatori; i++)
  {
    giocatori[i].nome = v_giocatori[i];
  }
}

void imposta_impostori()
{
/* Questo algoritmo assegna randomicamente gli impostori a seconda del numero di giocatori presenti,
   piu il numero aumenta piu probabilita abbiamo che aumentino gli impostori.
   Inoltre assegna casualmente il ruolo di impostore ai giocatori*/

  n_impostori = 0;

  for (int i = 0; i < 3; i++)
  {
    // genera un numero da 0 a 99
    int probabilita = rand() % 100;
    // in base al numero di giocatori assegno una probabilita' diversa di generare un impostore
    switch (n_giocatori)
    {
      case 4:
        if (probabilita <= 30)
          n_impostori++;
      break;
      case 5:
        if (probabilita <= 30)
          n_impostori++;
      break;
      case 6:
        if (probabilita <= 50)
          n_impostori++;
      break;
      case 7:
        if (probabilita <= 70)
          n_impostori++;
      break;
      case 8:
        if (probabilita <= 70)
          n_impostori++;
      break;
      case 9:
        if (probabilita <= 80)
          n_impostori++;
      break;
      case 10:
        if (probabilita <= 95)
        n_impostori++;
      break;
    }
  }
// deve essere presente almeno un impostore per giocare
  if (n_impostori == 0)
    n_impostori = 1;

  printf("\nIl numero degli impostori è: %d \n",n_impostori);

////////////////////////// ASSEGNO IL RUOLO AL GIOCATORE //////////////////////////////////////
/* vettore che conterra la posizione degl'impostori
   0 astronauta
   1 impostore
*/

  int vettore_temporaneo[n_giocatori];

  for (int i = 0; i < n_giocatori; i++)
  {
    vettore_temporaneo[i] = 0;
  }
  for (int i = 0; i < n_impostori; i++)
  {
    vettore_temporaneo[i] = 1;
  }
  // scambio posizioni
  for (int i = 0; i < n_giocatori; i++)
  {
    int scambio = vettore_temporaneo[i];
    int indiceRand = rand() % n_giocatori;
    vettore_temporaneo[i] = vettore_temporaneo[indiceRand];
    vettore_temporaneo[indiceRand] = scambio;
  }

  // inserisco lo stato nella stuttura
  for (int i = 0; i < n_giocatori; i++)
    giocatori[i].stato = vettore_temporaneo[i];
}

void imposta_quest()
{
  /* Questa funzione imposta il numero di quest che gli astronauti devono eseguire
     per vincere il gioco. Il numero non potra' essere inferiore al numero dei giocatori  */
    do
    {
      printf("\n\ninserisci il numero di quest totali: ");
      scanf("%hu", & quest_da_finire);
      if ((quest_da_finire <= n_giocatori))
      {
        system("clear");
        printf("\n\nNumero inserito minore del numero dei giocatori\n\n");
        while (getchar() != '\n');
      }
    } while (quest_da_finire <= n_giocatori);
    system("clear");

    if(quest_da_finire != 0)
      printf("\nQuest impostate\n\n");
}

void crea_stanza_inizio()
{
    /* Questa funzione crea la stanza iniziale del gioco TO FIX*/
    stanza_inizio = (struct Stanza*)malloc(sizeof(*stanza_inizio));
    if(stanza_inizio == NULL)
    {
        printf("Errore di allocazione\n");
        exit(0);
    }
    printf("\nSto creando la stanza\n");
    stanza_inizio -> avanti = NULL;
    stanza_inizio -> destra = NULL;
    stanza_inizio -> sinistra = NULL;
    stanza_inizio -> stanza_precedente = NULL;

    //tutti i giocatori iniziano il gioco dalla stanza iniziale
    printf("\n");
    for(int i = 0;i < n_giocatori;i++)
      giocatori[i].posizione = stanza_inizio;
}


void assegna_stato_stanza(struct Stanza *new_stanza)
{
  /*In che stanza mi trovo? Questa funzione assegna in maniera casuale
    la tipologia di stanza che andremo a creare
    25%botola, 15%quest_doppia, 30%quest_semplice, 30%vuota */

  int probabilita = rand()%100;
  if(probabilita <= 25)
  {
    new_stanza -> tipo = botola;
  }
  else
  {
    if(probabilita > 25 && probabilita <= 40)
    {
      new_stanza -> tipo = quest_complicata;
    }
    else
    {
      if(probabilita > 40 && probabilita <= 70)
      {
        new_stanza -> tipo = quest_semplice;
      }
      else
      {
        new_stanza -> tipo = botola;
      }
    }
  }
  printf("Si ok, ma che tipo di stanza?\n");
}

void stampa_giocatori()
{
  /* questa funzione stampa tutti i giocatori con il rispettivo stato*/
  if(setted == 0) // se il gioco non e' stato settato non e' possibile stampare i giocatori
  {
    printf("\n Non hai ancora impostato il gioco ");
  }
  else
  {
    printf("\nGIOCATORI\tSTATO\n\n");
    for (int i = 0; i < n_giocatori; i++)
    {
      switch (giocatori[i].nome)
      {
        case 0:
          printf("ROSSO\t\t");
          break;
        case 1:
          printf("BLU\t\t");
          break;
        case 2:
          printf("VERDE\t\t");
          break;
        case 3:
          printf("GIALLO\t\t");
          break;
        case 4:
          printf("ARANCIONE\t");
          break;
        case 5:
          printf("NERO\t\t");
          break;
        case 6:
          printf("ROSA\t\t");
          break;
        case 7:
          printf("VIOLA\t\t");
          break;
        case 8:
          printf("CELESTE\t\t");
          break;
        case 9:
          printf("GRIGIO\t\t");
          break;
      }
      switch (giocatori[i].stato)
      {
        case astronauta:
          printf("astronauta\n");
          break;
        case impostore:
          printf("impostore\n");
          break;
        case assassinato:
          printf("assassinato\n");
          break;
        case defenestrato:
          printf("defenestrato\n");
          break;
      }
    }
    printf("\n");
  }
}
void gioca()
{
  if(setted == 0) // controllo se il gioco e' stato impostato
  {
    system("clear");
    printf("\nPrima di poter giocare è necessaro impostare il gioco\n\n");
    while(getchar() != '\n');
    imposta_gioco();
  }
  else
  {
    system("clear");
    printf("Un gruppo n di astronauti si trova in viaggio sull’astronave Skelt,\ne il loro obiettivo è riuscire a completare tutte le attività previste (quest) per il mantenimento della nave,\narrivando così a destinazione.\nTra di loro si celano però anche degli impostori, \nil cui scopo è eliminare di nascosto gli astronautisenza farsi scoprire da essi.\nRiusciranno ad arrivare a destinazione prima di essere decimati?\nTrannoi è liberamente ispirato ad un gioco esistente.\n");

    for(int i = 0; i <n_giocatori; i++)
    {
      turno(i);
      if(i == n_giocatori-1)
        i = -1;
    }
  }
}

void turno(int id)
{
  system("clear");
  int scelta = 0;
  if(giocatori[id].stato == astronauta)
  {
    printf("\e[0;32m");
    do
    {
      printf("\t\tTurno %s\n\n1) Avanza\n\n2) Esegui quest\n\n3) Chiamata di emergenza\n\n", getNomeGiocatore(giocatori[id].nome));
      scanf("%d", & scelta);
        if (scelta != 1 && scelta != 2 && scelta != 3)
        {
          printf("\nNumero non valido. riprova\n");
          while (getchar() != '\n');
        }
    } while(scelta != 1 && scelta != 2 && scelta != 3);
    switch (scelta)
    {
      case 1:
        avanza(id);
        break;
      case 2:
        //esegui_quest();
        break;
      case 3:
        //chiamata_emergenza();
        break;
    }
  }
  else
  {
    if(giocatori[id].stato == impostore)
    {
      printf("\e[0;31m");
      do
      {
        printf("\t\tTurno %s\n\n1) Avanza\n\n2) Esegui quest\n\n3) Chiamata di emergenza\n\n4) Uccidi astronauta\n\n5) Usa botola\n\n6) Sabota\n\n", getNomeGiocatore(giocatori[id].nome));
        scanf("%d", & scelta);
          if (scelta < 1 && scelta > 6)
          {
            printf("\nNumero non valido. riprova\n");
            while (getchar() != '\n');
          }
      } while(scelta < 1 && scelta > 6);

      switch (scelta)
      {
        case 1:
          avanza(id);
          break;
        case 2:
          //esegui_quest();
          break;
        case 3:
          //chiamata_emergenza();
          break;
        case 4:
            //uccidi_astonauta();
          break;
        case 5:
            //usa_botola();
          break;
        case 6:
            //sabotaggio();
          break;
      }
    }
  }

}

void avanza(int id)
{
  int scelta = 0;
  system("clear");
  do
  {
    printf("\t\tTurno %s\n\n1) Avanti\n\n2) Destra\n\n3) Sinistra\n\n4) Fermati\n\n", getNomeGiocatore(giocatori[id].nome));
    scanf("%d", & scelta);
      if (scelta < 1 && scelta > 4)
      {

        printf("\nNumero non valido. riprova\n");
        while (getchar() != '\n');
      }
  } while(scelta < 1 && scelta > 4);

  switch (scelta)
  {
    case 1:
    /*
      if()
      {
        // se stanza null....
      }
    */
      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
  }
}

const char* getNomeGiocatore(enum Nome_giocatore nome)
{
   switch (nome)
   {
      case rosso: return "rosso"; break;
      case blu: return "blu"; break;
      case verde: return "verde"; break;
      case giallo: return "giallo"; break;
      case arancione: return "arancione"; break;
      case nero: return "nero"; break;
      case rosa: return "rosa"; break;
      case viola: return "viola"; break;
      case celeste: return "celeste"; break;
      case grigio: return "grigio"; break;
   }

}
void termina_gioco()
{
  // liberare memoria dinamica
  system("clear");
  printf("\nGrazie per aver giocato a TRANNOI\n");
  exit(0);
}
