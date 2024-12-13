#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype> // Per tolower

using namespace std;

bool Maiusc(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) {
        return false; // Lunghezze diverse
    }
    return equal(str1.begin(), str1.end(), str2.begin(),
                 [](char a, char b) {
                     return tolower(a) == tolower(b);
                 });
}

struct navi {
    bool nave5[5], nave4[4], nave3_1[3], nave3_2[3], nave2[2];
};

int main() {
    int giocatore1[10][10], giocatore2[10][10], i, j, r, c,z,aa,bb,l = 6;
    string verso, versor;
    bool finito = false;

    cout << "REGOLE\n1-Le navi sono una per tipo, da 5 spazi a 1.\n"
            "2-Per le coordinate inserire prima la riga e poi la colonna.\n"
            "3-Le navi non si possono sovrapporre.\n"
            "4-Le righe e le colonne partono dall'angolo in alto a sinistra.\n"
            "5-Le mappe hanno larghezza e lunghezza pari a 10 spazi.\n";

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            giocatore1[i][j] = 0 ;
            giocatore2[i][j] = 0 ;
        }
    }

    cout << "Giocatore 1, posiziona le tue navi: " << endl;

    while (finito == false) {
        for (i = 0, z = 0; i < 5; i++) {
            cout << "Da dove vuoi far partire la nave numero " << i + 1 << "? (lunghezza " << 5 - i << ")";
            cout << "Riga: ";
            cin >> r;
            r -= 1;
            cout << "Colonna: ";
            cin >> c;
            c -= 1;
            l--;
            cout << "Verso che parte? (sopra, destra, basso, sinistra): ";
            cin >> verso;

            if (r < 0 || r >= 10 || c < 0 || c >= 10) {
                cout << "Errore: Coordinate fuori dalla mappa!" << endl;
                i--; 
                continue;
            }

            if (giocatore1[r][c] != 0) {
                cout << "Errore: Posizione già occupata!" << endl;
                i--;
                continue;
            }

            giocatore1[r][c] = 1;
            versor = "sopra";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    r -= 1;
                    if (r < 0 || giocatore1[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore1[r][c] = 1;
                }
            }
            versor = "bassa";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    r += 1;
                    if (r < 0 || giocatore1[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore1[r][c] = 1;
                }
            }
            versor = "destra";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    c++;
                    if (r < 0 || giocatore1[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore1[r][c] = 1;
                }
            }
            versor = "sinistra";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    c--;
                    if (r < 0 || giocatore1[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore1[r][c] = 1;
                }
            }
            for(aa = 0;aa < 10;aa++)
            {
                for(bb = 0; bb < 10;bb++)
                {
                    cout << giocatore1[aa][bb];
                    cout << " ";
                }
            cout << "\n";
            }

            if (z == 1) {
                i--; // Ripeti il posizionamento
                continue;
            }
        }
        finito = true; // Uscita dal ciclo
    }
    //stampo mappa giocatore 1 

    cout <<  "Premere qualsiasi tasto per continuare e passare il turno al giocatore 2";
    cin >> i;
    cout << "\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Giocatore 2, posiziona le tue navi: " << endl;

    while (finito == false) {
        for (i = 0, z = 0; i < 5; i++) {
            cout << "Da dove vuoi far partire la nave numero " << i + 1 << "? (lunghezza " << 5 - i << ")";
            cout << "Riga: ";
            cin >> r;
            r -= 1;
            cout << "Colonna: ";
            cin >> c;
            c -= 1;
            l--;
            cout << "Verso che parte? (sopra, destra, basso, sinistra): ";
            cin >> verso;

            if (r < 0 || r >= 10 || c < 0 || c >= 10) {
                cout << "Errore: Coordinate fuori dalla mappa!" << endl;
                i--; 
                continue;
            }

            if (giocatore2[r][c] != 0) {
                cout << "Errore: Posizione già occupata!" << endl;
                i--;
                continue;
            }

            giocatore2[r][c] = 1;
            versor = "sopra";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    r -= 1;
                    if (r < 0 || giocatore2[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore2[r][c] = 1;
                }
            }
            versor = "bassa";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    r += 1;
                    if (r < 0 || giocatore2[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore2[r][c] = 1;
                }
            }
            versor = "destra";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    c++;
                    if (r < 0 || giocatore2[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore2[r][c] = 1;
                }
            }
            versor = "sinistra";
            if (Maiusc(verso, versor)) {
                for (j = 0; j < l; j++) {
                    c--;
                    if (r < 0 || giocatore2[r][c] != 0) {
                        cout << "Errore: Posizione non valida!" << endl;
                        z = 1;
                        break;
                    }
                    giocatore2[r][c] = 1;
                }
            }
            for(aa = 0;aa < 10;aa++)
            {
                for(bb = 0; bb < 10;bb++)
                {
                    cout << giocatore2[aa][bb];
                    cout << " ";
                }
            cout << "\n";
            }

            if (z == 1) {
                i--; // Ripeti il posizionamento
                continue;
            }
        }
        finito = true; // Uscita dal ciclo
    }

}
