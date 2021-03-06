#include <stdio.h>
#include <stdlib.h>
  enum Stato_giocatore {astronauta,impostore,assassinato,defenestrato};
  enum Nome_giocatore {rosso,blu,verde,giallo,arancione,azzurro,rosa,bianco,nero,viola};
  enum Tipo_stanza {vuota,quest_semplice,quest_complicata,botola};
  enum emergenza_chiamata{vero,falso};

  struct Stanza {
    struct Stanza *avanti;
    struct Stanza *destra;
    struct Stanza *sinistra;
    struct Stanza *stanza_precedente;
    enum Tipo_stanza tipo;
    enum emergenza_chiamata chiamata;
  };

  struct Giocatore {
    struct Stanza *posizione;
    enum Stato_giocatore stato;
    enum Nome_giocatore nome;
  };

  void imposta_gioco();
  void gioca();
  void termina_gioco();
