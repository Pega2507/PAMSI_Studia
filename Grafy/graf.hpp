#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
//bazowa, abstrakcyjna klasa dla grafu
class Graf 
{
protected:
	int m_B; //ilosc wierzcholkow i brzegow
	int m_W;
	double m_gestosc; //gestosc grafu

public:
	const int& getW() const { return m_W; }						
	const int& getB() const { return m_B; }

	virtual void wypelnijGraf(const bool allowLoops) const = 0; //wypelnia losowymi wartosciami
	virtual void pokazGraf() const =  0; //pokazuje graf na konsoli
	virtual const int czytPlik() = 0; //wypelnia graf wartosciami z pliku
	virtual void createInput(const int t_startNode) const = 0; 
	virtual ~Graf() {};
	explicit Graf(int t_W, int t_B, double t_gestosc) : m_B(t_W), m_W(t_B), m_gestosc(t_gestosc) {}
	Graf() {}; //Unparametrized constructor, so program can crete a graph without initialization. 
};				//This is beacause program must be able to crete graph based on the input file infomations.