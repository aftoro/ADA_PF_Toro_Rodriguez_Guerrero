#include "graph.hpp"
#include <cmath>


//Funcion para creacion del grafo
std::vector<Arista> construirGrafo(const std::vector<Solicitud>& Solicitudes) {
    const int N=20;
    double sumaMC[N] = {};
    int conteo[N] = {};

    //Calcular promedio por grupo (i % 20)
    for(int i=0; i < (int)Solicitudes.size(); i++) {
        int grupo = i % 20;
        sumaMC[grupo] += Solicitudes[i].monthlyCharges;
        conteo[grupo]++;
    }

    double avg[N];
    for (int k = 0; k < N; k++) {
        double raw =sumaMC[k] / conteo[k];
        avg[k] = std::round(raw*100.0) / 100.0;
    }

    std::vector<Arista> aristas;
    aristas.reserve(N* (N-1)/2);

    //Crear aristas para los pares
    for (int u=0; u < N; u++) {
        for (int v = u + 1; v < N; v++) {
            Arista a;
            a.u = u;
            a.v = v;
            a.peso = std::floor(avg[u] + avg[v]);
            aristas.push_back(a);
        }
    }

    return aristas;
}