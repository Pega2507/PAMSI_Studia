#include "lista_graf.hpp"

static int s_balance_of_interval = -1;

void GrafLista::dodajBrzeg(int t_guardNumber, int t_numer, int t_waga, int t_flaga) const 
{
	brzeg[t_flaga].destynacja = t_numer;
	brzeg[t_flaga].zrodlo = t_guardNumber;
	brzeg[t_flaga].waga = t_waga;
}


bool GrafLista::czyIstnieje(int t_guardNumber, int t_nodeNumber) const 
{
	for (int i = 0; i < m_B; ++i) { //sprawdz cala liste brzegow

		if (brzeg[i].destynacja == t_nodeNumber && brzeg[i].zrodlo == t_guardNumber) return true; 
	}
	return false;
}


void GrafLista::wypelnijGraf(const bool t_allowLoops) const 
{
	if (m_gestosc == 1) {  //przypadek z pelnym grafem

		int foo_flag = 0;
		for (int izrodlo = 0; izrodlo < m_W; ++izrodlo) {
			for (int idestynacja = 0; idestynacja < m_W; ++idestynacja) { 

				if (izrodlo!= idestynacja) {

					int foo_waga = rand() % 20 + s_balance_of_interval;
					while (foo_waga == 0) {

						foo_waga = rand() % 20 + s_balance_of_interval;
					}
					dodajBrzeg(izrodlo, idestynacja, foo_waga, foo_flag++);
				}
			}
		}
	}
	else {

		int foo_edges = 0;
		while (foo_edges < m_B) {

			int guardNode = rand() % m_W;	//blad
			int nodeNode = rand() % m_W;
			if (!czyIstnieje(guardNode, nodeNode)) {

				int foo_waga = rand() % 20 + s_balance_of_interval;
				while (foo_waga == 0) {

					foo_waga = rand() % 20 + s_balance_of_interval;
				}

				if (guardNode != nodeNode) dodajBrzeg(guardNode, nodeNode, foo_waga, foo_edges++);
				else if (t_allowLoops) dodajBrzeg(guardNode, nodeNode, foo_waga, foo_edges++);
			}
		}
	}
}


void GrafLista::pokazGraf() const {

	std::cout << std::string(30, '-') << "\n  Lista przylegajaca\n\n";
	for (int izrodlo = 0; izrodlo < m_W; ++izrodlo) {

		std::cout << izrodlo;
		for (int iBrzeg = 0; iBrzeg < m_B; ++iBrzeg) {

			if (brzeg[iBrzeg].zrodlo == izrodlo) 
				std::cout << "->" << "[" << brzeg[iBrzeg].destynacja << "|" << brzeg[iBrzeg].waga << "]";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


const int GrafLista::czytPlik() {

	std::ifstream file("Input.txt");
	if (!file.is_open()) {
		throw "Lista wejscia nie zostala otwarta!";
		return 1;
	}

	//inicjalizacja tablicy
	int start, zrodlo, destynacja, waga;
	file >> m_B >> m_W >> start;
	brzeg = new Brzeg[m_B];

	//dodawanie polaczen
	for (int iBrzeg = 0; iBrzeg < m_B; ++iBrzeg) {

		file >> zrodlo >> destynacja >> waga;
		dodajBrzeg(zrodlo, destynacja, waga, iBrzeg);
	}
	file.close();
	return start; //zwraca polaczenie poczatkowe
}


void GrafLista::createInput(const int t_startNode) const {

	std::ofstream file("CreatedInput.txt");
	if (!file.is_open()) {
		throw  "stworzony plik wejscia nie zostal otwarty!";
		return;
	}

	file << m_B << " " << m_W << " " << t_startNode << "\n";
	for (int iBrzeg = 0; iBrzeg < m_B; ++iBrzeg) {

		file << brzeg[iBrzeg].zrodlo << " ";
		file << brzeg[iBrzeg].destynacja << " ";
		file << brzeg[iBrzeg].waga << "\n";		
	}
	file.close();
}
