#include "graf_macierzowy.hpp"

static int s_infinity = 10000000; 

static int s_balance_of_interval = -1; //manipulacja randem w wypelnieniu grafu

//konstruktor. t_w - tymczasowe wierzcholki itd
MacierzowyGraf::MacierzowyGraf(int t_W, double t_gestosc) 
	: Graf(t_W, static_cast<int>(t_gestosc* t_W* (t_W - 1)), t_gestosc),
	  macierz(std::make_unique<std::unique_ptr<int[]>[]>(t_W)) 
{
	//inicjalizacja tablic w macierzy
	for (int i = 0; i < m_W; ++i) 	//i wiersze, j kolumny
	{ 	
		macierz[i] = std::make_unique<int[]>(t_W); 
		for (int j = 0; j < m_W; ++j) 
		{
			if (i == j) macierz[i][j] = 0; //"srodek" wypelniamy zerami
			else macierz[i][j] = s_infinity; 
		}
	}
}


void MacierzowyGraf::wypelnijGraf(const bool t_allowLoops) const {

	if (m_gestosc == 1) {  //pelny graf
		for (int i = 0; i < m_W; ++i) { //wiersze
			for (int j = 0; j < m_W; ++j) {  //kolumny
				if (i != j) 
				{
					int foo_waga = rand() % 20  + s_balance_of_interval;
					while (foo_waga == 0) {

						foo_waga = rand() % 20 + s_balance_of_interval;
					}
					macierz[i][j] = foo_waga;
				}
			}
		}
	}
	else { //inne gestosci

		int foo_brzegi = m_B;

		while (foo_brzegi) { //dopoki trzeba tworzyc brzegi

			int wezelRzedu = rand() % m_W; //losowo wybiera ilosc polaczen miedzy brzegami
			int wezelKolumny = rand() % m_W;

			//jesli brzeg jeszcze nie zostal stworzony
			if (macierz[wezelRzedu][wezelKolumny] == 0|| macierz[wezelRzedu][wezelKolumny]== s_infinity) { 

				int foo_waga = rand() % 20 + s_balance_of_interval;
				while (foo_waga == 0) { //tworzy rozne od 0

					foo_waga = rand() % 20 + s_balance_of_interval;
				}

				if (wezelRzedu != wezelKolumny) {

					macierz[wezelRzedu][wezelKolumny] = foo_waga;
					--foo_brzegi;
				}
				else if (t_allowLoops) {

					macierz[wezelRzedu][wezelKolumny] = foo_waga;
					--foo_brzegi;
				}
			}
		}
	}
}


void MacierzowyGraf::pokazGraf() const {

	std::cout << std::string(33, '-') << "\n  Adjencymacierz Representation\n\n ";

	//liczby na wierzchu
	for (int iIter = 0; iIter < m_W; ++iIter) {
		
		if (iIter <= 10) std::cout << "    " << iIter;
		else if (iIter <= 100) std::cout << "   " << iIter;
		else std::cout << "  " << iIter;
	}
	std::cout << "\n\n";

	//wiersze
	for (int i = 0; i < m_W; ++i) {	
		
		if (i < 10) std::cout << i << "   |";
		else if (i < 100) std::cout << i << "  |";
		else std::cout << i << " |";
		
		//polaczenia w kolumnach (wierszach???)
		for (int j = 0; j < m_W; ++j) {

			int foo = macierz[i][j];

			if (foo == s_infinity) std::cout << "*"; // jesli wezel ma nieskonczonosc - brak brzegu, wyrzuc gwiazdke 
			else std::cout << foo;					

			if (abs(foo) < 10 || abs(foo) == s_infinity) std::cout << "    ";
			else if (abs(foo) < 100) std::cout << "   ";
			else std::cout << "  ";

			if (foo < 0) std::cout << '\b'; 
		}
		
		std::cout << "|\n";
	}
	std::cout << std::endl;
}


const int MacierzowyGraf::czytPlik() {

	std::ifstream file("Input.txt"); 
	if (!file.is_open()) {
		throw "Macierz wejscia nie zostala otwarta!";
		return 1;
	}

	//inicjalizacja macierzy
	int start, zrodlo, destynacja, waga;
	file >> m_B >> m_W >> start;
	macierz = std::make_unique<std::unique_ptr<int[]>[]>(m_W);

	for (int i = 0; i < m_W; ++i) {

		macierz[i] = std::move(std::make_unique<int[]>(m_W));
		for (int j = 0; j < m_W; ++j) {

			if (i == j) macierz[i][j] = 0;
			else macierz[i][j] = s_infinity;
		}
	}

	//wypelnianie tablic z pliku
	for (int iEdge = 0; iEdge < m_B; ++iEdge) {

		file >> zrodlo >> destynacja >> waga;
		macierz[zrodlo][destynacja] = waga;;
	}
	file.close();
	return start; //zwraca start (wymagane do algorytmu)
}



void MacierzowyGraf::createInput(const int t_startNode) const {
	
	std::ofstream file("CreatedInput.txt");
	if (!file.is_open()) {
		throw  "CREATED INPUT macierz NOT OPEN!";
		return;
	}

	file << m_B << " " << m_W << " " << t_startNode << "\n";
	for (int i = 0; i < m_W; ++i) {
		for (int j = 0; j < m_W; ++j) {

			if (macierz[i][j] != s_infinity && macierz[i][j] != 0) {

				file << i << " ";
				file << j << " ";
				file << macierz[i][j] << "\n";
			}
		}
	}
	file.close();
}
