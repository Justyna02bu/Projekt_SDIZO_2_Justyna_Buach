cmake_minimum_required(VERSION 3.24)
project(Projekt_SDIZO_2_Justyna_Buach)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
<<<<<<< HEAD

=======
link_directories()
>>>>>>> d9de3bf (dyynamiczne2)
add_executable(Projekt_SDIZO_2_Justyna_Buach main.cpp Kruskal.cpp Kruskal.h Dijkstra.cpp Dijkstra.h Prim.cpp Prim.h Czasomierz.cpp Czasomierz.h Bellmanaforda.cpp Bellmanaforda.h)
