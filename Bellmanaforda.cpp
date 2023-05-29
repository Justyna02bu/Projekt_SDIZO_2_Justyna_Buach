//
// Created by Justy on 13.05.2023.
//

#include "Bellmanaforda.h"
#include <iostream>
#include <queue>
#include <climits>
#include <fstream>
#include "Czasomierz.h"

using namespace std;
Bellmanaforda::Bellmanaforda() {}

void Bellmanaforda::bell_lc(int ** lista, int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, string nazwa, int wierz) {
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "BELL Lista czas-"+nazwa;
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

    // 0 - nie sprawdzamy, -1 - podłącozny, nie sprawdzony, -2 - podłacozny sprawdzony
    q[wierzcholek_poczatkowy] = 1;
    int k = 1;
    int il = 0;
    while (k != 0) {
        k = 0;
        for (int i = 0; i < wierz; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (lista[j][0] == i && q[lista[j][0]] == 1)
                    if (tab[lista[j][1]][0] > tab[lista[j][0]][0] + lista[j][2]) {
                        tab[lista[j][1]][0] = tab[lista[j][0]][0] + lista[j][2];
                        tab[lista[j][1]][1] = lista[j][0];
                        q[lista[j][1]] = 1;
                        k = 1;
                    }
            }
        }
        int a;
        for (int i = 0; i < wierz && k != 0; i++) {
            if (i != wierzcholek_poczatkowy && q[i] == 1) {
                a = i;
                il = 0;
                while (a != wierzcholek_poczatkowy && k != 0) {
                    if (il > wierz + 1) {
                        k = 0;
                    }
                    a = tab[a][1];
                    if (a == -1) {
                        k = 0;
                        break;
                    }
                    il++;
                }
            }
        }
        for (int i = 0; i < wierz; i++){
            q[i] = 0;
        }
        q[1] = 1;
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

void Bellmanaforda::bell_l(int ** lista, int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, int wierz) {
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

    // 0 - nie sprawdzamy, -1 - podłącozny, nie sprawdzony, -2 - podłacozny sprawdzony
    q[wierzcholek_poczatkowy] = 1;
    int k = 1;
    int il = 0;
    while (k != 0) {
        k = 0;
        for (int i = 0; i < wierz; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (lista[j][0] == i && q[lista[j][0]] == 1)
                    if (tab[lista[j][1]][0] > tab[lista[j][0]][0] + lista[j][2]) {
                        tab[lista[j][1]][0] = tab[lista[j][0]][0] + lista[j][2];
                        tab[lista[j][1]][1] = lista[j][0];
                        q[lista[j][1]] = 1;
                        k = 1;
                    }
            }
        }
        int a;
        for (int i = 0; i < wierz && k != 0; i++) {
            if (i != wierzcholek_poczatkowy && q[i] == 1) {
                a = i;
                il = 0;
                while (a != wierzcholek_poczatkowy && k != 0) {
                    if (il > wierz + 1) {
                        k = 0;
                    }
                    a = tab[a][1];
                    if (a == -1) {
                        k = 0;
                        break;
                    }
                    il++;
                }
            }
        }
        for (int i = 0; i < wierz; i++){
            q[i] = 0;
        }
        q[1] = 1;
    }

    int a = 0;
    k = 0;
    cout << "Start: " << wierzcholek_poczatkowy << endl;
    for (int i = 0; i < wierz; i++) {
        if (i != wierzcholek_poczatkowy) {
            cout << i << "|" ;
            a = i;
            il = 0;
            k = 0;
            while (a != wierzcholek_poczatkowy && k == 0) {
                if(tab[a][1] != -1) {
                    a = tab[a][1];
                    cout << "<-" << a;
                    if (il > wierz + 1) {
                        cout << " !wykryto pętlę! " << endl;
                        k = 1;
                    }
                    il++;
                } else{
                    break;
                }
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

void Bellmanaforda::bell_mc(int ** macierz, int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, string nazwa, int wierz) {
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "BELL Macierz czas-"+nazwa;
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
    l_rozmiar = 0;
    for (int i = 0; i < wierz; i++) {
        for (int j = 0; j < wierz; j++) {
            if (macierz[i][j] != INT_MAX){
                lista2[l_rozmiar][0] = i;
                lista2[l_rozmiar][1] = j;
                lista2[l_rozmiar][2] = macierz[i][j];
                l_rozmiar++;
            }
        }
    }

    for (int j = 0; wierz > j; j++) {
        tab[j][0] = INT_MAX; //d[u]
        tab[j][1] = -1; //p[u]
    }
    tab[wierzcholek_poczatkowy][0] = 0;

    // 0 - nie sprawdzamy, -1 - podłącozny, nie sprawdzony, -2 - podłacozny sprawdzony
    q[wierzcholek_poczatkowy] = 1;
    int k = 1;
    int il = 0;
    while (k != 0) {
        k = 0;
        for (int i = 0; i < wierz; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (lista2[j][0] == i && q[lista2[j][0]] == 1)
                    if (tab[lista2[j][1]][0] > tab[lista2[j][0]][0] + lista2[j][2]) {
                        tab[lista2[j][1]][0] = tab[lista2[j][0]][0] + lista2[j][2];
                        tab[lista2[j][1]][1] = lista2[j][0];
                        q[lista2[j][1]] = 1;
                        k = 1;
                    }
            }
        }
        int a;
        for (int i = 0; i < wierz && k != 0; i++) {
            if (i != wierzcholek_poczatkowy && q[i] == 1) {
                a = i;
                il = 0;
                while (a != wierzcholek_poczatkowy && k != 0) {
                    if (il > wierz + 1) {
                        k = 0;
                    }
                    a = tab[a][1];
                    if (a == -1) {
                        k = 0;
                        break;
                    }
                    il++;
                }
            }
        }
        for (int i = 0; i < wierz; i++){
            q[i] = 0;
        }
        q[1] = 1;
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

void Bellmanaforda::bell_m(int ** macierz, int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, int wierz) {
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

    l_rozmiar = 0;
    for (int i = 0; i < wierz; i++) {
        for (int j = 0; j < wierz; j++) {
            if (macierz[i][j] != INT_MAX){
                lista2[l_rozmiar][0] = i;
                lista2[l_rozmiar][1] = j;
                lista2[l_rozmiar][2] = macierz[i][j];
                l_rozmiar++;
            }
        }
    }

    for (int j = 0; wierz > j; j++) {
        tab[j][0] = INT_MAX; //d[u]
        tab[j][1] = -1; //p[u]
    }
    tab[wierzcholek_poczatkowy][0] = 0;


    // 0 - nie sprawdzamy, -1 - podłącozny, nie sprawdzony, -2 - podłacozny sprawdzony
    q[wierzcholek_poczatkowy] = 1;
    int k = 1;
    int il = 0;
    while (k != 0) {
        k = 0;
        for (int i = 0; i < wierz; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (lista2[j][0] == i && q[lista2[j][0]] == 1)
                    if (tab[lista2[j][1]][0] > tab[lista2[j][0]][0] + lista2[j][2]) {
                        tab[lista2[j][1]][0] = tab[lista2[j][0]][0] + lista2[j][2];
                        tab[lista2[j][1]][1] = lista2[j][0];
                        q[lista2[j][1]] = 1;
                        k = 1;
                    }
            }
        }
        int a;
        for (int i = 0; i < wierz && k != 0; i++) {
            if (i != wierzcholek_poczatkowy && q[i] == 1) {
                a = i;
                il = 0;
                while (a != wierzcholek_poczatkowy && k != 0) {
                    if (il > wierz + 1) {
                        k = 0;
                    }
                    a = tab[a][1];
                    if (a == -1) {
                        k = 0;
                        break;
                    }
                    il++;
                }
            }
        }
        for (int i = 0; i < wierz; i++){
            q[i] = 0;
        }
        q[1] = 1;
    }

    int a = 0;
    k = 0;
    cout << "Start: " << wierzcholek_poczatkowy << endl;
    for (int i = 0; i < wierz; i++) {
        if (i != wierzcholek_poczatkowy) {
            cout << i << "|" ;
            a = i;
            il = 0;
            k = 0;
            while (a != wierzcholek_poczatkowy && k == 0) {
                if(tab[a][1] != -1) {
                    a = tab[a][1];
                    cout << "<-" << a;
                    if (il > wierz + 1) {
                        cout << " !wykryto pętlę! " << endl;
                        k = 1;
                    }
                    il++;
                } else{
                    break;
                }
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

