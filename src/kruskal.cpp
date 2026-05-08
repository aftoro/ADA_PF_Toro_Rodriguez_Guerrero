#include "kruskal.hpp"
#include <algorithm>
#include <vector>

struct UnionFind {
    std::vector<int> padre;
    std::vector<int> rango;

    //Inicializar nodos
    UnionFind(int n) : padre(n), rango(n, 0) {
        for (int i=0; i < n; i++) padre[i] = i;         
    }

    int find(int x) {
        if (padre[x] != x)
            padre [x] = find(padre[x]);
        return padre[x];
    }

    //Unir los componentes (si ya estan conectados retorna false)
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;

        if (rango[rx] < rango[ry]) std::swap(rx, ry);
        padre[ry] = rx;
        if (rango[rx] == rango[ry]) rango[rx]++;
        return true;
    }
};

ResultadosMST kruskal(std::vector<Arista> aristas, int numNodos) {
    //Ordenar por peso (Ascendente)
    std::sort(aristas.begin(), aristas. end(), [](const Arista& a, const Arista& b) {return a.peso < b.peso;});

    UnionFind uf(numNodos);
    ResultadosMST resultado;
    resultado.pesoTotal = 0.0;

    for(const Arista& a : aristas) {
        //Si no forma un cliclo, la arista entra al MST
        if (uf.unite(a.u, a.v)) {
            resultado.aristas.push_back(a);
            resultado.pesoTotal += a.peso;
        }
        //Un arbol de N nodos tiene exactamente N-1 aristas
        if ((int)resultado.aristas.size() == numNodos - 1) break;
    }

    return resultado;
}
