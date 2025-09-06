#ifndef maxItems
#define maxItems 52
#endif
#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
using namespace std;

// Estrutura auxiliar para armazenar o item e seu índice original
template<typename Tipo>
struct ListaAuxiliar{
    Tipo item = {};
    int tamanho = 0;
};

template<typename Tipo>
struct Lista{
    
    // Libera a lista (compatível com LUE/LDE)
    void liberar() {
        clear();
        comeco = nullptr;
        fim = nullptr;
    }
    // Ponteiros para compatibilidade com LUE/LDE e testes
    void* comeco = nullptr;
    void* fim = nullptr;

    Tipo items[maxItems] = {};
    int tamanho = -1;
    ListaAuxiliar<Tipo> itensOrdenado[maxItems] = {};

    // Adiciona um item no final
    bool addItem(Tipo input){
        return inserirFinal(input);
    }

    // Adiciona no final (compatível)
    bool inserirFinal(Tipo input){
        if((tamanho+1) >= maxItems)
            return false;
        items[++tamanho] = input;
        copyItems();
        return true;
    }
    // Verifica se a lista está vazia
    bool vazia() {
        return tamanho == -1;
    }
    // Adiciona no começo
    bool inserirComeco(Tipo input){
        if((tamanho+1) >= maxItems)
            return false;
        for(int i = tamanho+1; i > 0; i--){
            items[i] = items[i-1];
        }
        items[0] = input;
        tamanho++;
        copyItems();
        return true;
    }

    // Adiciona em ordem (usando operador <)
    bool inserirOrdem(Tipo input){
        if((tamanho+1) >= maxItems)
            return false;
        int pos = 0;
        while(pos <= tamanho && !(input < items[pos])) pos++;
        for(int i = tamanho+1; i > pos; i--){
            items[i] = items[i-1];
        }
        items[pos] = input;
        tamanho++;
        copyItems();
        return true;
    }

    // Acessa por índice (referência)
    Tipo& getItem(int i){
        try{
        if(i > tamanho || i < 0)
            throw std::out_of_range("Você está consultando fora do range");
        return items[i];
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }

    // Acesso via operador []
    Tipo& operator[](int i){
        return getItem(i);
    }

    // Remove por índice
    bool removeItem(int i) {
        if (i > tamanho || i < 0)
            return false;
        for (int j = i; j < tamanho; j++) {
            items[j] = items[j + 1];
        }
        tamanho--;
        copyItems();
        return true;
    }

    // Remove por valor (primeira ocorrência)
    bool retirar(Tipo valor){
        int idx = -1;
        for(int i=0;i<=tamanho;i++){
            if(items[i] == valor){
                idx = i;
                break;
            }
        }
        if(idx == -1) return false;
        return removeItem(idx);
    }

    // Busca binária no vetor ordenado, retorna índice original do item ou -1
    int searchItem(Tipo item){
        int left = 0;
        int right = tamanho;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (itensOrdenado[mid].item == item) {
                return itensOrdenado[mid].tamanho;
            } else if (itensOrdenado[mid].item < item) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    // Procura todos os índices de itens com o mesmo valor (.valor) do argumento
    Lista<int> procurarTrios(Tipo item) {
        Lista<int> tamanhos = {};
        for(int i=0;i<=tamanho;i++){
            if(items[i].valor == item.valor){
                tamanhos.addItem(i);
            }
        }
        return tamanhos;
    }

    // Copia os itens para o vetor auxiliar e ordena
    void copyItems(){
        for(int i = 0;i <= tamanho;i++){
            itensOrdenado[i].item = items[i];
            itensOrdenado[i].tamanho = i;
        }
        orderItems();
    }

    // Bubble Sort no vetor auxiliar
    void orderItems(){
        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho - i; j++) {
                if (itensOrdenado[j].item > itensOrdenado[j + 1].item) {
                    ListaAuxiliar<Tipo> temp = itensOrdenado[j];
                    itensOrdenado[j] = itensOrdenado[j + 1];
                    itensOrdenado[j + 1] = temp;
                }
            }
        }
    }

    void printItemsOrdenados(){
        for(int i = 0;i <= tamanho;i++){
            std::cout << "Item: " << itensOrdenado[i].item << ", tamanho original: " << itensOrdenado[i].tamanho << std::endl;
        }
    }
    void printItems(){
        for(int i = 0;i <= tamanho;i++){
            std::cout << "Item: " << items[i] << std::endl;
        }
    }

    // Limpa a lista
    void clear(){
        tamanho = -1;
        for(int i = 0;i < maxItems;i++){
            items[i] = {};
            itensOrdenado[i] = {};
        }
    }

    // Inicializa (compatível LUE/LDE)
    void inicializar(){
        clear();
    }

    // Tamanho (compatível LUE/LDE)
    int comprimento(){ return tamanho+1; }
};

#endif // LISTA_HPP