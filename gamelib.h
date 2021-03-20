#include <stdio.h>

enum Tipo_stanza {vuota,quest_semplice,quest_complicata,botola};
enum emergenza_chiamata {true,false};
enum Stato_giocatore {astronauta,impostore,assasinato,defenestrato};
enum Nome_giocatore {rosso,blu,verde,giallo,arancione,nero,rosa,viola,celeste,grigio};

   struct Stanza{
     struct Stanza *avanti;
     struct Stanza *destra;
     struct Stanza *sinistra;
     struct Stanza *precedente;
     enum Tipo_stanza tipo;
     enum emergenza_chiamata emergenza;
   };

   struct Giocatore{
     struct Stanza *posizione;
     enum Stato_giocatore stato;
     enum Nome_giocatore nome;
  };

  void imposta_gioco();
  void gioca();
  void termina_gioco();
