// Row-Reducer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <thread>
using namespace std;


vector<vector<float> > copyMatrice(vector < vector<float>> inputMatrice)
{
    //Denne funtion kopiere matricen, så vi kan redigere i den uden at ændre den originale.
    int antalrækker = inputMatrice.size();
    int antalsøjler = inputMatrice[0].size();
    vector<vector<float>> outputMatrice(antalrækker, vector<float>(antalsøjler));
    for (int i = 0; i < antalrækker; i++)
    {
        for (int j = 0; j < antalsøjler; j++)
        {
            outputMatrice[i][j] = inputMatrice[i][j];
        }
    }

    return outputMatrice;
}

vector<vector<float> > inputMatrice(int antalrækker, int antalsøjler) 
{
    //Denne funktion laver en matrice med vores input
    vector<vector<float>> matrice(antalrækker, vector<float>(antalsøjler));
    cout << "Vi laver en matrice med dimensionen " << antalrækker << " rækker og " << antalsøjler << " søjler. \n";

    // Vi ber om input og sætter disse i vores matrice.
    for (int i = 0; i < antalrækker; i++)
    {
        for (int j = 0; j < antalsøjler; j++)
        {
            float input = 0;
            cout << "Hvad skal der stå i " << i + 1 << ". række " << j + 1 << ". søjle? \n";
            cin >> input;
            matrice[i][j] = input;
        }
    }
    return matrice;
}

vector<vector<float> > randomMatrice(int antalrækker, int antalsøjler, int seed = 0, int min = -99, int max = 99)
{
    //Denne funktion laver en matrice med de indtastede dimensioner, som fyldes med tilfældige tal.
    vector<vector<float>> matrice(antalrækker, vector<float>(antalsøjler));
    cout << "Vi laver en matrice med dimensionen " << antalrækker << " rækker og " << antalsøjler << " søjler. \n";
    if (seed == 0)
    {
        seed = (int)time(NULL);
    }
    int range = max - min;
    srand(seed);
    // Vi ber om input og sætter disse i vores matrice.
    for (int i = 0; i < antalrækker; i++)
    {
        for (int j = 0; j < antalsøjler; j++)
        {
           float tilfældigtTal = 1.0f * (rand() % range + min);
            matrice[i][j] = tilfældigtTal ;
        }
    }
    return matrice;
}

vector<vector<float> > standardMatrice(int antalrækker, int antalsøjler)
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
    vector<vector<float>> matrice(antalrækker, vector<float>(antalsøjler));
    

    for (int i = 0; i < antalrækker; i++)
    {
        for (int j = 0; j < antalsøjler; j++)
        {
            matrice[i][j] = standardMatrice[i][j];
        }
    }
    return matrice;
}

vector<vector<float> > Test1Matrice()
{
    vector<vector<float>> test1Matrice(3, vector<float>(2));
        test1Matrice = { { 1, 2,  7},
                         { 4, 1, 14} };
    return test1Matrice;
}


vector<vector<float> > Test1ReducedMatrice()
{
    vector<vector<float>> test1ReducedMatrice(3, vector<float>(2));
    test1ReducedMatrice = { { 1, 0,  3},
                            { 0, 1,  2} };
    return test1ReducedMatrice;
}


void printMatrice(vector<vector<float>> matrice, const char * title = NULL)
{
    //Denne function skriver matricen ud i terminalen.
    int antalrækker = matrice.size();
    int antalsøjler = matrice[0].size();

    if (title == NULL)
    {
        title = "Matricen ser ud sådan her: ";
    }
    cout << title << ": \n";

    // Vi ser om vi få brugt vores input. 
    for (int i = 0; i < antalrækker; i++)
    {
        for (int j = 0; j < antalsøjler; j++)
        {
            cout << matrice[i][j] << ", ";
        }
        cout << "\n";
    }
}


vector<vector<float> > rowReduceMatrice(vector < vector<float>> inputMatrice)
{
    //Denne del finder vores pivotelementer og får 0'er under dem.
    int antalrækker = inputMatrice.size();
    int antalsøjler = inputMatrice[0].size();
    vector<vector<float>> outputMatrice = copyMatrice(inputMatrice);
    for (int h = 0; h < antalrækker - 1; h++)
    {
        // printMatrice(outputMatrice, "rowReduceMatrice for række");
        for (int i = h + 1; i < antalrækker; i++)
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
                    for (int j = h; j < antalsøjler; j++)
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
    // den fjerner alle tal over en ledende koefficient, så derfor kan det komme til at fjerne frie variable
    //Løs dette ved at indsætte en bool og få den til at vide hvornår den har fjernet for den ledende koefficient og således kun gøre det en gang.
    for (int i = antalrækker - 1; i >= 0; i--)
    {

        for (int j = 0; j < antalsøjler; j++)
        {
            bool foundCoeffiecient = false;
            float leadingCoeffiecient = outputMatrice[i][j];
            if (leadingCoeffiecient != 0 && foundCoeffiecient == false) // vi forsøger at finde en ledende koefficient
            {
                foundCoeffiecient = true;
                for (int h = i - 1; h >= 0; h--)
                {
                    float targetValue = outputMatrice[h][j];
                    if (targetValue != 0)
                    {
                        float factor = targetValue / leadingCoeffiecient;
                        outputMatrice[h][j] = targetValue - factor * leadingCoeffiecient;

                        for (int k = j + 1; k < antalsøjler; k++)
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

bool TestMatriceReduce(vector<vector<float>> matrice, vector<vector<float>> expectedReducedMatrice)
{
    //Denne function finder rowReduce matricen og sammenligner med den korrekte rowReduced Matrice.
    int matriceAntalrækker = matrice.size();
    int matriceAntalsøjler = matrice[0].size();

    int expectedReducedMatriceAntalrækker = expectedReducedMatrice.size();
    int expectedReducedMatriceAntalsøjler = expectedReducedMatrice[0].size();

    // vi chekker at størrelsen for expectedReducedMatrice passer
    if (matriceAntalrækker != expectedReducedMatriceAntalrækker)
    {
        cout << "Antal rækker passer ikke: " << matriceAntalrækker << " != " << expectedReducedMatriceAntalrækker << " for expectedReducedMatrice\n";
        return false;
    }

    if (matriceAntalsøjler != expectedReducedMatriceAntalsøjler)
    {
        cout << "Antal søjler passer ikke: " << matriceAntalrækker << " != " << expectedReducedMatriceAntalsøjler << " for expectedReducedMatrice\n";
        return false;
    }

    vector<vector<float>> reducedMatrice = rowReduceMatrice(matrice);
 
    int reducedMatriceAntalrækker = reducedMatrice.size();
    int reducedMatriceAntalsøjler = reducedMatrice[0].size();

    // vi chekker at størrelsen for reducedMatriceAntalrækker passer
    if (reducedMatriceAntalrækker != expectedReducedMatriceAntalrækker)
        {
            cout << "Antal rækker passer ikke: " << reducedMatriceAntalrækker << " != " << expectedReducedMatriceAntalrækker << " for reducedMatrice\n";
            return false;
        }

    if (reducedMatriceAntalsøjler != expectedReducedMatriceAntalsøjler)
    {
        cout << "Antal søjler passer ikke: " << reducedMatriceAntalrækker << " != " << expectedReducedMatriceAntalsøjler << " for reducedMatrice \n";
        return false;
    }

    bool isEqual = true;
    
    // Vi ser om alle pladser passer.
    for (int i = 0; i < reducedMatriceAntalrækker; i++)
    {
        for (int j = 0; j < reducedMatriceAntalsøjler; j++)
        {
            if (reducedMatrice[i][j] != expectedReducedMatrice[i][j])
            {
                cout << "Plads " << i << ", " << j << " passer ikke: " << reducedMatrice[i][j] << " != " << expectedReducedMatrice[i][j] << "  \n";
                isEqual = false;
            }
        }
        cout << "\n";
    }

    if (!isEqual)
    {
        printMatrice(matrice, "matrice");
        printMatrice(reducedMatrice, "reducedMatrice");
        printMatrice(expectedReducedMatrice, "expectedReducedMatrice");
    }
    return isEqual;
}

bool TestMatrices()
{
    cout << "Udfører test af row Reduce på test matricer-\n";
    bool allTestsOk = true;

    /*
    
    */

    vector<vector<float>> test1Matrice = Test1Matrice();
    vector<vector<float>> expectedTest1ReducedMatricee = Test1ReducedMatrice();

    allTestsOk &= TestMatriceReduce(test1Matrice, expectedTest1ReducedMatricee);
     

    cout << "\n";
    return allTestsOk;
}


int main()
{
    TestMatrices();

    char c = ' ';
    do
    {
        vector<vector<float>> matrice;
        int matrixMetode = 0;
        cout << "Hvordan vil du lave din matrice?\n tryk 1 for at lave din egen, 2 for en standardmatrix og 3 for en tilfældig matrice. T for test og S for stop\n";
        cin >> matrixMetode;
        if (matrixMetode > 0)
        {
            switch (matrixMetode)
            {
                case 1: // Skriv selv
                {
                    int antalsøjler = 0;
                    int antalrækker = 0;
                    // Vi ber om størrelsen på matricen og definerer den.
                    cout << "Hvor stor skal matricen være? Husk at det er rækker,søjler og derfor intet X\n";
                    cin >> antalrækker >> antalsøjler;
                    matrice = inputMatrice(antalrækker, antalsøjler);
                    break;
                }

                case 2: // Kendt standard
                {
                    int antalsøjler = 0;
                    int antalrækker = 0;
                    cout << "Hvor stor skal matricen være? Husk at det er rækker,søjler og derfor intet X\n";
                    cin >> antalrækker >> antalsøjler;
                    matrice = standardMatrice(antalrækker, antalsøjler);
                    break;
                }
                case 3: // Denne laver en tilfældig matrice ud fra maskintiden.
                {
                    int antalsøjler = 0;
                    int antalrækker = 0;
                    cout << "Hvor stor skal matricen være? Husk at det er rækker,søjler og derfor intet X\n";
                    cin >> antalrækker >> antalsøjler;
                    matrice = randomMatrice(antalrækker, antalsøjler);
                    break;
                }
                case 4: // Denne laver en lille test matrice
                {
                    matrice = Test1Matrice();
                    break;
                }
            }
            printMatrice(matrice);
            vector<vector<float>> reducedMatrice = rowReduceMatrice(matrice);
            printMatrice(reducedMatrice);
        }
        c = '\0';
        cin >> c;
        if (c == 'T')
        {
            TestMatrices();
        }
    } while (c != 'S');
}