#include "sortingalgorithm.h"
#include <vector>
#include <QDebug>
#include <QTime>

using namespace std;

template <class T>
void swap_ab(T &a, T &b)
{
    T value = a;
    a = b;
    b = value;
}

SortingAlgorithm::SortingAlgorithm()
{

}

bool SortingAlgorithm::sorting_Stepbystep(vector<int> &vc, vector<int> &position,SortType sortType)
{
    switch (sortType) {
    case Bubble_Sort:
        return sorting_SBS_Bubble_Sort(vc, position);
        break;
    case Select_Sort:
        return sorting_SBS_Selection_Sort(vc, position);
        break;
    default:
        return true;
    }
}

bool SortingAlgorithm::sorting_SBS_Bubble_Sort(vector<int> &vc, vector<int> &position)
{
    if (position[0] != position[1] && position[0] == position[2])
    {
        swap_ab(vc[position[0]], vc[position[1]]);
        swap_ab(position[0], position[1]);
        position[4] = position[0];
        return false;
    }
    else if (position[0] != position[1] && position[0] == position[3] -1)
    {
        bool is_completed = (position[4] == 1 ? true : false);
        position[3] = position[4];
        position[0] = 0;
        position[1] = 0;
        position[2] = 0;
        return is_completed;
    }
    else if (position[0] != position[1])
    {
        position[1] = position[0];
        position[2] = position[1];
        position[4] = position[1];
        return false;
    }
    else if (position[1] == position[2])
    {
        position[1] = position[1] + 1;
        position[0] = position[1];
        return false;
    }
    else
    {
        if (vc[position[1]] < vc[position[2]])
        {
            position[0] = position[2];
            return false;
        }
        else if (position[1] == position[3] - 1)
        {
            bool is_completed = (position[4] == 1 ? true : false);
            position[3] = position[4];
            position[0] = 0;
            position[1] = 0;
            position[2] = 0;
            position[4] = 1;
            return is_completed;
        }
        else
        {
            position[2] = position[1];
            return false;
        }
    }
}

bool SortingAlgorithm::sorting_SBS_Selection_Sort(vector<int> &vc, vector<int> &position)
{
    int vc_size = vc.size();

    if (vc[position[1]] > vc[position[2]])
    {
        if (vc_size - 1 > position[2])
        {
            position[0] = position[2];
            position[1] = position[2];
            position[2] = position[2] + 1;
            return false;
        }
        else if (position[3] == vc_size - 3)
        {
            swap_ab(vc[position[3] + 1], vc[position[2]]);
            position[3] = vc_size - 1;
            position[0] = position[3];
            position[1] = position[0];
            position[2] = position[1];
            return true;
        }
        else
        {
            swap_ab(vc[position[3] + 1], vc[position[2]]);
            position[3] = position[3] + 1;
            position[0] = position[3] + 1;
            position[1] = position[0];
            position[2] = position[1] + 1;
            return false;
        }
    }
    else if (position[2] == vc_size - 1)
    {
        swap_ab(vc[position[3] + 1], vc[position[0]]);

        if (position[3] == vc_size -3)
        {
            position[3] = vc_size - 1;
            position[0] = position[3];
            position[1] = position[0];
            position[2] = position[1];
            return true;
        }
        else
        {
            position[3]++;
            position[0] = position[3] + 1;
            position[1] = position[0];
            position[2] = position[1] + 1;
            return false;
        }
    }
    else
    {
        position[2]++;
        return false;
    }
}

vector<int> SortingAlgorithm::random_vector(int n)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    vector<int> r_vector(n, 0);
    vector<bool> b_vector(n, false);
    for (int k = n; k >= 1; k--)
    {
        int r = (k != 1) ? (qrand()%k + 1) : 1;

        for (int j = 0; j < n; j++)
        {
            if (b_vector[j])
            {
                r = r +1;
            }
            else if (j + 1 == r)
            {
                r_vector[n - k] = r;
                b_vector[j] = true;
            }
        }
    }

    return r_vector;
}
