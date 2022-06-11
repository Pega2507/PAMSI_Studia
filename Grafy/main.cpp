#include <time.h>

#include "bellman_ford.hpp"


//petle - ile razy algorytm rozwiaze dany obiekt (im wiecej tym dokladniej)
//wierzTab, gestTab - parametry obiektu
template<typename T>
std::ostream& testy(std::ostream& file, int (&wierzTab)[5], double (&gestTab)[4], int petle) {
	
	for (double gestosc : gestTab) {
		for (int wierzcholki : wierzTab) { //dla kazdej ilosci wierzcholkow
			double sum = 0;
			for (int iPetle = 0; iPetle < petle; ++iPetle) {

				std::shared_ptr<T> graf = std::make_shared<T>(wierzcholki, gestosc); //tworzymy odpowiedni obiekt
				int startNode = rand() % wierzcholki; //tworzenie losowego wezla startowego

				graf->wypelnijGraf(true); //wypelnienie grafu z mozliwoscia petli	//blad

				sum += bellmanFord(std::move(graf), startNode, false); //algorytm zwraca czas wykonania
				std::cout << (iPetle * 100 / petle) + 1 << "%" << "\r" << std::flush;
			}
			file << sum / petle << " "; //zapis sredniej
			std::cout << wierzcholki << " wierzcholki skonczone!" << std::endl;
		}
		std::cout << "\n" << gestosc << " gestosc skonczona!\n" << std::endl;
	}
	file << "\n";
	return file;
}


int main() {

	srand(static_cast<unsigned int>(time(NULL)));

	bool testZone = true; // Wybor strefy!
	

	// TEST ZONE //

	//automatycznie testuje wybrane grafy

	if (testZone) {
		
		// zmienialne zmienne//
		int wierzTab[5] = {5, 15, 30, 50, 100}; //liczba wierzchholkow do testowania
		double gestTab[4] = {0.25, 0.5, 0.75}; //liczba gestosci -||-
		int petle = 100;		// ile razy algorytm ma przetestowac graf z tymi samymi parametrami

		std::ofstream file("OutputTimes.txt");
		if (!file.is_open()) {

			std::cerr << "Plik z czasami wyjscia nie zostal otwarty!" << std::flush;
			return 1;
		}

		testy<GrafLista>(file, wierzTab, gestTab, petle); //test listy 		//blad
		std::cout << "Lista zrobiona\n" << std::endl;
		testy<MacierzowyGraf>(file, wierzTab, gestTab, petle);	//test macierzy
		std::cout << "Macierz zrobiona" << std::endl;

		file.close();
		return 0;
	}

	return 0;
}