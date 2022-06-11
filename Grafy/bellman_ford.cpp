#include "bellman_ford.hpp"

static int  s_infinity = 10000000; 
static int  s_neg_infinity = -10000000;	

//wyswietla na konsoli i tworzy plik Output.txt
void finalSolution(std::string t_tabSciezek[], int t_dist[], int t_n, int t_startNode) {

	std::ofstream file("Output.txt");
	
	std::cout << std::string(20, '-') << "\n   Rozwiazanie\n\n";
	std::cout << "Wezel poczatkowy -> " << t_startNode << "\n\n";

	file << std::string(20, '-') << "\n   Rozwiazanie\n\n";
	file << "Wezel poczatkowy -> " << t_startNode << "\n\n";

	for (int i = 0; i < t_n; ++i) {
		 
		if (t_dist[i] == s_neg_infinity) {
			std::cout << i << "->" << "-inf\n";
			file << i << "->" << "-inf\n";
			continue; 
		}
		else if (t_dist[i] == s_infinity) {
			std::cout << i << "->" << "inf\n";
			file << i << "->" << "inf\n";
			continue;
		}
		else {
			std::cout << i << "->" << t_dist[i];
			file << i << "->" << t_dist[i];
		}

		//liczba wezlow
		if (i < 10) {
			std::cout << "   ";
			file << "   ";
		}
		else if (i < 100) {
			std::cout << "  ";
			file << "  ";
		}
		else {
			std::cout << " ";
			file << " ";
		}
		
		//najkrotszy dystans
		if ((t_dist[i] >= 100 && t_dist[i] < 1000) || (-100 > t_dist[i]  && t_dist[i] <= -10)) {
		
			std::cout << " Najkrotsza sciezka: " << t_tabSciezek[i] << i;
			file << " Najkrotsza sciezka: " << t_tabSciezek[i] << i;
		}
		else if (0 <= t_dist[i] && t_dist[i] < 10) {

			std::cout << "   Najkrotsza sciezka: " << t_tabSciezek[i] << i;
			file << "   Najkrotsza sciezka: " << t_tabSciezek[i] << i;
		}
		else if ((t_dist[i] >= 10 && t_dist[i] < 100) || (-10 < t_dist[i] && t_dist[i] < 0)) {

			std::cout << "  Najkrotsza sciezka: " << t_tabSciezek[i] << i;
			file << "  Najkrotsza sciezka: " << t_tabSciezek[i] << i;
		}
		else {
			
			std::cout << "Najkrotsza sciezka: " << t_tabSciezek[i] << i;
			file << "Najkrotsza sciezka: " << t_tabSciezek[i] << i;
		}
		std::cout << std::endl;
		file << std::endl;
	}
	std::cout << std::endl;
	file.close();
}


//algorytm dla listy
double bellmanFord(std::shared_ptr<GrafLista> t_graf, int t_startNode, bool t_wyswRozw) {

	std::string* sciezki = new std::string[t_graf->getW()]; //przechowuje sciezki

	auto t_start = std::chrono::high_resolution_clock::now(); //zaczyna odliczanie
	int* najkrotszeSciezki = new int[t_graf->getW()]; //przechowuje najkrotsze sciezki
	
	for (int i = 0; i < t_graf->getW(); ++i) {

		najkrotszeSciezki[i] = s_infinity;
	}

	najkrotszeSciezki[t_startNode] = 0;

	for (int i = 1; i < t_graf->getW(); ++i) {
		for (int j = 0; j < t_graf->getB(); ++j) { //dla brzegow

			int u = t_graf->getStruct()[j].zrodlo;
			int v = t_graf->getStruct()[j].destynacja;
			int waga = t_graf->getStruct()[j].waga;

			if (najkrotszeSciezki[u] + waga < najkrotszeSciezki[v]) { //sprawdzenie czy znaleziono krotsza sciezke
				najkrotszeSciezki[v] = najkrotszeSciezki[u] + waga;
					
				if (t_wyswRozw) {
						
					sciezki[v].clear();
					sciezki[v].append(sciezki[u] + std::to_string(u) + "->");
				}
			}
		}
	}

	//sprawdzenie czy wystepua negatywne cykle
	for (int i = 1; i < t_graf->getW(); ++i) {
		for (int j = 0; j < t_graf->getB(); ++j) {
			
			int u = t_graf->getStruct()[j].zrodlo;
			int v = t_graf->getStruct()[j].destynacja;
			int waga = t_graf->getStruct()[j].waga;
			if (najkrotszeSciezki[u] + waga < najkrotszeSciezki[v]) {

				if (najkrotszeSciezki[u] > s_infinity/2) najkrotszeSciezki[u] = s_infinity;  
				else najkrotszeSciezki[v] = s_neg_infinity;
			}
			else if (najkrotszeSciezki[u] > s_infinity/2) najkrotszeSciezki[u] = s_infinity;  
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now(); //zatrzymanie odliczania

	if (t_wyswRozw) finalSolution(std::move(sciezki), std::move(najkrotszeSciezki), t_graf->getW(), t_startNode);
	delete[] najkrotszeSciezki;
	delete[] sciezki;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //return the time difference
}


//algorytm dla macierzy
double bellmanFord(std::shared_ptr<MacierzowyGraf> t_graf, int t_startNode, bool t_wyswRozw) {
	
	std::string* sciezki = new std::string[t_graf->getW()];

	auto t_start = std::chrono::high_resolution_clock::now(); 

	int* najkrotszeSciezki = new int[t_graf->getW()];

	for (int i = 0; i < t_graf->getW(); ++i) {

		najkrotszeSciezki[i] = s_infinity;
	}

	najkrotszeSciezki[t_startNode] = 0;

	for (int i = 1; i < t_graf->getW(); ++i) {
		for (int j = 0; j < t_graf->getW(); ++j) {
			for (int w = 0; w < t_graf->getW(); ++w) {

				int u = j;
				int v = w;
				int waga = t_graf->getElMacierz(j, w);
				if (najkrotszeSciezki[u] + waga < najkrotszeSciezki[v]) {
					
					najkrotszeSciezki[v] = najkrotszeSciezki[u] + waga;
					if (t_wyswRozw) {

						sciezki[v].clear();
						sciezki[v].append(sciezki[u] + std::to_string(u) + "->");
					}
				}
			}
		}
	}
	for (int i = 1; i < t_graf->getW(); ++i) {
		for (int j = 0; j < t_graf->getW(); ++j) {
			for (int w = 0; w < t_graf->getW(); ++w) {

				int u = j;
				int v = w;
				int waga = t_graf->getElMacierz(j, w);
				if (najkrotszeSciezki[u] + waga < najkrotszeSciezki[v]) {
				
					if (najkrotszeSciezki[u] > s_infinity / 2) najkrotszeSciezki[u] = s_infinity;
					else if (waga == s_infinity) continue;
					else najkrotszeSciezki[v] = s_neg_infinity;
				}
				else if (najkrotszeSciezki[u] > s_infinity/2) najkrotszeSciezki[u] = s_infinity;	
			}
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now(); 

	if (t_wyswRozw) finalSolution(std::move(sciezki), std::move(najkrotszeSciezki), t_graf->getW(), t_startNode);
	delete[] najkrotszeSciezki;
	delete[] sciezki;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count(); 
}
