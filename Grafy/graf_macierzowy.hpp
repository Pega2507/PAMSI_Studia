#pragma once

#include "graf.hpp" 

#include <cstdlib>
#include <memory>


class MacierzowyGraf : public Graf {

	std::unique_ptr<std::unique_ptr<int[]>[]> macierz; 
														
public:
	void wypelnijGraf(const bool allowLoops) const override;
	void pokazGraf() const override;
	const int czytPlik() override;
	void createInput(const int t_startNode) const override;

	//zwraca wartosc danej komorki z macierzy
	const int& getElMacierz(int t_rzad, int t_kolumna) const { return macierz[t_rzad][t_kolumna]; } 

	explicit MacierzowyGraf(int t_W, double t_gestosc);
	MacierzowyGraf() : Graf() {};
};