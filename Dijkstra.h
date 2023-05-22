//
// Created by Justy on 13.05.2023.
//

#ifndef PROJEKT_SDIZO_2_JUSTYNA_BUACH_DIJKSTRA_H
#define PROJEKT_SDIZO_2_JUSTYNA_BUACH_DIJKSTRA_H

#endif //PROJEKT_SDIZO_2_JUSTYNA_BUACH_DIJKSTRA_H
#include <string>
using namespace std;
class Dijkstra {
public:

    void dijkstra_lc(int lista[10000][3], int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, string nazwa, int wierz);

    void dijkstra_l(int lista[10000][3], int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, int wierz);

    void dijkstra_mc(int macierz[100][100], int wierzcholek_poczatkowy, int wierzcholek_koncowy, string nazwa, int wierz);

    void dijkstra_m(int macierz[100][100], int wierzcholek_poczatkowy, int wierzcholek_koncowy, int wierz);
};