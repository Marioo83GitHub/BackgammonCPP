import os
import random


class Dado:
    def tirar(self):
        return random.randint(1, 6)


class Casilla:
    def __init__(self, _color, _cant, _cuadrante):
        self.cant_piezas = _cant
        self.cuadrante = _cuadrante
        self.color_pieza = _color

    def getCant(self):
        return self.cant_piezas

    # def setCant(self, _cant):
    #     self.cant_piezas = _cant

    # def setColor(self, _color):
    #     self.color_pieza = _color

    def getCuadrante(self):
        return self.cuadrante

    def getColor(self):
        return self.color_pieza


class Tablero:

    def __init__(self, _casillas):
        self.x_comidas = 0
        self.o_comidas = 0
        self.x_fuera = 0
        self.o_fuera = 0
        self.casillas = _casillas

    def setCasilla(self, i, _casilla):
        self.casillas[i] = _casilla

    def getCasilla(self, i):
        return self.casillas[i]

    def get_x_comidas(self):
        return self.x_comidas

    def get_o_comidas(self):
        return self.o_comidas

    def get_x_fuera(self):
        return self.x_fuera

    def get_o_fuera(self):
        return self.o_fuera

    def set_x_comidas(self, _x):
        self.x_comidas = _x

    def set_o_comidas(self, _o):
        self.o_comidas = _o

    def set_x_fuera(self, _x):
        self.x_fuera = _x

    def set_o_fuera(self, _o):
        self.o_fuera = _o


def inicializarTablero():
    cants = [0] * 24
    cants[0] = 2
    cants[5] = 5
    cants[9] = 3
    cants[11] = 5
    cants[12] = 5
    cants[14] = 3
    cants[18] = 5
    cants[23] = 2

    colores = [0] * 24
    colores[0] = "X"
    colores[5] = "O"
    colores[9] = "O"
    colores[11] = "X"
    colores[12] = "O"
    colores[14] = "X"
    colores[18] = "X"
    colores[23] = "O"

    cuadrante = 0
    casillas = [0] * 24

    for i in range(24):
        if cants[i] < 1:
            cants[i] = 0
            colores[i] = "None"

        if i % 6 == 0:
            cuadrante += 1

        casillas[i] = Casilla(colores[i], cants[i], cuadrante)

    return Tablero(casillas)


def imprimirTablero(tablero):
    for i in range(24):
        if i < 9:
            print(" ", end="")
        print(i + 1, end=" | ")

        c = tablero.getCasilla(i).getCant()

        for j in range(c):
            print(tablero.getCasilla(i).getColor(), end="")

        for q in range(5 - c):
            print("-", end="")

        print()

    print("\nFichas en penitencia:")
    print("--------------------------")
    print("26 | blancas (X) > ", tablero.get_x_comidas())
    print("27 | negras  (O) > ", tablero.get_o_comidas())
    print("\nFichas fuera:")
    print("--------------------------")
    print("[] | blancas (X) > ", tablero.get_x_fuera())
    print("[] | negras  (O) > ", tablero.get_o_fuera())
    print()


def bienvenida():
    print("--------------------------------")
    print("  Bienvenido a Backgammon!")
    print("--------------------------------\n")

    input("Presione Enter para continuar...")

# int getFichasPorCuadrante(Tablero tablero, string turno, int cuadrante)
# {
#    int fichas_cuadrante = 0;
#
#    for (int i = 0; i < 24; i++)
#    {
#        if (tablero.getCasilla(i).getColor() == turno && tablero.getCasilla(i).getCuadrante() == cuadrante)
#        {
#            fichas_cuadrante += tablero.getCasilla(i).getCant();
#        }
#    }
#
#    return fichas_cuadrante;
# }


def getFichasPorCuadrante(tablero, turno, cuadrante):

    fichas_cuadrante = 0

    for i in range(24):
        if tablero.getCasilla(i).getColor() == turno and tablero.getCasilla(i).getCuadrante() == cuadrante:
            fichas_cuadrante += tablero.getCasilla(i).getCant()

    return fichas_cuadrante


def validarMovimiento(tablero, origen, mover, turno):
    destino = 0
    t = 1
    cuadrante_final = 0

    # Verificar si la casilla de origen es la misma que la del turno
    if turno != tablero.getCasilla(origen).getColor():
        print("No puedes mover una ficha que no es tuya\n")
        input("Presione Enter para continuar...")
        os.system("cls")
        return False

    if turno == "O":
        # Validaciones para las negras

        # Verificar que el origen no sea la penitencia de las negras
        if origen == 26:
            print("No puedes sacar las fichas en penitencia de tu rival\n")
            input("Presione Enter para continuar...")
            os.system("cls")
            return False

        if origen == 27:
            origen = 23

        t = -1
        cuadrante_final = 4
    else:
        # Validaciones para las blancas

        # Verificar que el origen no sea la penitencia de las blancas
        if origen == 27:
            print("No puedes sacar las fichas en penitencia de tu rival\n")
            input("Presione Enter para continuar...")
            os.system("cls")
            return False

        if origen == 26:
            origen = 0

        cuadrante_final = 1

    destino = origen + (mover * t)

    # Verificar que el destino no sea mayor a 24 o menor a 1
    if destino > 24 or destino < 1:
        print("No puedes mover una ficha fuera del tablero\n")
        input("Presione Enter para continuar...")
        os.system("cls")
        return False

    if destino == 24 or destino == 0:
        # Verificar que no hayan fichas en ningun otro cuadrante
        for i in range(1, 5):
            if getFichasPorCuadrante(tablero, turno, i) > 0 and i != cuadrante_final:
                print("No puedes mover una ficha a la salida si tienes fichas en otros cuadrantes\n")
                input("Presione Enter para continuar...")
                os.system("cls")
                return False

    # Verificar que no hayan dos o mas fichas del turno contrario en la casilla de destino
    if tablero.getCasilla(destino).getColor() != turno and tablero.getCasilla(destino).getCant() > 1:
        print("No puedes mover a una casilla con dos o mas fichas del contrario\n")
        input("Presione Enter para continuar...")
        os.system("cls")
        return False

    # Verificar que no hayan mas de 5 fichas aliadas en la casilla de destino
    if tablero.getCasilla(destino).getColor() == turno and tablero.getCasilla(destino).getCant() > 5:
        print("No puedes mover a una casilla con mas de 5 fichas aliadas\n")
        input("Presione Enter para continuar...")
        os.system("cls")
        return False

    # Se han aprobado todas las validaciones
    return True

def moverFicha(tablero, origen, moves, turno):
    C_origen = tablero.getCasilla(origen)

    if turno == "O":
        moves *= -1

    destino = origen + moves

    #validar que la casilla destino sea 24 o -1
    if destino == 24 or destino == -1:
        
        #Sacar ficha del origen
        cant = C_origen.getCant() - 1
        cuadrante = C_origen.getCuadrante()

        color = C_origen.getColor()

        if cant == 0:
            color = "None"

        tablero.setCasiila(origen, Casilla(color, cant, cuadrante))

        # Mover fichas fuera de tablero
        if turno == "O":
            tablero.set_o_fuera(tablero.get_o_fuera() + 1)
        else:
            tablero.set_x_fuera(tablero.get_x_fuera() + 1)

        return tablero

    # Validar que la casilla destino sea de distinto color que la casilla origen

    cant_d = tablero.getCasilla(destino).getCant() + 1
    cuadrante_d = tablero.getCasilla(destino).getCuadrante()

    if tablero.getCasilla(destino).getColor() != turno:
        if tablero.getCasilla(destino).getCant() == 1:
            if turno == "X":
                tablero.set_o_comidas(tablero.get_o_comidas() + 1)

            else:
                tablero.set_x_comidas(tablero.get_x_comidas() + 1)

            cant_d -= 1



# void pedirMovimiento(Tablero tablero, string turno, int d1, int d2)
# {
#    int origen = 0, origen2 = 0;
#    bool val = false;
#
#    do
#    {
#        system("cls");
#
#        imprimirTablero(tablero);
#
#        origen -= 1;
#
#        // Mover una sola ficha
#        if (d2 == 0)
#        {
#            cout << "Ingrese el origen: ";
#            cin >> origen;
#
#            val = validarMovimiento(tablero, origen, d1, turno);
#        }
#        // Mover dos fichas
#        else
#        {
#            cout << "Ingrese el origen de la primera ficha\n> ";
#            cin >> origen;
#
#            if (validarMovimiento(tablero, origen, d1, turno))
#            {
#                cout << "Ingrese el origen de la segunda ficha\n> ";
#                cin >> origen2;
#
#                val = validarMovimiento(tablero, origen2, d2, turno);
#            }
#        }
#
#    } while (!val);
#
#    moverFicha(tablero, origen, d1, turno);
#
#    if (d2 != 0)
#    {
#        moverFicha(tablero, origen2, d2, turno);
#    }
# }

def pedirMovimiento(tablero, turno, d1, d2):
    origen = 0
    origen2 = 0
    val = False

    while not val:
        os.system("cls")

        imprimirTablero(tablero)

        origen -= 1

        # Mover una sola ficha
        if d2 == 0:
            print("Ingrese el origen: ")
            origen = int(input("> "))

            val = validarMovimiento(tablero, origen, d1, turno)
        # Mover dos fichas
        else:
            print("Ingrese el origen de la primera ficha")
            origen = int(input("> "))

            if validarMovimiento(tablero, origen, d1, turno):
                print("Ingrese el origen de la segunda ficha")
                origen2 = int(input("> "))

                val = validarMovimiento(tablero, origen2, d2, turno)

    moverFicha(tablero, origen, d1, turno)

    if d2 != 0:
        moverFicha(tablero, origen2, d2, turno)


# int main()
# {
#    bool salir = false;
#    int moves = 0;
#    string turno = "X";
#
#    Tablero tablero = inicializarTablero();
#
#    do
#    {
#        imprimirTablero(tablero);
#
#        cout << "\nTurno : " << turno << "\n\n";
#
#        cout << "Desea tirar los dados?\n1. Tirar\n2. Abandonar\n> ";
#        int opc;
#        cin >> opc;
#
#        switch (opc)
#        {
#        case 1:
#
#           {
#           	 Dado dado = Dado();
#            int d1 = dado.tirar();
#            int d2 = dado.tirar();
#
#            cout << "Dado 1: " << d1 << endl;
#            cout << "Dado 2: " << d2 << endl;
#
#            cout << "\nDesea mover una o dos fichas?";
#            cin >> moves;
#
#            if (moves == 1)
#            {
#                d1 = d1 + d2;
#                d2 = 0;
#            }
#
#            pedirMovimiento(tablero, turno, d1, d2);
#
#            if (turno == "X")
#            {
#                turno = "O";
#            }
#            else
#            {
#                turno = "X";
#            }
#            break;
# }
#
#        case 2:
#            {
#            	salir = true;
#            break;
# }
#        }
#
#        system("pause");
#        system("cls");
#
#    } while (!salir);
#
#    system("pause");
#    return 0;
# }

def main():
    salir = False
    moves = 0
    turno = "X"

    tablero = inicializarTablero()

    while not salir:
        imprimirTablero(tablero)

        print("\nTurno : " + turno + "\n\n")

        print("Desea tirar los dados?\n1. Tirar\n2. Abandonar\n> ")
        opc = int(input())

        if opc == 1:
            dado = Dado()
            d1 = dado.tirar()
            d2 = dado.tirar()

            print("Dado 1: " + str(d1))
            print("Dado 2: " + str(d2))

            print("\nDesea mover una o dos fichas?")
            moves = int(input())

            if moves == 1:
                d1 = d1 + d2
                d2 = 0

            pedirMovimiento(tablero, turno, d1, d2)

            if turno == "X":
                turno = "O"
            else:
                turno = "X"
        elif opc == 2:
            salir = True

        os.system("pause")
        os.system("cls")

    os.system("pause")
    return 0


main()
