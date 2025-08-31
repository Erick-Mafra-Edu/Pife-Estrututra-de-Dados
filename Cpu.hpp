#include "./Listas/listaestatica.hpp"
#include "./cards.hpp"
struct Cpu
{
    int id = 0;
    int pontos = 0;
    ListaEstatica<Carta> mao = {};
    ListaEstatica<Carta> cartasJogadas = {};
    void adquirirCarta(Carta& carta)
    {
        mao.addItem(carta);
    }
};