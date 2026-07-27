#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

// ======================================
// Data Structure
// ======================================
struct Record
{
    int number;
};

// Global array allocated safely to handle up to 50,000 records
Record records[50000];
int dataSize = 100;

// ======================================
// Core Functions
// ======================================
void generateData()
{
    for(int i = 0; i < dataSize; i++)
    {
        records[i].number = rand() % 1000000; // Generates clean random values
    }
    cout << "\n[System] " << dataSize << " Data Records Generated Successfully!\n";
}

void displayRecords()
{
    cout << "\n========== RECORDS ==========\n";

    if (dataSize <= 100) 
    {
        // If dataset is 100 or less, print everything
        for(int i = 0; i < dataSize; i++)
        {
            cout << records[i].number << "\t";
            if ((i + 1) % 10 == 0) cout << "\n";
        }
    } 
    else 
    {
        // If dataset is massive, print first 50 to prove it sorted the smallest numbers
        for(int i = 0; i < 50; i++)
        {
            cout << records[i].number << "\t";
            if ((i + 1) % 10 == 0) cout << "\n";
        }

        cout << "\n... [ " << dataSize - 100 << " records hidden to save screen space ] ...\n\n";

        // Print the last 50 to prove it sorted the largest numbers
        for(int i = dataSize - 50; i < dataSize; i++)
        {
            cout << records[i].number << "\t";
            if ((i - (dataSize - 50) + 1) % 10 == 0) cout << "\n";
        }
    }

    cout << "\nTotal records currently in system: " << dataSize << endl;
}

void swapRecord(Record &a, Record &b)
{
    Record temp = a;
    a = b;
    b = temp;
}

void pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ======================================
// Sorting Algorithms
// ======================================
void selectionSort()
{
    for(int i = 0; i < dataSize - 1; i++)
    {
        int min = i;
        for(int j = i + 1; j < dataSize; j++)
        {
            if(records[j].number < records[min].number)
            {
                min = j;
            }
        }
        swapRecord(records[i], records[min]);
    }
}

int partition(int low, int high)
{
    int pivot = records[high].number;
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(records[j].number < pivot)
        {
            i++;
            swapRecord(records[i], records[j]);
        }
    }
    swapRecord(records[i + 1], records[high]);
    return i + 1;
}

void quickSort(int low, int high)
{
    if(low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void merge(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Record> L(n1);
    vector<Record> R(n2);

    for(int i = 0; i < n1; i++) L[i] = records[left + i];
    for(int j = 0; j < n2; j++) R[j] = records[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2)
    {
        if(L[i].number <= R[j].number)
        {
            records[k] = L[i];
            i++;
        }
        else
        {
            records[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1) { records[k] = L[i]; i++; k++; }
    while(j < n2) { records[k] = R[j]; j++; k++; }
}

void mergeSort(int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

// ======================================
// Searching Algorithms
// ======================================
int binarySearch(int key)
{
    int left = 0;
    int right = dataSize - 1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(records[mid].number == key) return mid;
        if(records[mid].number < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int interpolationSearch(int key)
{
    int low = 0;
    int high = dataSize - 1;
    while(low <= high && key >= records[low].number && key <= records[high].number)
    {
        if(records[high].number == records[low].number)
        {
            if(records[low].number == key) return low;
            return -1;
        }
        int pos = low + ((double)(high - low) / (records[high].number - records[low].number) * (key - records[low].number));
        if(pos < low || pos > high) return -1;
        if(records[pos].number == key) return pos;
        if(records[pos].number < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// ======================================
// Main Function & CLI
// ======================================
int main()
{
    srand(time(0));
    int sizeChoice;

    cout << "=====================================\n";
    cout << "      SELECT DATA SIZE\n";
    cout << "=====================================\n";
    cout << "1. 100 Records\n2. 500 Records\n3. 1000 Records\n4. 5000 Records\n5. 10000 Records\n6. 50000 Records\n";
    cout << "Enter your choice: ";
    cin >> sizeChoice;

    switch(sizeChoice)
    {
        case 1: dataSize = 100; break;
        case 2: dataSize = 500; break;
        case 3: dataSize = 1000; break;
        case 4: dataSize = 5000; break;
        case 5: dataSize = 10000; break;
        case 6: dataSize = 50000; break;
        default: dataSize = 100;
    }

    generateData();
    
    char choice;
    bool isRunning = true;

    do
    {
        cout << "\n=====================================\n";
        cout << "      DSA MINI PROJECT\n";
        cout << "=====================================\n";
        cout << "A. Display All Records\n";
        cout << "B. Sort Records\n";
        cout << "C. Search for Number\n";
        cout << "R. Regenerate New Random Dataset\n"; // Kept your custom feature under 'R'
        cout << "D. Exit Application\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        choice = toupper(choice); // Handles lowercase inputs seamlessly

        // Clear input buffer safely after reading char
        cin.ignore(256, '\n'); 

        switch(choice)
        {
            case 'A':
                displayRecords();
                pause();
                break;

            case 'B':
            {
                int sortChoice;
                cout << "\n----- SORT MENU -----\n";
                cout << "1. Selection Sort\n2. Quick Sort\n3. Merge Sort\nEnter your choice: ";
                cin >> sortChoice;
                cin.ignore(256, '\n');

                auto start = steady_clock::now();
                switch(sortChoice)
                {
                    case 1: selectionSort(); cout << "\nSelection Sort Completed.\n"; break;
                    case 2: quickSort(0, dataSize - 1); cout << "\nQuick Sort Completed.\n"; break;
                    case 3: mergeSort(0, dataSize - 1); cout << "\nMerge Sort Completed.\n"; break;
                    default: cout << "\nInvalid Choice!\n"; continue;
                }
                auto stop = steady_clock::now();
                duration<double, milli> dynamic_time = stop - start;

                cout << "Time Taken: " << dynamic_time.count() << " ms\n";
                displayRecords();
                pause();
                break;
            }

            case 'C':
            {
                int searchChoice, key;
                cout << "\n----- SEARCH MENU -----\n";
                cout << "1. Binary Search\n2. Interpolation Search\nEnter your choice: ";
                cin >> searchChoice;
                cin.ignore(256, '\n');

                if(searchChoice != 1 && searchChoice != 2) 
                {
                    cout << "Invalid Choice!\n";
                    break;
                }

                cout << "Enter number to search: ";
                cin >> key;
                cin.ignore(256, '\n');

                auto start = steady_clock::now();
                int result = (searchChoice == 1) ? binarySearch(key) : interpolationSearch(key);
                auto stop = steady_clock::now();
                duration<double, milli> dynamic_time = stop - start;

                if(result != -1) cout << "\nNumber Found at Index: " << result << endl;
                else cout << "\nNumber Not Found.\n";
                
                cout << "Time Taken: " << dynamic_time.count() << " ms\n";
                pause();
                break;
            }
            
            case 'R':
                generateData();
                break;
                
            case 'D':
                cout << "\nExiting Program. Goodbye!\n";
                isRunning = false;
                break;
                
            default:
                cout << "\nInvalid option. Please enter A, B, C, R, or D.\n";
        }
    } while(isRunning);

    return 0;
}