#pragma once
#include "parser.hpp"
#include <vector>

struct ResultadoMochila {
    int valorOptimo;
    std::vector<int> indices;  
};

ResultadoMochila mochila(const std::vector<Solicitud>& solicitudes, int W);

void contraejemploCodicioso(const std::vector<Solicitud>& solicitudes, 
                             int W, std::ofstream& file);