#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <math.h>

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
    int o_comidas;
    int x_comidas;
    int o_fuera;
    int x_fuera;
    Casilla casillas[24];

public:
    Tablero(Casilla[]);
    Casilla getCasilla(int);
    int get_x_comidas();
    int get_o_comidas();
};

Casilla Tablero::getCasilla(int i)
{
    return this->casillas[i];
}

int Tablero::get_x_comidas()
{
    return this->x_comidas;
}

int Tablero::get_o_comidas()
{
    return this->o_comidas;
}

Tablero::Tablero(Casilla _casillas[])
{
    this->x_comidas = 0;
    this->o_comidas = 0;
    this->x_fuera = 0;
    this->o_fuera = 0;

    for (int i = 0; i < 24; i++)
    {

        this->casillas[i] = _casillas[i];
    }
}

// Funciones

Tablero inicializarTablero()
{

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
        if (i < 9)
        {
            cout << " ";
        }
        cout << i + 1 << " | ";

        int c = tablero.getCasilla(i).getCant();

        for (int j = 0; j < c; j++)
        {
            cout << tablero.getCasilla(i).getColor();
        }

        for (int q = 0; q < 5 - c; q++)
        {
            cout << "-";
        }

        cout << endl;
    }

    cout << "\nPiezas comidas:\n";
    cout << "25 | blancas (X) > " << tablero.get_x_comidas() << endl;
    cout << "26 | negras  (O) > " << tablero.get_o_comidas() << endl;
}

void bienvenida()
{
    cout << "--------------------------------\n";
    cout << "  Bienvenido a Backgammon!\n";
    cout << "--------------------------------\n\n";

    system("pause");
    system("cls");
}

int getFichasPorCuadrante(Tablero tablero, string turno, int cuadrante)
{
    int fichas = 0;

    if (turno == "X")
    {
        for (int i = 0; i < 6; i++)
        {
            fichas += tablero.getCasilla(i).getCant();
        }
    }
    else
    {
        for (int i = 23; i >= 18; i++)
        {
            fichas += tablero.getCasilla(i).getCant();
        }
    }

    return fichas;
}

bool validarMovimiento(Tablero tablero, int origen, int mover, string turno)
{
    // Validaciones
}

bool pedirMovimiento(Tablero tablero, string turno, int d1, int d2)
{
    int origen = 0, origen2 = 0;
    bool val = false;

    do
    {
        system("cls");

        imprimirTablero(tablero);

        origen -= 1;

        // Mover una sola ficha
        if (d2 == 0)
        {
            cout << "Ingrese el origen: ";
            cin >> origen;

            val = validarMovimiento(tablero, origen, d1, turno);
        }
        // Mover dos fichas
        else
        {
            cout << "Ingrese el origen de la primera ficha\n> ";
            cin >> origen;

            if (validarMovimiento(tablero, origen, d1, turno))
            {
                cout << "Ingrese el origen de la segunda ficha\n> ";
                cin >> origen2;

                val = validarMovimiento(tablero, origen2, d2, turno);
            }
        }

    } while (!val);
}

int main()
{
    bool salir = false;
    int moves = 0;
    string turno = "X";

    Tablero tablero = inicializarTablero();

    do
    {
        imprimirTablero(tablero);

        cout << "\nTurno : " << turno << "\n\n";

        cout << "Desea tirar los dados?\n1. Tirar\n2. Abandonar\n> ";
        int opc;
        cin >> opc;

        switch (opc)
        {
        case 1:

            Dado dado = Dado();
            int d1 = dado.tirar();
            int d2 = dado.tirar();

            cout << "Dado 1: " << d1 << endl;
            cout << "Dado 2: " << d2 << endl;

            cout << "\nDesea mover una o dos fichas?";
            cin >> moves;

            if (moves == 1)
            {
                d1 = d1 + d2;
                d2 = 0;
            }

            pedirMovimiento(tablero, turno, d1, d2);

            if (turno == "X")
            {
                turno = "O";
            }
            else
            {
                turno = "X";
            }

        case 2:
            salir = true;
        }

        system("pause");
        system("cls");

    } while (!salir);

    system("pause");
    return 0;
}