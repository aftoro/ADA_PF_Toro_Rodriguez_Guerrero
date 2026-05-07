#include "mergesort.hpp"

void merge(std::vector<Solicitud>& arr, int izq, int mid, int der) {
    // Copiar cada mitad en vectores temporales
    std::vector<Solicitud> L(arr.begin() + izq, arr.begin() + mid + 1);
    std::vector<Solicitud> R(arr.begin() + mid + 1, arr.begin() + der + 1);

    int i = 0, j = 0, k = izq;

    while (i < (int)L.size() && j < (int)R.size()) {
        if (L[i].tenure >= R[j].tenure) { 
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];
}

void mergeSort(std::vector<Solicitud>& arr, int izq, int der) {
    if (izq >= der) return;  

    int mid = (izq + der) / 2;

    mergeSort(arr, izq, mid);       
    mergeSort(arr, mid + 1, der);   
    merge(arr, izq, mid, der);      
}