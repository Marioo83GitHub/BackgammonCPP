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

    cout <<"\nPiezas comidas:\n";
    cout <<"25 | blancas (X) > "<< tablero.get_x_comidas()<<endl;
    cout <<"26 | negras  (O) > "<< tablero.get_o_comidas()<<endl;
}

void bienvenida()
{
    cout <<"--------------------------------\n";
    cout <<"  Bienvenido a Backgammon!\n";
    cout <<"--------------------------------\n\n";

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


bool validarMovimiento(Tablero tablero, int movs, int origen, string turno)
{
    int avanzar = 0;
    int cuadrante = 0;
    int salida = 0;

    if (turno == "X")
    {
        if (origen == 26)
        {
            return false;
        }
        avanzar = movs;
        cuadrante = 4;
        salida = 24;
    }   
    else 
    {
        if (origen == 25)
        {
            return false;
        }
        avanzar = movs * -1;
        cuadrante = 1;
        salida = -1;
    }

    if(origen + avanzar == salida)
    {
        if (getFichasPorCuadrante(tablero, turno, cuadrante) == 15)
        {
            return true;
        }

        return false;
    }

    Casilla destino = tablero.getCasilla(origen + avanzar);
    Casilla origen = tablero.getCasilla(origen);

    

    int cant = destino.getCant();

    if (cant < 1 || cant == 5)
    {
        return false;
    }
    


    return true;

}

bool pedirMovimiento(string turno, Tablero tablero)
{
    Dado dado = Dado();
    int origen = 0, opc_cant = 0, movidas = 0;

    bool band = true;
    bool mov = false;

    int d1 = dado.tirar();
    int d2 = dado.tirar();
    
    int *movs = new int[3];
    movs[0] = d1;
    movs[1] = d2;
    movs[2] = d1+d2;
    
    do{

        system("pause");
        system("cls");

        imprimirTablero(tablero);

        cout << "\nSeleccione la casilla de la ficha que desea mover\n> ";
        cin >> origen;

        origen -= 1;

        if (tablero.getCasilla(origen).getColor() != turno)
        {
            cout << "Esas fichas no te pertenecen";
            continue;
        }

        cout << "\nSeleccionar la cantidad de casillas a mover\n";
        cout << "1. Dado 1     : " << d1<<endl;
        cout << "2. Dado 2     : " << d2<<endl;
        cout << "3. Ambos      : " << d1 + d2<<endl;
        do
        {
            cout << "opc > "; cin >> opc_cant; cout << endl;
        }while(opc_cant > 3 || opc_cant < 1);

        opc_cant -= 1;

        movidas = 0;

        while(true)
        {
            mov = validarMovimiento(tablero, movs[opc_cant], origen, turno);

            if (mov)
            {
                // Hacer Movimiento

                movidas += movs[opc_cant];

                if (movidas == d1 + d2)
                {
                    band = true;
                    break;
                }
                else 
                {
                    opc_cant = opc_cant + (pow(-1,opc_cant+1));
                }
            }
            else
            {
                cout << "-----------------------\n";
                cout << " Movimiento erroneo...\n";
                cout << "-----------------------\n";
                break;
            }
        }    


        
    }while(!band);
    


    delete[] movs;
    return true;

}

int main()
{
    bool salir = false;
    string turno = "X";

    
    Tablero tablero = inicializarTablero();


    do
    {
        imprimirTablero(tablero);

        cout << "\nTurno : " << turno <<"\n\n";

        cout << "Desea tirar los dados?\n1. Tirar\n2. Abandonar\n> ";
        int opc;
        cin >> opc;

        switch (opc)
        {
            case 1:
                


                // pedir, validar y hacer movimiento


                if (turno == "X")
                {
                    turno = "O";
                } else {
                    turno = "X";
                }



            case 2:
                salir = true;
        }



        

        system ("pause");
        system ("cls");

    } while (!salir);
    

    

    

    system("pause");
    return 0;
}