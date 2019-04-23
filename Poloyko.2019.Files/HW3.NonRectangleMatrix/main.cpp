#include<iostream>
#include<fstream>

using namespace std;

typedef bool(*predicate)(double, double);
typedef bool(*ConditionToIncludeOrDelete)(double, int, int);

void CreateFile(char* fileName, int n, int*);
int ContentsFile(char*);
double** InitMatrix(char*, int, int*);
void AddFile(char* fileName, double** matrix, int n, int* dimension,const char* message);

double* allocateMemoryForArray(int n);
void mergeSort(double*, int, int, predicate);
void merge(double*, int, int, int, predicate);
void sortMatrix(double**,  int , int* , int*);
double** allocateMemory(int rows, int* dimensions);
double** deleteElementsInMatrix(double** , int , int* , int, int, int*,ConditionToIncludeOrDelete);
double* deleteElementsInArray(double* , int& , int , int , ConditionToIncludeOrDelete);

int inputRows();
int* inputDimensions(int);
void displayArray(double* array, int n);
void displayMatrix(double** matrix, int rows, int* dimensions);

bool ifNumberFits(double, int, int);
bool ifNumberOfOnesGreater(double, double);
int numberOnes(double);
int numberZeroes(double);
int inputNumberOfOnes();
int inputNumberOfZeroes();
int* InputRowsToSort(int);

int main(int argc, const char * argv[])
{
    
    char* fileName = "/Users/larisapoloyko/Desktop/XCode/Files/task.txt";
    int n = inputRows();
    int* dimension = inputDimensions(n);
    
    CreateFile(fileName, n, dimension);
    double** matrix = InitMatrix(fileName, n, dimension);
    
    displayMatrix(matrix, n, dimension);
    
    int* rowsToSort = InputRowsToSort(n);
    
    sortMatrix(matrix, n, dimension, rowsToSort);
    
    AddFile(fileName, matrix, n, dimension, "\nSorted matrix:\n");
    int ones = inputNumberOfOnes(), zeroes = inputNumberOfZeroes();
    matrix = deleteElementsInMatrix(matrix,  n, dimension,  ones,  zeroes, rowsToSort, ifNumberFits);
    AddFile(fileName, matrix, n, dimension, "Matrix without elements having corresponding amount of 0 and 1:\n ");
    
    //system("pause");
    return 0;
}

void CreateFile(char* fileName, int n, int* dimension)
{
    ofstream streamOut(fileName);
    
    if (!streamOut.is_open())
    {
        cout << "Cannot open file to write!" << endl;
        system("pause");
        exit(1);
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < dimension[i]; j++)
        {
            double temp;
            cout << "a[" << i+1<<"]["<<j+1<<"] = ";
            cin >> temp;
            streamOut.width(5);
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
    
    int count = 0, term;
    
    while (!streamIn.eof())
    {
        streamIn >> term;
        count++;
    }
    streamIn.close();
    return count;
}

double** InitMatrix(char* fileName, int n, int* dimension)
{
    ifstream streamIn(fileName);
    if (!streamIn.is_open())
    {
        cout << "Cannot open file to read!" << endl;
        system("pause");
        exit(1);
    }
    double** matrix = allocateMemory(n, dimension);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < dimension[i]; j++)
        {
            streamIn >> matrix[i][j];
        }
    }
    
    streamIn.close();
    return matrix;
}

void AddFile(char* fileName, double** matrix, int n, int* dimension,const char* message)
{
    ofstream streamOut(fileName, ios::app);
    
    if (!streamOut.is_open())
    {
        cout << "\nCannot open file to addition!\n";
        system("pause");
        exit(1);
    }
    streamOut << message;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < dimension[i]; j++)
        {
            streamOut.width(5);
            streamOut << matrix[i][j];
        }
        streamOut <<"\n";
    }
    streamOut.close();
}

void merge(double* array, int left, int mid, int right, predicate condition)
{
    if (array == nullptr)
    {
        throw std::invalid_argument("Array can not be null.");
    }
    
    if (left < 0 || mid < 0 || right < 0)
    {
        throw std::invalid_argument("Left, mid and right parameters can not be less 0.");
    }
    
    int pos1 = left, pos2 = mid + 1, pos3 = 0;
    
    double *temp = allocateMemoryForArray(right - left + 1);
    
    while (pos1 <= mid && pos2 <= right)
    {
        if (condition(array[pos2], array[pos1]))
        {
            temp[pos3++] = array[pos1++];
        }
        else
        {
            temp[pos3++] = array[pos2++];
        }
    }
    
    while (pos2 <= right)
    {
        temp[pos3++] = array[pos2++];
    }
    while (pos1 <= mid)
    {
        temp[pos3++] = array[pos1++];
    }
    
    for (pos3 = 0; pos3 < right - left + 1; pos3++)
    {
        array[left + pos3] = temp[pos3];
    }
    
    delete[] temp;
}

void mergeSort(double* array, int left, int right, predicate condition)
{
    if (array == nullptr)
    {
        throw std::invalid_argument("Array can not be null.");
    }
    
    if (left < 0 || right < 0)
    {
        throw std::invalid_argument("Left, mid and right parameters can not be less 0.");
    }
    
    int mid;
    
    if (left < right)
    {
        mid = left + (right - left) / 2;
        mergeSort(array, left, mid, condition);
        mergeSort(array, mid + 1, right, condition);
        merge(array, left, mid, right, condition);
    }
    else
    {
        return;
    }
    
}

void sortMatrix(double** matrix, int rows, int* dimensions, int* rowsToSort)
{
    if (rows <= 0)
    {
        throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
    }
    
    if (matrix == nullptr)
    {
        throw std::invalid_argument("Matrix can not be null.");
    }
    if (dimensions == nullptr)
    {
        throw std::invalid_argument("Array can not be null.");
    }
    if (rowsToSort == nullptr)
    {
        throw std::invalid_argument("Array can not be null.");
    }
    
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (i == rowsToSort[j])
        {
            mergeSort(matrix[i], 0, dimensions[i] - 1, ifNumberOfOnesGreater);
            j++;
        }
    }
}

double* allocateMemoryForArray(int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Number of elements in an array can not be less or equal 0.");
    }
    
    double* array = new double[n];
    return array;
}

bool ifNumberOfOnesGreater(double a, double b)
{
    return (numberOnes(a) > numberOnes(b));
}

int numberOnes(double a)
{
    int b = a;
    if (b == 1)
    {
        return 1;
    }
    int count = 0;
    while (abs(b))
    {
        if (abs(b) % 2 == 1)
            count++;
        b /= 2;
    }
    return count;
}

int numberZeroes(double a)
{
    int b = a;
    
    if (b == 0)
    {
        return 1;
    }
    int count = 0;
    while (abs(b))
    {
        if (abs(b) % 2 == 0)
            count++;
        b /= 2;
    }
    return count;
}

int inputNumberOfOnes()
{
    int a;
    while (true)
    {
        cout << "Please enter the number of 1 in the number to be copied, a = ";
        cin >> a;
        if (a >= 0)
        {
            return a;
        }
        throw std::invalid_argument("Number of 1 can not be less or equal 0.");
    }
}

int inputNumberOfZeroes()
{
    int b;
    while (true)
    {
        cout << "Please enter the number of 0 in the number to be copied, b = ";
        cin >> b;
        if (b >= 0)
        {
            return b;
        }
        throw std::invalid_argument("Number of 0 can not be less or equal 0.");
    }
}

bool ifNumberFits(double n, int a, int b)
{
    return (numberOnes(n) == a && numberZeroes(n) == b);
}

double** allocateMemory(int rows, int* dimensions)
{
    if (rows <= 0)
    {
        throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
    }
    if (dimensions == nullptr)
    {
        throw std::invalid_argument("Dimension array can not be null.");
    }
    
    double** matrix = new double*[rows];
    
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new double[dimensions[i]];
    }
    
    return matrix;
}

int inputRows()
{
    int rows;
    cout << "Enter the number of rows: ";
    cin >> rows;
    if (rows <= 0)
    {
        throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
    }
    return rows;
}

int* inputDimensions(int rows)
{
    if (rows <= 0)
    {
        throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
    }
    
    int* dimensions = new int[rows];
    
    if (dimensions == nullptr)
    {
        throw invalid_argument("The dimension of an array can not be 0.");
    }
    
    cout << "Initializing number of elements in a row..." << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "Row " << i + 1 << ": ";
        cin >> dimensions[i];
        
        if (dimensions[i] <= 0)
        {
            throw invalid_argument("Number of elements in a row can not be less than 0.");
        }
    }
    return dimensions;
}


void displayArray(double* array, int n)
{
    if (array == nullptr)
    {
        throw std::invalid_argument("Array can not be null.");
    }
    
    if (n <= 0)
    {
        throw std::invalid_argument("Count of array elements can not be less or equal 0.");
    }
    
    for (double* p = array; p < array + n; p++)
    {
        std::cout << *p << " ";
    }
    
    cout << endl;
}

void displayMatrix(double** matrix, int rows, int* dimensions)
{
    if (matrix == nullptr)
    {
        throw std::invalid_argument("Matrix can not be null.");
    }
    
    if (rows <= 0)
    {
        throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
    }
    
    if (dimensions == nullptr)
    {
        throw std::invalid_argument("Dimension array can not be null.");
    }
    
    for (int i = 0; i < rows; i++)
    {
        displayArray(matrix[i], dimensions[i]);
        cout <<endl;
    }
}

int* InputRowsToSort(int rows)
{
    cout << "Enter number of the rows to sort: ";
    int numberOfRows;
    cin >> numberOfRows;
    if (numberOfRows > rows)
    {
        throw invalid_argument("Number of the rows to sort can not be more than number of rows.");
    }
    int* rowsToSort = new int[numberOfRows];
    cout << "Enter indexes of the rows to sort(starting with 1)" << endl;
    for (int i = 0; i < numberOfRows; i++)
    {
        cout << "Inputting the " << i + 1 << " index: ";
        int currentIndex;
        cin >> currentIndex;
        rowsToSort[i] = currentIndex - 1;
        cout << endl;
    }
    
    return rowsToSort;
}

double** deleteElementsInMatrix(double** matrix, int rows, int* dimensions,int ones, int zeroes, int* rowsToSort,ConditionToIncludeOrDelete condition)
{
    if (matrix == nullptr)
    {
        throw std::invalid_argument("Matrix can not be null.");
    }
    if (rows <= 0)
    {
        throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
    }
    if (dimensions == nullptr)
    {
        throw std::invalid_argument("Dimension of an array can not be null.");
    }
    if (rowsToSort == nullptr)
    {
        throw std::invalid_argument("Dimension of an array can not be null.");
    }
    
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (i == rowsToSort[j])
        {
            matrix[i] = deleteElementsInArray(matrix[i], dimensions[i], ones, zeroes, condition);
            j++;
        }
    }
    return matrix;
}

double* deleteElementsInArray(double* array, int& n, int ones, int zeroes, ConditionToIncludeOrDelete condition)
{
    if (array == nullptr)
    {
        throw std::invalid_argument("Array can not be null.");
    }
    
    if (n <= 0)
    {
        throw std::invalid_argument("Count of array elements can not be less or equal 0.");
    }
    
    if (ones <= 0 || zeroes <= 0)
    {
        throw std::invalid_argument("Number of ones and zeroes cannot be less or equal 0.");
    }
    
    int copy = n;
    int length = 0;
    for (double *p = array; p < array + n; p++)
    {
        if (condition(*p, ones, zeroes))
        {
            length++;
        }
    }
    
    double* newArray = allocateMemoryForArray(length);
    
    
    for (int i = 0, j = 0; i < copy; i++)
    {
        if (!(condition(array[i], ones, zeroes)))
        {
            newArray[j] = array[i];
            j++;
        }
        else n--;
    }
    return newArray;
}
