#include "./Listas/listaestatica.hpp"
#include "./cards.hpp"
struct Cpu
{
    int id = 0;
    int pontos = 0;
    ListaEstatica<Carta> mao = {};
    ListaEstatica<Carta> cartasJogadas = {};
    void adquirirCarta(Carta carta)
    {
        mao.addItem(carta);
    }
    void procuraTrioeJoga(){
         // Procurar trios na mao e usar para jogar
        for (short int i = 0; i <= mao.indice; i++)
        {
            Carta carta = mao.getItem(i);
            ListaEstatica<int> indicesTrio = mao.procurarTrios(carta);

            if(indicesTrio.indice >= 2) // Encontrou um trio
            {
                // Joga o trio encontrado
                for (short int j = 0; j < 3; j++)
                {
                    int indiceAtual = indicesTrio.getItem(j);
                    Carta cartaAtual = mao.getItem(indiceAtual);
                    cartasJogadas.addItem(cartaAtual);
                    cout << "CPU jogou: " << cartaAtual << endl;
                }

                // Remove as cartas jogadas da mao, de trás para frente nos índices
                for (short int j = 2; j >= 0; j--)
                {
                    int indiceParaRemover = indicesTrio.getItem(j);
                    mao.removeItem(indiceParaRemover);
                }
                
                // A CPU já fez sua jogada, então sai do loop de decisão
                break; 
            }
        }
    }
    bool escolherDescarte(LUE<Carta>& Descarte){
        for (short int i = 0; i <= mao.indice; i++)
        {
            ListaEstatica<int> temp = mao.procurarTrios(mao.getItem(i));
            if(temp.indice < 1 && temp.indice != -1){
                cout << "CPU " << id << " descartou: " << mao.getItem(temp[0]) << endl;
                Descarte.inserirComeco(mao.getItem(temp[0]));
                mao.removeItem(temp[0]);
                return true;
            }
        }
        mao.removeItem(rand()%mao.indice);
        return true;
    }
    void comprar(LUE<Carta>& Baralho, LUE<Carta>& Descarte){
        bool temPar = false;
        // Carta cartaNecessaria;
        if(Descarte.comeco != NULL){
            temPar = mao.procurarTrios(Descarte[0]).indice == 1;
            // cartaNecessaria = Descarte[0];
        } 
        if(temPar){
            cout << "CPU " << id << " comprou: " << Descarte[0] << endl;
            adquirirCarta(Descarte[0]);
            Descarte.retirar(Descarte[0]);
        }else if(Baralho.comeco != NULL){
            cout << "CPU " << id << " comprou: " << Baralho[0] << endl;
            adquirirCarta(Baralho[0]);
            Baralho.retirar(Baralho[0]);
        }
        escolherDescarte(Descarte);
    }
    void mostrarMao(){
        cout << "Mão do CPU " << id << ": ";
        for(int i = 0; i < mao.indice; i++){
            cout << mao.getItem(i) << " ";
        }
        cout << endl;
    }
    void tomarDecisao(LUE<Carta>& Baralho, LUE<Carta>& Descarte)
    {
        mostrarMao();
        if(cartasJogadas.indice >= 8){
            cout << "Ganhou bot id:" << id;
        }
        procuraTrioeJoga();
        comprar(Baralho, Descarte);
    }
};