#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class Dado
{
    public:
        int tirar();
};

int Dado::tirar()
{
    srand(time(NULL));

    int aleatorio = rand() % 6;

    return aleatorio + 1;
}

class Casilla
{
    private:
        int cant_piezas;
        int cuadrante;
        string color_pieza;

    public:
        Casilla() = default;
        Casilla(int, int, string);
        int getCant();
        int getCuadrante();
        string getColor();
};

Casilla::Casilla(int _cant, int _cuadrante, string _color)
{
    this->cant_piezas = _cant;
    this->cuadrante = _cuadrante;
    this->color_pieza = _color;
}

int Casilla::getCant()
{
    return this->cant_piezas;
}

int Casilla::getCuadrante()
{
    return this->cuadrante;
}

string Casilla::getColor()
{
    return this->color_pieza;
}

class Tablero
{
    private:
        int n_comidas;
        int b_comidas;
        int n_fuera;
        int b_fuera;
        Casilla casillas[24];

    public:
        Tablero(Casilla[]);
        Casilla getCasilla(int);
        int get_n_comidas();
};

Casilla Tablero::getCasilla(int i)
{
    return this->casillas[i];
}

int Tablero::get_n_comidas()
{
    return this->n_comidas;
}

Tablero::Tablero(Casilla _casillas[])
{
    this->n_comidas = 0;
    this->b_comidas = 0;
    this->n_fuera = 0;
    this->b_fuera = 0;

    for (int i = 0; i < 24; i++)
    {

        this->casillas[i] = _casillas[i];
    }
}


// Funciones

Tablero inicializarTablero(){

    int *cants = new int[24];
    cants[0] = 2;
    cants[5] = 5;
    cants[9] = 3;
    cants[11] = 5;
    cants[12] = 5;
    cants[14] = 3;
    cants[18] = 5;
    cants[23] = 2;

    string *colores = new string[24];
    colores[0] = "X";
    colores[5] = "O";
    colores[9] = "O";
    colores[11] = "X";
    colores[12] = "O";
    colores[14] = "X";
    colores[18] = "X";
    colores[23] = "O";

    int cuadrante = 0;

    Casilla casillas[24];

    for (int i = 0; i < 24; i++)
    {
        if (cants[i] < 1)
        {
            cants[i] = 0;
            colores[i] = "vacio";
        }

        
        if (i % 6 == 0)
        {
            cuadrante++;
        }

        casillas[i] = Casilla(cants[i], cuadrante, colores[i]);
    }

    delete[] colores;
    delete[] cants;

    return Tablero(casillas);

}

void imprimirTablero(Tablero tablero)
{
    for (int i = 0; i < 24; i++)
    {
        if (i < 9) { 
            cout <<" "; 
        }
        cout << i + 1 << " | ";

        int c = tablero.getCasilla(i).getCant();

        for (int j = 0; j < c; j++)
        {
            cout << tablero.getCasilla(i).getColor();
        }

        for (int q = 0; q < 5-c; q++)
        {
            cout <<"-";
        }

        cout << endl;
    }
}

void bienvenida()
{
    cout <<"--------------------------------\n";
    cout <<"  Bienvenido a Backgammon!\n";
    cout <<"--------------------------------\n\n";

    system("pause");
    system("cls");

}


// bool validarMovimiento(Tablero tablero, int movs, int origen, string turno)
// {
//     // Casilla destino = tablero.getCasilla(origen);

//     // return true;
//     return 1;

// }

void pedirMovimiento(string turno, Tablero tablero)
{
    system("pause");
    system("cls");

    imprimirTablero(tablero);

    int origen = 0, cant = 0;
    Dado dado = Dado();

    int d1 = dado.tirar();
    int d2 = dado.tirar();
    
    int movs[] = {d1,d2,d1+d2};

    do
    {
        cout << "\nSeleccionar la cantidad de casillas a mover\n";
        cout << "1. Dado 1 : " << d1<<endl;
        cout << "2. Dado 2 : " << d2<<endl;
        cout << "3. Ambos  : " << d1 + d2<<endl;
        cout << "opc > "; cin >> cant; cout << endl;
    }while(cant > 3 || cant < 1);


    cout << "Seleccione la casilla de la ficha que desea mover\n> ";
    cin >> origen;

    // validarMovimiento(tablero, movs[cant-1], origen, turno);

}

int main()
{
    bool salir = false;
    string turno = "X";

    
    Tablero tablero = inicializarTablero();

    // bienvenida();

    imprimirTablero(tablero);

    cout << tablero.getCasilla(9).getColor();

    // do
    // {
    //     imprimirTablero(tablero);

    //     cout << "\nTurno : " << turno <<"\n\n";

    //     cout << "Desea tirar los dados?\n1. Tirar\n2. Abandonar\n> ";
    //     int opc;
    //     cin >> opc;

    //     switch (opc)
    //     {
    //         case 1:
                
    //             pedirMovimiento(turno, tablero);





    //         case 2:
    //             exit(0);
    //     }



    //     if (turno == "X")
    //     {
    //         turno = "O";
    //     } else {
    //         turno = "X";
    //     }

    //     system ("pause");
    //     system ("cls");

    // } while (!salir);
    

    

    

    system("pause");
    return 0;
}