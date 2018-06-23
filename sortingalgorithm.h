#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H
#include "vector"

using namespace std;

class SortingAlgorithm
{
public:
    SortingAlgorithm();
    enum SortType {Bubble_Sort, SortType2};
    static bool sorting_Stepbystep(vector<int> &vc, vector<int> &position, SortType sortType);
    static vector<int> random_vector(int n);

private:
    static bool sorting_SBS_Bubble_Sort(vector<int> &vc, vector<int> &position);
};

#endif // SORTINGALGORITHM_H
