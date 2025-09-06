#include "./Listas/lue.hpp"
#include "./cards.hpp"
struct Cpu
{
    int id = 0;
    int pontos = 0;
    Lista<Carta> mao = {};
    Lista<Carta> cartasJogadas = {};
    bool adquirirCarta(Carta carta)
    {
        return mao.addItem(carta);
    }
    void procuraTrioeJoga(){
         // Procurar trios na mao e usar para jogar
        for (short int i = 0; i <= mao.tamanho; i++)
        {
            Carta carta = mao.getItem(i);
            Lista<int> tamanhosTrio = mao.procurarTrios(carta);
            cout << "[CPU] Analisando carta: " << carta << " na posição " << i << endl;
            cout << "[CPU] tamanhos encontrados para valor " << carta.valor << ": ";
            for (int k = 0; k <= tamanhosTrio.tamanho; k++) {
                cout << tamanhosTrio.getItem(k) << " ";
            }
            cout << endl;
            cout << "[CPU] Quantidade de cartas iguais: " << tamanhosTrio.tamanho + 1 << endl;
            cout << "Encontrar Trio:" << tamanhosTrio.tamanho << endl;
            if(tamanhosTrio.tamanho != -1){
                cout << "[CPU] Primeiro índice do trio/par: " << tamanhosTrio[0] << endl;
            }
            if(tamanhosTrio.tamanho >= 2) // Encontrou um trio
            {
                cout << "[CPU] Trio encontrado! Jogando trio..." << endl;
                // Joga o trio encontrado
                for (short int j = 0; j < 3; j++)
                {
                    int tamanhoAtual = tamanhosTrio.getItem(j);
                    Carta cartaAtual = mao.getItem(tamanhoAtual);
                    cartasJogadas.addItem(cartaAtual);
                    cout << "CPU jogou: " << cartaAtual << " (índice " << tamanhoAtual << ")" << endl;
                }

                // Remove as cartas jogadas da mao, de trás para frente nos índices
                for (short int j = 2; j >= 0; j--)
                {
                    int tamanhoParaRemover = tamanhosTrio.getItem(j);
                    cout << "[CPU] Removendo carta do trio no índice: " << tamanhoParaRemover << endl;
                    mao.removeItem(tamanhoParaRemover);
                    mao.printItems();
                }
                cout << "[CPU] Trio removido da mão." << endl;
                break;
            }
        }
    }
    bool escolherDescarte(Lista<Carta>& Descarte){
        // Estratégia: descartar carta que não forma par/trio
        for (short int i = 0; i <= mao.tamanho; i++) {
            Lista<int> temp = mao.procurarTrios(mao.getItem(i));
            if (temp.tamanho == 0) { // valor único na mão
                Carta cartaRemovida = mao.getItem(i);
                cout << "[CPU Estrategia] Descartando carta única: " << cartaRemovida << endl;
                Descarte.inserirComeco(cartaRemovida);
                mao.removeItem(i);
                return true;
            }
        }
        // Se todas as cartas têm pares/trios, descarta a primeira
        if (mao.tamanho >= 0) {
            Carta cartaRemovida = mao.getItem(0);
            cout << "[CPU Estrategia] Todas têm pares/trios, descartando: " << cartaRemovida << endl;
            Descarte.inserirComeco(cartaRemovida);
            mao.removeItem(0);
        }
        return true;
    }
    void comprar(Lista<Carta>& Baralho, Lista<Carta>& Descarte){
        bool temPar = false;
        // Carta cartaNecessaria;
        if(Descarte.vazia() == false){
            temPar = mao.procurarTrios(Descarte[0]).tamanho == 1;
            cout<<"Tem par? "<<temPar<<endl;
            // cartaNecessaria = Descarte[0];
        }
        if(temPar){
            cout << "CPU " << id << " comprou do descarte: " << Descarte[0] << endl;
            if(adquirirCarta(Descarte[0]))
                cout <<"FOI";
            Descarte.retirar(Descarte[0]);
            cout << "A mao atual";
            mostrarMao();
        }else if(Baralho.vazia() == false){
            cout << "CPU " << id << " comprou do baralho: " << Baralho[0] << endl;
            if(adquirirCarta(Baralho[0]))
                cout <<"FOI";
            Baralho.retirar(Baralho[0]);
            cout << "A mao atual";
            mostrarMao();
        }
        escolherDescarte(Descarte);
    }
    void mostrarMao(){
        cout << "Mão do CPU " << id << ": ";
        for(int i = 0; i < mao.tamanho + 1; i++){
            cout << mao.getItem(i) << " ";
        }
        cout << endl;
    }
    bool tomarDecisao(Lista<Carta>& Baralho, Lista<Carta>& Descarte)
    {
        mostrarMao();
        if(cartasJogadas.tamanho >= 8 || mao.tamanho < 0){
            cout << "Ganhou bot id:" << id;
            return true;
        }
        procuraTrioeJoga();
        comprar(Baralho, Descarte);
        return false;
    }
    bool operator <(const Cpu& other) const {
        return this->pontos < other.pontos;
    }
    bool operator >(const Cpu& other) const {
        return this->pontos > other.pontos;
    }
};
