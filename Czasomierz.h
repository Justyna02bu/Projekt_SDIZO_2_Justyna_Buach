//
// Created by Justy on 13.05.2023.
//

#ifndef PROJEKT_SDIZO_2_JUSTYNA_BUACH_CZASOMIERZ_H
#define PROJEKT_SDIZO_2_JUSTYNA_BUACH_CZASOMIERZ_H

#endif //PROJEKT_SDIZO_2_JUSTYNA_BUACH_CZASOMIERZ_H
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Czasomierz {
public:
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;

    void Start();

    void Stop();

    string czas_do_pliku();
};
