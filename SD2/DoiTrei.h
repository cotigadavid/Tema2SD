#pragma once

#include <iostream>
#include <algorithm>

class Nod {
public:
    int date;
    Nod* stanga;
    Nod* mijloc;
    Nod* dreapta;

    Nod(int date) {
        this->date = date;
        this->stanga = nullptr;
        this->mijloc = nullptr;
        this->dreapta = nullptr;
    }
};

class TwoThreeHeap {
public:
    Nod* radacina;

    TwoThreeHeap() {
        radacina = nullptr;
    }

    Nod* merge(Nod* a, Nod* b) {
        if (!a) return b;
        if (!b) return a;

        if (a->date > b->date) std::swap(a, b);

        if (!a->stanga) {
            a->stanga = b;
        }
        else if (!a->mijloc) {
            a->mijloc = b;
            if (a->stanga->date > a->mijloc->date) std::swap(a->stanga, a->mijloc);
        }
        else {
            a->dreapta = merge(a->dreapta, b);
            if (a->dreapta->date < a->mijloc->date) std::swap(a->dreapta, a->mijloc);
            if (a->mijloc->date < a->stanga->date) std::swap(a->stanga, a->mijloc);
        }

        return a;
    }

    void insert(int date) {
        Nod* nod = new Nod(date);
        radacina = merge(radacina, nod);
    }

    int extractMin() {
        if (!radacina) {
            std::cout << "Heap este gol." << std::endl;
            return -1;
        }

        int valMin = radacina->date;
        Nod* temp = radacina;
        radacina = merge(radacina->stanga, merge(radacina->mijloc, radacina->dreapta));
        delete temp;

        return valMin;
    }

    void mergeHeaps(TwoThreeHeap& altHeap) {
        radacina = merge(radacina, altHeap.radacina);
        altHeap.radacina = nullptr;
    }
};



