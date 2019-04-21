#include<iostream>
#include<fstream>

using namespace std;

typedef bool(*predicate)(double, double);
typedef bool(*conditionToIncludeOrDelete)(double, int, int);

double* allocateMemory(int);
double* deleteElements(double*, int&, int, int, conditionToIncludeOrDelete);

void mergeSort(double*, int, int, predicate);
void merge(double*, int, int, int, predicate);

void CreateFile(char* fileName, int n);
int ContentsFile(char*);
double* InitArray(char*, int);
void AddFile(char*, double*, int,const char*);
void inputArray(double* array, int n);

bool ifNumberOfOnesGreater(double, double);
bool ifNumberFits(double, int, int);
int numberOnes(double);
int numberZeroes(double);
int inputNumberOfOnes();
int inputNumberOfZeroes();

int main(int argc, const char * argv[])
{
    int ones = inputNumberOfOnes(), zeroes = inputNumberOfZeroes();
    
    
    const int N = 30;
    char* fileName = "/Users/larisapoloyko/Desktop/XCode/Files/task.txt";
    //cout << "Enter the name of file: ";
    //cin.getline(fileName, N, '\n');
    int n;
    cout << "Enter count of the numbers:";
    cin >> n;
    CreateFile(fileName, n);
    int count = ContentsFile(fileName);
    cout << count << endl;
    double* array = InitArray(fileName, count);
    mergeSort(array, 0, n - 1, ifNumberOfOnesGreater);
    
    AddFile(fileName, array, n, "\nSorted array:\n");
    
    array = deleteElements(array, n, ones, zeroes, ifNumberFits);
    
    AddFile(fileName, array, n, "\Without elements with corresponding amount of zeroes and ones:\n");
    
    //system("pause");
    return 0;
}

void CreateFile(char* fileName, int n)
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
    
    
    for (int i = 0; i < n; i++)
    {
        double temp;
        cout << "a[" << i + 1 << "] = ";
        cin >> temp;
        streamOut.width(5);
        streamOut << temp;
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

double* InitArray(char* fileName, int n)
{
    ifstream streamIn(fileName);
    if (!streamIn.is_open())
    {
        cout << "Cannot open file to read!" << endl;
        system("pause");
        exit(1);
    }
    double* arr = new double[n];
    
    for (int i = 0; i < n; i++)
    {
        streamIn >> arr[i];
    }
    streamIn.close();
    return arr;
}


void AddFile(char* fileName, double* arr, int n, const char* message)
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
        streamOut.width(5);
        streamOut << arr[i];
    }
    streamOut << "\n";
    streamOut.close();
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

double* deleteElements(double* array, int& n,int ones, int zeroes, conditionToIncludeOrDelete condition)
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
    
    double* new_array = new double [length];
    
    
    for (int i = 0, j = 0; i < copy; i++)
    {
        if (!(condition(array[i], ones, zeroes)))
        {
            new_array[j] = array[i];
            j++;
        }
        else n--;
    }
    return new_array;
}

double* allocateMemory(int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Count of array elements can not be less or equal 0.");
    }
    
    if (n <= 0)
    {
        return nullptr;
    }
    double* array = new double[n];
    return array;
}

bool ifNumberFits(double n, int a, int b)
{
    return (numberOnes(n) == a && numberZeroes(n) == b);
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
    
    double *temp = allocateMemory(right - left + 1);
    
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
