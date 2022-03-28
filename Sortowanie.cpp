// PAMSI Aleksandra Machelak 259238
//Sortowanie
#include "Algorytmy.h"

template<typename T>
using SortFncPoint = void (*)(T*, T*, int, int, int);

template<typename T>
void print_table(T *tab, int n)
{
    for (int i = 0; i < n; i++) std::cout << tab[i] << " ";
}

template<typename T>
T *create_table(int n)
{
	return new T[n];
}

template<typename T>
void kill_table(T *table)
{
	delete[] table;
}

template<typename T>
void fill_random(T *tab, int n)
{
	for (int i = 0; i < n; i++) tab[i] = rand() % 100000 + 1;
}

//sortuje dany procent tablicy (od pierwszego elementu)
template<typename T>
void sort_percent(T *tab, int n, double percent)
{
    if (percent == 100) //sortuje w odwrotnej kolejności
    {
        std::sort(tab, tab + n, std::greater<T>());
        return;
    }
	std::sort(tab, tab + (int)((n*percent) / 100));
}

template<typename T>
void check_if_sorted(T *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            std::cout << "Table not sorted!\nProgram closing...";
            std::cin.get();
            exit(1);
        }
    }
}


template<typename T>
double sort_it(SortFncPoint<int> fp, int n, T *tab, T *tmp)
{
    auto t_start = std::chrono::high_resolution_clock::now(); //start clock
    fp(tab, tmp, 0, n-1, log(n) * 2);
    auto t_end = std::chrono::high_resolution_clock::now(); //stop clock

    return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //Zwraca roznice czasu
}



int main()
{
    srand(time(NULL));

	int loops = 1; //liczba sortowanych tablice
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000}; //rozmiary tablic
	double percenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100 }; //procent poczatkowo posortowanych elementow

	SortFncPoint<int> mpoint= &mergeWrap, qpoint = &quickWrap, ipoint = &introWrap; //wskazniki do funkcji
    SortFncPoint<int> ptable[3] = {qpoint, mpoint, ipoint};

	double counter = 0;
	int iter = 0;
	std::string sorts[3] = {"QUCIK_SORT", "MERGE_SORT", "INTRO_SORT"};

    for(SortFncPoint<int> fp : ptable) 
    {
        std::cout << sorts[iter++] << std::endl;
        for (double percent : percenttab) 
        {
            for (int n : ntab) 
            {
                int *tab = create_table<int>(n);
                int *tmp = create_table<int>(n);

                for (int i = 0; i < loops; i++) 
                {
                    fill_random<int>(tab, n);
                    sort_percent<int>(tab, n, percent);
                    counter += sort_it<int>(fp, n, tab, tmp);
                    check_if_sorted<int>(tab, n);

                    std::cout << i << "%" << "\r";
                }
                kill_table<int>(tab);
                kill_table<int>(tmp);

                std::cout << n << " table sorted!" << std::endl;
                counter = 0;
            }
            std::cout << percent << " % done!" << std::endl;
        }
    }
    std::cout << "END OF SORTING!";
	std::cin.get();

	return 0;


}
