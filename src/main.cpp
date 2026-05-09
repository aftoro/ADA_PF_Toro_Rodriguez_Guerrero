#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "parser.hpp"
#include "mergesort.hpp"
#include "binary_search.hpp"
#include "graph.hpp"
#include "kruskal.hpp"
#include "knapsack.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./ada_pf data/archivo.csv\n";
        return 1;
    }

    std::vector<Solicitud> solicitudes = leerCSV(argv[1]);

    int churnNo = 0, tenureMax = 0, tenureMin = 999, nulos = 0;
    double sumaMensual = 0.0;
    for (const auto& s : solicitudes) {
        if (!s.churn) churnNo++;
        if (s.tenure > tenureMax) tenureMax = s.tenure;
        if (s.tenure < tenureMin) tenureMin = s.tenure;
        sumaMensual += s.monthlyCharges;
        if (s.totalCharges == 0.0 && s.tenure == 0) nulos++;
    }
    std::cout << "Churn = No : " << churnNo << "\n";
    std::cout << "tenure max/min : " << tenureMax << " / " << tenureMin << "\n";
    std::cout << "MonthlyCharges : " << std::fixed << std::setprecision(2)
              << (sumaMensual / solicitudes.size()) << " USD \n";

    // modulo A 
    auto inicio = std::chrono::high_resolution_clock::now();
    mergeSort(solicitudes, 0, (int)solicitudes.size() - 1);
    auto fin = std::chrono::high_resolution_clock::now();
    double ms7043 = std::chrono::duration<double, std::milli>(fin - inicio).count();

    std::vector<Solicitud> sub3500(solicitudes.begin(), solicitudes.begin() + 3500);
    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(sub3500, 0, (int)sub3500.size() - 1);
    fin = std::chrono::high_resolution_clock::now();
    double ms3500 = std::chrono::duration<double, std::milli>(fin - inicio).count();

    std::vector<Solicitud> sub1000(solicitudes.begin(), solicitudes.begin() + 1000);
    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(sub1000, 0, (int)sub1000.size() - 1);
    fin = std::chrono::high_resolution_clock::now();
    double ms1000 = std::chrono::duration<double, std::milli>(fin - inicio).count();

    std::cout << "\n Modulo A - MergeSort \n";
    std::cout << "n=1000 : " << ms1000 << " ms\n";
    std::cout << "n=3500 : " << ms3500 << " ms\n";
    std::cout << "n=7043 : " << ms7043 << " ms\n";

    // Busqueda binaria
    int consultas[] = {72, 60, 45, 30, 12};
    std::string nombres[] = {"Q_A01","Q_A02","Q_A03","Q_A04","Q_A05"};

    std::cout << "\n Modulo A - Busqueda Binaria \n";
    std::ofstream fileBusquedas("results/busquedas_A.txt");
    for (int i = 0; i < 5; i++) {
        int idx = busquedaBinaria(solicitudes, 0, (int)solicitudes.size() - 1, consultas[i]);
        std::string res = (idx != -1) ? solicitudes[idx].customerID : "No encontrado";
        std::cout << nombres[i] << " (k=" << consultas[i] << "): " << res << "\n";
        fileBusquedas << nombres[i] << " k=" << consultas[i] << " -> " << res << "\n";
    }
    fileBusquedas.close();

    // Guardar solicitudes ordenadas
    std::ofstream fileOrdenadas("results/solicitudes_ordenadas.csv");
    fileOrdenadas << "customerID,tenure,monthlyCharges,totalCharges,churn\n";
    for (const auto& s : solicitudes) {
        fileOrdenadas << s.customerID << ","
                      << s.tenure << ","
                      << s.monthlyCharges << ","
                      << s.totalCharges << ","
                      << (s.churn ? "Yes" : "No") << "\n";
    }
    fileOrdenadas.close();

    std::cout << "results/busquedas_A.txt generado\n";
    std::cout << "results/solicitudes_ordenadas.csv generado\n";

    // modulo B
    auto aristas = construirGrafo(solicitudes);
    double sumaPesos = 0;
    for (auto& a : aristas) sumaPesos += a.peso;

    std::cout << "\nModulo B \n";
    std::cout << "Nodos  : 20\n";
    std::cout << "Aristas: " << aristas.size() << "\n";
    std::cout << "Costo promedio de arista: "
              << std::fixed << std::setprecision(2)
              << (sumaPesos / aristas.size()) << "\n";

    auto mst = kruskal(aristas, 20);
    std::cout << "Peso total del MST: " << mst.pesoTotal << "\n";
    std::cout << "Aristas en el MST : " << mst.aristas.size() << "\n";

    std::ofstream fileMST("results/mst_red.txt");
    fileMST << "Aristas del MST (nodo_u -- nodo_v, peso):\n";
    for (auto& a : mst.aristas)
        fileMST << "  nodo " << a.u << " -- nodo " << a.v
                << "   peso = " << a.peso << "\n";
    fileMST << "\nPeso total del MST: " << mst.pesoTotal << "\n";
    fileMST.close();
    std::cout << "results/mst_red.txt generado\n";

    //  modulo C 
    std::vector<Solicitud> activas;
    for (const auto& s : solicitudes) {
        if (!s.churn) {
            activas.push_back(s);
            if ((int)activas.size() == 50) break;
        }
    }

    int W = 500;

    ResultadoMochila resultado = mochila(activas, W);

    std::cout << "\n Modulo C \n";
    std::cout << "Solicitudes activas tomadas : " << activas.size() << "\n";
    std::cout << "Capacidad W                 : " << W << "\n";
    std::cout << "Valor optimo                : " << resultado.valorOptimo << "\n";
    std::cout << "Solicitudes seleccionadas   : " << resultado.indices.size() << "\n";

    std::ofstream fileBW("results/asignacion_bw.txt");
    fileBW << " Modulo C \n";
    fileBW << "Capacidad W        : " << W << "\n";
    fileBW << "Valor optimo total : " << resultado.valorOptimo << "\n\n";
    fileBW << "Solicitudes seleccionadas:\n";
    fileBW << std::left << std::setw(15) << "customerID"
           << std::setw(10) << "peso(w)"
           << std::setw(10) << "valor(v)" << "\n";
    fileBW << std::string(35, '-') << "\n";

    int pesoTotal = 0;
    for (int idx : resultado.indices) {
        int wi = (int)std::round(activas[idx].totalCharges / 10.0);
        int vi = (int)std::round(activas[idx].monthlyCharges * 10);
        pesoTotal += wi;
        fileBW << std::setw(15) << activas[idx].customerID
               << std::setw(10) << wi
               << std::setw(10) << vi << "\n";
    }
    fileBW << std::string(35, '-') << "\n";
    fileBW << "Peso total usado   : " << pesoTotal << " / " << W << "\n";
    fileBW << "Valor optimo total : " << resultado.valorOptimo << "\n";
    
    contraejemploCodicioso(activas, W, fileBW);
    fileBW.close();
    std::cout << "results/asignacion_bw.txt generado\n";

    return 0;
}