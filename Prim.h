//
// Created by Justy on 13.05.2023.
//

#ifndef PROJEKT_SDIZO_2_JUSTYNA_BUACH_PRIM_H
#define PROJEKT_SDIZO_2_JUSTYNA_BUACH_PRIM_H
#include <iostream>

#endif //PROJEKT_SDIZO_2_JUSTYNA_BUACH_PRIM_H
class Prim {
public:
    Prim();

    void prim_m(int ** macierz, int rozmiar, int wierz, int start);

    void prim_mc(int ** macierz, int rozmiar, int wierz, std::string nazwa, int start);

    void prim_l(int lista[10000][3], int rozmiar, int wierz, int start);

    void prim_lc(int lista[10000][3], int rozmiar, int wierz, std::string nazwa, int start);
};