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
 *  14/12/2023
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>  // Necesario para setw


using namespace std;


struct Carta {
    int TIPO;
    int NUM;
};

const int k = 6;
const int totalCartas = 52;
const int totalPalo = 13;

// Función para imprimir una carta con delimitadores alineados.
void ImprimirCarta(const Carta& c, int ancho) {
    const char* nombresPalo[] = {"Espadas", "Treboles", "Diamantes", "Corazones"};
    const char* numStr = (c.NUM == 1) ? "A" : (c.NUM == 11) ? "J" : (c.NUM == 12) ? "Q" : (c.NUM == 13) ? "K" : to_string(c.NUM).c_str();

    // Imprimir con delimitadores alineados
    cout << " | " << setw(ancho/2) << left << numStr << " de " << setw(ancho) << left << nombresPalo[c.TIPO - 1] << " | ";
}
// Función para imprimir un vector de cartas.
void ImprimirVector(const vector<Carta>& vector, string mensaje) {
    cout << mensaje << endl;
    for (const auto& carta : vector) {
        ImprimirCarta(carta,10);
        cout << endl;
    }
    cout << endl << endl;
}


vector<Carta> Obtener(const vector<Carta>& vectorial, size_t n) {
    vector<Carta> vect;
    // Obtén el tamaño máximo del vector
    size_t maxSize = vectorial.size();


    // Asegúrate de que n no sea mayor que el tamaño máximo del vector
    n = min(n, maxSize);

    //Recorre desde el punto elegido hasta el final. En pocas palabras, de 14 a 20 por ejemplo.
    for (size_t i = maxSize - n; i < maxSize; ++i) {
        vect.push_back(vectorial[i]);
    }


    return vect;
}

//METODO PARA ASEGURAR LA DIFERENCIA DE 6 PASOS.
bool Evaluar(const vector<Carta>& solucionActual, const Carta& cartaSeleccionada) {

    //Obtiene el valor menor posible si es el caso. Esto es util cuando en solucion hay menos de 6 cartas
    vector<Carta> ultimasCartas = Obtener(solucionActual, k);
    

     //Se usa any_of para encontrar cualquer coincidencia dentro del rango de cartas. Retornando un True o False.
     // Esta función se utiliza para determinar si algún elemento de un rango satisface cierta condición.
     //La condicion es un valor donde el campo NUM sea igual a la carta seleccionada.
    return any_of(ultimasCartas.begin(), ultimasCartas.end(), [&](const Carta& carta) {
          return carta.NUM == cartaSeleccionada.NUM;
    });
}
vector<Carta> DesordenarCartas(const vector<Carta>& cartasOrdenadas) {
    vector<Carta> solucion;
    solucion.reserve(cartasOrdenadas.size()); //Se reserva espacio en la memoria igual al tamaño de las cartas. 


    vector<Carta> cartasShuffle = cartasOrdenadas;  // Crear una copia para hacer shuffle


    random_device rd;
    mt19937 gen(rd());


    for (const auto& carta : cartasOrdenadas) { //Usar cartasOrdenadas porque los demas vectores varian de tamaño
        // Barajar las cartas
        shuffle(cartasShuffle.begin(), cartasShuffle.end(), gen);


        // Seleccionar la primera carta válida y añadirla a solucion
        //FIND_IF encuentra el primer elemento del shuffle que cumple con la condicion. usa const Carta& c como elemento guia. Pasa por referencia [&].
        //Usa la estructura de datos auto. que obtiene un iterador vector carta.
        auto it = find_if(cartasShuffle.begin(), cartasShuffle.end(), [&](const Carta& c) 
        { //El uso de auto es necesario para el find_if ya que la funcion devuelve un vector<Carta>::iterator.
            return !Evaluar(solucion, c);
        });

        /*verifica si el iterador it no apunta al final del vector cartasShuffle.
        Si it no es igual a cartasShuffle.end(), significa que se encontró una carta que cumple con la condición establecida por el find_if.
        si auto it retorna el final de cartasshuffle( cartasshuffle.end()), significa que returno un elemento inexistente. 
 */
       if (it != cartasShuffle.end()) {
            solucion.push_back(*it);
            cartasShuffle.erase(it);  // Eliminar la carta seleccionada de cartasShuffle
        }
    }


    return solucion;
}




//// Función para inicializar el vector de cartas con todas las cartas del mazo.
void InicializarMazo(vector<Carta>& mazo) {
    for (int i = 1; i <= totalPalo; i++) {
        mazo.push_back({1, i});
        mazo.push_back({2, i});
        mazo.push_back({3, i});
        mazo.push_back({4, i});
    }
}


// Función para reiniciar el juego.
void IniciarJuego() {
    vector<Carta> cartasOrdenadas;


    // Inicializar cartasOrdenadas con todas las cartas del mazo
    InicializarMazo(cartasOrdenadas);


    char opcion;
    do {
        // Desordenar cartas y mostrar resultados
        vector<Carta> cartasDesordenadas = DesordenarCartas(cartasOrdenadas);


        // Imprimir cartas ordenadas
        ImprimirVector(cartasOrdenadas, "Cartas Ordenadas:");


        // Imprimir cartas desordenadas
        ImprimirVector(cartasDesordenadas, "Cartas Desordenadas:");


        // Preguntar al jugador si desea seguir barajando
        cout << "¿Quieres seguir barajando? (Y para continuar, otro caracter para terminar el juego): ";
        cin >> opcion;


        // Limpiar la pantalla antes de la siguiente jugada
        system("cls || clear");


    } while (toupper(opcion) == 'Y');
}


int main() {
   
    IniciarJuego();


    return 0;
}




