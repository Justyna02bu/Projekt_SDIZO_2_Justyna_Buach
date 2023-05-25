//
// Created by Justy on 13.05.2023.
//

#ifndef PROJEKT_SDIZO_2_JUSTYNA_BUACH_BELLMANAFORDA_H
#define PROJEKT_SDIZO_2_JUSTYNA_BUACH_BELLMANAFORDA_H

#endif //PROJEKT_SDIZO_2_JUSTYNA_BUACH_BELLMANAFORDA_H
#include <iostream>
class Bellmanaforda {
public:
    Bellmanaforda();

    void bell_lc(int lista[10000][3], int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, std::string nazwa, int wierz);

    void bell_l(int lista[10000][3], int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, int wierz);

    void bell_mc(int ** macierz, int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, std::string nazwa, int wierz);

    void bell_m(int ** macierz, int wierzcholek_poczatkowy, int wierzcholek_koncowy, int rozmiar, int wierz);
};