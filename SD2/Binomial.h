#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

struct NodBinomial {
    int cheie;
    int grad;
    NodBinomial* parinte;
    NodBinomial* copil;
    NodBinomial* frate;

    explicit NodBinomial(int k) : cheie(k), grad(0), parinte(nullptr), copil(nullptr), frate(nullptr) {}

    NodBinomial* unesteArboriBinomiali(NodBinomial* arbore2) {
        if (!this) return arbore2;
        if (!arbore2) return this;

        if (this->cheie < arbore2->cheie) {
            this->frate = this->frate->unesteArboriBinomiali(arbore2);
            this->frate->parinte = this;
            return this;
        }
        else {
            arbore2->frate = this->unesteArboriBinomiali(arbore2->frate);
            arbore2->frate->parinte = arbore2;
            return arbore2;
        }
    }

    NodBinomial* combinaGramezi(NodBinomial* cap2) {
        NodBinomial* fictiv = new NodBinomial(0);
        NodBinomial* curent = fictiv;
        NodBinomial* cap1 = this;
        while (cap1 && cap2) {
            if (cap1->grad <= cap2->grad) {
                curent->frate = cap1;
                cap1 = cap1->frate;
            }
            else {
                curent->frate = cap2;
                cap2 = cap2->frate;
            }
            curent = curent->frate;
        }
        if (cap1) curent->frate = cap1;
        else curent->frate = cap2;
        return fictiv->frate;
    }
};

void insereaza(NodBinomial*& cap, int cheie) {
    NodBinomial* temp = new NodBinomial(cheie);
    cap = cap->combinaGramezi(temp);
}

int obtineMinim(NodBinomial*& cap) {
    if (!cap) return INT_MIN;
    NodBinomial* nodMinim = cap;
    NodBinomial* curent = cap->frate;
    while (curent) {
        if (curent->cheie < nodMinim->cheie) {
            nodMinim = curent;
        }
        curent = curent->frate;
    }
    return nodMinim->cheie;
}

int eliminaMinim(NodBinomial*& cap) {
    if (!cap) return INT_MIN;
    NodBinomial* anterior = nullptr;
    NodBinomial* nodMinim = cap;
    NodBinomial* curent = cap->frate;
    NodBinomial* anteriorMinim = nullptr;
    while (curent) {
        if (curent->cheie < nodMinim->cheie) {
            nodMinim = curent;
            anteriorMinim = anterior;
        }
        anterior = curent;
        curent = curent->frate;
    }
    if (anteriorMinim) anteriorMinim->frate = nodMinim->frate;
    else cap = nodMinim->frate;

    NodBinomial* copil = nodMinim->copil;
    while (copil) {
        NodBinomial* urmatorCopil = copil->frate;
        copil->parinte = nullptr;
        copil->frate = nullptr;
        NodBinomial* temp = copil;
        cap = cap->combinaGramezi(temp);
        copil = urmatorCopil;
    }

    int valoareMinima = nodMinim->cheie;
    delete nodMinim;
    return valoareMinima;
}


