//
// Created by Justy on 13.05.2023.
//

#include "Kruskal.h"
#include <iostream>
#include <fstream>
#include "Czasomierz.h"

using namespace std;

Kruskal::Kruskal() {}

void Kruskal::kruskal_mc(int ** macierz, int rozmiar, int wierz, string nazwa){
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "KRUSKAL macierz czas-"+nazwa;
    plikWyjsciowy.open(daneWyjsciowe, fstream::app);

    int t_rozmiar = 0;
    int waga = 0;
    int l_rozmiar = 0;
    int ** lista2 = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        lista2[i] = new int [3];
    }
    int * pentla = new int [wierz];
    int ** t = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        t[i] = new int [3];
    }

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
    for (int i = 0; i < wierz; i++)
        pentla[i] = 0;
    pentla[lista2[0][0]] = 1;
    for (int i = 0; wierz-1 > i; i++) {
        for (int j = 0; rozmiar > j; j++) {
            if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 1) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 1){
                int wsk = 0;
                int wsk3 = 0;
                int * pentlawe = new int [wierz];
                for (int l = 0; l < wierz; l++)
                    pentlawe[l] = 0;
                pentlawe[lista2[j][0]] = 1;
                while (wsk == 0 && wsk3 == 0){
                    wsk3 = 1;
                    for (int l = 0; t_rozmiar > l; l++) {
                        if(pentlawe[t[l][0]] == 1 && pentlawe[t[l][1]] == 0){
                            wsk3 = 0;
                            if(t[l][1] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][1]] = 1;
                            }
                        }
                        if(pentlawe[t[l][0]] == 0 && pentlawe[t[l][1]] == 1){
                            wsk3 = 0;
                            if(t[l][0] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][0]] = 1;
                            }
                        }
                    }
                }
                if (wsk == 1)
                {
                    delete[] pentlawe;
                } else {
                    t[t_rozmiar][0] = lista2[j][0];
                    t[t_rozmiar][1] = lista2[j][1];
                    t[t_rozmiar][2] = lista2[j][2];
                    waga = waga + lista2[j][2];
                    t_rozmiar++;
                    pentla[lista2[j][1]] = 1;
                    pentla[lista2[j][0]] = 1;
                    delete[] pentlawe;
                    break;
                }
            }
        }
    }
    czas.Stop();
    plikWyjsciowy << czas.czas_do_pliku() << endl;
    plikWyjsciowy.clear();
    plikWyjsciowy.close();

    delete[] pentla;

    for (int i = 0; i < rozmiar; i++) {
        delete[] lista2[i];
    }
    delete[] lista2;

    for (int i = 0; i < rozmiar; i++) {
        delete[] t[i];
    }
    delete[] t;
}

void Kruskal::kruskal_m(int ** macierz, int rozmiar, int wierz){
    int t_rozmiar = 0;
    int waga = 0;
    int l_rozmiar = 0;
    int ** lista2 = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        lista2[i] = new int [3];
    }
    int * pentla = new int [wierz];
    int ** t = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        t[i] = new int [3];
    }

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
    for (int i = 0; i < wierz; i++)
        pentla[i] = 0;
    pentla[lista2[0][0]] = 1;
    for (int i = 0; wierz-1 > i; i++) {
        for (int j = 0; rozmiar > j; j++) {
            if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 1) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 1){
                int wsk = 0;
                int wsk3 = 0;
                int * pentlawe = new int [wierz];
                for (int l = 0; l < wierz; l++)
                    pentlawe[l] = 0;
                pentlawe[lista2[j][0]] = 1;
                while (wsk == 0 && wsk3 == 0){
                    wsk3 = 1;
                    for (int l = 0; t_rozmiar > l; l++) {
                        if(pentlawe[t[l][0]] == 1 && pentlawe[t[l][1]] == 0){
                            wsk3 = 0;
                            if(t[l][1] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][1]] = 1;
                            }
                        }
                        if(pentlawe[t[l][0]] == 0 && pentlawe[t[l][1]] == 1){
                            wsk3 = 0;
                            if(t[l][0] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][0]] = 1;
                            }
                        }
                    }
                }
                if (wsk == 1)
                {
                    delete[] pentlawe;
                } else {
                    t[t_rozmiar][0] = lista2[j][0];
                    t[t_rozmiar][1] = lista2[j][1];
                    t[t_rozmiar][2] = lista2[j][2];
                    waga = waga + lista2[j][2];
                    t_rozmiar++;
                    pentla[lista2[j][1]] = 1;
                    pentla[lista2[j][0]] = 1;
                    delete[] pentlawe;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < t_rozmiar; i++)
        cout << "[" << t[i][0] << "->" << t[i][1] << "]" << t[i][2] << endl;
    cout << "   Suma wag: " << waga << endl;
    cout << "   Ilość krawędzi: " << t_rozmiar << endl;

    delete[] pentla;

    for (int i = 0; i < rozmiar; i++) {
        delete[] lista2[i];
    }
    delete[] lista2;

    for (int i = 0; i < rozmiar; i++) {
        delete[] t[i];
    }
    delete[] t;
}

void Kruskal::kruskal_lc(int ** lista, int rozmiar, int wierz, string nazwa){
    Czasomierz czas;
    ofstream plikWyjsciowy;
    string daneWyjsciowe = "KRUSKAL Lista czas-"+nazwa;
    plikWyjsciowy.open(daneWyjsciowe, fstream::app);
    int t_rozmiar = 0;
    int waga = 0;
    int ** lista2 = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        lista2[i] = new int [3];
    }
    int * pentla = new int [wierz];
    int ** t = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        t[i] = new int [3];
    }

    czas.Start();
    for (int j = 0; rozmiar > j; j++) {
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

    for (int i = 0; i < wierz; i++)
        pentla[i] = 0;
    pentla[lista2[0][0]] = 1;
    for (int i = 0; wierz-1 > i; i++) {
        for (int j = 0; rozmiar > j; j++) {
            if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 1) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 1){
                int wsk = 0;
                int wsk3 = 0;
                int * pentlawe = new int [wierz];
                for (int l = 0; l < wierz; l++)
                    pentlawe[l] = 0;
                pentlawe[lista2[j][0]] = 1;
                while (wsk == 0 && wsk3 == 0){
                    wsk3 = 1;
                    for (int l = 0; t_rozmiar > l; l++) {
                        if(pentlawe[t[l][0]] == 1 && pentlawe[t[l][1]] == 0){
                            wsk3 = 0;
                            if(t[l][1] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][1]] = 1;
                            }
                        }
                        if(pentlawe[t[l][0]] == 0 && pentlawe[t[l][1]] == 1){
                            wsk3 = 0;
                            if(t[l][0] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][0]] = 1;
                            }
                        }
                    }
                }
                if (wsk == 1)
                {
                    delete[] pentlawe;
                } else {
                    t[t_rozmiar][0] = lista2[j][0];
                    t[t_rozmiar][1] = lista2[j][1];
                    t[t_rozmiar][2] = lista2[j][2];
                    waga = waga + lista2[j][2];
                    t_rozmiar++;
                    pentla[lista2[j][1]] = 1;
                    pentla[lista2[j][0]] = 1;
                    delete[] pentlawe;
                    break;
                }
            }
        }
    }
    czas.Stop();
    plikWyjsciowy << czas.czas_do_pliku() << endl;
    plikWyjsciowy.clear();
    plikWyjsciowy.close();

    delete[] pentla;

    for (int i = 0; i < rozmiar; i++) {
        delete[] lista2[i];
    }
    delete[] lista2;

    for (int i = 0; i < rozmiar; i++) {
        delete[] t[i];
    }
    delete[] t;
}

void Kruskal::kruskal_l(int ** lista, int rozmiar, int wierz) {
    int t_rozmiar = 0;
    int waga = 0;
    int ** lista2 = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        lista2[i] = new int [3];
    }
    int * pentla = new int [wierz];
    int ** t = new int * [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        t[i] = new int [3];
    }

    for (int j = 0; rozmiar > j; j++) {
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
    for (int i = 0; i < wierz; i++)
        pentla[i] = 0;
    pentla[lista2[0][0]] = 1;
    for (int i = 0; wierz-1 > i; i++) {
        for (int j = 0; rozmiar > j; j++) {
            if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 0 && pentla[lista2[j][0]] == 1) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 0) {
                t[t_rozmiar][0] = lista2[j][0];
                t[t_rozmiar][1] = lista2[j][1];
                t[t_rozmiar][2] = lista2[j][2];
                waga = waga + lista2[j][2];
                t_rozmiar++;
                pentla[lista2[j][1]] = 1;
                pentla[lista2[j][0]] = 1;
                break;
            } else if (pentla[lista2[j][1]] == 1 && pentla[lista2[j][0]] == 1){
                int wsk = 0;
                int wsk3 = 0;
                int * pentlawe = new int [wierz];
                for (int l = 0; l < wierz; l++)
                    pentlawe[l] = 0;
                pentlawe[lista2[j][0]] = 1;
                while (wsk == 0 && wsk3 == 0){
                    wsk3 = 1;
                    for (int l = 0; t_rozmiar > l; l++) {
                        if(pentlawe[t[l][0]] == 1 && pentlawe[t[l][1]] == 0){
                            wsk3 = 0;
                            if(t[l][1] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][1]] = 1;
                            }
                        }
                        if(pentlawe[t[l][0]] == 0 && pentlawe[t[l][1]] == 1){
                            wsk3 = 0;
                            if(t[l][0] == lista2[j][1]){
                                wsk = 1;
                            }
                            else{
                                pentlawe[t[l][0]] = 1;
                            }
                        }
                    }
                }
                if (wsk == 1)
                {
                    delete[] pentlawe;
                } else {
                    t[t_rozmiar][0] = lista2[j][0];
                    t[t_rozmiar][1] = lista2[j][1];
                    t[t_rozmiar][2] = lista2[j][2];
                    waga = waga + lista2[j][2];
                    t_rozmiar++;
                    pentla[lista2[j][1]] = 1;
                    pentla[lista2[j][0]] = 1;
                    delete[] pentlawe;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < t_rozmiar; i++)
        cout << "[" << t[i][0] << "->" << t[i][1] << "]" << t[i][2] << endl;
    cout << "   Suma wag: " << waga << endl;
    cout << "   Ilość krawędzi: " << t_rozmiar << endl;

    delete[] pentla;

    for (int i = 0; i < rozmiar; i++) {
        delete[] lista2[i];
    }
    delete[] lista2;

    for (int i = 0; i < rozmiar; i++) {
        delete[] t[i];
    }
    delete[] t;
}