// Author: Kent Tran
// CECS 325-02 Prog 3
// Due Date: 3/5/2026
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source including inappropriate AI use. I did not share this program with anyone. I
// further certify that I typed each and every line of code in this program.

#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

//create a global variable which will keep track of all the swaps that take place
long long totalSwaps = 0;
mutex swapMutex;

struct ThreadData
{
    int* arr;
    int size;
    int processNum;
};

void printMessage(string quote, int threadNum)
{
    cout << "thread:" << threadNum << " " << quote << endl;
}

void bubble(ThreadData* data)
{
    int* arr = data->arr;
    int n = data->size;
    int pNum = data->processNum;
    long long localSwaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                localSwaps++;
            }
        }
    }

    cout << "Process " << pNum << "swap count:" << localSwaps << endl;

    swapMutex.lock();
    totalSwaps += localSwaps;
    swapMutex.unlock();
}

//merge 2 adjacent sections into a sorted super section
void merge(int* arr, int leftSide, int rightSide)
{
    int totalSize = leftSide + rightSide;
    int* temp = new int[totalSize];

    int i = 0;
    int j = leftSide;
    int k = 0;
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cerr << "Error: Usage: mysort inputfile outputfile -test" << endl;
        return 1;
    }

    bool test = false;
    if(argc == 4 && string(argv[3]) == "-test")
    {
        test = true;
    }

    //lambda expression, can write this in a if loop instead
    int totalNum = test ? 10000 : 1000000;

    ifstream inFile(argv[1]);
    if (!inFile)
    {
        cerr << "Error: Could not open input file: " << argv[1] << endl;
        return 1;
    }

    int* num = new int[totalNum];

    while (inFile >> num)
    {
        
    }
    inFile.close();

    bubble(nums);

    ofstream outFile(argv[2]);
    if(!outFile)
    {
        cerr << "Error: Could not open output file: " << argv[2] << endl;
        return 1;
    }

    for (int i = 0; i < (int)numbers.size(); i++)
    {
        outFile << numbers[i] << "\n";
    }
    outFile.close();

    delete[] num;
    return 0;
}