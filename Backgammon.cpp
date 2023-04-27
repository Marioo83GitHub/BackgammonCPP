// Arroz con pollo

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
    void setCant(int);
    int getCuadrante();
    string getColor();
    void setColor(string);
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

void Casilla::setCant(int _cant)
{
    this->cant_piezas = _cant;
}

void Casilla::setColor(string _color)
{
    this->color_pieza = _color;
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
    int x_comidas;
    int o_comidas;
    int x_fuera;
    int o_fuera;
    Casilla casillas[24];

public:
    Tablero(Casilla[]);
    Casilla getCasilla(int);
    int get_x_comidas();
    int get_o_comidas();
    int get_x_fuera();
    int get_o_fuera();
    void set_x_comidas(int);
    void set_o_comidas(int);
    void set_x_fuera(int);
    void set_o_fuera(int);
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

int Tablero::get_x_fuera()
{
    return this->x_fuera;
}

int Tablero::get_o_fuera()
{
    return this->o_fuera;
}

void Tablero::set_x_comidas(int _x)
{
    this->x_comidas = _x;
}

void Tablero::set_o_comidas(int _o)
{
    this->o_comidas = _o;
}

void Tablero::set_x_fuera(int _x)
{
    this->x_fuera = _x;
}

void Tablero::set_o_fuera(int _o)
{
    this->o_fuera = _o;
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
            colores[i] = "None";
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

    cout << "\nPiezas en penitencia:\n";
    cout << "26 | blancas (X) > " << tablero.get_x_comidas() << endl;
    cout << "27 | negras  (O) > " << tablero.get_o_comidas() << endl;
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
    int fichas_cuadrante = 0;

    for (int i = 0; i < 24; i++)
    {
        if (tablero.getCasilla(i).getColor() == turno && tablero.getCasilla(i).getCuadrante() == cuadrante)
        {
            fichas_cuadrante += tablero.getCasilla(i).getCant();
        }
    }

    return fichas_cuadrante;
}

bool validarMovimiento(Tablero tablero, int origen, int mover, string turno)
{
    int destino = 0, t = 1, limite = 24, cuadrante_final = 0;

    // Verificar si la casilla de origen es la misma que la del turno
    if (turno != tablero.getCasilla(origen).getColor())
    {
        cout << "No puedes mover una ficha que no es tuya\n";
        system("pause");
        return false;
    }

    if (turno == "O")
    {
        // Validaciones para las negras

        // Verificar que el origen no sea la penitencia de las negras
        if (origen == 26)
        {
            cout << "No puedes sacar las fichas en penitencia de tu rival\n";
            system("pause");
            return false;
        }

        if (origen == 27)
        {
            origen = 23;
        }

        limite = -1;
        t = -1;
        cuadrante_final = 4;
    }
    else
    {
        // Validaciones para las blancas

        // Verificar que el origen no sea la penitencia de las blancas
        if (origen == 27)
        {
            cout << "No puedes sacar las fichas en penitencia de tu rival\n";
            system("pause");
            return false;
        }

        if (origen == 26)
        {
            origen = 0;
        }

        cuadrante_final = 1;
    }

    destino = origen + (mover * t);

    // Verificar que el destino no sea mayor a 24 o menor a 1
    if (destino > 24 || destino < 1)
    {
        cout << "No puedes mover una ficha fuera del tablero\n";
        system("pause");
        return false;
    }

    if (destino == 24 || destino == 0)
    {
        // Verificar que no hayan fichas en ningun otro cuadrante
        for (int i = 1; i < 5; i++)
        {
            if (getFichasPorCuadrante(tablero, turno, i) > 0 && i != cuadrante_final)
            {
                cout << "No puedes mover una ficha a la salida si tienes fichas en otros cuadrantes\n";
                system("pause");
                return false;
            }
        }
    }

    // Verificar que no hayan dos o mas fichas del turno contrario en la casilla de destino
    if (tablero.getCasilla(destino).getColor() != turno && tablero.getCasilla(destino).getCant() > 1)
    {
        cout << "No puedes mover a una casilla con dos o mas fichas del contrario\n";
        system("pause");
        return false;
    }

    // Verificar que no hayan mas de 5 fichas aliadas en la casilla de destino
    if (tablero.getCasilla(destino).getColor() == turno && tablero.getCasilla(destino).getCant() > 5)
    {
        cout << "No puedes mover a una casilla con mas de 5 fichas aliadas\n";
        system("pause");
        return false;
    }

    // Se han aprobado todas las validaciones
    return true;
}

void moverFicha(Tablero tablero, int origen, int moves, string turno)
{
    if (turno == "O")
    {
        moves *= -1;
    }

    int destino = origen + moves;


    // Mover la ficha
    tablero.getCasilla(origen).setCant(tablero.getCasilla(origen).getCant() - 1);
    tablero.getCasilla(destino).setCant(tablero.getCasilla(destino).getCant() + 1);

    // Validar que la casilla destino este vacia
    if (tablero.getCasilla(destino).getCant() == 0)
    {
        tablero.getCasilla(destino).setColor(turno);
    }

    // Validar que haya una ficha enemiga en la casilla destino
    if (tablero.getCasilla(destino).getColor() != turno && tablero.getCasilla(destino).getCant() == 1)
    {
        if (turno == "O")
        {
            // Comer ficha blanca
            tablero.set_x_comidas(tablero.get_x_comidas() + 1);
        }
        else
        {
            // Comer ficha negra
            tablero.set_o_comidas(tablero.get_o_comidas() + 1);
        }
        
        // Cambiar el color de la casilla destino
        tablero.getCasilla(destino).setColor(turno);
        tablero.getCasilla(destino).setCant(0);
    }
}

void pedirMovimiento(Tablero tablero, string turno, int d1, int d2)
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

    moverFicha(tablero, origen, d1, turno);

    if (d2 != 0)
    {
        moverFicha(tablero, origen2, d2, turno);
    }
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

           {
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
            break;
		   }
				
        case 2:
            {
            	salir = true;
            break;
			}
        }

        system("pause");
        system("cls");

    } while (!salir);

    system("pause");
    return 0;
}
