#ifndef LUE_PADRONIZADO_HPP
#define LUE_PADRONIZADO_HPP

#include <iostream>
using namespace std;

template <typename T>
struct NoLUE {
    T info;
    NoLUE<T>* elo;
};

template <typename T>
struct Lista {
    NoLUE<T>* comeco = nullptr;
    NoLUE<T>* fim = nullptr;
    int tamanho = -1;

    // Acesso indexado (referência)
    T& operator[](int i) {
        return getItem(i);
    }
    bool vazia(){
        return tamanho == -1;
    }
    // Adiciona no final
    bool addItem(T valor) {
        return inserirFinal(valor);
    }

    // Acessa item na posição i
    T& getItem(int i) {
        if (i < 0 || i > tamanho)
            throw "Índice fora do range";
        NoLUE<T>* aux = comeco;
        int idx = 0;
        while (aux != nullptr && idx < i) {
            aux = aux->elo;
            idx++;
        }
        return aux->info;
    }

    // Remove item na posição i (por índice)
    bool removeItem(int i) {
        if (i < 0 || i > tamanho || comeco == nullptr)
            return false;
        if (i == 0) {
            NoLUE<T>* temp = comeco;
            comeco = comeco->elo;
            if (comeco == nullptr)
                fim = nullptr;
            delete temp;
            tamanho--;
            return true;
        }
        NoLUE<T>* atual = comeco;
        NoLUE<T>* anterior = nullptr;
        int idx = 0;
        while (atual != nullptr && idx < i) {
            anterior = atual;
            atual = atual->elo;
            idx++;
        }
        if (atual == nullptr)
            return false;
        anterior->elo = atual->elo;
        if (atual == fim)
            fim = anterior;
        delete atual;
        tamanho--;
        return true;
    }

    // Busca por valor, retorna índice do primeiro igual
    int searchItem(T valor) {
        NoLUE<T>* aux = comeco;
        int idx = 0;
        while (aux != nullptr) {
            if (aux->info == valor) return idx;
            aux = aux->elo;
            idx++;
        }
        return -1;
    }

    // Procurar todos os índices de itens com o mesmo .valor do argumento
    Lista<int> procurarTrios(const T& item) {
        Lista<int> indices;
        NoLUE<T>* aux = comeco;
        int idx = 0;
        while (aux != nullptr) {
            if (aux->info.valor == item.valor) {
                indices.addItem(idx);
            }
            aux = aux->elo;
            idx++;
        }
        return indices;
    }

    // Exibe todos os itens
    void printItems() {
        NoLUE<T>* aux = comeco;
        while (aux != nullptr) {
            cout << aux->info << " ";
            aux = aux->elo;
        }
        cout << endl;
    }

    // Limpa a lista
    void clear() {
        liberar();
    }

    // Métodos originais e utilitários
    void inicializar() {
        comeco = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    bool inserirFinal(T valor) {
        NoLUE<T>* novo = new NoLUE<T>;
        if (novo == nullptr) return false;
        novo->info = valor;
        novo->elo = nullptr;
        if (comeco == nullptr) {
            comeco = novo;
            fim = novo;
        } else {
            fim->elo = novo;
            fim = novo;
        }
        tamanho++;
        return true;
    }

    bool inserirComeco(T valor) {
        NoLUE<T>* novo = new NoLUE<T>;
        if (novo == nullptr) return false;
        novo->info = valor;
        novo->elo = comeco;
        if (comeco == nullptr)
            fim = novo;
        comeco = novo;
        tamanho++;
        return true;
    }

    bool inserirOrdem(T valor) {
        NoLUE<T>* novo = new NoLUE<T>;
        if (novo == nullptr) return false;
        novo->info = valor;
        novo->elo = nullptr;
        if (comeco == nullptr) {
            comeco = novo;
            fim = novo;
            tamanho++;
            return true;
        }
        if (valor < comeco->info) {
            novo->elo = comeco;
            comeco = novo;
            tamanho++;
            return true;
        }
        if (valor > fim->info) {
            fim->elo = novo;
            fim = novo;
            tamanho++;
            return true;
        }
        NoLUE<T>* ant = comeco;
        NoLUE<T>* prox = ant->elo;
        while (prox != nullptr) {
            if (ant->info < valor && valor < prox->info) {
                ant->elo = novo;
                novo->elo = prox;
                tamanho++;
                return true;
            }
            ant = prox;
            prox = ant->elo;
        }
        return false;
    }

    NoLUE<T>* localizar(T valor) {
        NoLUE<T>* aux = comeco;
        while (aux != nullptr) {
            if (aux->info == valor) return aux;
            aux = aux->elo;
        }
        return nullptr;
    }

    bool retirar(T valor) {
        NoLUE<T>* ant = nullptr, *aux = comeco;
        while (aux != nullptr) {
            if (valor == aux->info) break;
            ant = aux;
            aux = aux->elo;
        }
        if (aux == nullptr) return false;
        if (aux == comeco && aux == fim) {
            comeco = nullptr;
            fim = nullptr;
            delete aux;
            tamanho--;
            return true;
        }
        if (aux == comeco) {
            comeco = aux->elo;
            delete aux;
            tamanho--;
            return true;
        }
        if (aux == fim) {
            ant->elo = nullptr;
            fim = ant;
            delete aux;
            tamanho--;
            return true;
        }
        ant->elo = aux->elo;
        delete aux;
        tamanho--;
        return true;
    }

    int comprimento() {
        return tamanho;
    }

    void liberar() {
        NoLUE<T>* aux = comeco;
        NoLUE<T>* prox;
        while (aux != nullptr) {
            prox = aux->elo;
            delete aux;
            aux = prox;
        }
        comeco = nullptr;
        fim = nullptr;
        tamanho = 0;
    }
};

#endif // LUE_PADRONIZADO_HPP