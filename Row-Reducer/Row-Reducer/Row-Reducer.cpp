// Row-Reducer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <thread>
using namespace std;

vector<vector<float> > inputMatrice(int antalr�kker, int antals�jler) 
{
    //Denne funktion laver en matrice med vores input
    vector<vector<float>> matrice(antalr�kker, vector<float>(antals�jler));
    cout << "Vi laver en matrice med dimensionen " << antalr�kker << " r�kker og " << antals�jler << " s�jler. \n";

    // Vi ber om input og s�tter disse i vores matrice.
    for (int i = 0; i < antalr�kker; i++)
    {
        for (int j = 0; j < antals�jler; j++)
        {
            float input = 0;
            cout << "Hvad skal der st� i " << i + 1 << ". r�kke " << j + 1 << ". s�jle? \n";
            cin >> input;
            matrice[i][j] = input;
        }
    }
    return matrice;
}

vector<vector<float> > randomMatrice(int antalr�kker, int antals�jler, int seed = 0, int min = -99, int max = 99)
{
    //Denne funktion laver en matrice med de indtastede dimensioner, som fyldes med tilf�ldige tal.
    vector<vector<float>> matrice(antalr�kker, vector<float>(antals�jler));
    cout << "Vi laver en matrice med dimensionen " << antalr�kker << " r�kker og " << antals�jler << " s�jler. \n";
    if (seed == 0)
    {
        seed = time(NULL);
    }
    int range = max - min;
    srand(seed);
    // Vi ber om input og s�tter disse i vores matrice.
    for (int i = 0; i < antalr�kker; i++)
    {
        for (int j = 0; j < antals�jler; j++)
        {
           int tilf�ldigtTal =  rand() % range + min;
            matrice[i][j] = tilf�ldigtTal;
        }
    }
    return matrice;
}

vector<vector<float> > standardMatrice(int antalr�kker, int antals�jler)
{
    //Denne funktion laver en en mindre standardmatrice ud fra den store matrice som er lavet.
    vector<vector<float>> standardMatrice(10, vector<float>(10));

        standardMatrice = {
                          { 1, 2, 3, 1, 2, 3, 1, 2, 3, 6 },
                          { 4, 5, 6, 4, 5, 6, 4, 5, 6, 3 },
                          { 7, 8, 9, 4, 5, 6, 4, 5, 6, 7 },
                          { 1, 2, 3, 1, 2, 3, 1, 2, 3, 7 },
                          { 4, 5, 6, 6, 4, 5, 6, 4, 5, 6, },
                          { 7, 8, 9, 5, 7, 8, 9, 7, 8, 9, },
                          { 1, 2, 3, 3, 1, 2, 3, 1, 2, 3, },
                          { 4, 5, 6, 9, 4, 5, 6, 4, 5, 6, },
                          { 7, 8, 9, 9, 7, 8, 9, 7, 8, 9, },
                          { 1, 3, 4, 8, 1, 3, 4, 1, 3, 4, } };
    vector<vector<float>> matrice(antalr�kker, vector<float>(antals�jler));
    

    for (int i = 0; i < antalr�kker; i++)
    {
        for (int j = 0; j < antals�jler; j++)
        {
            matrice[i][j] = standardMatrice[i][j];
        }
    }
    return matrice;
}

void printMatrice(vector<vector<float>> matrice)
{
    //Denne function skriver matricen ud i terminalen.
    int antalr�kker = matrice.size();
    int antals�jler = matrice[0].size();

    // Vi ser om vi f� brugt vores input.
    cout << "Matricen ser ud s�dan her: \n";
    for (int i = 0; i < antalr�kker; i++)
    {
        for (int j = 0; j < antals�jler; j++)
        {
            cout << matrice[i][j] << ", ";
        }
        cout << "\n";
    }
}

vector<vector<float> > copyMatrice(vector < vector<float>> inputMatrice)
{
    //Denne funtion kopiere matricen, s� vi kan redigere i den uden at �ndre den originale.
    int antalr�kker = inputMatrice.size();
    int antals�jler = inputMatrice[0].size();
    vector<vector<float>> outputMatrice(antalr�kker, vector<float>(antals�jler));
    for (int i = 0; i < antalr�kker; i++)
    {
        for (int j = 0; j < antals�jler; j++)
        {
            outputMatrice[i][j] = inputMatrice[i][j];
        }
    }

    return outputMatrice;
}

vector<vector<float> > rowReduceMatrice(vector < vector<float>> inputMatrice)
{
    //Denne del finder vores pivotelementer og f�r 0'er under dem.
    int antalr�kker = inputMatrice.size();
    int antals�jler = inputMatrice[0].size();
    vector<vector<float>> outputMatrice = copyMatrice(inputMatrice);
    for (int h = 0; h < antalr�kker-1; h++)
    {
        printMatrice(outputMatrice);
        for (int i = h + 1; i < antalr�kker; i++)
        {
            float leadingCoeffiecient = outputMatrice[h][h];
            if (leadingCoeffiecient == 0)
            {
                vector<float> oldRow = outputMatrice[h];
                outputMatrice[h] = outputMatrice[h + 1];
                outputMatrice[h + 1] = oldRow;
            }
            else
            {
                float targetelement = outputMatrice[i][h];
                float factor = targetelement / leadingCoeffiecient;
                if (factor != 0)
                {
                    for (int j = h; j < antals�jler; j++)
                    {
                        float targetValue = outputMatrice[i][j];
                        float factorUser = outputMatrice[h][j];
                        outputMatrice[i][j] = targetValue - factor * factorUser;
                    }
                }
            }
        }
    }
    
    //Denne del kan fjerne de indgange over vores pivotelementer for at kunne reducere.
    // den fjerner alle tal over en ledende koefficient, s� derfor kan det komme til at fjerne frie variable
    //L�s dette ved at inds�tte en bool og f� den til at vide hvorn�r den har fjernet for den ledende koefficient og s�ledes kun g�re det en gang.
    for (int i = antalr�kker - 1; i >= 0; i--)
    {
        
        for (int j = 0; j < antals�jler; j++ )
        {bool foundCoeffiecient = false;
            float leadingCoeffiecient = outputMatrice[i][j];
            if (leadingCoeffiecient != 0 && foundCoeffiecient == false) // vi fors�ger at finde en ledende koefficient
            {
                foundCoeffiecient = true;
                for (int h = i-1; h >= 0; h--)
                {
                    float targetValue = outputMatrice[h][j];
                    if (targetValue != 0)
                    {
                        float factor = targetValue / leadingCoeffiecient;
                        outputMatrice[h][j] = targetValue - factor * leadingCoeffiecient;
                        
                        for (int k = j + 1; k < antals�jler; k++)
                        {
                            float factorUser = outputMatrice[h][k];
                            outputMatrice[h][k] = outputMatrice[h][k] - factor * factorUser;
                        }
                    }
                }
            }
        }
    }
    return outputMatrice;
}

int main()
{
    char c;
    do
    {

    
        vector<vector<float>> matrice;
        int matrixMetode;
        cout << "Hvordan vil du lave din matrice?\n tryk 1 for at lave din egen, 2 for en standardmatrix og 3 for en tilf�ldig matrice\n";
        cin >> matrixMetode;
        switch (matrixMetode)
        {
        case 1: // Skriv selv
        {
            int antals�jler = 0;
            int antalr�kker = 0;
            // Vi ber om st�rrelsen p� matricen og definerer den.
            cout << "Hvor stor skal matricen v�re? Husk at det er r�kker,s�jler og derfor intet X\n";
            cin >> antalr�kker >> antals�jler;
            matrice = inputMatrice(antalr�kker, antals�jler);
            break;
        }

        case 2: // Kendt standard
        {
            int antals�jler = 0;
            int antalr�kker = 0;
            cout << "Hvor stor skal matricen v�re? Husk at det er r�kker,s�jler og derfor intet X\n";
            cin >> antalr�kker >> antals�jler;
            matrice = standardMatrice(antalr�kker, antals�jler);
            break;
        }
        case 3: // Denne laver en tilf�ldig matrice ud fra maskintiden.
        {
            int antals�jler = 0;
            int antalr�kker = 0;
            cout << "Hvor stor skal matricen v�re? Husk at det er r�kker,s�jler og derfor intet X\n";
            cin >> antalr�kker >> antals�jler;
            matrice = randomMatrice(antalr�kker, antals�jler);
            break;
        }
        }
        printMatrice(matrice);
        vector<vector<float>> reducedMatrice = rowReduceMatrice(matrice);
        printMatrice(reducedMatrice);
        cin >> c;
    } while (c != 'S');
}