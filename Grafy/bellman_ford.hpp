#pragma once

#include <chrono>
#include <string> 

#include "lista_graf.hpp"
#include "graf_macierzowy.hpp"


double bellmanFord(std::shared_ptr<GrafLista> t_graf, int t_startNode, bool t_wyswietl);

double bellmanFord(std::shared_ptr<MacierzowyGraf> t_graf, int t_startNode, bool t_wyswietl);