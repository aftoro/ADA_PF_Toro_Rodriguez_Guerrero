#include "binary_search.hpp"

// Busca la ULTIMA posicion donde tenure >= k (array descendente)
// Es decir, el indice mas a la derecha que aun cumple tenure >= k
// Ese es el "primero" que encontramos al buscar desde la izquierda
int busquedaBinaria(const std::vector<Solicitud>& arr, int izq, int der, int k) {
    if (izq > der) return -1;

    int mid = (izq + der) / 2;

    if (arr[mid].tenure >= k) {
        // mid cumple, pero puede haber mas a la derecha que tambien cumplan
        int mejor = busquedaBinaria(arr, mid + 1, der, k);
        return (mejor != -1) ? mejor : mid;
    } else {
        // arr[mid] < k, buscar a la izquierda donde estan los mayores
        return busquedaBinaria(arr, izq, mid - 1, k);
    }
}