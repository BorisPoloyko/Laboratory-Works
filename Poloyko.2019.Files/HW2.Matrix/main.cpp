#include<iostream>
#include<fstream>
#include <cmath>

using namespace std;

typedef double(*Method)(int,int);

void CreateFile(char* fileName, int n, double**, double**);
int ContentsFile(char**);
void AddFile(char* fileName, double, const char*);

double inbuilt(int, int);
double taylor(int, int);
double customSin(double, double);

double** createMatrix(int columns, int rows);
double** fillMatrix(double** matrix, int columns, int rows, Method method);
double matrixComparisonByDifference(double** matrixA, double** matrixB, int columns, int rows);

double accuracy = 0.001;

int main(int argc, const char * argv[])
{
    
    const int N = 30;
    char* fileName = "/Users/larisapoloyko/Desktop/XCode/Files/task.txt";
    
    int n;
    cout << "Enter size of the matrix:";
    cin >> n;
    
    double** matrixA = createMatrix(n, n);
    double** matrixB = createMatrix(n, n);
    matrixA = fillMatrix(matrixA, n, n, taylor);
    matrixB = fillMatrix(matrixB, n, n, inbuilt);
    
    CreateFile(fileName, n, matrixA, matrixB);
    double difference = matrixComparisonByDifference(matrixA, matrixB, n, n);
    AddFile(fileName, difference, "\nThe difference is:\n");
    
    
    //system("pause");
    return 0;
}

void CreateFile(char* fileName, int n, double** matrixA, double** matrixB)
{
    ofstream streamOut(fileName);
    //    ofstream streamOut;
    //    streamOut.open(fileName, ios::out);
    
    if (!streamOut.is_open())
    {
        cout << "Cannot open file to write!" << endl;
        system("pause");
        exit(1);
    }
    
    streamOut << "Taylor matrix:\n";
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double temp;
            temp = *(*(matrixA + i) + j);
            streamOut.width(10);
            streamOut << temp;
        }
        streamOut << "\n";
    }
    
    streamOut << "Inbuilt matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double temp;
            temp = *(*(matrixB + i) + j);
            streamOut.width(10);
            streamOut << temp;
        }
        streamOut << "\n";
    }
    
    
    streamOut.close();
}

int ContentsFile(char* fileName)
{
    ifstream streamIn(fileName);
    
    if (!streamIn.is_open())
    {
        cout << "Cannot open file to read!" << endl;
        system("pause");
        exit(1);
    }
    
    int count = 0;
    double term;
    
    while (!streamIn.eof())
    {
        streamIn >> term;
        count++;
    }
    streamIn.close();
    return count;
}

void AddFile(char* fileName, double result, const char* message)
{
    ofstream streamOut(fileName, ios::app);
    
    if (!streamOut.is_open())
    {
        cout << "\nCannot open file to addition!\n";
        system("pause");
        exit(1);
    }
    streamOut <<message;
    
    streamOut <<result;
    
    streamOut.close();
}

double inbuilt(int i, int j)
{
    return (i == j) ? i+1 : (sin(2 *(i+1)*(j+1)) + sin(i+1)) / (((i + 1) - (j + 1) - 4) ^ 3 + ((i + 1) + (j + 1)) ^ 2);
}

double taylor(int i, int j)
{
    return (i == j) ? i+1 : (customSin(2 * (i + 1)*(j + 1), accuracy) + customSin((i + 1), accuracy)) / (((i + 1) - (j + 1) - 4) ^ 3 + ((i + 1) + (j + 1)) ^ 2);
}

double customSin(double number, double accuracy)
{
    if (accuracy < 0 || accuracy >1)
    {
        throw out_of_range("Accuracy can not be less than 0 or more than 1");
    }
    const double PI = 3.14159265358979323846;
    number = fmod(number, PI*2);
    double sin = 0, term = number;
    int i = 1;
    while (abs(term)> accuracy)
    {
        sin += term;
        term *= -1.0*(number * number) / (2 * i) / (2 * i + 1);
        i++;
    }
    return sin;
}

double** fillMatrix(double** matrix, int columns, int rows, Method method)
{
    if (matrix == nullptr)
    {
        throw invalid_argument("Matrix can not be null.");
    }
    
    if (rows <= 0 || columns <= 0)
    {
        throw invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
    }
    
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            *(*(matrix + i) + j) = method(i, j);
        }
    }
    
    return matrix;
}

double** createMatrix(int columns, int rows)
{
    if (rows <= 0 || columns <=0)
    {
        throw std::invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
    }
    double** matrix = new double*[columns];
    for (int i = 0; i < columns; ++i)
    {
        matrix[i] = new double[rows];
    }
    return matrix;
}

double matrixComparisonByDifference(double** matrixA, double** matrixB, int columns, int rows)
{
    if (matrixA == nullptr || matrixB == nullptr)
    {
        throw invalid_argument("Matrix can not be null.");
    }
    
    if (rows <= 0 || columns <= 0)
    {
        throw invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
    }
    double maxDifference = 0;
    for (int i = 0; i < columns; i++)
    {
        double difference = 0;
        for (int j = 0; j < rows; j++)
        {
            difference = *(*(matrixA + i) + j) - *(*(matrixB + i) + j);
            if (difference > maxDifference)
            {
                maxDifference = difference;
            }
        }
    }
    
    return maxDifference;
}
