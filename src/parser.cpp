#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

static std::vector<std::string> dividirCSV(const std::string& linea) {
    std::vector<std::string>cols;
    std::string col;
    bool dentroComillas = false;

    for (char c : linea) {
        if (c == '"') {
            dentroComillas = !dentroComillas;
        } else if (c == ',' && !dentroComillas) {
            cols.push_back(col);
            col.clear();
        } else {
            col += c;
        }
    }
    cols.push_back(col);
    return cols;
}

std::vector<Solicitud> leerCSV(const std::string& ruta) {
    std::vector<Solicitud> solicitudes;
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << ruta << "\n";
        return solicitudes;
    }

    std::string linea;
    int nulos = 0;

    std::getline(archivo, linea); 

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        auto cols = dividirCSV(linea);
        if (cols.size() < 21) continue;

        Solicitud s;

        s.customerID = cols[0];
        s.tenure = std::stoi(cols[5]);
        s.monthlyCharges = std::stod(cols[18]);

        std::string tc = cols[19];
        size_t ini = tc.find_first_not_of(" \t");
        if (ini == std::string::npos) {
            s.totalCharges = 0.0;
            nulos++;
        } else {
            tc = tc.substr(ini);
            s.totalCharges = std::stod(tc);
        }

        s.churn = (cols[20] == "Yes");

        solicitudes.push_back(s);
    }

    std::cout << "Registros cargados : " << solicitudes.size() << "\n";
    std::cout << "TotalCharges nulos : " << nulos << "\n";

    return solicitudes;
}