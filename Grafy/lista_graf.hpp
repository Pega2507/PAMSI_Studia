#pragma once
#include "graf.hpp"

struct Brzeg {
	int zrodlo, destynacja, waga; 
};


//Graf jako lista przylegajaca
class GrafLista : public Graf {

	Brzeg* brzeg; //Tablica brzegow w grafie

public:
	void wypelnijGraf(const bool allowLoops) const override; 
	void pokazGraf() const override;
	const int czytPlik() override;
	void createInput(const int t_startNode) const override;

	const Brzeg* getStruct() const { return brzeg; } 
	void dodajBrzeg(int t_guardNumber, int t_numer, int t_waga, int flaga) const; //dodaje polaczenie na fladze
	bool czyIstnieje(int t_guardNumber, int t_nodeNumber) const; //sprawdza czy istnieje polaczenie
	
	explicit GrafLista(int t_W, double t_gestosc)
		:Graf(t_W, static_cast<int>(t_gestosc* t_W* (t_W - 1)), t_gestosc),
		 brzeg(new Brzeg[static_cast<int>(t_gestosc* t_W* (t_W - 1))]) {}
	GrafLista() : Graf() {};
	~GrafLista() { delete[] brzeg; }
};
