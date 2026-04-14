// Author: Kent Tran
// CECS 325-02 Prog 4
// Due Date: 4/14/2026
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
mutex mutexSwap;
mutex mutexPrint;

void bubble(int* arr, int n, string pNum)
{
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

    mutexPrint.lock();
    cout << pNum << " swap count: " << localSwaps << endl;
    mutexPrint.unlock();

    /* lock the thread to allow only the current thread to run until unlocked
    prevents it from being accessed by multiple threads
    */
    mutexSwap.lock();
    totalSwaps += localSwaps;
    mutexSwap.unlock();
}

//merge 2 adjacent sections into a sorted super section
void merge(int* arr, int leftSide, int rightSide)
{
    int totalSize = leftSide + rightSide;
    int n = leftSide;
    int m = rightSide;
    int i = 0, j = 0, k = 0;
    int* merged = new int[totalSize];

    while(i < n && j < m)
    {
        if(arr[i] <= arr[n + j])
        {
            merged[k] = arr[i];
            i++;
        }
        else
        {
            merged[k] = arr[n + j];
            j++;
        }
        k++;
    }

    while (i < n)
    {
        merged[k] = arr[i];
        i++;
        k++;
    }

    while (j < m)
    {
        merged[k] = arr[n + j];
        j++;
        k++;
    }

    for(int x = 0; x < totalSize; x++)
    {
        arr[x] = merged[x];
    }

    delete[] merged;
}

int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 4)
    {
        cerr << "Error: Usage: mysort inputfile outputfile [-test]" << endl;
        return 1;
    }

    bool test = false;
    if(argc == 4)
    {
        if (string(argv[3]) == "-test")
        {
            test = true;
        }
        else
        {
            cerr << "Error: Usage: mysort inputfile outputfile [-test]" << endl;
        }
    }

    //changes totalNum to 10k if it's in test mode
    int totalNum = 1000000;
    if(test)
    {
        totalNum = 10000;
    }

    ifstream inFile(argv[1]);
    if (!inFile)
    {
        cerr << "Error: Could not open input file: " << argv[1] << endl;
        return 1;
    }

    int* num = new int[totalNum];

    int count = 0;
    while(count < totalNum && inFile >> num[count])
    {
        count++;
    }
    inFile.close();

    int NUM_THREADS = 16;
    int sectionSize = count / NUM_THREADS;

    thread* threads = new thread[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++)
    {
        threads[i] = thread(bubble, num + (i * sectionSize), 
                            sectionSize, "Process " + to_string(i));
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads[i].join();
    }

    cout << "Total Swaps: " << totalSwaps << endl;

    delete[] threads;

    int currentSize = sectionSize;
    int currentSection = NUM_THREADS;

    while (currentSection > 1)
    {
        for (int i = 0; i < currentSection; i += 2)
        {
            merge(num + (i * currentSize), currentSize, currentSize);
        }
        currentSize *= 2;
        currentSection /= 2;
    }

    ofstream outFile(argv[2]);
    if(!outFile)
    {
        cerr << "Error: Could not open output file: " << argv[2] << endl;
        delete[] num;
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        outFile << num[i] << endl;
    }
    outFile.close();

    delete[] num;
    return 0;
}