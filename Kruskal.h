//
// Created by Justy on 13.05.2023.
//

#ifndef PROJEKT_SDIZO_2_JUSTYNA_BUACH_KRUSKAL_H
#define PROJEKT_SDIZO_2_JUSTYNA_BUACH_KRUSKAL_H
#include <iostream>

#endif //PROJEKT_SDIZO_2_JUSTYNA_BUACH_KRUSKAL_H
class Kruskal {
public:
    Kruskal();

    void kruskal_m(int ** macierz, int rozmiar, int wierz);

    void kruskal_mc(int ** macierz, int rozmiar, int wierz, std::string nazwa);

    void kruskal_l(int ** lista, int rozmiar, int wierz);

    void kruskal_lc(int ** lista, int rozmiar, int wierz, std::string nazwa);
};