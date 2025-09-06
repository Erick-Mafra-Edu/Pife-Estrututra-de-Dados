#ifndef LDE_PADRONIZADO_HPP
#define LDE_PADRONIZADO_HPP

#include <iostream>
using namespace std;

template <typename T>
struct NoLDE {
    T info;
    NoLDE<T>* eloA;
    NoLDE<T>* eloP;
};

template <typename T>
struct Lista {
    NoLDE<T>* comeco = nullptr;
    NoLDE<T>* fim = nullptr;
    int tamanho = -1;

    // Acesso indexado (referência)
    T& operator[](int i) {
        return getItem(i);
    }

    // Adiciona no final
    bool addItem(T valor) {
        return inserirFinal(valor);
    }
    bool vazia() {
        return (tamanho == -1);
    }
    // Acessa item na posição i
    T& getItem(int i) {
        if (i < 0 || i > tamanho)
            throw "Índice fora do range";
        NoLDE<T>* aux = comeco;
        int idx = 0;
        while (aux != nullptr && idx < i) {
            aux = aux->eloP;
            idx++;
        }
        return aux->info;
    }

    // Remove item na posição i (por índice)
    bool removeItem(int i) {
        if (i < 0 || i > tamanho || comeco == nullptr)
            return false;

        NoLDE<T>* atual = comeco;
        int idx = 0;
        while (atual != nullptr && idx < i) {
            atual = atual->eloP;
            idx++;
        }
        if (atual == nullptr)
            return false;

        if (atual == comeco && atual == fim) { // Único elemento
            comeco = nullptr;
            fim = nullptr;
        } else if (atual == comeco) { // Primeiro elemento
            comeco = atual->eloP;
            comeco->eloA = nullptr;
        } else if (atual == fim) { // Último elemento
            fim = atual->eloA;
            fim->eloP = nullptr;
        } else { // Elemento do meio
            atual->eloA->eloP = atual->eloP;
            atual->eloP->eloA = atual->eloA;
        }
        delete atual;
        tamanho--;
        return true;
    }

    // Busca por valor, retorna índice do primeiro igual
    int searchItem(T valor) {
        NoLDE<T>* aux = comeco;
        int idx = 0;
        while (aux != nullptr) {
            if (aux->info == valor) return idx;
            aux = aux->eloP;
            idx++;
        }
        return -1;
    }

    // Procurar todos os índices de itens com o mesmo .valor do argumento
    Lista<int> procurarTrios(const T& item) {
        Lista<int> indices;
        NoLDE<T>* aux = comeco;
        int idx = 0;
        while (aux != nullptr) {
            if (aux->info.valor == item.valor) {
                indices.addItem(idx);
            }
            aux = aux->eloP;
            idx++;
        }
        return indices;
    }

    // Exibe todos os itens
    void printItems() {
        NoLDE<T>* aux = comeco;
        while (aux != nullptr) {
            cout << aux->info << " ";
            aux = aux->eloP;
        }
        cout << endl;
    }

    // Limpa a lista
    void clear() {
        liberar();
    }

    // Métodos utilitários e originais
    bool inserirFinal(T valor) {
        NoLDE<T>* novo = new NoLDE<T>;
        if (novo == nullptr) return false;
        novo->info = valor;
        novo->eloA = nullptr;
        novo->eloP = nullptr;
        if (comeco == nullptr) {
            comeco = novo;
            fim = novo;
        } else {
            fim->eloP = novo;
            novo->eloA = fim;
            fim = novo;
        }
        tamanho++;
        return true;
    }

    bool inserirComeco(T valor) {
        NoLDE<T>* novo = new NoLDE<T>;
        if (novo == nullptr) return false;
        novo->info = valor;
        novo->eloA = nullptr;
        novo->eloP = comeco;
        if (comeco == nullptr) {
            fim = novo;
        } else {
            comeco->eloA = novo;
        }
        comeco = novo;
        tamanho++;
        return true;
    }

    bool inserirOrdem(T valor) {
        NoLDE<T>* novo = new NoLDE<T>;
        if (novo == nullptr) return false;
        novo->info = valor;
        novo->eloA = nullptr;
        novo->eloP = nullptr;
        if (comeco == nullptr) {
            comeco = novo;
            fim = novo;
            tamanho++;
            return true;
        }
        if (valor < comeco->info) {
            novo->eloP = comeco;
            comeco->eloA = novo;
            comeco = novo;
            tamanho++;
            return true;
        }
        if (valor > fim->info) {
            fim->eloP = novo;
            novo->eloA = fim;
            fim = novo;
            tamanho++;
            return true;
        }
        NoLDE<T>* ant = comeco;
        NoLDE<T>* prox = ant->eloP;
        while (prox != nullptr) {
            if (ant->info < valor && valor < prox->info) {
                ant->eloP = novo;
                novo->eloA = ant;
                prox->eloA = novo;
                novo->eloP = prox;
                tamanho++;
                return true;
            }
            ant = prox;
            prox = ant->eloP;
        }
        return false;
    }

    NoLDE<T>* localizar(T valor) {
        NoLDE<T>* aux = comeco;
        while (aux != nullptr) {
            if (aux->info == valor) return aux;
            aux = aux->eloP;
        }
        return nullptr;
    }

    bool retirar(T valor) {
        NoLDE<T>* aux = localizar(valor);
        if (aux == nullptr) return false;
        if (aux == comeco && aux == fim) {
            comeco = nullptr;
            fim = nullptr;
            delete aux;
            tamanho--;
            return true;
        }
        if (aux == comeco) {
            comeco = aux->eloP;
            comeco->eloA = nullptr;
            delete aux;
            tamanho--;
            return true;
        }
        NoLDE<T>* ant = aux->eloA;
        if (aux == fim) {
            ant->eloP = nullptr;
            fim = ant;
            delete aux;
            tamanho--;
            return true;
        }
        NoLDE<T>* prox = aux->eloP;
        ant->eloP = prox;
        prox->eloA = ant;
        delete aux;
        tamanho--;
        return true;
    }

    int comprimento() {
        return tamanho;
    }

    void liberar() {
        NoLDE<T>* aux = comeco;
        NoLDE<T>* prox;
        while (aux != nullptr) {
            prox = aux->eloP;
            delete aux;
            aux = prox;
        }
        comeco = nullptr;
        fim = nullptr;
        tamanho = -1;
    }


};

#endif // LDE_PADRONIZADO_HPP