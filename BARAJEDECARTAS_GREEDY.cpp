/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Realizar un programa C++ que simule un baraje de cartas usando el paradigma de programacion greedy o Voraz.
 *  Autores (ID - Nombre):
 *  1107555 - Angel Soriano
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114290 - Angel Antonio Orona Pimentel
 *  1116252 - Radhames Ventura 
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  12/12/2023
 */



#include <iostream>
#include <list> 
#include <string>

using namespace std;

// Definición de la estructura Carta que tiene un número (NUM) y un palo (TIPO).
struct Carta {
    int TIPO;
    int NUM;
};

// Lista que contiene todas las cartas del mazo y la solución actual.
list<Carta> mazo, solucion;

// Función para imprimir una carta.
void ImprimirCarta(const Carta& c) {
    const char* nombresPalo[] = {"Espadas", "Tréboles", "Diamantes", "Corazones"};
    const char* numStr = (c.NUM == 1) ? "A" : (c.NUM == 11) ? "J" : (c.NUM == 12) ? "Q" : (c.NUM == 13) ? "K" : to_string(c.NUM).c_str();

    std::cout << " | " << numStr << " de " << nombresPalo[c.TIPO - 1] << " | ";
}


// Función para imprimir una lista de cartas.
void ImprimirLista(const list<Carta>& lista, string mensaje) {
    cout << mensaje;
    for (const auto& carta : lista) {
        ImprimirCarta(carta);
        cout << endl;
    }
    cout << endl << endl;

}

// Función para verificar si dos cartas son iguales.
bool SonIguales(const Carta& carta1, const Carta& carta2) {
    return carta1.NUM == carta2.NUM;
}

// Función para inicializar la lista de cartas con todas las cartas del mazo.
void InicializarMazo() {
    for (int i = 1; i <= 13; i++) {
        mazo.push_back({1, i});
        mazo.push_back({2, i});
        mazo.push_back({3, i});
        mazo.push_back({4, i});
    }

    ImprimirLista(mazo, "Mazo Inicial: ");
}

// Función para obtener los últimos n elementos de una lista.
list<Carta> ObtenerUltimasCartas(const list<Carta>& lista, int n) {
    if (n <= 0) {
        return {};
    }

    list<Carta> subconjunto;
    int tamañoLista = lista.size();
    int elementosAObtener = min(n, tamañoLista);

    auto it = lista.rbegin();
    for (int i = 0; i < elementosAObtener && it != lista.rend(); ++i, ++it) {
        subconjunto.push_back(*it);
    }

    return subconjunto;
}

// Función para realizar un movimiento irregular en la lista de cartas.
list<Carta> MoverCartasIrregularmente(const list<Carta>& lista) {
    int tamañoLista = lista.size();
    int mitad = tamañoLista / 2;

    auto itInicio = lista.begin();
    auto itMitad = lista.begin();
    advance(itMitad, mitad);

    list<Carta> listaIrregular;

    auto itPrimeraMitad = itInicio;
    auto itSegundaMitad = itMitad;

    while (itPrimeraMitad != itMitad || itSegundaMitad != lista.end()) {
        // Mover algunas cartas al final y otras al principio para distribuir irregularmente
        if (itSegundaMitad != lista.end()) {
            listaIrregular.push_back(*itSegundaMitad);
            ++itSegundaMitad;
        }

        if (itPrimeraMitad != itMitad) {
            listaIrregular.push_back(*itPrimeraMitad);
            ++itPrimeraMitad;
        }
    }

    return listaIrregular;
}

// Función objetivo: Maximizar el desorden penalizando la repetición cercana de números.
int EvaluarDesorden(const list<Carta>& solucionActual, const Carta& cartaSeleccionada) {
    int penalizacion = 0;
    list<Carta> UltimasCartas = ObtenerUltimasCartas(solucionActual, 6);

    for (const auto& carta : UltimasCartas) {
        if (SonIguales(carta, cartaSeleccionada)) {
            penalizacion++;
        }
    }

    return penalizacion;
}

// Función para seleccionar y agregar una carta a la solución.
void SeleccionarCarta() {
    Carta candidato = mazo.front();
    int penalizacion = EvaluarDesorden(solucion, candidato);

    if (penalizacion == 0) {
        solucion.push_back(candidato);
        ImprimirLista(solucion, "Solución Actual: \n");
        mazo.pop_front();
    } else {
        candidato = mazo.back();
        penalizacion = EvaluarDesorden(solucion, candidato);
        
        if (penalizacion == 0) {
            solucion.push_back(candidato);
            ImprimirLista(solucion, "Solución Actual: \n");
            mazo.pop_back();
        } else {
            mazo = MoverCartasIrregularmente(mazo);
            SeleccionarCarta();

        }
    }
    
    
}

// Función principal que inicializa las cartas y realiza la selección hasta tener 52 en la solución.
int main(){

    InicializarMazo();
        
    for (size_t i = 0; i < 3; i++)
    {
        mazo = MoverCartasIrregularmente(mazo);
    }
    while (solucion.size() < 52) 
    {
        SeleccionarCarta();
        ImprimirLista(mazo, "Restantes: \n");
    }

    return 0;
}
