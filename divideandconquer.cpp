using namespace std;

#include <iostream>
#include <string>


bool EsNumeroValido(string str) {
    if (str.empty() ) {
        return false;
    }

    try {
        double numero = stod(str);
        return true; // Si la conversión fue exitosa, es un número decimal válido.
    }
    catch (const invalid_argument& e) 
    {
        return false; // Si la conversión falla, no es un número decimal válido.
    }
}
int* obtenerprimerasubdivision(double num) {
    int* arreglo = new int[7]; // Asigna dinámicamente un arreglo de 7 enteros

    // Obtener la parte entera del número
    int parte_entera = static_cast<int>(num);

    // Obtener la parte decimal del número
    double parte_decimal = num - parte_entera;

    // Calcular la subdivisión
    arreglo[0] = (parte_entera / 100000000) ; // Centenas de millones
    arreglo[1] = (parte_entera % 100000000) / 1000000; // Decenas y unidades de millón
    arreglo[2] = ((parte_entera % 1000000) / 100000 ); // Centenas de miles
    arreglo[3] = (parte_entera % 100000) / 1000; // Decenas y unidades de miles
    arreglo[4] = (parte_entera / 100) % 10; // Centenas
    arreglo[5] = parte_entera % 100; // Decenas y unidades
    arreglo[6] = parte_decimal * 100; // Decimales
    return arreglo;
}

string CentenasEnTexto(int centena) 
{
    string unidades[] = {"Cero", "Cien", "Doscientos", "Trescientos", "Cuatrocientos", "Quinientos", "Seiscientos", "Setecientos", "Ochocientos", "Novecientos"};

    return unidades[centena];
}

string DecenasUnidadesEnTexto(int numero) {
    string unidades[] = {"Cero", "Uno", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve"};
    string especiales[] = {"Diez", "Once", "Doce", "Trece", "Catorce", "Quince", "Dieciséis", "Diecisiete", "Dieciocho", "Diecinueve"};
    string decenas[] = {"", "", "Veinti", "Treinta", "Cuarenta", "Cincuenta", "Sesenta", "Setenta", "Ochenta", "Noventa"};

    string texto;

    if (numero == 0) {
        texto = "Cero";
    } else if (numero < 10) {
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
    string texto;
    string nomenclatura[] = {" Millones ", " mil "," Pesos dominicanos con ", " Centimos "};

    for (size_t i = 0; i < 7; i++)
    {
        if(arr[i] == 0 && i != 6)
        {
            continue;
        }
        else
        {
            if(i % 2 == 0 && i < 6)
            {
                texto += CentenasEnTexto(arr[i]);
                if (arr[i] == 1 && arr[i+1] != 0)
                {
                    texto += "to";
                }
                
            }
            else
            {
                texto += DecenasUnidadesEnTexto(arr[i]);
            }

            if (i == 1)
            {
                texto += nomenclatura[0];
            }
            else if (i == 3)
            {
                texto += nomenclatura[1];

            }
            else if (i == 5)
            {
                texto += nomenclatura[2];
            }
            
            else if(i == 6)
            {
                texto += nomenclatura[3] + " ";

            }
            else
            {            
                texto += " ";

            }
            
            
        }
    }

    cout << texto;
    
}

int main() {
    double numero;
    string entrada;
    bool invalido = true;

    while (invalido) {
        cout << "Ingresa un número válido: ";   
        cin >> entrada;

        if (EsNumeroValido(entrada)) {
            numero = stod(entrada);
            break;
        } else {
            cout << "No has ingresado un número válido. Inténtalo de nuevo." << endl;
        }
    }


    int* resultado = obtenerprimerasubdivision(numero);


    for (size_t i = 0; i < 7; i++)
    {
        cout << resultado[i] << " ";
    }
    
    cout << endl;

    finality(resultado);

    delete[] resultado;

    return 0;
}


