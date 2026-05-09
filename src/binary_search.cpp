#include "binary_search.hpp"

int busquedaBinaria(const std::vector<Solicitud>& arr, int izq, int der, int k) {
    if (izq > der) return -1;

    int mid = (izq + der) / 2;

    if (arr[mid].tenure == k) {
        return mid;  
    } else if (arr[mid].tenure > k) {
        return busquedaBinaria(arr, mid + 1, der, k);
    } else {
        return busquedaBinaria(arr, izq, mid - 1, k);
    }
}