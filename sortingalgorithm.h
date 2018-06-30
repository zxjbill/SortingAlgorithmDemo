#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H
#include "vector"

using namespace std;

class SortingAlgorithm
{
public:
    SortingAlgorithm();

    enum SortType {
        BubbleSort,
        SelectSort,
        InsertSort,
        InsertSortLog,
        QuickSort,
        ShellSort,
        HeapSort,
        MergeSort
    };

    static bool sortingStepbystep(vector<int> &vc, vector<int> &position, SortType sortType);
    static vector<int> randomVector(int n);
    static vector<int> positiveVector(int n);
    static vector<int> reverseVector(int n);

private:
    static bool sortingSbsBubbleSort(vector<int> &vc, vector<int> &position);
    static bool sortingSbsSelectionSort(vector<int> &vc, vector<int> &position);
    static bool sortingSbsInsertSort(vector<int> &vc, vector<int> &position);
    static bool sortingSbsInsertSortLog(vector<int> &vc, vector<int> &position);
    static bool sortingSbsQuickSort(vector<int> &vc, vector<int> &position);
    static bool sortingSbsShellSort(vector<int> &vc, vector<int> &position);
    static bool sortingSbsHeapSort(vector<int> &vc, vector<int> &position);
    static int BuildHeapSbs(vector<int> &vc, int position, int boundery);
    static bool sortingSbsMergeSort(vector<int> &vc, vector<int> &position);
};

#endif // SORTINGALGORITHM_H
