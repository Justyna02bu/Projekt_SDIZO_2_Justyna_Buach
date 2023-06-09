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

    void dijkstra_lc(int ** lista, int wierzcholek_poczatkowy, int rozmiar, string nazwa, int wierz);

    void dijkstra_l(int ** lista, int wierzcholek_poczatkowy, int rozmiar, int wierz);

    void dijkstra_mc(int ** macierz, int wierzcholek_poczatkowy, string nazwa, int wierz);

    void dijkstra_m(int ** macierz, int wierzcholek_poczatkowy, int wierz);
};