#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

static int n_giocatori = 0;
static int n_impostori = 0;
// quest da finire per vincere il gioco
static unsigned short quest_da_finire = 0;
static int setted = 0;
// puntatore all’array struct Giocatore che
// viene creato dinamicamente in base ai giocatori
static struct Giocatore * giocatori = NULL;


static struct Stanza * stanza_inizio = NULL;
static struct Stanza * lista_stanze = NULL;
static void creazione_giocatori();
static void imposta_impostori();
static void imposta_quest();
static void crea_stanza();
static void assegna_stato_stanza(struct Stanza *new_stanza);
static void stampa_giocatori();

time_t t;

// questa funzione imposta il numero dei giocatori, la tipologia
// e il numero di quest da completare
// Inoltre crea anche la stanza iniziale del gioco
void imposta_gioco()
{
  if(setted == 1)
  {
    //eleminare impostazioni precedenti
  }
  int scelta = 0;
  do
  {
    printf("\t\tImpostazioni\n\n1) Imposta Giocatori\n\n2) Imposta il numero di quest\n\n3) Termina gioco\n\n4) Indietro\n\n");
    scanf("%d", & scelta);
      if (scelta != 1 && scelta != 2 && scelta != 3)
      {
        printf("\nNumero non valido. riprova\n");
        while (getchar() != '\n');
      }
  } while ((scelta != 1 && scelta != 2 && scelta != 3));
  system("clear");
  switch (scelta)
    {
      case 1:
        creazione_giocatori();
        break;
      case 2:
        imposta_quest();
        break;
      case 3:
        termina_gioco();
        break;
    }

    imposta_impostori();
    stampa_giocatori();
    crea_stanza();
    assegna_stato_stanza(stanza_inizio);

}

void creazione_giocatori()
{
  do
  {

    printf("\ninserisci il numero di giocatori (4-10): ");
    scanf("%d", & n_giocatori);
      if ((n_giocatori < 4 || n_giocatori > 10))
      {
        printf("\nNumero non valido. riprova\n");
        while (getchar() != '\n');
      }
  } while ((n_giocatori < 4 || n_giocatori > 10));

  giocatori = calloc(n_giocatori, sizeof( * giocatori));

  if (giocatori == NULL)
  {
    printf("Errore di allocazione\n");
    exit(0);
  }

//////////////////////// CREAZIONE GIOCATORI ////////////////////////////////
// Questo algoritmo mi permette di creare un array di 10 giocatori
  srand(time(0));
  int v_giocatori[n_giocatori];
  int vettore_temporaneo[10];

  for (int i = 0; i < 10; i++)                                    // fill array
    vettore_temporaneo[i] = i;

  for (int i = 0; i < 10; i++)
  {                                                              // shuffle array
    int scambio = vettore_temporaneo[i];
    int indiceRand = rand() % 10;
    vettore_temporaneo[i] = vettore_temporaneo[indiceRand];
    vettore_temporaneo[indiceRand] = scambio;
  }

  for (int i = 0; i < n_giocatori; i++)
    v_giocatori[i] = vettore_temporaneo[i];

    //inserimento dati nella struttura
  for(int i = 0; i < n_giocatori; i++)
  {
    giocatori[i].nome = v_giocatori[i];
  }
  setted = 1;
}

void imposta_impostori()
{
  n_impostori = 0;
  for (int i = 0; i < 3; i++)
  {
    int probabilita = rand() % 100;
          //printf("Probabilita: %d\n",probabilita);
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

  if (n_impostori == 0)
    n_impostori = 1;

  printf("\nIl numero degli impostori è: %d \n",n_impostori);

////////////////////////// RUOLO GIOCATORE //////////////////////////////////////
  int vettore_temporaneo[n_giocatori];

  for (int i = 0; i < n_giocatori; i++)
  {
    vettore_temporaneo[i] = 0;
    //printf("%d\n",vettore_temporaneo[i]);
  }
  printf("\n");
  for (int i = 0; i < n_impostori; i++)
  {
    vettore_temporaneo[i] = 1;
    //printf("%d\n",vettore_temporaneo[i]);
  }

  for (int i = 0; i < n_giocatori; i++)
  { // shuffle array
    int scambio = vettore_temporaneo[i];
    int indiceRand = rand() % n_giocatori;
    vettore_temporaneo[i] = vettore_temporaneo[indiceRand];
    vettore_temporaneo[indiceRand] = scambio;
  }
/*
  for(int i = 0;i < n_giocatori;i++)
    printf("%d\n",vettore_temporaneo[i]);
*/

  // inserisco lo stato nella stuttura
  for (int i = 0; i < n_giocatori; i++)
    giocatori[i].stato = vettore_temporaneo[i];
}

void imposta_quest()
{
  if(setted == 1)
  {
    do
    {
      printf("inserisci il numero di quest totali:\n");
      scanf("%hu", & quest_da_finire);
      if ((quest_da_finire <= 0))
      {
        printf("Numero inserito minore del numero dei giocatori\n\n");
        while (getchar() != '\n');
      }
    } while (quest_da_finire <= n_giocatori);
    system("clear");

    if(quest_da_finire != 0)
      printf("\nQuest impostate\n\n");
  }
  else
  {
    printf("\nNon hai ancora impostato il gioco :(");
    imposta_gioco();
  }
}

void crea_stanza()
{
    stanza_inizio = (struct Stanza*)malloc(sizeof(*stanza_inizio));
    if(stanza_inizio == NULL)
    {
        printf("Errore di allocazione\n");
        exit(0);
    }
    printf("fiero?\n");
    stanza_inizio -> avanti = NULL;
    stanza_inizio -> destra = NULL;
    stanza_inizio -> sinistra = NULL;
    stanza_inizio -> precedente = NULL;

    //tutti i giocatori iniziano il gioco dalla stanza iniziale
    printf("\n");
    for(int i = 0;i < n_giocatori;i++)
      giocatori[i].posizione = stanza_inizio;
}


void assegna_stato_stanza(struct Stanza *new_stanza)
{
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
  printf("possible anche qui?\n");
}

void stampa_giocatori()
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
}
void gioca()
{
  printf("ciao\n");
  if(setted == 0 && quest_da_finire == 0)
  {
    printf("\nPrima di poter giocare a TRANNOI è necessaro impostare il gioco\n\n");
    while(getchar() != '\n');
    imposta_gioco();
  }
}
void termina_gioco()
{
  system("clear");
  printf("\nGrazie per aver giocato a TRANNOI\n");
  exit(0);

    }
