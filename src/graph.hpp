#pragma once
#include <vector>
#include "parser.hpp"

//Arista para conectar los nodos de la red
struct Arista {
    int u, v;
    double peso;
};


//Funcion para construir el grado con los datos del CSV
std::vector<Arista> construirGrafo(const std::vector<Solicitud>& solicitudes);