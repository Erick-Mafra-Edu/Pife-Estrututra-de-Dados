#ifndef LUE_HPP
#define LUE_HPP

#include <iostream>
using namespace std;

template <typename T>
struct NoLUE{
    T info;
    NoLUE <T> *elo;
};

template <typename T>
struct LUE{
    NoLUE <T> *comeco, *fim;

    // Operador []
    T& operator[](int i) {
        NoLUE<T>* aux = comeco;
        int idx = 0;
        while (aux != NULL && idx < i) {
            aux = aux->elo;
            idx++;
        }
        if (aux == NULL) throw std::out_of_range("Index out of range");
        // cout << aux->info << endl;
        return aux->info;
    }

    // Inicializar
    void inicializar(){
        comeco = NULL;
        fim = NULL;
    }

    // Inserir no final
    bool inserirFinal(T valor){
        NoLUE <T> *novo = new NoLUE <T>;
        if(novo == NULL) return false;

        novo->info = valor;
        novo->elo = NULL;

        if(comeco == NULL){ // Lista está vazia
            comeco = novo;
            fim = novo;
        }
        else{
            fim->elo = novo;
            fim = novo;
        }
        return true;
    }

    // Mostrar
    void mostrar(){
        NoLUE <T> *aux = comeco;
        while(aux != NULL){
            cout << aux->info << " ";
            aux = aux->elo;
        }
    }

    // Inserir ordenado
    bool inserirOrdem(T valor){
        NoLUE <T> *novo = new NoLUE<T>;
        if(novo == NULL) return false;

        novo->info = valor;
        novo->elo = NULL;

        if(comeco == NULL){ // Lista vazia
            comeco = novo;
            fim = novo;
            return true;
        }
        if(valor < comeco->info){ // Inserção no começo
            novo->elo = comeco;
            comeco = novo;
            return true;
        }
        if(valor > fim->info){ // Inserção no final
            fim->elo = novo;
            fim = novo;
            return true;
        }
        // Inserção no meio da lista
        NoLUE <T> *ant = comeco;
        NoLUE <T> *prox = ant->elo;
        while(prox != NULL){
            if(ant->info < valor && valor < prox->info){
                ant->elo = novo;
                novo->elo = prox;
                return true;
            }
            ant = prox;
            prox = ant->elo;
        }
        return false;
    }
    // Inserir no começo
    bool inserirComeco(T valor) {
        NoLUE<T> *novo = new NoLUE<T>;
        if (novo == NULL) return false;

        novo->info = valor;
        novo->elo = comeco;

        if (comeco == NULL) { // Lista vazia
            fim = novo;
        }
        comeco = novo;
        return true;
    }
    // Localizar
    NoLUE <T> * localizar(T valor){
        NoLUE <T> *aux = comeco;
        while(aux != NULL){
            if(aux->info == valor) return aux;
            aux = aux->elo;
        }
        return NULL;
    }

    // Retirar
    bool retirar(T valor){
        NoLUE <T> *ant = NULL, *aux = comeco;

        while(aux != NULL){
            if(valor == aux->info) break;
            ant = aux;
            aux = aux->elo;
        }
        if(aux == NULL) return false;

        if(aux == comeco && aux == fim){ // Unico elemento
            comeco = NULL;
            fim = NULL;
            delete aux;
            return true;
        }
        if(aux == comeco){ // Retirando o primeiro
            comeco = aux->elo;
            delete aux;
            return true;
        }
        if(aux == fim){ // Retirando o ultimo
            ant->elo = NULL;
            fim = ant;
            delete aux;
            return true;
        }
        // Retirando do meio
        ant->elo = aux->elo;
        delete aux;
        return true;
    }

    // Liberar
    void liberar(){
        NoLUE <T> *aux = comeco;
        NoLUE <T> *prox;

        while(aux != NULL){
            prox = aux->elo;
            delete aux;
            aux = prox;
        }
        comeco = NULL;
        fim = NULL;
    }
};

#endif // LUE_HPP