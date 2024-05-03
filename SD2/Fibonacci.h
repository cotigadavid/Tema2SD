#pragma once

#include <vector>
#include <unordered_map>
#include <limits>

class FibonacciHeap {
private:
    struct Nod {
        int cheie;
        int grad;
        bool marcat;
        Nod* parinte;
        Nod* copil;
        Nod* stanga;
        Nod* dreapta;

        Nod(int k) : cheie(k), grad(0), marcat(false), parinte(nullptr), copil(nullptr), stanga(this), dreapta(this) {}
    };

    Nod* minNode;
    int dimensiune;

    void link(Nod* copil, Nod* parinte) {
        copil->stanga->dreapta = copil->dreapta;
        copil->dreapta->stanga = copil->stanga;

        copil->parinte = parinte;
        if (!parinte->copil) {
            parinte->copil = copil;
            copil->stanga = copil;
            copil->dreapta = copil;
        }
        else {
            copil->stanga = parinte->copil;
            copil->dreapta = parinte->copil->dreapta;
            parinte->copil->dreapta->stanga = copil;
            parinte->copil->dreapta = copil;
        }

        parinte->grad++;
        copil->marcat = false;
    }

    void consolidate() {
        int gradMax = static_cast<int>(std::log2(dimensiune)) + 1;
        std::vector<Nod*> tabelGrad(gradMax, nullptr);

        Nod* curent = minNode;
        std::vector<Nod*> deVizitat;
        do {
            deVizitat.push_back(curent);
            curent = curent->dreapta;
        } while (curent != minNode);

        for (Nod* nod : deVizitat) {
            Nod* x = nod;
            int d = x->grad;
            while (tabelGrad[d]) {
                Nod* y = tabelGrad[d];
                if (x->cheie > y->cheie) std::swap(x, y);
                link(y, x);
                tabelGrad[d] = nullptr;
                d++;
            }
            tabelGrad[d] = x;
        }

        minNode = nullptr;
        for (Nod* nod : tabelGrad) {
            if (nod) {
                if (!minNode || nod->cheie < minNode->cheie) minNode = nod;
            }
        }
    }

    void mergeRootLists(Nod* rootList1, Nod* rootList2) {
        if (!rootList1) {
            minNode = rootList2;
        }
        else if (!rootList2) {
            minNode = rootList1;
        }
        else {
            Nod* temp = rootList1->dreapta;
            rootList1->dreapta = rootList2->dreapta;
            rootList2->dreapta->stanga = rootList1;
            rootList2->dreapta = temp;
            temp->stanga = rootList2;

            if (rootList2->cheie < rootList1->cheie) {
                minNode = rootList2;
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), dimensiune(0) {}

    ~FibonacciHeap() {
        if (minNode) {
            std::unordered_map<Nod*, bool> vizitat;
            std::vector<Nod*> deVizitat;
            deVizitat.push_back(minNode);
            while (!deVizitat.empty()) {
                Nod* curent = deVizitat.back();
                deVizitat.pop_back();
                if (!vizitat[curent]) {
                    vizitat[curent] = true;
                    Nod* copil = curent->copil;
                    if (copil) {
                        deVizitat.push_back(copil);
                        Nod* urmator = copil->dreapta;
                        while (urmator != copil) {
                            deVizitat.push_back(urmator);
                            urmator = urmator->dreapta;
                        }
                    }
                    delete curent;
                }
            }
        }
    }

    void insert(int cheie) {
        Nod* nodNou = new Nod(cheie);
        if (!minNode) {
            minNode = nodNou;
        }
        else {
            nodNou->stanga = minNode;
            nodNou->dreapta = minNode->dreapta;
            minNode->dreapta->stanga = nodNou;
            minNode->dreapta = nodNou;
            if (cheie < minNode->cheie) minNode = nodNou;
        }
        dimensiune++;
    }

    int getMin() {
        if (!minNode) return std::numeric_limits<int>::max();
        return minNode->cheie;
    }

    int extractMin() {
        if (!minNode) return std::numeric_limits<int>::max();

        Nod* z = minNode;
        int minKey = z->cheie;

        if (z->copil) {
            Nod* copil = z->copil;
            do {
                Nod* urmator = copil->dreapta;
                copil->stanga->dreapta = copil->dreapta;
                copil->dreapta->stanga = copil->stanga;
                copil->stanga = minNode;
                copil->dreapta = minNode->dreapta;
                minNode->dreapta->stanga = copil;
                minNode->dreapta = copil;
                copil->parinte = nullptr;
                copil = urmator;
            } while (copil != z->copil);
        }

        z->stanga->dreapta = z->dreapta;
        z->dreapta->stanga = z->stanga;

        if (z == z->dreapta) {
            minNode = nullptr;
        }
        else {
            minNode = z->dreapta;
            consolidate();
        }

        delete z;
        dimensiune--;

        return minKey;
    }

    void merge(FibonacciHeap& altul) {
        mergeRootLists(minNode, altul.minNode);
        if (!minNode || (altul.minNode && altul.minNode->cheie < minNode->cheie)) {
            minNode = altul.minNode;
        }
        dimensiune += altul.dimensiune;
        altul.minNode = nullptr;
        altul.dimensiune = 0;
    }
};