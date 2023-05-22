//
// Created by Justy on 13.05.2023.
//

#include "Prim.h"
#include <iostream>
#include <fstream>
#include "Czasomierz.h"

using namespace std;

Prim::Prim() {}

void Prim::prim_mc(int macierz[100][100], int rozmiar, int wierz, string nazwa, int start){
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "PRIM macierz czas-"+nazwa;
    plikWyjsciowy.open(daneWyjsciowe, fstream::app);

    int lista2[10000][3] = {0};
    int l_rozmiar = 0;
    int t_rozmiar = 0;
    int waga = 0;
    int t[10000][3] = {0};
    int pentla[100] = {0};

    czas.Start();
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

    for (int i = 0; i < l_rozmiar; i++) {
        for (int j = 0; j < l_rozmiar-1; j++) {
            if (lista2[j][2] > lista2[j + 1][2]) {
                int a = lista2[j][0];
                int b = lista2[j][1];
                int c = lista2[j][2];
                lista2[j][0] = lista2[j + 1][0];
                lista2[j][1] = lista2[j + 1][1];
                lista2[j][2] = lista2[j + 1][2];
                lista2[j + 1][0] = a;
                lista2[j + 1][1] = b;
                lista2[j + 1][2] = c;
            }
        }
    }

    pentla[start] = 1;
    for(int i = 0; wierz-1 > i; i++){
        for (int j = 0; l_rozmiar > j; j++){
            if (pentla[lista2[j][0]] == 1 && pentla[lista2[j][1]] == 0){
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            }
        }
    }

    czas.Stop();
    plikWyjsciowy << czas.czas_do_pliku() << endl;
    plikWyjsciowy.clear();
    plikWyjsciowy.close();
}

void Prim::prim_m(int macierz[100][100], int rozmiar, int wierz, int start){
    int lista2[10000][3] = {0};
    int l_rozmiar = 0;
    int t_rozmiar = 0;
    int waga = 0;
    int t[10000][3] = {0};
    int pentla[100] = {0};

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

    for (int i = 0; i < l_rozmiar; i++) {
        for (int j = 0; j < l_rozmiar-1; j++) {
            if (lista2[j][2] > lista2[j + 1][2]) {
                int a = lista2[j][0];
                int b = lista2[j][1];
                int c = lista2[j][2];
                lista2[j][0] = lista2[j + 1][0];
                lista2[j][1] = lista2[j + 1][1];
                lista2[j][2] = lista2[j + 1][2];
                lista2[j + 1][0] = a;
                lista2[j + 1][1] = b;
                lista2[j + 1][2] = c;
            }
        }
    }

    pentla[start] = 1;
    for(int i = 0; wierz-1 > i; i++){
        for (int j = 0; l_rozmiar > j; j++){
            if (pentla[lista2[j][0]] == 1 && pentla[lista2[j][1]] == 0){
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            }
        }
    }
    for (int i = 0; i < t_rozmiar; i++)
        cout << "[" << t[i][0] << "->" << t[i][1] << "]" << t[i][2] << endl;
    cout << "   Suma wag: " << waga << endl;
    cout << "   Ilość krawędzi: " << t_rozmiar << endl;
}

void Prim::prim_lc(int lista[10000][3], int rozmiar, int wierz, string nazwa, int start){
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "PRIM Lista czas-"+nazwa;
    plikWyjsciowy.open(daneWyjsciowe, fstream::app);
    int lista2[10000][3] = {0};
    int t_rozmiar = 0;
    int waga = 0;
    int t[10000][3] = {0};
    int pentla[100] = {0};

    czas.Start();
    for (int j = 0; rozmiar >= j; j++) {
        for (int i = 0; 3 > i; i++) {
            lista2[j][i] = lista[j][i];
        }
    }

    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar-1; j++) {
            if (lista2[j][2] > lista2[j + 1][2]) {
                int a = lista2[j][0];
                int b = lista2[j][1];
                int c = lista2[j][2];
                lista2[j][0] = lista2[j + 1][0];
                lista2[j][1] = lista2[j + 1][1];
                lista2[j][2] = lista2[j + 1][2];
                lista2[j + 1][0] = a;
                lista2[j + 1][1] = b;
                lista2[j + 1][2] = c;
            }
        }
    }

    pentla[start] = 1;
    for(int i = 0; wierz-1 > i; i++){
        for (int j = 0; rozmiar > j; j++){
            if (pentla[lista2[j][0]] == 1 && pentla[lista2[j][1]] == 0){
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            }
        }
    }

    czas.Stop();
    plikWyjsciowy << czas.czas_do_pliku() << endl;
    plikWyjsciowy.clear();
    plikWyjsciowy.close();
}

void Prim::prim_l(int lista[10000][3], int rozmiar, int wierz, int start) {
    int lista2[10000][3] = {0};
    int t_rozmiar = 0;
    int waga = 0;
    int t[10000][3] = {0};
    int pentla[100] = {0};

    for (int j = 0; rozmiar >= j; j++) {
        for (int i = 0; 3 > i; i++) {
            lista2[j][i] = lista[j][i];
        }
    }

    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar-1; j++) {
            if (lista2[j][2] > lista2[j + 1][2]) {
                int a = lista2[j][0];
                int b = lista2[j][1];
                int c = lista2[j][2];
                lista2[j][0] = lista2[j + 1][0];
                lista2[j][1] = lista2[j + 1][1];
                lista2[j][2] = lista2[j + 1][2];
                lista2[j + 1][0] = a;
                lista2[j + 1][1] = b;
                lista2[j + 1][2] = c;
            }
        }
    }

    pentla[start] = 1;
    for(int i = 0; wierz-1 > i; i++){
        for (int j = 0; rozmiar > j; j++){
            if (pentla[lista2[j][0]] == 1 && pentla[lista2[j][1]] == 0){
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            }
        }
    }
    for (int i = 0; i < t_rozmiar; i++)
        cout << "[" << t[i][0] << "->" << t[i][1] << "]" << t[i][2] << endl;
    cout << "   Suma wag: " << waga << endl;
    cout << "   Ilość krawędzi: " << t_rozmiar << endl;
}
