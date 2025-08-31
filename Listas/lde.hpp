#ifndef LDE_HPP
#define LDE_HPP

#include <iostream>
using namespace std;

template <typename T>
struct NoLDE{
    T info;
    NoLDE <T> *eloA, *eloP;
};

template <typename T>
struct LDE{
    NoLDE <T> *comeco = NULL, *fim = NULL;
    T operator[](int i) {
        return getItem(i);
    }

    bool inserirFinal(T valor) {
        NoLDE <T> *novo = new NoLDE <T>;
        if(novo == NULL) return false;

        novo->info = valor;
        novo->eloA = NULL;
        novo->eloP = NULL;

        if(comeco == NULL) { // Lista está vazia
            comeco = novo;
            fim = novo;
        }
        else{
            fim->eloP = novo;
            novo->eloA = fim;
            fim = novo;
        }
        return true;
    }

    void mostrar(char sentido='C') {
        NoLDE <T> *aux = (sentido=='C') ? comeco : fim;

        while(aux != NULL) {
            cout << aux->info << " ";
            aux = (sentido=='C') ? aux->eloP : aux->eloA;
        }
    }

    bool inserir(T valor) {
        NoLDE <T> *novo = new NoLDE<T>;
        if(novo == NULL) return false;

        novo->info = valor;
        novo->eloA = NULL;
        novo->eloP = NULL;

        if(comeco == NULL) { // Lista vazia
            comeco = novo;
            fim = novo;
            return true;
        }
        if(valor < comeco->info) { // Inserção no começo
            novo->eloP = comeco;
            comeco->eloA = novo;
            comeco = novo;
            return true;
        }
        if(valor > fim->info) { // Inserção no final
            fim->eloP = novo;
            novo->eloA = fim;
            fim = novo;
            return true;
        }
        // Inserção no meio da lista
        NoLDE <T> *ant = comeco;
        NoLDE <T> *prox = ant->eloP;
        while(prox != NULL) {
            if(ant->info < valor && valor < prox->info) {
                ant->eloP = novo;
                novo->eloA = ant;
                prox->eloA = novo;
                novo->eloP = prox;
                return true;
            }
            ant = prox;
            prox = ant->eloP;
        }
        return false;
    }

    T getItem(int i) {
        NoLDE<T> *aux = comeco;
        int idx = 0;
        while(aux != NULL && idx < i) {
            aux = aux->eloP;
            idx++;
        }
        if(aux == NULL || i < 0)
            throw "voce ta consultando fora do range";
        return aux->info;
    }

    NoLDE <T> * localizar(T valor) {
        NoLDE <T> *aux = comeco;

        while(aux != NULL) {
            if(aux->info == valor) return aux;
            aux = aux->eloP;
        }
        return NULL;
    }

    bool retirar(T valor) {
        NoLDE <T> *aux = localizar(valor);
        if(aux == NULL) return false;

        if(aux == comeco && aux == fim) { // Unico elemento
            comeco = NULL;
            fim = NULL;
            delete aux;
            return true;
        }
        if(aux == comeco) { // Retirando o primeiro
            comeco = aux->eloP;
            comeco->eloA = NULL;
            delete aux;
            return true;
        }

        NoLDE <T> *ant = aux->eloA;
        if(aux == fim) { // Retirando o ultimo
            ant->eloP = NULL;
            fim = ant;
            delete aux;
            return true;
        }
        // Retirando do meio
        NoLDE <T> *prox = aux->eloP;
        ant->eloP = prox;
        prox->eloA = ant;
        delete aux;
        return true;
    }

    void liberar() {
        NoLDE <T> *aux = comeco;
        NoLDE <T> *prox;

        while(aux != NULL) {
            prox = aux->eloP;
            delete aux;
            aux = prox;
        }
        comeco = NULL;
        fim = NULL;
    }

    // // Destrutor
    // ~LDE() {
    //     liberar();
    // }
};

#endif // LDE_HPP