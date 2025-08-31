#include <locale>
#include <iostream>
#include <windows.h>
#include "./Cards.hpp"
#include "./Listas/listaestatica.hpp"
#include "./Listas/lde.hpp"
#include "./Baralho.hpp"
#include "./Listas/lue.hpp"
#include "./Cpu.hpp"
#include<ctime>
LUE<Carta> baralho = {};

int main(){
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); // Definindo o console para usar caracteres UTF-8 (SAÍDA)  
    SetConsoleCP(CP_UTF8);       // Definindo o console para usar caracteres UTF-8 (ENTRADA)
    

    //LUE<string> log;
    //inicializar(log);

    inicializarBaralho(baralho);
    LUE<Carta> baralhoJogo = {}, descarte = {};
    for(int fim = 52; fim > 0; fim--){
        int carta = rand() % fim;
        Carta tmp = baralho[carta];
        baralhoJogo.inserirComeco(tmp);
        baralho.retirar(tmp);
    }
    
    LDE<Cpu> cpus;
    for(int i=0; i<52; i++){
        cout << baralhoJogo[i] << " ";
    }
    cout << endl;
    int numberCpu = 2+rand()%2;
    for(int i = 0;i < numberCpu;i++){
        Cpu* atualCpu = new Cpu();
        atualCpu->id = i;
        for(int j = 0;j<9;j++){
            atualCpu->adquirirCarta(baralhoJogo[0]);
            baralhoJogo.retirar(baralhoJogo[0]);
        }
        cpus.inserirComeco(*atualCpu);
    }
    while(true){
        for(int i = 0;i < numberCpu;i++){
            cpus[i].tomarDecisao(baralhoJogo,descarte);
            if(baralhoJogo.comeco == NULL && descarte.comeco != NULL){
                for(int i = 0;i>descarte.comprimento();i++){
                    baralhoJogo.inserirComeco(descarte[i]);
                } 
            }
        }
    }
    // cpu.adquirirCarta({Naipe::COPAS, "A"});
    // cpu.adquirirCarta({Naipe::COPAS, "2"});
    // cpu.adquirirCarta({Naipe::PAUS, "A"});
    // cpu.adquirirCarta({Naipe::PAUS, "2"});
    // cpu.adquirirCarta({Naipe::ESPADAS, "A"});
    // cpu.adquirirCarta({Naipe::ESPADAS, "2"});
    // cpu.mao.printItems();
    // cpu.tomarDecisao(baralhoJogo, descarte);
    // cpu.mao.printItems();
    return 0;
}