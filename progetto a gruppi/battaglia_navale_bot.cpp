#include <iostream>
#include <string>
#include <cctype> // Per tolower
#include <cstdlib>
#include <ctime>

using namespace std;
/**
 * Un enumeratore in sostanza serve a definire un set di elementi
 * appartenenti alla stessa categoria.
 *
 * ES: Colori: blu, rosso e verde.
 *
 * Un enum non puo essere valorizzato e non puo' assumere valori
 * differenti da quelli a se definiti.
 *
 * ES: Colori viola  NO!, gatto  NO!.... rosso ? SI!
 */
enum Giocatore
{
    giocatore1, //0
    bot //1
};

int grigliaGiocatore1[10][10] = {0}, grigliaGiocatore1f[10][10] = {0}, grigliaBot2f[10][10] = {0}, grigliaBot2[10][10] = {0}, turno = 0, r, c;

int naviDeiGiocatori[2][5] = {
    {1, 2, 3, 4, 5}, // giocatore
    {1, 2, 3, 4, 5}, // bot
}; 
int totNaviGiocatore = 14;
int totNaviBot = 14;

Giocatore chiGiocaOra()
{
    return turno % 2 == 0 ? giocatore1 : bot;
}

int (*tabellaDiGiocaOra())[10]
{
    return (chiGiocaOra() == bot) ? grigliaBot2 : grigliaGiocatore1;
}
int (*tabellaDiGiocaOra_f())[10]
{
    return (chiGiocaOra() == bot) ? grigliaBot2f : grigliaGiocatore1f;
}

int generaRigaOColonna()
{
    return rand() % 10;
}

string generaDirezione()
{
    string direzioni[4] = {"sopra", "sotto", "destra", "sinistra"};
    return direzioni[rand() % 4];
}

// Funzione per confrontare due stringhe ignorando maiuscole/minuscole
bool Maiusc(const string &str1, const string &str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }
    return equal(str1.begin(), str1.end(), str2.begin(),
                 [](char a, char b)
                 {
                     return tolower(a) == tolower(b);
                 });
}

// Funzione per stampare la griglia 10x10 del giocatore corrente
void stampaGriglia()
{
    // recupero la matrice[10][10] del giocatore corrente
    int(*griglia)[10] = tabellaDiGiocaOra();

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << griglia[i][j] << "\t";
        }
        cout << endl;
    }
}

// Funzione per validare se una nave può essere posizionata
bool validaPosizione(int r, int c, int lunghezza, string direzione)
{
    // recupero la matrice[10][10] del giocatore corrente
    int(*griglia)[10] = tabellaDiGiocaOra();

    for (int i = 0; i < lunghezza; i++)
    {
        if (r < 0 || r >= 10 || c < 0 || c >= 10 || griglia[r][c] != 0)
        {
            return false; // Fuori dai limiti o posizione già occupata
        }

        if (Maiusc(direzione, "sopra"))
            r--;
        else if (Maiusc(direzione, "sotto"))
            r++;
        else if (Maiusc(direzione, "destra"))
            c++;
        else if (Maiusc(direzione, "sinistra"))
            c--;
    }
    return true;
}

// Funzione per posizionare una nave
void posizionaNave(int r, int c, int lunghezza, string direzione)
{
    // recupero la matrice[10][10] del giocatore corrente
    int(*griglia)[10] = tabellaDiGiocaOra();

    for (int i = 0; i < lunghezza; i++)
    {
        griglia[r][c] = lunghezza; // Posiziona la nave
        if (Maiusc(direzione, "sopra"))
            r--;
        else if (Maiusc(direzione, "sotto"))
            r++;
        else if (Maiusc(direzione, "destra"))
            c++;
        else if (Maiusc(direzione, "sinistra"))
            c--;
    }
}

void generaTabella(Giocatore giocatore, int lunghezza)
{
    bool generaDaSolo = giocatore == bot;

    for (int i = 0; i < 5; i++)
    {
        string direzione;
        if (!generaDaSolo)
        {
            cout << "Nave " << i + 1 << " (lunghezza " << lunghezza << "):";
        }
        while (true)
        {
            if (generaDaSolo)
            {
                r = generaRigaOColonna();
                c = generaRigaOColonna();
                direzione = generaDirezione();
            }
            else
            {
                cout << "Riga (1-10): ";
                cin >> r;
                cout << "Colonna (1-10): ";
                cin >> c;
                cout << "Direzione (sopra, sotto, destra, sinistra): ";
                cin >> direzione;
            }
            if (validaPosizione(r - 1, c - 1, lunghezza, direzione))
            {
                posizionaNave(r - 1, c - 1, lunghezza, direzione);
                break;
            }
            else
            {
                if (!generaDaSolo)
                {
                    cout << "Errore: Posizione non valida! Riprova." << endl;
                }
            }
        }

        if (!generaDaSolo)
        {
            stampaGriglia(); // Stampa la griglia aggiornata
        }
        lunghezza--;
    }
}

void attacco()
{
    Giocatore giocatore = chiGiocaOra();
    int(*griglia)[10] = tabellaDiGiocaOra();
    int(*griglia_f)[10] = tabellaDiGiocaOra_f();

    if (giocatore == giocatore1)
    {
        stampaGriglia();
       
        while(r<=10&&c<=10) {
            cout << "[GIOCATORE-" << giocatore + 1 << "] - Inserisci riga <spazio> colonna:";
            cin >> r >> c;
            if(r>10||c>10){
                cout<<"Valori non validi, riprova"<<endl;
            }
        }
        
    }
    else
    {
        r = generaRigaOColonna();
        c = generaRigaOColonna();
    }

    int casella = griglia[r][c];
    int casella_f = griglia_f[r][c];

    if (casella_f == 1)
    {
        cout << "Hai gia attaccato queste coordinate!";
    }
    else
    {
        int nave = naviDeiGiocatori[giocatore][casella - 1];
        if (nave != 0)
        {
            nave -= 1; // decremento il contatore della nave presa
            cout << "Hai preso un blocco della nave lunga " << casella << "! Gli rimangono " << nave << " spazi!!";

            if (giocatore == bot)
            {
                totNaviBot--;
            }
            else
            {
                totNaviGiocatore--;
            }
        }
        else
        {
            cout << "Hai mancato le navi!";
        }
    }
}

bool partitaNonTerminata()
{
    // Se uno dei due giocatori ha terminato le navi la partita e' completa
    bool totNaviGiocatoreFinite = (totNaviGiocatore != 0);
    bool totNaviBotFinite = (totNaviBot != 0);

    if (!totNaviGiocatoreFinite || !totNaviBotFinite)
    {
        cout << "Il vincitore e' " << (!totNaviGiocatoreFinite ? "il giocatore" : "il computer");
    }

    return totNaviGiocatoreFinite || totNaviBotFinite;
}

// Programma principale
int main()
{
    // Inizializzo il generatore di numeri casuali
    srand(time(0));
    cout << "REGOLE:\n1-Le navi sono una per tipo, da 5 spazi a 1.\n"
            "2-Per le coordinate inserire prima la riga e poi la colonna.\n"
            "3-Le navi non si possono sovrapporre.\n"
            "4-Le righe e le colonne partono dall'angolo in alto a sinistra.\n"
            "5-Le mappe hanno larghezza e lunghezza pari a 10 spazi.\n\n";

    for (int turno = 1; turno <= 2; turno++)
    {
        Giocatore giocatore = turno == 1 ? giocatore1 : bot;
        cout << "Giocatore " << turno << ", posiziona le tue navi!" << endl;
        int lunghezza = 5; // Indica la lunghezza della nave corrente

        generaTabella(giocatore, lunghezza);
        if (giocatore != bot)
        {
            cout << "Premi un tasto per passare il turno al prossimo giocatore." << endl;
            cin.ignore();
            cin.get();
        }

        system("clear");
    }

    cout << "Entrambi i giocatori hanno posizionato le loro navi!" << endl;
    cout << "Inizia la fase di battaglia! Premi un tasto per iniziare" << endl;

    // si inizia ad attaccare.
    while (partitaNonTerminata())
    {
        cin.ignore();
        system("clear");
        attacco();
        turno++;
    }
    return 0;
}
