#include <iostream>
#include <list>
#include <algorithm>
#include <random>

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
    const char* simbolosPalo[] = {"♠", "♣", "♦", "♥"};
    const char* numStr = (c.NUM == 11) ? "J" : (c.NUM == 12) ? "Q" : (c.NUM == 13) ? "K" : to_string(c.NUM).c_str();

    cout << " | " << numStr << simbolosPalo[c.TIPO - 1] << " | ";
}

// Función para imprimir una lista de cartas.
void ImprimirLista(const list<Carta>& lista, string mensaje) {
    cout << mensaje;
    for (const auto& carta : lista) {
        ImprimirCarta(carta);
    }
    cout << endl;
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

        if (itSegundaMitad != lista.end()) {
            listaIrregular.push_back(*itSegundaMitad);
            ++itSegundaMitad;
        }
    }

    return listaIrregular;
}

// Función para verificar cuántas veces una carta se repite en un conjunto de cartas.
int ContarRepeticiones(const list<Carta>& conjunto, const Carta& cartaSeleccionada) {
    int repeticiones = 0;
    for (const auto& carta : conjunto) {
        if (SonIguales(carta, cartaSeleccionada)) {
            repeticiones++;
        }
    }
    return repeticiones;
}

// Función objetivo: Maximizar el desorden penalizando la repetición cercana de números.
int EvaluarDesorden(const list<Carta>& solucionActual, const Carta& cartaSeleccionada) {
    int penalizacion = 0;
    list<Carta> ultimasCuatroCartas = ObtenerUltimasCartas(solucionActual, 4);

    for (const auto& carta : ultimasCuatroCartas) {
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
        ImprimirLista(solucion, "Solución Actual: ");
        mazo.pop_front();
    } else {
        mazo = MoverCartasIrregularmente(mazo);
    }
}
bool EsNumeroValido(string str) {
    bool valido = true;

    if (str.empty()) {
        return false;
    }

    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return valido;
}

string IngresarNumeroValido() {
    string entrada;
    bool valido = false;

    while (!valido) {
        cout << "Ingrese un número válido: ";
        cin >> entrada;

        if (EsNumeroValido(entrada)) {
            valido = true;
        } else {
            cout << "Entrada no válida. Por favor, ingrese un número válido." << endl;
        }
    }

    return entrada;
    }

void Movimientos_Iniciales()
{ 

string entrada = IngresarNumeroValido();

int movimientos = stoi(entrada);

for (size_t i = 0; i < movimientos; i++)
{
    mazo = MoverCartasIrregularmente(mazo);
}


}

// Función principal que inicializa las cartas y realiza la selección hasta tener 52 en la solución.
int main() {
    InicializarMazo();

    Movimientos_Iniciales();

    while (solucion.size() < 52) {
        SeleccionarCarta();
    }

    return 0;
}
