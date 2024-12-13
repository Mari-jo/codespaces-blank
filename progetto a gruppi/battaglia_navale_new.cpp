#include <iostream>
#include <string>
#include <cctype> // Per tolower
#include <cstdlib>

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
enum Giocatori {giocatore1, giocatore2}; 

int grigliaGiocatore1[10][10] = {0}, grigliaGiocatore1f[10][10] = {0}, grigliaBot2f[10][10] = {0}, grigliaBot2[10][10] = {0}, turno, r, c;

int nave15 = 5;
int nave14 = 4;
int nave13 = 3;
int nave12 = 2;
int nave25 = 5;
int nave24 = 4;
int nave23 = 3;
int nave22 = 2;
int totnavi1 = 14;
int totnavi2 = 14;
bool statopartita = true;

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

// Funzione per stampare una griglia 10x10
void stampaGriglia(int griglia[10][10])
{
    char alfabeto[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' , 'I', 'L'};
    for (int i = 0; i < 10; i++)
    {
        cout << i << "\t|\t"; // r || n | n | 
        for (int j = 0; j < 10; j++)
        {
            
            cout << alfabeto[j] << " | " << griglia[i][j] << "  |  ";
        }
        cout << endl;
    }
}

// Funzione per validare se una nave può essere posizionata
bool validaPosizione(int griglia[10][10], int r, int c, int lunghezza, string direzione)
{

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
void posizionaNave(int griglia[10][10], int r, int c, int lunghezza, string direzione, int numero)
{
    for (int i = 0; i < lunghezza; i++)
    {
        griglia[r][c] = numero; // Posiziona la nave
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

// Programma principale
int main()
{

    cout << "REGOLE:\n1-Le navi sono una per tipo, da 5 spazi a 1.\n"
            "2-Per le coordinate inserire prima la riga e poi la colonna.\n"
            "3-Le navi non si possono sovrapporre.\n"
            "4-Le righe e le colonne partono dall'angolo in alto a sinistra.\n"
            "5-Le mappe hanno larghezza e lunghezza pari a 10 spazi.\n\n";

    for (int turno = 1; turno <= 2; turno++)
    {
        int(*grigliaAttuale)[10] = (turno == 1) ? grigliaGiocatore1 : grigliaBot2;
        cout << "Giocatore " << turno << ", posiziona le tue navi!" << endl;

        int numero = 5; // Indica la lunghezza della nave corrente
        for (int i = 0; i < 5; i++)
        {
            string direzione;
            cout << "Nave " << i + 1 << " (lunghezza " << numero << "):";

            while (true)
            {
                cout << "Riga (1-10): ";
                cin >> r;
                cout << "Colonna (1-10): ";
                cin >> c;
                cout << "Direzione (sopra, sotto, destra, sinistra): ";
                cin >> direzione;

                if (validaPosizione(grigliaAttuale, r - 1, c - 1, numero, direzione))
                {
                    posizionaNave(grigliaAttuale, r - 1, c - 1, numero, direzione, numero);
                    break;
                }
                else
                {
                    cout << "Errore: Posizione non valida! Riprova." << endl;
                }
            }
            stampaGriglia(grigliaAttuale); // Stampa la griglia aggiornata
            numero--;
        }
        cout << "Premi un tasto per passare il turno al prossimo giocatore." << endl;
        cin.ignore();
        cin.get();
        cout << string(50, '\n'); // Pulisce lo schermo
    }

    cout << "Entrambi i giocatori hanno posizionato le loro navi!" << endl;
    cout << "Inizia la fase di battaglia" << endl;

    // si inizia ad attaccare.
    while (statopartita == true)
    {
        cin.ignore();
        cin.get();
        system("clear");


        if (turno % 2 == 0)
        {
            stampaGriglia(grigliaBot2f);
            cout << "giocatore 1 inserisci riga e colonne dell'attacco: ";
            cin >> r;
            cin >> c;
            if (grigliaBot2[r][c] != 0)
            {
                if (grigliaBot2f[r][c] == 1)
                {
                    cout << "Hai gia attaccato queste coordinate!";
                }
                else
                {
                    switch (grigliaBot2[r][c])
                    {
                    case 5:
                        nave15 -= 1;
                        totnavi1 -= 1;
                        cout << "Hai preso un blocco della nave lunga 5! Gli rimangono " << nave15 << " spazi!!";
                        break;

                    case 4:
                        nave14 -= 1;
                        totnavi1 -= 1;
                        cout << "Hai preso un blocco della nave lunga 4! Gli rimangono " << nave14 << " spazi!!";
                        break;

                    case 3:
                        nave13 -= 1;
                        totnavi1 -= 1;
                        cout << "Hai preso un blocco della nave lunga 3! Gli rimangono " << nave13 << " spazi!!";
                        ;
                        break;

                    case 2:
                        nave12 -= 1;
                        totnavi1 -= 1;
                        cout << "Hai preso un blocco della nave lunga 2! Gli rimangono " << nave12 << " spazi!!";
                        break;

                    default:
                        cout << "Hai mancato le navi!";
                        break;
                    }
                }
            }
        }
        if (turno % 2 == 1)
        {
            stampaGriglia(grigliaGiocatore1f);
            cout << "giocatore 2 inserisci riga e colonne dell'attacco: ";
            cin >> r;
            cin >> c;
            if (grigliaGiocatore1[r][c] != 0)
            {
                if (grigliaGiocatore1f[r][c] == 1)
                {
                    cout << "Hai gia attaccato queste coordinate!";
                }
                else
                {
                    switch (grigliaGiocatore1[r][c])
                    {
                    case 5:
                        nave25 -= 1;
                        totnavi2 -= 1;
                        cout << "Hai preso un blocco della nave lunga 5! Gli rimangono " << nave25 << " spazi!!";
                        break;

                    case 4:
                        nave24 -= 1;
                        totnavi2 -= 1;
                        cout << "Hai preso un blocco della nave lunga 4! Gli rimangono " << nave24 << " spazi!!";
                        break;

                    case 3:
                        nave23 -= 1;
                        totnavi2 -= 1;
                        cout << "Hai preso un blocco della nave lunga 3! Gli rimangono " << nave23 << " spazi!!";
                        ;
                        break;

                    case 2:
                        nave22 -= 1;
                        totnavi2 -= 1;
                        cout << "Hai preso un blocco della nave lunga 2! Gli rimangono " << nave22 << " spazi!!";
                        break;

                    default:
                        cout << "Hai mancato le navi!";
                        break;
                    }
                }
            }
        }
        turno++;
        if (totnavi1 == 0)
        {
            statopartita = false;
            cout << "Il vincitore e' il giocatore numero 1!";
        }
        if (totnavi2 == 0)
        {
            statopartita = false;
            cout << "Il vincitore e' il giocatore numero 2!";
        }
    }
    return 0;
}