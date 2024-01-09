/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Realizar un programa C++ que simule el juego de N reinas.
 *  Donde se buscara la configuracion donde la cantidad N de reinas en un tablero no se elimine ninguna.
 *  Autores (ID - Nombre):
 *  1107555 - Angel Soriano
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114290 - Angel Antonio Orona Pimentel
 *  1116252 - Radhames Ventura 
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  08/01/2024
 */

#include <iostream>
#include <string>
#include <locale.h>
#include <math.h>
#include <vector>

int contadorSolucion;


using namespace std;


bool Entrada(string& entrada)
{
    for (char c : entrada)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

void ImprimirTablero(vector<vector<char>> tablero, int nReinas)
{    
    // Imprimir letras de columna encima de cada columna
    for (char letra = 'A'; letra < 'A' + nReinas; letra++)
    {
        cout << "   " << letra;
    }
    cout << endl;

            cout << " +";
        for (int i = 0; i < nReinas - 1; i++)
        {
            cout << "---+";
        }
        cout << "---+" << endl;

    // Imprimir el tablero
    for (int fila = 0; fila < nReinas; fila++)
    {
        // Imprimir número de fila
        cout << fila + 1 << "|";
        
        for (int columna = 0; columna < nReinas; columna++)
        {
            if (tablero[columna][fila] == 'Q')
                cout << " Q |";
            else
                cout << "   |";
        }
        cout << endl;

        // Imprimir la línea divisoria entre filas
        cout << " +";
        for (int i = 0; i < nReinas - 1; i++)
        {
            cout << "---+";
        }
        cout << "---+" << endl;
    }
}

bool ValidarMovimiento(int TablaReinas[], int nReinas, int profundidad)
{
    for (int i = 0; i < profundidad; i++)
    {
        if ((TablaReinas[i] == TablaReinas[profundidad]) || (abs(profundidad - i) == abs(TablaReinas[profundidad] - TablaReinas[i])))
        {
            return false;
        }
    }

    return true;
}

void jugadasReinas(int TablaReinas[], int nReinas, int profundidad)
{
    vector<vector<char>> tablero(nReinas, vector<char>(nReinas, '_')); 

    if (profundidad == nReinas) // Se ha encontrado la solución.
    {
        contadorSolucion++;
        cout << "Solución " << contadorSolucion << ": ";

        for (int columna = 0; columna < nReinas; columna++)
        {
            cout << TablaReinas[columna]+1 << " | ";
        }

        cout << endl<< endl;

        for (int columna = 0; columna < nReinas; columna++)
        {
            tablero[columna][TablaReinas[columna]] = 'Q';
        }

        ImprimirTablero(tablero, nReinas);
        cout << endl;
    }
    else
     // Quedan Reinas por Colocar.
    {
        for (TablaReinas[profundidad] = 0; TablaReinas[profundidad] < nReinas; TablaReinas[profundidad]++)
        {
            if (ValidarMovimiento(TablaReinas, nReinas, profundidad))
            {
                jugadasReinas(TablaReinas, nReinas, profundidad + 1);
            }
        }
    }
}

int main()
{
    string nReinasString;
    int profundidad = 0;

    cout << "+---------------- Juego de las N Reinas ----------------+\n\n";

    do
    {
        cout << "Ingrese la cantidad de reinas a colocar: ";
        cin >> nReinasString;

        if (Entrada(nReinasString))
        {
            cout << "\nBuscando Soluciones para " << nReinasString << " reinas:\n\n";

            int nReinasInt = stoi(nReinasString);
            int* reinasArray = new int[nReinasInt];

            for (int columna = 0; columna < nReinasInt; columna++)
            {
                reinasArray[columna] = -1;
            }

            jugadasReinas(reinasArray, nReinasInt, profundidad);
        }
        else
        {
            cout << "\n¡Valor Inválido! Por favor, ingrese un número entero positivo.\n\n";
        }

    } while (!Entrada(nReinasString));

    return 0;
}
