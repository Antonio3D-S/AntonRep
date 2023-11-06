/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Realizar un programa C++ que realice una conversion de numero a texto usando un algoritmo de Divide y Venceras. 

 *  Autores (ID - Nombre):
 *  1113891 - Alan Arturo Sosa Del Villar
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114290 - Angel Antonio Orona Pimentel
 *  Radhames - Ventura 1116252
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  06/11/2023
 */

using namespace std;

#include <iostream>
#include <string>


bool EsNumeroValido(string str) {
    if (str.empty()) {
        return false;
    }

    try {
        double numero = stod(str);
        // Verificar si el número está dentro del rango deseado
        if (numero >= 0.0 && numero <= 999999999.99) {
            return true; // Si la conversión fue exitosa y está en el rango, es válido.
        } else {
            return false; // Si el número no está en el rango, no es válido.
        }
    } catch (const invalid_argument& e) {
        return false; // Si la conversión falla, no es un número decimal válido.
    }
}

int* DivisionDeTerminos(double num) {
    int* arreglo = new int[7]; // Asigna dinámicamente un arreglo de 7 enteros

    // Obtener la parte entera del número
    int parte_entera = static_cast<int>(num);

    // Obtener la parte decimal del número
    int parte_decimal_entera = ((num - parte_entera) * 100); // Multiplicar por 100 para obtener los centavos como número entero

    // Calcular la subdivisión
    arreglo[0] = (parte_entera / 100000000); // Centenas de millones
    arreglo[1] = (parte_entera % 100000000) / 1000000; // Decenas y unidades de millón
    arreglo[2] = ((parte_entera % 1000000) / 100000); // Centenas de miles
    arreglo[3] = (parte_entera % 100000) / 1000; // Decenas y unidades de miles
    arreglo[4] = (parte_entera / 100) % 10; // Centenas
    arreglo[5] = parte_entera % 100; // Decenas y unidades
    arreglo[6] = parte_decimal_entera; // Centavos como número entero

    return arreglo;
}

string CentenasEnTexto(int centena, bool cientos) 
{
    string unidades[] = {"", "Cien", "Doscientos", "Trescientos", "Cuatrocientos", "Quinientos", "Seiscientos", "Setecientos", "Ochocientos", "Novecientos"};
    if (cientos)
    {
    unidades[1] = "Ciento";
    }

    return unidades[centena];
}
//parametros: un_uno es para diferenciar si se usa UN en vez de UNO. el booleano CENT es solo para expresar CERO. Que es valido para los centimos.
string DecenasUnidadesEnTexto(int numero,bool un_uno, bool cent) {
    string unidades[] = {" ", "Uno", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve"};
    string especiales[] = {"Diez", "Once", "Doce", "Trece", "Catorce", "Quince", "Dieciséis", "Diecisiete", "Dieciocho", "Diecinueve"};
    string decenas[] = {"", "", "Veinti", "Treinta", "Cuarenta", "Cincuenta", "Sesenta", "Setenta", "Ochenta", "Noventa"};

    string texto;

    if(un_uno == true)
    {
        unidades[1] = "Un";
    }

    if (numero == 0 && cent == true) {
        texto = "Cero";
    } else if (numero < 10 && numero > 0) {
        texto = unidades[numero];
    } else if (numero < 20) {
        texto = especiales[numero - 10];
    } else {
        int decena = numero / 10;
        int unidad = numero % 10;

        if (decena == 2) {
            // Caso especial para "Veinti"
            if (unidad == 0) {
                texto = "Veinte";
            } else {
                texto = decenas[decena] + unidades[unidad];
            }
        } else if (unidad == 0) {
            texto = decenas[decena];
        } else {
            texto = decenas[decena] + " y " + unidades[unidad];
        }
    }

    return texto;
}

void finality(int* arr)
{
    string texto = "";

    if (arr[0] + arr[1] != 0)
    {
        texto += CentenasEnTexto(arr[0], arr[1] > 0) + " " + DecenasUnidadesEnTexto(arr[1], arr[0] == 0, false) + ((arr[0] == 0 && arr[1] == 1) ? " Millon " : " Millones ");
    } //cada if compone la estructura de unidades de centena y las decenas e unidades. 
        //El operador ? es ternario. Funciona como un IF resumido. En este caso verifica si solo hay una unidad en esta seccion. osea, UN MILLON.
        //Para diferenciar entre UN y UNO. se utiliza de referencia las centenas. Si existe un valor de centena, el parametro sera false y se colocara UNO. En el caso contrario se ocloca UN.
        //EJ: 101 = Ciento uno. 1,000,000 = UN MILLON.
        
    if (arr[2] + arr[3] != 0)
    {
        texto += CentenasEnTexto(arr[2], arr[3] > 0) + " ";
        
        texto += ((arr[2] == 0 && arr[3] == 1) ? "" : DecenasUnidadesEnTexto(arr[3], arr[2] > 0, false)) + " Mil ";
    }
    //En este caso si exite solo la unidad (1). El ternario va a omitir UN y UNO y solo colocara MIl para evitar la salida UN MIL,
    if (arr[4] + arr[5] != 0)
    {
        texto += CentenasEnTexto(arr[4], arr[5] > 0) + " " + DecenasUnidadesEnTexto(arr[5], (arr[4] == 0), false);
    }
    
    texto += " Pesos Dominicanos Con " + DecenasUnidadesEnTexto(arr[6], arr[6] == 1, true) + " Centimos ";

    cout << texto;
}
int main() 
{
    while (true) {
        double numero;
        string entrada;
        cout << "Ingresa un numero valido (o -1 para salir): ";
        getline(cin, entrada);

        if (entrada == "-1") {
            break;  // Salir del bucle si se ingresa -1
        }

        if (EsNumeroValido(entrada)) {
            numero = stod(entrada);
            int* resultado = DivisionDeTerminos(numero);

            cout << endl;
            finality(resultado);
            delete[] resultado;
        } else {
            cout << "No has ingresado un numero valido. Intentalo de nuevo." << endl;
        }

        cout << endl;
    }

    return 0;
}

