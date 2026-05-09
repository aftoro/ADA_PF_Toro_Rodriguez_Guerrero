#include "knapsack.hpp"
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

ResultadoMochila mochila(const std::vector<Solicitud>& solicitudes, int W) {
    int n = solicitudes.size();

    std::vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) {
        w[i] = (int)std::round(solicitudes[i].totalCharges / 10.0);
        v[i] = (int)std::round(solicitudes[i].monthlyCharges * 10);
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i-1][c];
            if (w[i-1] <= c) {
                dp[i][c] = std::max(dp[i][c], dp[i-1][c - w[i-1]] + v[i-1]);
            }
        }
    }

    ResultadoMochila resultado;
    resultado.valorOptimo = dp[n][W];

    int c = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][c] != dp[i-1][c]) {
            resultado.indices.push_back(i - 1);
            c -= w[i-1];
        }
    }

    return resultado;
}

void contraejemploCodicioso(const std::vector<Solicitud>& solicitudes,
                             int W, std::ofstream& file) {
    int wA = 250, vA = 300;
    int wB = 250, vB = 290;
    int wC = 400, vC = 500;
    int Wce = 500;

    std::string idA = solicitudes[41].customerID; 
    std::string idB = solicitudes[6].customerID;  
    std::string idC = solicitudes[12].customerID; 

    double rA = (double)vA/wA;
    double rB = (double)vB/wB;
    double rC = (double)vC/wC;

    file << "\n Contraejemplo Codicioso \n";
    file << "(W = " << Wce << ")\n";
    file << std::left << std::setw(15) << "Solicitud"
         << std::setw(8)  << "w"
         << std::setw(8)  << "v"
         << std::setw(10) << "v/w" << "\n";
    file << std::string(41, '-') << "\n";
    file << std::setw(15) << idA << std::setw(8) << wA
         << std::setw(8)  << vA
         << std::setw(10) << std::fixed << std::setprecision(3) << rA << "\n";
    file << std::setw(15) << idB << std::setw(8) << wB
         << std::setw(8)  << vB
         << std::setw(10) << rB << "\n";
    file << std::setw(15) << idC << std::setw(8) << wC
         << std::setw(8)  << vC
         << std::setw(10) << rC << "\n";
    file << std::string(41, '-') << "\n";

    // Codicioso por ratio descendente
    struct Item { int w, v; double r; std::string id; };
    std::vector<Item> items = {{wA,vA,rA,idA},{wB,vB,rB,idB},{wC,vC,rC,idC}};
    std::sort(items.begin(), items.end(),
              [](const Item& a, const Item& b){ return a.r > b.r; });

    int valorCodicioso = 0, pesoCodicioso = 0;
    std::string elegidoCodicioso = "";
    for (auto& item : items) {
        if (pesoCodicioso + item.w <= Wce) {
            pesoCodicioso += item.w;
            valorCodicioso += item.v;
            elegidoCodicioso += item.id + " ";
        }
    }

    // PD con 3 items
    int ws[] = {wA, wB, wC};
    int vs[] = {vA, vB, vC};
    std::string ids[] = {idA, idB, idC};
    std::vector<std::vector<int>> dp(4, std::vector<int>(Wce+1, 0));
    for (int i = 1; i <= 3; i++)
        for (int c = 0; c <= Wce; c++) {
            dp[i][c] = dp[i-1][c];
            if (ws[i-1] <= c)
                dp[i][c] = std::max(dp[i][c], dp[i-1][c-ws[i-1]] + vs[i-1]);
        }

    int valorPD = dp[3][Wce];
    std::string elegidoPD = "";
    int c = Wce;
    for (int i = 3; i >= 1; i--)
        if (dp[i][c] != dp[i-1][c]) {
            elegidoPD += ids[i-1] + " ";
            c -= ws[i-1];
        }

    file << "\nEnfoque            Seleccionadas                  Valor  Optimo?\n";
    file << std::string(62, '-') << "\n";
    file << std::left << std::setw(19) << "Codicioso (v/w)"
         << std::setw(25) << elegidoCodicioso
         << std::setw(7)  << valorCodicioso << "No\n";
    file << std::setw(19) << "PD (Mochila 0-1)"
         << std::setw(25) << elegidoPD
         << std::setw(7)  << valorPD << "Si\n";
    
}