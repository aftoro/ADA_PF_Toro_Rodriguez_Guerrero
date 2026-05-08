#pragma once
#include "graph.hpp"
#include <vector>

struct ResultadosMST {
    std::vector<Arista> aristas;
    double pesoTotal;
};

ResultadosMST kruskal(std::vector<Arista> aristas, int numNodos);
