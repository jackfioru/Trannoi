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
static int num_botole = 0;
// puntatore all’array struct Giocatore che
// viene creato dinamicamente in base ai giocatori
static struct Giocatore * giocatori = NULL;
int main();
static struct Stanza * stanza_inizio = NULL;
static struct Stanza * lista_stanze = NULL;
static struct Stanza * nuova_stanza = NULL;
static void creazione_giocatori();
static void imposta_impostori();
static void imposta_quest();
static void crea_stanza_inizio();
static void assegna_stato_stanza(struct Stanza *nuova_stanza);
static void stampa_giocatori();
static void turno(int id);
static void avanza(int id);
static void crea_stanza(int id);
static void esegui_quest(int id);
static void chiamata_emergenza(int id);
static void uccidi_astronauta(int id);
static int menu_uccisione(int id);
static void usa_botola(int id);
static void sabotaggio(int id);
static void controllo_vittoria();
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

  do
  {
    printf("\t\tTrannoi\n\n\t\tImpostazioni\n\n1) Imposta Giocatori\n\n2) Stampa Giocatori\n\n3) Indietro\n\n");
    scanf("%d", & scelta);
    while (getchar() != '\n');
    if (scelta != 1 && scelta != 2 && scelta != 3)
    {
      //system("clear");
      printf("\nNumero non valido. riprova\n");

    }
  } while ((scelta != 1 && scelta != 2 && scelta != 3)); // lettura input da tastiera
  //system("clear");
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
    while (getchar() != '\n');
    if ((n_giocatori < 4 || n_giocatori > 10))
    {
      //system("clear");
      printf("\nNumero non valido. riprova\n");
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
  while (getchar() != '\n');
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
      while (getchar() != '\n');
      if ((quest_da_finire <= n_giocatori))
      {
        //system("clear");
        printf("\n\nNumero inserito minore del numero dei giocatori\n\n");
        while (getchar() != '\n');
      }
    } while (quest_da_finire <= n_giocatori);
    //system("clear");

    if(quest_da_finire != 0)
      printf("\nQuest impostate\n\n");

    while (getchar() != '\n');
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


void assegna_stato_stanza(struct Stanza *nuova_stanza)
{
  /*In che stanza mi trovo? Questa funzione assegna in maniera casuale
    la tipologia di stanza che andremo a creare
    25%botola, 15%quest_doppia, 30%quest_semplice, 30%vuota */

  int probabilita = rand()%100;
  if(probabilita <= 25)
  {
    nuova_stanza -> tipo = botola;
    num_botole++;
  }
  else
  {
    if(probabilita > 25 && probabilita <= 40)
    {
      nuova_stanza -> tipo = quest_complicata;
    }
    else
    {
      if(probabilita > 40 && probabilita <= 70)
      {
        nuova_stanza -> tipo = quest_semplice;
      }
      else
      {
        nuova_stanza -> tipo = botola;
      }
    }
  }
}

void stampa_giocatori()
{
  /* questa funzione stampa tutti i giocatori con il rispettivo stato*/
  if(setted == 0) // se il gioco non e' stato settato non e' possibile stampare i giocatori
  {
    printf("\n Non hai ancora impostato il gioco ");
    while (getchar() != '\n');
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
    while (getchar() != '\n');
  }
}
void gioca()
{
  if(setted == 0) // controllo se il gioco e' stato impostato
  {
    //system("clear");
    printf("\nPrima di poter giocare è necessaro impostare il gioco\n\n");
    while(getchar() != '\n');
    imposta_gioco();
  }
  else
  {
    //system("clear");
    printf("Un gruppo n di astronauti si trova in viaggio sull’astronave Skelt,\ne il loro obiettivo è riuscire a completare tutte le attività previste (quest) per il mantenimento della nave,\narrivando così a destinazione.\nTra di loro si celano però anche degli impostori, \nil cui scopo è eliminare di nascosto gli astronautisenza farsi scoprire da essi.\nRiusciranno ad arrivare a destinazione prima di essere decimati?\nTrannoi è liberamente ispirato ad un gioco esistente.\n");
    while(getchar() != '\n');

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
///////////////////////////////////////////// TURNO ASTRONAUTA ////////////////////////////////////////////////////
  if(giocatori[id].stato == astronauta)
  {
    printf("\e[0;32m");
    do
    {
      printf("\t\tTurno %s\n\n1) Avanza\n\n2) Esegui quest\n\n3) Chiamata di emergenza\n\n", getNomeGiocatore(giocatori[id].nome));
      scanf("%d", & scelta);
      while (getchar() != '\n');
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
        esegui_quest(id);
        break;
      case 3:
        for(int i = 0; i < n_giocatori;i++)
        {
          if(giocatori[i].stato == assassinato && giocatori[i].posizione == giocatori[id].posizione)
            chiamata_emergenza(id);
        }
        break;
    }
  }
  else
  {
    ///////////////////////////////////////////////////////// TURNO IMPOSTORE ///////////////////////////////////////////////////////////
    if(giocatori[id].stato == impostore)
    {
      printf("\e[0;31m");
      do
      {
        printf("\t\tTurno %s\n\n1) Avanza\n\n2) Sabota\n\n3) Chiamata di emergenza\n\n4) Uccidi astronauta\n\n5) Usa botola\n\n", getNomeGiocatore(giocatori[id].nome));
        scanf("%d", & scelta);
        while (getchar() != '\n');
        if (scelta < 1 || scelta > 6)
        {
          printf("\nNumero non valido. riprova\n");
          while (getchar() != '\n');
        }
      } while(scelta < 1 || scelta > 6);

      switch (scelta)
      {
        case 1:
          avanza(id);
          break;
        case 2:
          sabotaggio(id);
          break;
        case 3:
          for(int i = 0; i < n_giocatori;i++)
          {
            if(giocatori[i].stato == assassinato && giocatori[i].posizione == giocatori[id].posizione)
              chiamata_emergenza(id);
            else
              printf("Nessun giocatore assasinato nella stanza\n");

              while (getchar() != '\n');
          }
          break;
        case 4:
            uccidi_astronauta(id);
          break;
        case 5:
          if(giocatori[id].posizione->tipo == botola)
            usa_botola(id);
          else
            printf("Non ci sono botole nella stanza...\n");

            while (getchar() != '\n');
          break;
      }
    }
  }
  printf("posizione %s: %p\n",getNomeGiocatore(giocatori[id].nome) , giocatori[id].posizione);
  //while (getchar()!='\n');
}

void avanza(int id)
{
  int scelta = 0;
  //system("clear");
  do
  {
    printf("\t\tTurno %s\n\n1) Avanti\n\n2) Destra\n\n3) Sinistra\n\n4) Fermati\n\n", getNomeGiocatore(giocatori[id].nome));
    while (getchar() != '\n');
    scanf("%d", &scelta);
      if (scelta < 1 || scelta > 4)
      {

        printf("\nNumero non valido. riprova\n");
        while (getchar() != '\n');
      }
  } while(scelta < 1 || scelta > 4);

  switch (scelta)
  {
    case 1:
      if(giocatori[id].posizione->avanti == NULL)
      {
        crea_stanza(id);
        giocatori[id].posizione->avanti = nuova_stanza;
        giocatori[id].posizione = nuova_stanza;
      }
      else
      {
        giocatori[id].posizione = giocatori[id].posizione->avanti;
      }
      break;
    case 2:
      if(giocatori[id].posizione->destra == NULL)
      {
        crea_stanza(id);
        giocatori[id].posizione->destra = nuova_stanza;
        giocatori[id].posizione = nuova_stanza;
      }
      else
      {
        giocatori[id].posizione = giocatori[id].posizione->destra;
      }
      break;
    case 3:
      if(giocatori[id].posizione->sinistra == NULL)
      {
        crea_stanza(id);
        giocatori[id].posizione->sinistra = nuova_stanza;
        giocatori[id].posizione = nuova_stanza;
      }
      else
      {
        giocatori[id].posizione = giocatori[id].posizione->sinistra;
      }
      break;
    case 4:
    // non si muove
      break;
  }
}

void crea_stanza(int id)
{
  nuova_stanza = (struct Stanza*)malloc(sizeof(*nuova_stanza));
  nuova_stanza -> avanti = NULL;
  nuova_stanza -> destra = NULL;
  nuova_stanza -> sinistra = NULL;
  nuova_stanza -> stanza_precedente = giocatori[id].posizione;
  nuova_stanza -> emergenza = false;
  assegna_stato_stanza(nuova_stanza);
  printf("stanza appena creata %p\n",nuova_stanza);
  lista_stanze = stanza_inizio;

  while(lista_stanze->cronologia != NULL)
  {
    lista_stanze = lista_stanze->cronologia;
  }
  lista_stanze->cronologia = nuova_stanza;
  lista_stanze->cronologia->cronologia = NULL;

}

void esegui_quest(int id)
{
  //printf("%d\n", giocatori[id].posizione->tipo);

  switch (giocatori[id].posizione->tipo) {
    case quest_semplice:
      quest_da_finire--;

      giocatori[id].posizione->tipo = vuota;
      printf("Quest semplice eseguita con successo\n");
      while (getchar() != '\n');
      break;
    case quest_complicata:
      if(quest_da_finire == 1)
      {
        quest_da_finire--;
      }
      else
      {
        quest_da_finire -= 2;
      }

      giocatori[id].posizione->tipo = vuota;
      printf("Quest complicata eseguita con successo\n");
      while (getchar() != '\n');
      break;
    default:
      printf("Non ci sono quest da eseguire\n");
      while (getchar() != '\n');
  }
  printf("%hu\n", quest_da_finire);
  while(getchar()!='\n'){}

  if(quest_da_finire == 0)
  {

    system("clear");
    printf("Gli astronauti hanno completato tutte le quest\nL'asrtronave è in salvo\nGli ASTRONAUTI vincono la parita\n");
    while (getchar() != '\n');
    termina_gioco();
  }
}

void chiamata_emergenza(int id)
{
  // varabili che contengono il numero di astronauti e impostori
  int num_a = 0, num_i = 0;

  int prob_a = 0, prob_i = 0;
  //int p_in_room = 0;

  if(giocatori[id].posizione->emergenza == true)
  {
    printf("chiamata di emergenza gia effettuata\n");
    while (getchar() != '\n');
    return;
  }
  /* imposto la chiamata di emergenza a vera cosi da non essere più possibile rieffettuare
    la chiamata */
    giocatori[id].posizione->emergenza = true;

  for(int i = 0;i<n_giocatori;i++)
  {
    if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
    {
      num_a++;
    }
    if(giocatori[i].stato == impostore && giocatori[i].posizione == giocatori[id].posizione)
    {
      num_i++;
    }
  }
  /* se nella stanza sono presenti solo impostori viene negata la chiamata di emergenza
  perchè nel gioco gli impostori si conoscono tra loro */
  if(num_a == 0)
  {
    printf("Nella stanza non sembrano esserci astronauti...\n");
    while (getchar() != '\n');
    giocatori[id].posizione -> emergenza = false;
    return;
  }
  // se non ce stanno impostori uno a caso fori
  if(num_i == 0)
  {
    srand(time(0));
    // estraggo un numero random che corrisponde al giocatore da uccidere
    int prob = rand()%num_a;
    for(int i= 0;i<n_giocatori;i++)
    {
      printf("debugger o: %d random: %d\n",i ,prob);
      if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
      {
        if(prob == 0)
        {
          giocatori[i].stato = defenestrato;
          printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
          while (getchar() != '\n');
          break;
        }
        prob--;
      }
    }
    controllo_vittoria();
    return;
  }
  // se il numero di astronauti e impostori equivale allora tutti hanno le stesse probabilità
  if(num_a == num_i)
  {
    srand(time(0));
    // estraggo un numero random che corrisponde al giocatore da uccidere
    int prob = rand()%(num_a+num_i);
    for(int i= 0;i<n_giocatori;i++)
    {
      printf("debugger : %d random: %d\n",i ,prob);
      if((giocatori[i].stato == astronauta || giocatori[i].stato == impostore)  && giocatori[i].posizione == giocatori[id].posizione)
      {
        if(prob == 0)
        {
          giocatori[i].stato = defenestrato;
          printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
          while (getchar() != '\n');
          break;
        }
        prob--;
      }
    }
    controllo_vittoria();
    return;
  }

  // calcolo la probailità dell'astronauta
    prob_a = 30 + (20*num_i) - (30*(num_a-1));

  // se almeno un impostore è presente nella stanza calcolo la probabilita di venire defenestrato
  if(num_i >= 1 )
  {
    prob_i = 30 + (20*num_a) - (30*(num_i-1));
  }

  /* se la probabilita di essere defenestrato é negativa automaticamente in entrambi i casi
    viene scelto un giocatore appartenente al ruolo opposto
  */
  if(prob_i <= 0)
    {
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_a;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }

  if(prob_a <= 0)
  {
    srand(time(0));
    // estraggo un numero random che corrisponde al giocatore da uccidere
    int prob = rand()%num_i;
    for(int i= 0;i<n_giocatori;i++)
    {
      printf("debugger o: %d random: %d\n",i ,prob);
      if(giocatori[i].stato == impostore && giocatori[i].posizione == giocatori[id].posizione)
      {
        if(prob == 0)
        {
          giocatori[i].stato = defenestrato;
          printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
          while (getchar() != '\n');
          break;
        }
        prob--;
      }
    }
    controllo_vittoria();
    return;
  }

  // dopo aver calcolato tutte le possibili combinazioni rimangono 4 casi possibili

  if(num_a == 2 && num_i == 1)
  {
    //  da 0 a 20 un astronauta viene defenstrato
    // da 21 a 90 un impostore viene defestrato
    int p_tot = prob_a + prob_i;
    srand(time(0));
    // valore randomico da 0 a 90
    int r = rand()%p_tot;
    if(r <= 20)
    {
      //Astronauta defenestrato
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_a;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }
    else
    {
      // Impostore defenestrato
      for(int i= 0;i<n_giocatori;i++)
      {
        if(giocatori[i].stato == impostore && giocatori[i].posizione == giocatori[id].posizione)
        {
          giocatori[i].stato = defenestrato;
          printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
          while (getchar() != '\n');
          break;
        }
      }
       controllo_vittoria();
      return;
    }
  }
  if(num_a == 1 && num_i == 2)
  {
    //  da 0 a 20 un  viene impostore defenstrato
    // da 21 a 90 un astronauta viene defestrato
    int p_tot = prob_a + prob_i;
    srand(time(0));
    int r = rand()%p_tot;
    if(r <= 20)
    {
      //Impostore defenestrato
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_i;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == impostore && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }
    else
    {
      // atronauta defenestrato
      for(int i= 0;i<n_giocatori;i++)
      {
        if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
        {
          giocatori[i].stato = defenestrato;
          printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
          while (getchar() != '\n');
          break;
        }
      }
      controllo_vittoria();
      return;
    }
  }
  if(num_a == 3 && num_i == 2)
  {
    //  da 0 a 10 un  viene astronauta defenstrato
    // da 10 a 60 un impostore viene defestrato
    int p_tot = prob_a + prob_i;
    srand(time(0));
    int r = rand()%p_tot;
    if(r <= 10)
    {
      //astronauta defenstrato
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_a;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }
    else
    {
      // impo
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_i;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == impostore && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }
  }
  if(num_a == 2 && num_i == 3)
  {
    //  da 0 a 10 un  viene impostore defenstrato
    // da 10 a 60 un astronauta viene defestrato
    int p_tot = prob_a + prob_i;
    srand(time(0));
    int r = rand()%p_tot;
    if(r <= 10)
    {
      //impostore defenstrato
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_i;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == impostore && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }
    else
    {
      // astronauta defenestrato
      srand(time(0));
      // estraggo un numero random che corrisponde al giocatore da uccidere
      int prob = rand()%num_a;
      for(int i= 0;i<n_giocatori;i++)
      {
        printf("debugger o: %d random: %d\n",i ,prob);
        if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
        {
          if(prob == 0)
          {
            giocatori[i].stato = defenestrato;
            printf("%s é stato defenestrato\n", getNomeGiocatore(giocatori[i].nome));
            while (getchar() != '\n');
            break;
          }
          prob--;
        }
      }
      controllo_vittoria();
      return;
    }
  }



  printf("probabilita astro: %d probabilita impo: %d\n",prob_a, prob_i);
}
void uccidi_astronauta(int id)
{

  int count_astronauti = 0,sospetto = 0;

  for(int i = 0; i < n_giocatori;i++)
  {
    // controllo se ci sono astronauti nella stanza
    if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
      count_astronauti++;
  }
  printf("Astronauti in stanza: %d\n", count_astronauti );
  while (getchar() != '\n');

  if(count_astronauti == 0)
    printf("Sembra non esserci nessun astronauta nelle vicinanze...\n");
    while (getchar() != '\n');

  // caso in cui un astronauta sia presente nella stanza
  if(count_astronauti == 1)
  {
    // uccisione astronauta
    for(int i = 0; i < n_giocatori;i++)
    {
      if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
      {
        giocatori[i].stato = assassinato;
        printf("Hai ucciso %s\n", getNomeGiocatore(giocatori[i].nome));
        while (getchar() != '\n');
        controllo_vittoria();
      }
    }
    /*controllo se ci sono altri astronauti nelle stanza precedente,
    in caso positivo aumento il livello di sospetto*/
    for(int i = 0; i < n_giocatori;i++)
    {
      if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione->stanza_precedente)
      {
        sospetto += 20;
        printf("Potrebbe averti visto %s\n", getNomeGiocatore(giocatori[i].nome));
        while (getchar() != '\n');
      }
    }
    // in base al livello di sopetto il giocatore a più o meno probabilità di essere scoperto
    srand(time(0));
    int probabilita = 1+rand()%100;
    if(probabilita <= sospetto)
    {
      //muori
      printf("Qualcuno ti ha visto\n\nSei stato defenestrato\n");
      while (getchar() != '\n');
      giocatori[id].stato = defenestrato;
      controllo_vittoria();
    }
    else
    {
      printf("Nessuno sta sospettando di te\n");
      while (getchar() != '\n');
    }
  }
  // più di un astronauta presente nella stanza
  if(count_astronauti > 1)
  {
    int scelta = menu_uccisione(id);
    giocatori[scelta].stato = assassinato;
    printf("Hai ucciso %s\n", getNomeGiocatore(giocatori[scelta].nome) );
    while (getchar() != '\n');
    // incremento il livello di sospetto del 50% per ogni astronauta nella stanza
    sospetto = (count_astronauti-1)*50;
    /*controllo se ci sono altri astronauti nelle stanza precedente,
    in caso positivo aumento il livello di sospetto*/
    for(int i = 0; i < n_giocatori;i++)
    {
      if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione->stanza_precedente)
      {
        sospetto += 20;
        printf("Potrebbe averti visto %s\n", getNomeGiocatore(giocatori[i].nome));
        while (getchar() != '\n');
      }
    }
    // in base al livello di sopetto il giocatore a più o meno probabilità di essere scoperto
    srand(time(0));
    int probabilita = 1+rand()%100;
    if(probabilita <= sospetto)
    {
      printf("Ti hanno beccato...\n\nSei stato defenestrato\n");
      while (getchar() != '\n');
      giocatori[id].stato = defenestrato;
      controllo_vittoria();
    }
    else
    {
      printf("Nessuno sta sospettando di te\n");
      while (getchar() != '\n');
    }
  }
}
int menu_uccisione(int id)
{
  int scelta = 0;
  do{
    printf("Scegli chi vuoi uccidere\n");
    for(int i = 0; i < n_giocatori;i++)
    {
      if(giocatori[i].stato == astronauta && giocatori[i].posizione == giocatori[id].posizione)
      {
        printf("%d) %s\n", i, getNomeGiocatore(giocatori[i].nome));
      }
    }
    scanf("%d",&scelta);
    while (getchar() != '\n');
    //printf("valore : %d\n", scelta);
    if(giocatori[scelta].stato != astronauta || giocatori[scelta].posizione != giocatori[id].posizione ||(scelta > n_giocatori)){
      //system("clear");
      printf("\nNumero non valido. riprova\n\n");
       while(getchar() != '\n');
    }
  } while(giocatori[scelta].stato != astronauta || giocatori[scelta].posizione != giocatori[id].posizione||(scelta > n_giocatori));
  return scelta;
}
void usa_botola(int id)
{

  srand(time(0));
  printf("nuemro di botole %d\n", num_botole);
  /* in caso non fossero presenti altre stanze di tipo botola
   il giocatore viene telerasprotato in una stanza a caso */
  if(num_botole <= 1)
  {
    //genero un numero random
    int rnd = num_botole + rand() % 20;
    printf("Numero random: %d\n", rnd);

    //scorro lista tante volte quante il numero random
    lista_stanze = stanza_inizio;
    for(int i = 0;i < rnd;i++)
    {
      if(lista_stanze->cronologia == NULL)
        lista_stanze = stanza_inizio;

      lista_stanze = lista_stanze->cronologia;
    }
    giocatori[id].posizione = lista_stanze;
    printf("spostamento avvenuto con successo %p\n", giocatori[id].posizione);
    while (getchar() != '\n');
  }

  if(num_botole > 1)
  {
    //genero un numero random
    int rnd = num_botole + rand() % 20;

    //scorro lista finche il numero random non diventa uguale a 0
    lista_stanze = stanza_inizio;
    while(true)
    {
      if(rnd == 0)
      {
        giocatori[id].posizione = lista_stanze;
        printf("spostamento avvenuto con successo %p\n", giocatori[id].posizione);
        while (getchar() != '\n');
        break;
      }
      // ricomincio lo scorrimento da capo
      if(lista_stanze->cronologia == NULL)
        lista_stanze = stanza_inizio;

      // decremento il numero random ogni stanza di tipo botola
      if(lista_stanze->tipo == botola)
        rnd--;

      lista_stanze = lista_stanze->cronologia;
    }
  }

}
void sabotaggio(int id)
{
  printf("%d\n", giocatori[id].posizione->tipo);

  switch (giocatori[id].posizione->tipo)
  {
    case quest_semplice:
      giocatori[id].posizione->tipo = vuota;
      printf("Quest sabotata\n");
      while (getchar() != '\n');
      break;
    case quest_complicata:
      giocatori[id].posizione->tipo = vuota;
      printf("Quest sabotata\n");
      while (getchar() != '\n');
      break;
    default:
      printf("Non ci sono quest da sabotare\n");
      while (getchar() != '\n');
  }
  //while(getchar()!='\n'){}
}
void controllo_vittoria()
{
  /* Queste due variabili conterranno il numero di impostori e astronauti rimasti */
  int c_a = 0, c_i = 0;
  for(int i = 0;i < n_giocatori;i++)
  {
    if(giocatori[i].stato == astronauta)
      c_a++;

    if(giocatori[i].stato == impostore)
      c_i++;
  }
  if(c_a == 0)
  {
    system("clear");
    printf("Tutti gli astronauti sono stati eliminati\n\nGli IMPOSTORI vincono la parita\n");
    while (getchar() != '\n');
    termina_gioco();
  }
  if(c_i == 0)
  {
    system("clear");
    printf("Tutti gli impostori sono stati defenestrati\n\nGli Astronauti vincono la parita\n");
    while (getchar() != '\n');
    termina_gioco();
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
      default: return "errore";
   }
}
void termina_gioco()
{
  if(setted == 1)
  {
    //Svuoto tutte le stanze dalla memoria dinamica
    lista_stanze = stanza_inizio;
    while(lista_stanze -> cronologia != NULL)
    {
      free(lista_stanze);
      printf("stanza: %p\n", lista_stanze);
      lista_stanze = lista_stanze -> cronologia;
    }
    // libero ultima stanza
    free(lista_stanze);

    free(giocatori);
  }

  //system("clear");
  printf("\nGrazie per aver giocato a TRANNOI\n");
  exit(0);
}
