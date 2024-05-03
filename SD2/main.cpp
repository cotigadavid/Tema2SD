#include <iostream>
#include <fstream>
#include <chrono>

#include "Binomial.h"
#include "DoiTrei.h"
#include "Fibonacci.h"
#include "Binary.h"

struct Test
{
	short code;
	int heap;
	int nr;
};

int main() {

	std::ifstream fin("test3.txt");

	int nrHeapuri;
	int nrTask;

	fin >> nrHeapuri;
	fin >> nrTask;

	std::vector<Test> teste;

	for (int i = 0; i < nrTask; ++i)
	{
		Test temp;
		teste.push_back(temp);
		fin >> teste[i].code;
		fin >> teste[i].heap;

		if (teste[i].code != 2)
			fin >> teste[i].nr;
		else
			teste[i].nr = -1;
	}
	
	NodBinomial* caps[1005];

	for (int i = 0; i < 1004; ++i)
		caps[i] = nullptr;

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < teste.size(); ++i)
	{
		if (teste[i].code == 1)
			insereaza(caps[teste[i].heap], teste[i].nr);
		if (teste[i].code == 2)
			eliminaMinim(caps[teste[i].heap]);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Binomial Timp executie : " << duration.count() << "ms" << "\n";

	BinaryHeap bh[1005];

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < teste.size(); ++i)
	{
		if (teste[i].code == 1)
			bh[teste[i].heap].insereaza(teste[i].nr);
		if (teste[i].code == 2)
			bh[teste[i].heap].extrageMin();
	}

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Bynary Timp executie : " << duration.count() << "ms" << "\n";

	TwoThreeHeap tth[1005];

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < teste.size(); ++i)
	{
		if (teste[i].code == 1)
			tth[teste[i].heap].insert(teste[i].nr);
		if (teste[i].code == 2)
			tth[teste[i].heap].extractMin();
	}

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "2-3 Timp executie : " << duration.count() << "ms" << "\n";


	FibonacciHeap fh[1005];

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < teste.size(); ++i)
	{
		if (teste[i].code == 1)
			fh[teste[i].heap].insert(teste[i].nr);
		if (teste[i].code == 2)
			fh[teste[i].heap].extractMin();
	}
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Fibonacci Timp executie : " << duration.count() << "ms" << "\n";


	return 0;
}
