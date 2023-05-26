//
// Created by Justy on 13.05.2023.
//

#include "Dijkstra.h"
#include <iostream>
#include <climits>
#include <fstream>
#include "Czasomierz.h"

using namespace std;

void Dijkstra::dijkstra_m(int ** macierz, int wierzcholek_poczatkowy, int wierz){
    int * q = new int [wierz];
    for (int i = 0; i < wierz; i++) {
        q[i] = 0;
    }

    int ** tab = new int * [wierz];
    for (int i = 0; i < wierz; i++) {
        tab[i] = new int [2];
    }

    int l_rozmiar = 0;
    for (int i = 0; i < wierz; i++) {
        for (int j = 0; j < wierz; j++) {
            if (macierz[i][j] != INT_MAX){
                l_rozmiar++;
            }
        }
    }

    int ** lista2 = new int * [l_rozmiar];
    for (int i = 0; i < l_rozmiar; i++) {
        lista2[i] = new int [3];
    }

    int l_rozmiar2 = 0;
    for (int i = 0; i < wierz; i++) {
        for (int j = 0; j < wierz; j++) {
            if (macierz[i][j] != INT_MAX){
                lista2[l_rozmiar2][0] = i;
                lista2[l_rozmiar2][1] = j;
                lista2[l_rozmiar2][2] = macierz[i][j];
                l_rozmiar2++;
            }
        }
    }

    for (int i = 0; i < l_rozmiar; i++){
        if (lista2[i][2] < 0){
            cout << "Błąd: znaleziono ujęmną krawęź" << endl;
            return;
        }
    }


    for (int j = 0; wierz > j; j++) {
        tab[j][0] = INT_MAX; //d[u]
        tab[j][1] = -1; //p[u]
    }
    tab[wierzcholek_poczatkowy][0] = 0;

    q[wierzcholek_poczatkowy] = 1;
    tab[wierzcholek_poczatkowy][0] = 0;
    int wierzob = wierzcholek_poczatkowy;
    for (int i = 0; i < wierz - 1; i++) {
        int min = INT_MAX;
        int minj = 0;
        for (int j = 0; j < l_rozmiar; j++) {
            if (lista2[j][0] == wierzob && q[lista2[j][1]] != 1)
                if (tab[lista2[j][1]][0] > tab[lista2[j][0]][0] + lista2[j][2]) {
                    tab[lista2[j][1]][0] = tab[lista2[j][0]][0] + lista2[j][2];
                    tab[lista2[j][1]][1] = lista2[j][0];
                }
            if (q[lista2[j][1]] != 1 && min > tab[lista2[j][1]][0]) {
                min = tab[lista2[j][1]][0];
                minj = lista2[j][1];
            }
        }
        if (min == -1){
            break;
        }
        q[minj] = 1;
        wierzob = minj;
    }

    int a = 0;
    cout << "Start: " << wierzcholek_poczatkowy << endl;
    for (int i = 0; i < wierz; i++) {
        if (i != wierzcholek_poczatkowy) {
            cout << i << "|" ;
            a = i;
            while (a != wierzcholek_poczatkowy) {
                a = tab[a][1];
                if (a == -1){
                    break;
                }
                cout << "<-" << a ;
            }
            if (tab[i][0] == INT_MAX){
                cout << "| waga: brak trasy"<< endl;
            } else {
                cout << "| waga: "<< tab[i][0] << endl;
            }
        }
    }
    cout << endl;

    delete[] q;

    for (int i = 0; i < l_rozmiar; i++) {
        delete[] lista2[i];
    }
    delete[] lista2;

    for (int i = 0; i < wierz; i++) {
        delete[] tab[i];
    }
    delete[] tab;
}

void Dijkstra::dijkstra_mc(int ** macierz, int wierzcholek_poczatkowy, string nazwa, int wierz){
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "DIJKSTRA Macierz czas-"+nazwa;
    plikWyjsciowy.open(daneWyjsciowe, fstream::app);

    int * q = new int [wierz];
    for (int i = 0; i < wierz; i++) {
        q[i] = 0;
    }

    int ** tab = new int * [wierz];
    for (int i = 0; i < wierz; i++) {
        tab[i] = new int [2];
    }

    int l_rozmiar = 0;
    for (int i = 0; i < wierz; i++) {
        for (int j = 0; j < wierz; j++) {
            if (macierz[i][j] != INT_MAX){
                l_rozmiar++;
            }
        }
    }

    int ** lista2 = new int * [l_rozmiar];
    for (int i = 0; i < l_rozmiar; i++) {
        lista2[i] = new int [3];
    }

    czas.Start();
    int l_rozmiar2 = 0;
    for (int i = 0; i < wierz; i++) {
        for (int j = 0; j < wierz; j++) {
            if (macierz[i][j] != INT_MAX){
                lista2[l_rozmiar2][0] = i;
                lista2[l_rozmiar2][1] = j;
                lista2[l_rozmiar2][2] = macierz[i][j];
                l_rozmiar2++;
            }
        }
    }

    for (int i = 0; i < l_rozmiar; i++){
        if (lista2[i][2] < 0){
            czas.Stop();
            plikWyjsciowy << czas.czas_do_pliku() << endl;
            plikWyjsciowy.clear();
            plikWyjsciowy.close();
            return;
        }
    }

    for (int j = 0; wierz > j; j++) {
        tab[j][0] = INT_MAX; //d[u]
        tab[j][1] = -1; //p[u]
    }
    q[wierzcholek_poczatkowy] = 1;
    tab[wierzcholek_poczatkowy][0] = 0;
    int wierzob = wierzcholek_poczatkowy;
    for (int i = 0; i < wierz - 1; i++) {
        int min = INT_MAX;
        int minj = 0;
        for (int j = 0; j < l_rozmiar; j++) {
            if (lista2[j][0] == wierzob && q[lista2[j][1]] != 1)
                if (tab[lista2[j][1]][0] > tab[lista2[j][0]][0] + lista2[j][2]) {
                    tab[lista2[j][1]][0] = tab[lista2[j][0]][0] + lista2[j][2];
                    tab[lista2[j][1]][1] = lista2[j][0];
                }
            if (q[lista2[j][1]] != 1 && min > tab[lista2[j][1]][0]) {
                min = tab[lista2[j][1]][0];
                minj = lista2[j][1];
            }
        }
        if (min == -1){
            break;
        }
        q[minj] = 1;
        wierzob = minj;
    }
    czas.Stop();
    plikWyjsciowy << czas.czas_do_pliku() << endl;
    plikWyjsciowy.clear();
    plikWyjsciowy.close();

    delete[] q;

    for (int i = 0; i < l_rozmiar; i++) {
        delete[] lista2[i];
    }
    delete[] lista2;

    for (int i = 0; i < wierz; i++) {
        delete[] tab[i];
    }
    delete[] tab;
}

void Dijkstra::dijkstra_l(int ** lista, int wierzcholek_poczatkowy, int rozmiar, int wierz) {
    int ** tab = new int * [wierz];
    for (int i = 0; i < wierz; i++) {
        tab[i] = new int [2];
    }

    int * q = new int [wierz];
    for (int i = 0; i < wierz; i++) {
        q[i] = 0;
    }

    for (int j = 0; wierz > j; j++) {
        tab[j][0] = INT_MAX; //d[u]
        tab[j][1] = -1; //p[u]
    }
    tab[wierzcholek_poczatkowy][0] = 0;

    for (int i = 0; i < rozmiar; i++){
        if (lista[i][2] < 0){
            cout << "Błąd: znaleziono ujęmną krawęź" << endl;
            return;
        }
    }

    q[wierzcholek_poczatkowy] = 1;
    tab[wierzcholek_poczatkowy][0] = 0;
    int wierzob = wierzcholek_poczatkowy;
    for (int i = 0; i < wierz - 1; i++) {
        int min = INT_MAX;
        int minj = 0;
        for (int j = 0; j < rozmiar; j++) {
            if (lista[j][0] == wierzob && q[lista[j][1]] != 1)
                if (tab[lista[j][1]][0] > tab[lista[j][0]][0] + lista[j][2]) {
                    tab[lista[j][1]][0] = tab[lista[j][0]][0] + lista[j][2];
                    tab[lista[j][1]][1] = lista[j][0];
                }
            if (q[lista[j][1]] != 1 && min > tab[lista[j][1]][0]) {
                    min = tab[lista[j][1]][0];
                    minj = lista[j][1];
            }
        }
        if (min == -1){
            break;
        }
        q[minj] = 1;
        wierzob = minj;
    }

    int a = 0;
    cout << "Start: " << wierzcholek_poczatkowy << endl;
    for (int i = 0; i < wierz; i++) {
        if (i != wierzcholek_poczatkowy) {
            cout << i << "|" ;
            a = i;
            while (a != wierzcholek_poczatkowy) {
                a = tab[a][1];
                if (a == -1){
                    break;
                }
                cout << "<-" << a ;
            }
            if (tab[i][0] == INT_MAX){
                cout << "| waga: brak trasy"<< endl;
            } else {
                cout << "| waga: "<< tab[i][0] << endl;
            }
        }
    }
    cout << endl;

    delete[] q;

    for (int i = 0; i < wierz; i++) {
        delete[] tab[i];
    }
    delete[] tab;
}

void Dijkstra::dijkstra_lc(int ** lista, int wierzcholek_poczatkowy, int rozmiar, string nazwa, int wierz) {
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "DIJKSTRA Lista czas-"+nazwa;
    plikWyjsciowy.open(daneWyjsciowe, fstream::app);

    int ** tab = new int * [wierz];
    for (int i = 0; i < wierz; i++) {
        tab[i] = new int [2];
    }

    int * q = new int [wierz];
    for (int i = 0; i < wierz; i++) {
        q[i] = 0;
    }

    czas.Start();
    for (int j = 0; wierz > j; j++) {
        tab[j][0] = INT_MAX; //d[u]
        tab[j][1] = -1; //p[u]
    }
    tab[wierzcholek_poczatkowy][0] = 0;

    for (int i = 0; i < rozmiar; i++){
        if (lista[i][2] < 0){
            czas.Stop();
            plikWyjsciowy << czas.czas_do_pliku() << endl;
            plikWyjsciowy.clear();
            plikWyjsciowy.close();
            return;
        }
    }

    // 0 - nie sprawdzamy, -1 - podłącozny, nie sprawdzony, -2 - podłacozny sprawdzony
    q[wierzcholek_poczatkowy] = 1;
    tab[wierzcholek_poczatkowy][0] = 0;
    int wierzob = wierzcholek_poczatkowy;
    for (int i = 0; i < wierz - 1; i++) {
        int min = INT_MAX;
        int minj = 0;
        for (int j = 0; j < rozmiar; j++) {
            if (lista[j][0] == wierzob && q[lista[j][1]] != 1)
                if (tab[lista[j][1]][0] > tab[lista[j][0]][0] + lista[j][2]) {
                    tab[lista[j][1]][0] = tab[lista[j][0]][0] + lista[j][2];
                    tab[lista[j][1]][1] = lista[j][0];
                }
            if (q[lista[j][1]] != 1 && min > tab[lista[j][1]][0]) {
                min = tab[lista[j][1]][0];
                minj = lista[j][1];
            }
        }
        if (min == -1){
            break;
        }
        q[minj] = 1;
        wierzob = minj;
    }

    czas.Stop();
    plikWyjsciowy << czas.czas_do_pliku() << endl;
    plikWyjsciowy.clear();
    plikWyjsciowy.close();

    delete[] q;

    for (int i = 0; i < wierz; i++) {
        delete[] tab[i];
    }
    delete[] tab;
}

