// Author: Kent Tran
// CECS 325-02 Prog 4
// Due Date: 4/14/2026
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source including inappropriate AI use. I did not share this program with anyone. I
// further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cerr << "Error: Usage: generate COUNT MIN MAX" << endl;
        return 1;
    }

    int count = atoi(argv[1]);
    int minVal = atoi(argv[2]);
    int maxVal = atoi(argv[3]);

    srand(time(0));

    ofstream outFile("numbers.dat");
    if (!outFile)
    {
        cerr << "Error: Could not open numbers.dat for writing" << endl;
        return 1;
    }

    int range = maxVal - minVal + 1;
    for (int i = 0; i < count; i++)
    {
        outFile << (rand() % range) + minVal << "\n";

    }
    outFile.close();
    return 0;
}