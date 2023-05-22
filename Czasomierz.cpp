//
// Created by Justy on 13.05.2023.
//
#include "Czasomierz.h"
#include <chrono>

using namespace std::chrono;

void Czasomierz::Start() {
    start = high_resolution_clock::now();
}

void Czasomierz::Stop() {
    stop = high_resolution_clock::now();
}

string Czasomierz::czas_do_pliku() {
    long zmierzony_czas = duration_cast<nanoseconds>(Czasomierz::stop - Czasomierz::start).count();
    return to_string(zmierzony_czas);
}