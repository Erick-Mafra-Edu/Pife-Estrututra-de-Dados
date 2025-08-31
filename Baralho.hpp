#include "Cards.hpp"
#include "./Listas/lue.hpp"

void inicializarBaralho(LUE<Carta>& baralho) {
    // Valores das cartas (A, 2, ..., K)
    std::string valores[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    
    // Percorre os 4 naipes
    for(int n = OUROS; n <= PAUS; n++) {
        for(int v = 0; v < 13; v++) {
            Carta c;
            c.naipe = static_cast<Naipe>(n);
            c.valor = valores[v];
            baralho.inserirFinal(c);
        }
    }
}