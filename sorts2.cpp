#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cmath>

using namespace std;

//TO WHOEVER IS MARKING MY CODE, PLEASE NOTE:
//I did the copying of the original vector for merge sort and quick sort outside of the timing parts so it is not included in my times

void copyVector(vector<long long> numbers, vector<long long> &copiedV)
{
    for (int i = 0; i < numbers.size(); i++)
    {
        copiedV[i] = numbers[i];
    }
}

void generateVector(vector<long long> &numbers, int N)
{
    numbers.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (int i = 0; i < N; i++)
    {
        numbers.push_back(dis(gen));
    }
}

//INSERTION SORT
vector<long long> insertionSort(vector<long long> numbers)
{
    long long x;
    int j = 0;
    for (int i = 1; i < numbers.size(); i++)
    {
        x = numbers[i];
        j = i - 1;
        while ((j >= 0) && (numbers[j] > x))
        {
            numbers[j + 1] = numbers[j];
            j--;
            if (j < 0)
            {
                break;
            }
        }
        if (j + 1 < numbers.size())
        {
            numbers[j + 1] = x;
        }
    }
    return numbers;
}

//MERGE SORT
void mergeSort(int left, int right, vector<long long> &numbers, vector<long long> &temp)
{
    if (right - left > 0)
    {
        int mid = floor((left + right) / 2);
        mergeSort(left, mid, numbers, temp);
        mergeSort(mid + 1, right, numbers, temp);
        for (int i = mid; i >= left; i--)
        {
            temp[i] = numbers[i];
        }
        for (int j = mid + 1; j <= right; j++)
        {
            temp[right + mid + 1 - j] = numbers[j];
        }
        int i = left;
        int j = right;
        for (int k = left; k <= right; k++)
        {
            if (temp[i] < temp[j])
            {
                numbers[k] = temp[i];
                i++;
            }
            else
            {
                numbers[k] = temp[j];
                j--;
            }
        }
    }
}

vector<long long> performMergeSort(vector<long long> numbers, int N)
{
    vector<long long> temp(N);
    vector<long long> numbers3(N);
    copyVector(numbers, numbers3);
    mergeSort(0, numbers.size() - 1, numbers3, temp);

    return numbers3;
}

vector<long long> selectionSort(vector<long long> numbers)
{

    int minPos;
    int temp;
    for (int i = 0; i <= numbers.size() - 2; i++)
    {
        minPos = i;
        for (int j = i + 1; j <= numbers.size() - 1; j++)
        {
            if (numbers[j] < numbers[minPos])
            {
                minPos = j;
            }
        }
        //swap
        temp = numbers[minPos];
        numbers[minPos] = numbers[i];
        numbers[i] = temp;
    }
    return numbers;
}

vector<long long> bubbleSort(vector<long long> numbers)
{

    int temp;
    for (int i = numbers.size() - 1; i >= 1; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                //swap
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    return numbers;
}

vector<long long> bubbleSortEscapeClause(vector<long long> numbers)
{

    int temp;

    int i = numbers.size() - 1;
    bool sorting = true;
    bool swopped;
    while (i >= 1 && sorting == true)
    {
        swopped = false;
        for (int j = 0; j <= i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                //swap
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                swopped = true;
            }
        }
        if (swopped == false)
        {
            sorting = false;
        }
        else
        {
            i = i - 1;
        }
    }
    return numbers;
}

//QUICK SORT
void quickSort(int left, int right, vector<long long> &numbers)
{
    int t;
    if (right > left)
    {
        int v = numbers[right];
        int i = left;
        int j = right;
        while (i < j)
        {
            while (numbers[i] < v)
            {
                i++;
            }
            while ((j > i) && (numbers[j] >= v))
            {
                j--;
            }
            if (j > i)
            {
                t = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = t;
            }
            else
            {
                t = numbers[i];
                numbers[i] = numbers[right];
                numbers[right] = t;
            } //if
        }     //while
        quickSort(left, i - 1, numbers);
        quickSort(i + 1, right, numbers);
    } //huge if
}

vector<long long> performQuicksort(vector<long long> numbers, int N)
{
    vector<long long> numbers3(N);
    copyVector(numbers, numbers3);
    quickSort(0, numbers.size() - 1, numbers3);

    return numbers3;
}

//DISPLAY VECTORS TO TEST IF SORTING ALGOS WORK
void displayVector(vector<long long> numbers)
{
    for (int i = 0; i < 10; i++)
    {
        cout << to_string(numbers[i]) << " ";
    }
    cout << endl;
}

int main()
{
    vector<long long> numbers;

    //clear text file to re-write it each time attempt is re-run
    std::ofstream outfile;
    fstream ofs;
    ofs.open("data2.txt", ios::out | ios::trunc);
    ofs.close();
    outfile.open("data2.txt", std::ios_base::app);

    //TESTING TO SEE IF SORTING ALGOS WORK
    int N = 10;
    generateVector(numbers, N);

    //original numbers
    displayVector(numbers);
    cout << endl;

    //INSERTION SORT

    vector<long long> numbers5 = insertionSort(numbers);

    displayVector(numbers5);

    //MERGE SORT
    vector<long long> numbers3 = performMergeSort(numbers, N);
    displayVector(numbers3);

    //QUICK SORT
    vector<long long> numbers4 = performQuicksort(numbers, N);
    displayVector(numbers4);

    //=======================================================================================================
    //TIMING OF ALGORITHMS
    //lists to store time data of the sorting algos
    list<long long> iSort;
    list<long long> mSort;
    list<long long> qSort;
    list<long long> bSort;
    list<long long> bSortEsc;
    list<long long> sSort;

    //set average runs to 5
    int n_runs = 5;
    vector<long long> numbers2;
    long long average_time1, average_time2, average_time3, average_time4, average_time5, average_time6;

    //get average of times
    for (int N = 1000; N <= 20000; N += 1000)
    {
        //output what N is so that it is known where algo currently is in running state
        cout << N << endl;
        long long total_time1 = 0;
        long long total_time2 = 0;
        long long total_time3 = 0;
        long long total_time4 = 0;
        long long total_time5 = 0;
        long long total_time6 = 0;
        for (int i = 0; i < n_runs; i++)
        {
            //generate the random number filled vector of size N
            generateVector(numbers, N);

            //time selection sort
            auto start = chrono::high_resolution_clock::now();
            numbers2 = selectionSort(numbers);
            auto finish = chrono::high_resolution_clock::now();
            long long nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time4 = total_time4 + nanoseconds;

            //time bubble sort
            start = chrono::high_resolution_clock::now();
            numbers2 = bubbleSort(numbers);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time5 = total_time5 + nanoseconds;

            //time bubble sort with escape clause
            start = chrono::high_resolution_clock::now();
            numbers2 = bubbleSortEscapeClause(numbers);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time6 = total_time6 + nanoseconds;

            //time insertion sort
            start = chrono::high_resolution_clock::now();
            numbers2 = insertionSort(numbers);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time1 = total_time1 + nanoseconds;

            //time merge sort
            vector<long long> temp(N);
            copyVector(numbers, numbers2);
            start = chrono::high_resolution_clock::now();
            mergeSort(0, numbers.size() - 1, numbers2, temp);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time2 = total_time2 + nanoseconds;

            //time quick sort
            copyVector(numbers, numbers2);
            start = chrono::high_resolution_clock::now();
            quickSort(0, numbers.size() - 1, numbers2);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time3 = total_time3 + nanoseconds;
        }

        //calculate average times

        //avg time insertion sort
        average_time1 = total_time1 / n_runs;
        iSort.push_back(average_time1);
        //average time merge sort
        average_time2 = total_time2 / n_runs;
        mSort.push_back(average_time2);
        //average time quick sort
        average_time3 = total_time3 / n_runs;
        qSort.push_back(average_time3);
        //average time selection sort
        average_time4 = total_time4 / n_runs;
        sSort.push_back(average_time4);
        //average time bubble sort
        average_time5 = total_time5 / n_runs;
        bSort.push_back(average_time5);
        //average time bubble sort with escape clause
        average_time6 = total_time6 / n_runs;
        bSortEsc.push_back(average_time6);
    }

    //display that algo is done
    cout << "done" << endl;

    //====================================================================
    // APPEND TO TEXT FILE

    std::list<long long>::iterator it;

    //append selection sort

    for (it = sSort.begin(); it != sSort.end(); ++it)
    {
        if (std::prev(sSort.end()) == it)
        {
            outfile << *it;
        }
        else
        {
            outfile << *it << ",";
        }
    }

    //append bubble sort
    outfile << "\n";
    for (it = bSort.begin(); it != bSort.end(); ++it)
    {
        if (std::prev(bSort.end()) == it)
        {
            outfile << *it;
        }
        else
        {
            outfile << *it << ",";
        }
    }

    //append bubble sort with escape clause
    outfile << "\n";
    for (it = bSortEsc.begin(); it != bSortEsc.end(); ++it)
    {
        if (std::prev(bSortEsc.end()) == it)
        {
            outfile << *it;
        }
        else
        {
            outfile << *it << ",";
        }
    }

    //append insertion sort
    outfile << "\n";
    for (it = iSort.begin(); it != iSort.end(); ++it)
    {
        if (std::prev(iSort.end()) == it)
        {
            outfile << *it;
        }
        else
        {
            outfile << *it << ",";
        }
    }

    //append merge sort
    outfile << "\n";
    for (it = mSort.begin(); it != mSort.end(); ++it)
    {
        if (std::prev(mSort.end()) == it)
        {
            outfile << *it;
        }
        else
        {
            outfile << *it << ",";
        }
    }

    //append quicksort
    outfile << "\n";
    for (it = qSort.begin(); it != qSort.end(); ++it)
    {
        if (std::prev(qSort.end()) == it)
        {
            outfile << *it;
        }
        else
        {
            outfile << *it << ",";
        }
    }

    return 0;
}
