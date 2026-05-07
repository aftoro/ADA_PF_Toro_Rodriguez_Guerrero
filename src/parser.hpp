#pragma once
#include <string>
#include <vector>

struct Solicitud {
    std::string customerID;
    int         tenure;
    double      monthlyCharges;
    double      totalCharges;
    bool        churn;
};

std::vector<Solicitud> leerCSV(const std::string& ruta);