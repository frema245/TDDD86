/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150         45 ms       22 ms
    200         111 ms      39 ms
    300         324 ms      63 ms
    400         758 ms      91 ms
    800         5980 ms     280 ms
   1600         46976 ms    1091 ms
   3200         (376 s)     4578 ms            
   6400         (3008 s)    19137 ms
  12800         (24064 s)   82166 ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Gissningar inom parentes.

Brute: O(N^4)
I brute ser vi ett djup på 3 som itererar över (nästan) alla punkter. 
Längst in är en loop som inte itererar över alla punkter men som växer proportioneligt med N i det värsta fallet.
Därför bör det värsta fallet motsvara (N^4) även om de fallen vi testat tycks ligga närmare (N^3).


Sortering: O(N^2)
Djup av loopar = 2. En dubblering av punkter motsvarar en multiplikation med faktor 4 i körtiden, vilket ser ut att
stämma bra med vårt resultat. 






