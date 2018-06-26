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

bool SortingAlgorithm::sortingStepbystep(vector<int> &vc, vector<int> &position,SortType sortType)
{
    switch (sortType) {
    case BubbleSort:
        return sortingSbsBubbleSort(vc, position);
        break;
    case SelectSort:
        return sortingSbsSelectionSort(vc, position);
        break;
    case InsertSort:
        return sortingSbsInsertSort(vc, position);
        break;
    case InsertSortLog:
        return sortingSbsInsertSortLog(vc, position);
    default:
        return true;
    }
}

bool SortingAlgorithm::sortingSbsBubbleSort(vector<int> &vc, vector<int> &position)
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

bool SortingAlgorithm::sortingSbsSelectionSort(vector<int> &vc, vector<int> &position)
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

bool SortingAlgorithm::sortingSbsInsertSort(vector<int> &vc, vector<int> &position)
{
    auto num = vc[position[3] + 1];

    if (position[0] == -1)
    {
        vc.erase(vc.begin() + position[3] +1);
        vc.insert(vc.begin(), num);

        position[3] = position[3] + 1;
        position[0] = position[3];
        return (position[3] == vc.size() - 1) ? true : false;
    }

    if (vc[position[0]] > num)
    {
        --position[0];
        return false;
    }
    else
    {
        vc.erase(vc.begin() + position[3] +1);
        vc.insert(vc.begin() + position[0] + 1, num);
        position[3] = position[3] + 1;
        position[0] = position[3];
        return (position[3] == vc.size() - 1) ? true : false;
    }
}

bool SortingAlgorithm::sortingSbsInsertSortLog(vector<int> &vc, vector<int> &position)
{
    int num = vc[position[3] + 1];
    int insert_position = -1;
    bool isDone = false;

    if (num < vc[position[0]])
    {
        if (position[0] == 0)
        {
            insert_position = 0;
        }
        else
        {
            position[2] = position[0];
            position[0] = (position[0] + position[1]) / 2;
        }
    }
    else if (num == vc[position[0]])
    {
        insert_position = position[0];
    }
    else
    {
        if (position[0] == position[3])
        {
            insert_position = position[3] + 1;
        }
        else if (position[0] - position[2] == -1)
        {
            insert_position = position[2];
        }
        else
        {
            position[1] = position[0];
            position[0] = (position[1] + position[2]) / 2;
        }
    }

    if (insert_position != -1)
    {
        vc.erase(vc.begin() + position[3] +1);
        vc.insert(vc.begin() + insert_position, num);

        isDone = position[3] == vc.size() -2;
        position[3] = position[3] + 1;
        position[2] = position[3];
        position[1] = 0;
        position[0] = position[3];
    }

    return isDone;
}

vector<int> SortingAlgorithm::randomVector(int n)
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

vector<int> SortingAlgorithm::positiveVector(int n)
{
    vector<int> vc(n, 0);

    for (int i = 0; i < n; i++)
    {
        vc[i] = i + 1;
    }

    return vc;
}

vector<int> SortingAlgorithm::reverseVector(int n)
{
    vector<int> vc(n,0);

    for (int i = 0; i < n; i++)
    {
        vc[i] = n - i;
    }

    return vc;
}
