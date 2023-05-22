#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <fstream>
#include <direct.h>
#include <cstdlib>
#include <random>
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "Bellmanaforda.h"
#define rozmiarm 100
#define rozmiarl 10000

using namespace std;
const int INF = 1e9; // wartość reprezentująca brak krawędzi / nieskończoność
const string mala_liczba = "∞";
string daneWejsciowe;
Prim prim;
Kruskal kruskal;
Dijkstra dijkstra;
Bellmanaforda bellmanforda;
int macierz_s[rozmiarm][rozmiarm] = {0};
int macierz[rozmiarm][rozmiarm]= {0};
int lista[rozmiarl][3]= {0};
int lista_s[rozmiarl][3]= {0};
int liczba_krawedzi;
int liczba_krawedzi_s;
int liczba_wierzcholkow;
int cwierzcholek_poczotkowy, cwierzcholek_koncowy;


struct Krawedz {
    int zrodlo, cel, waga;
};
vector<Krawedz> krawedzie; // wektor krawędzi

void utworzmacierz(){
    for (int j = 0; liczba_wierzcholkow > j; j++) {
        for (int i = 0; liczba_wierzcholkow > i; i++) {
            macierz_s[j][i] = INT_MAX;
            macierz[j][i] = INT_MAX;
        }
    }
    for(int i = 0; liczba_krawedzi > i; i++){
        macierz_s[krawedzie[i].zrodlo][krawedzie[i].cel] = krawedzie[i].waga;
        macierz[krawedzie[i].cel][krawedzie[i].zrodlo] = krawedzie[i].waga;
        macierz[krawedzie[i].zrodlo][krawedzie[i].cel] = krawedzie[i].waga;
    }
}

void utworzlista(){
    int l_rozmiar = 0;
    for (int i = 0; i < liczba_wierzcholkow; i++) {
        for (int j = 0; j < liczba_wierzcholkow; j++) {
            if (macierz[i][j] != INT_MAX){
                lista[l_rozmiar][0] = i;
                lista[l_rozmiar][1] = j;
                lista[l_rozmiar][2] = macierz[i][j];
                l_rozmiar++;
            }
        }
    }
    liczba_krawedzi = l_rozmiar;

    l_rozmiar = 0;
    for (int i = 0; i < liczba_wierzcholkow; i++) {
        for (int j = 0; j < liczba_wierzcholkow; j++) {
            if (macierz_s[i][j] != INT_MAX){
                lista_s[l_rozmiar][0] = i;
                lista_s[l_rozmiar][1] = j;
                lista_s[l_rozmiar][2] = macierz_s[i][j];
                l_rozmiar++;
            }
        }
    }
    liczba_krawedzi_s = l_rozmiar;
}

void wczytaj_plik(){
    int wierzcholek_poczotkowy, wierzcholek_koncowy, waga_krawedzi;
    ifstream plikWejsciowy;
    cout << "Podaj nazwę pliku z końcówką .txt" << endl;
    cin >> daneWejsciowe;
    plikWejsciowy.open(daneWejsciowe);

    if (plikWejsciowy.is_open()) {
        cout << "Otwarto plik " << daneWejsciowe << endl;
    } else {
        cout << "Nie udało się otworzyć pliku wejściowego" << endl;
        return;
    }

    plikWejsciowy >> liczba_krawedzi >> liczba_wierzcholkow >> cwierzcholek_poczotkowy >> cwierzcholek_koncowy;

    while(plikWejsciowy.good()){
        plikWejsciowy >> wierzcholek_poczotkowy >> wierzcholek_koncowy >> waga_krawedzi;
        macierz[wierzcholek_poczotkowy][wierzcholek_koncowy] = macierz[wierzcholek_koncowy][wierzcholek_poczotkowy] = waga_krawedzi; /* dodanie krawędzi do macierzy sąsiedztwa */
        krawedzie.push_back({wierzcholek_poczotkowy, wierzcholek_koncowy, waga_krawedzi}); // dodanie krawędzi do wektora krawędzi
    }

    plikWejsciowy.close();
    plikWejsciowy.clear();
    utworzmacierz();
    utworzlista();
}

void wczytaj_plik_po(){
    int wierzcholek_poczotkowy, wierzcholek_koncowy, waga_krawedzi;
    ifstream plikWejsciowy;
    plikWejsciowy.open(daneWejsciowe);

    if (plikWejsciowy.is_open()) {
        cout << "Otwarto plik " << daneWejsciowe << endl;
    } else {
        cout << "Nie udało się otworzyć pliku wejściowego" << endl;
        return;
    }

    plikWejsciowy >> liczba_krawedzi >> liczba_wierzcholkow >> cwierzcholek_poczotkowy >> cwierzcholek_koncowy;

    while(plikWejsciowy.good()){
        plikWejsciowy >> wierzcholek_poczotkowy >> wierzcholek_koncowy >> waga_krawedzi;
        macierz[wierzcholek_poczotkowy][wierzcholek_koncowy] = macierz[wierzcholek_koncowy][wierzcholek_poczotkowy] = waga_krawedzi; /* dodanie krawędzi do macierzy sąsiedztwa */
        krawedzie.push_back({wierzcholek_poczotkowy, wierzcholek_koncowy, waga_krawedzi}); // dodanie krawędzi do wektora krawędzi
    }

    plikWejsciowy.close();
    plikWejsciowy.clear();
    utworzmacierz();
    utworzlista();
}

void wypiszmacierz(int opcja_poczatkowa) {
    int a;
        if (opcja_poczatkowa == 0) {
            for (int j = 0; liczba_wierzcholkow > j; j++) {
                for (int i = 0; liczba_wierzcholkow > i; i++) {
                    a = macierz_s[j][i];
                    if (a==INT_MAX)
                        cout << "[∞]";
                    else
                        cout << "[" << a << "]";
                }
                cout << endl;
            }
            return;
        } else if (opcja_poczatkowa == 1) {
            for (int j = 0; liczba_wierzcholkow > j; j++) {
                for (int i = 0; liczba_wierzcholkow > i; i++) {
                    a = macierz[j][i];
                    if (a==INT_MAX)
                        cout << "[∞]";
                    else
                        cout << "[" << a << "]";
                }
                cout << endl;
            }
            return;
        } else
            cout << "Błędna opcja" << endl << endl;
}

void wypiszlista(int opcja_poczatkowa) {
    int a;
    if (opcja_poczatkowa == 0) {
        for (int i = 0; liczba_krawedzi > i; i++) {
            cout << "[" << lista_s[i][0] << "->" << lista_s[i][1] << "]:" << lista_s[i][2] << endl;
        }
        return;
    } else if (opcja_poczatkowa == 1) {
        for (int i = 0; liczba_krawedzi * 2 > i; i++) {
            cout << "[" << lista[i][0] << "->" << lista[i][1] << "]:" << lista[i][2] << endl;
        }
        return;
    }
}

void testy() {
    fstream plikWyjsciowy;
    const char* tab1[9] = {"10","20","30","40","50","25%","50%","75%","99%"};
    string tab1s[9] = {"10","20","30","40","50","25%","50%","75%","99%"};
    const char* tab2[9] = {"pm", "pl", "km", "kl", "dm", "dl", "bm", "bl"};
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 100; i++) {
            _mkdir(tab1[j]);
            _chdir(tab1[j]);
            daneWejsciowe = to_string(i + 1) + ".txt";
            string nazwa = tab1s[j] + ".txt";
            wczytaj_plik_po();
            chdir("..");

            _mkdir(tab2[0]);
            _chdir(tab2[0]);
            prim.prim_mc(macierz, liczba_krawedzi, liczba_wierzcholkow, nazwa ,cwierzcholek_poczotkowy);
            chdir("..");

            _mkdir(tab2[1]);
            _chdir(tab2[1]);
            prim.prim_lc(lista, liczba_krawedzi, liczba_wierzcholkow, nazwa ,cwierzcholek_poczotkowy);
            chdir("..");

            _mkdir(tab2[2]);
            _chdir(tab2[2]);
            kruskal.kruskal_mc(macierz, liczba_krawedzi, liczba_wierzcholkow, nazwa);
            chdir("..");

            _mkdir(tab2[3]);
            _chdir(tab2[3]);
            kruskal.kruskal_lc(lista, liczba_krawedzi, liczba_wierzcholkow, nazwa);
            chdir("..");

            _mkdir(tab2[4]);
            _chdir(tab2[4]);
            dijkstra.dijkstra_mc(macierz_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, nazwa, liczba_wierzcholkow);
            chdir("..");

            _mkdir(tab2[5]);
            _chdir(tab2[5]);
            dijkstra.dijkstra_lc(lista_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_krawedzi_s, nazwa, liczba_wierzcholkow);
            chdir("..");

            _mkdir(tab2[6]);
            _chdir(tab2[6]);
            bellmanforda.bell_mc(macierz_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_krawedzi_s, nazwa, liczba_wierzcholkow);
            chdir("..");

            _mkdir(tab2[7]);
            _chdir(tab2[7]);
            bellmanforda.bell_lc(lista_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_krawedzi_s, nazwa, liczba_wierzcholkow);
            chdir("..");


        }
    }
};

int losuj (int min, int max){
    max = max-1;
    int val = 0;
    random_device rd; // non-deterministic generator
    mt19937 gen ( rd ( ) ) ; // random engine seeded with rd()
    uniform_int_distribution<> dist(min, max); // distribute results between
    val = dist(gen); // pass the generator to the distribution
    return val;
};

void generuj() {
    fstream plikWyjsciowy;
    const char* tab1[9] = {"10","20","30","40","50","25%","50%","75%","99%"};
    int tabwierz[9] = {10,20,30,40,50,20,20,20,20};
    int tabkra[9] = {50,200,450,800,1250,100,200,300,399};
    int ilosc_wierz;
    int ilosc_kra;
    int kraw [2000][2] = {0};
    int ob = 0;
    int pier;
    int ost;
    for (int j = 0; j < 9; j++) {
        _mkdir(tab1[j]);
        _chdir(tab1[j]);
        for (int i = 0; i < 100; i++) {
            string daneWyjsciowe = to_string(i+1) + ".txt";
            plikWyjsciowy.open(daneWyjsciowe, ios::out);

            ilosc_wierz = tabwierz[j];
            ilosc_kra = tabkra[j];

            pier = losuj(0,ilosc_wierz);
            int k = 0;
            int a;
            int b;
            int c;

            while (k != 1) {
                ost = losuj(0,ilosc_wierz);
                if (ost != pier){
                    k = 1;
                }
            }

            plikWyjsciowy << ilosc_kra << " " << ilosc_wierz << " " << pier << " " << ost << endl;
            plikWyjsciowy.flush();

            for (int l = 0; l < ilosc_kra;){
                k = 0;
                a = losuj(0,ilosc_wierz);
                while (k == 0) {
                    b = losuj(0,ilosc_wierz);
                    if (b != a){
                        k = 1;
                    }
                }
                c = losuj(0,INT_MAX);
                k = 0;
                for (int m = 0; m < l && k == 0; m++){
                    if (kraw[m][0] == a && kraw[m][0] == b){
                        if (kraw[m][1] == a && kraw[m][1] == b){
                            k = 1;
                        }
                    }
                }
                if (k == 0){
                    kraw[l][0] = a;
                    kraw[l][1] = b;
                    plikWyjsciowy << a << " " << " " << b << " " << c << endl;
                    l++;
                }
            }

            plikWyjsciowy.clear();
            plikWyjsciowy.close();
        }
        chdir("..");
    }
};

    int main() {
        daneWejsciowe = "tak.txt";
        wczytaj_plik_po();
        SetConsoleOutputCP(CP_UTF8); // Konsola ustawiona na utf-8 aby były Polskie litery
        cout << "Autor: Justyna Bułach" << endl;
        int opcja_poczatkowa;
        int opcja2=0;

        while (true) {
            cout << "Opcje:" << endl;
            cout << "1 - Wczytanie grafu z pliku" << endl;
            cout << "2 - Wyświetlenie grafu macierzowo i listowo" << endl;
            cout << "3 - Algorytm Kruskala" << endl;
            cout << "4 - Algorytm Prima" << endl;
            cout << "5 - Algorytm Dijkstry" <<endl;
            cout << "6 - Algorytm BellmanaForda" <<endl;
            cout << "7 - WYJŚCIE" << endl;
            cout << "8 - Testy" << endl;
            cout << "9 - Generruj pliki" << endl << endl;
            cout << "Wybór: ";
            cin >> opcja_poczatkowa;
            system("CLS");
            cout << endl;

            switch (opcja_poczatkowa) {
                default:
                    system("CLS");
                    cout << "Błędna opcja" << endl << endl;
                    break;
                case 1:
                        wczytaj_plik();
                    break;
                case 2:
                    cout << "Lista skierowana - 0"<< endl;
                    cout << "Lista nieskierowana - 1" << endl;
                    cout << "Wybór: ";
                    cin >> opcja2;
                        wypiszmacierz(opcja2);
                        wypiszlista(opcja2);
                    break;
                case 3:
                    cout << "Listowo:" << endl;
                    kruskal.kruskal_l(lista, liczba_krawedzi, liczba_wierzcholkow);
                    cout << endl << "Macierzowo:" << endl;
                    kruskal.kruskal_m(macierz, liczba_krawedzi, liczba_wierzcholkow);
                    cout << endl;
                    break;
                case 4:
                    cout << "Listowo:" << endl;
                    prim.prim_l(lista, liczba_krawedzi, liczba_wierzcholkow, cwierzcholek_poczotkowy);
                    cout << endl << "Macierzowo:" << endl;
                    prim.prim_m(macierz, liczba_krawedzi, liczba_wierzcholkow, cwierzcholek_poczotkowy);
                    cout << endl;
                    break;
                case 5:
                    cout << "Listowo:" << endl;
                    dijkstra.dijkstra_l(lista_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_krawedzi_s, liczba_wierzcholkow);
                    cout << "Macierzowo:" << endl;
                    dijkstra.dijkstra_m(macierz_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_wierzcholkow);
                    cout << endl;
                    break;
                case 6:
                    cout << "Listowo:" << endl;
                    bellmanforda.bell_l(lista_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_krawedzi_s, liczba_wierzcholkow);
                    cout << "Macierzowo:" << endl;
                    bellmanforda.bell_m(macierz_s, cwierzcholek_poczotkowy, cwierzcholek_koncowy, liczba_krawedzi_s, liczba_wierzcholkow);
                    cout << endl;
                    break;
                case 7:
                    return 0;
                case 8:
                    testy();
                    break;
                case 9:
                    generuj();
                    break;
            }
        }
    }
