#pragma once

#include <vector>
#include <stdexcept>

class BinaryHeap {
private:
    std::vector<int> heap;

    void siftUp(int index) {
        while (index > 0 && heap[tata(index)] > heap[index]) {
            std::swap(heap[tata(index)], heap[index]);
            index = tata(index);
        }
    }

    void siftDown(int index) {
        int stanga = fiuStanga(index);
        int dreapta = fiuDreapta(index);

        int celMaiMic = index;

        if (stanga < heap.size() && heap[stanga] < heap[celMaiMic])
            celMaiMic = stanga;
        if (dreapta < heap.size() && heap[dreapta] < heap[celMaiMic])
            celMaiMic = dreapta;

        if (celMaiMic != index) {
            std::swap(heap[index], heap[celMaiMic]);
            siftDown(celMaiMic);
        }
    }

    int tata(int index) { return (index - 1) / 2; }
    int fiuStanga(int index) { return 2 * index + 1; }
    int fiuDreapta(int index) { return 2 * index + 2; }

public:
    void insereaza(int cheie) {
        heap.push_back(cheie);
        siftUp(heap.size() - 1);
    }

    int extrageMin() {
        if (heap.empty())
            throw std::runtime_error("Heap is empty");

        int radacina = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        siftDown(0);

        return radacina;
    }

    void merge(BinaryHeap& altul) {
        for (int cheie : altul.heap)
            insereaza(cheie);
    }
};