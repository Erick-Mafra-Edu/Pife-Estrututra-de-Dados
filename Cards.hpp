#ifndef CARDS_HPP
#define CARDS_HPP

#include <iostream>
#include <string>
using namespace std;

// enum naipe {OURO = '♦', ESPADA = '♠', COPAS = '♥', PAUS = '♣'};
enum Naipe {OUROS, ESPADAS, COPAS, PAUS};
string nomeNaipe[4] = {"♦","♠","♥","♣"}; 
string nomeValor[14] = {"A","1","2","3","4","5","6","7","8","9","10","J","Q","K"};

struct Carta
{
    Naipe naipe; // ♦  ♠  ♥  ♣
    string valor; // A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
    // exibição == A♦, J♠, 3♥, K♣.
    friend ostream& operator<<(ostream& os, const Carta& carta) {
        os << carta.valor << nomeNaipe[carta.naipe];
        return os;
    }
    bool operator==(const Carta& other) const {
        return naipe == other.naipe && valor == other.valor;
    }

};
#endif // CARDS_HPP