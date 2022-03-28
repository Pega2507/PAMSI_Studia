//Algorytmy definicje
#include <iostream>
#include <chrono>
#include <fstream>
#include <list>
#include <algorithm>

template<typename T>
void introWrap(T *tab, T *tmp, int left, int right, int maxdepth);

template<typename T>
void quickWrap(T *tab, T *tmp, int left, int right, int maxdepth);

template<typename T>
void mergeWrap(T *tab, T *tmp, int left, int right, int maxdepth);
