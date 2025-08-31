#include <locale>
#include <iostream>
#include <windows.h>
#include "./Cards.hpp"
#include "./Listas/listaestatica.hpp"
#include "./Listas/lde.hpp"
#include "./Baralho.hpp"
#include "./Listas/lue.hpp"

LUE<Carta> baralho;

int main(){
    SetConsoleOutputCP(CP_UTF8); // Definindo o console para usar caracteres UTF-8 (SAÍDA)  
    SetConsoleCP(CP_UTF8);       // Definindo o console para usar caracteres UTF-8 (ENTRADA)
    

    //LUE<string> log;
    //inicializar(log);

    inicializarBaralho(baralho);
    LUE<Carta> baralhoJogo;
    for(int i=0,fim=52; i<52; i++){
        int carta = rand()%fim--;
        Carta tmp = baralho[carta];
        baralhoJogo.inserirComeco(tmp);
        baralho.retirar(tmp);
    }

    for(int i=0; i<52; i++){
        cout << baralhoJogo[i] << " ";
    }

    return 0;
}