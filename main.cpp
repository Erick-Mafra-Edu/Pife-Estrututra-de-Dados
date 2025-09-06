#include <locale>
#include <iostream>
#include <windows.h>
#include "./Cards.hpp"
#include "./Listas/lue.hpp"
#include "./Baralho.hpp"
#include "./Cpu.hpp"
#include<ctime>
Lista<Carta> baralho = {};

int main(){
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); // Definindo o console para usar caracteres UTF-8 (SAÍDA)
    SetConsoleCP(CP_UTF8);       // Definindo o console para usar caracteres UTF-8 (ENTRADA)


    //LUE<string> log;
    //inicializar(log);

    inicializarBaralho(baralho);
    Lista<Carta> baralhoJogo = {}, descarte = {};
    for(int fim = 52; fim > 0; fim--){
        int carta = rand() % fim;
        Carta tmp = baralho[carta];
        baralhoJogo.inserirComeco(tmp);
        baralho.retirar(tmp);
    }

    Lista<Cpu> cpus;
    // Cpu* cpus = new Cpu();
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
    bool jogoAcabou = false;
    while(!jogoAcabou){
        descarte.printItems();
        for(int i = 0;i < numberCpu && !jogoAcabou;i++){
            jogoAcabou = cpus[i].tomarDecisao(baralhoJogo,descarte);
            cout << baralhoJogo.comeco << " " << descarte.comeco << endl;
            if(baralhoJogo.vazia() && !descarte.vazia()){
                cout<< "Baralho acabou, reembaralhando o descarte"<<endl;
                for(int j = 0;j<descarte.comprimento();j++){
                    baralhoJogo.inserirComeco(descarte[j]);
                    baralhoJogo.printItems();
                }
            // descarte.liberar();
            }
        }
    }
    return 0;
}
