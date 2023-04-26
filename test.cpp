#include <iostream>

using namespace std;

class Reales
{
public:
    int numeros[5];
    Reales(int[]);
};

Reales::Reales(int a1[])
{
    for (int i = 0; i < 5; i++)
    {
        this->numeros[i] = a1[i];
    }
}

int numeros(int i)
{
    
    int n[] = {1,2,3,4,5};

    return n[i];
}


int main()
{
    // int a1[] = {1, 2, 3, 4, 5};

    // Reales reales = Reales(a1);

    // for (int i = 0; i < 5; i++)
    // {
    //     cout << reales.numeros[i] << endl;
    // }


    for (int i = 0; i < 5; i++)
    {
        
    }
    

    return 0;
}