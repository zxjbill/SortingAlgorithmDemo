#include "sortingalgorithm.h"
#include <vector>
#include <QDebug>
#include <QTime>
#include <math.h>

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
        break;
    case QuickSort:
        return sortingSbsQuickSort(vc, position);
        break;
    case ShellSort:
        return sortingSbsShellSort(vc, position);
        break;
    case HeapSort:
        return sortingSbsHeapSort(vc, position);
        break;
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
        position[2] = 1;  //作为是否交换顺序的标志

        position[3] = position[3] + 1;
        position[0] = position[3];
        return (position[3] == int(vc.size()) - 1) ? true : false;
    }

    if (vc[position[0]] > num)
    {
        --position[0];        
        position[2] = 0;  //作为是否交换顺序的标志
        return false;
    }
    else
    {
        vc.erase(vc.begin() + position[3] +1);
        vc.insert(vc.begin() + position[0] + 1, num);
        position[2] = 1;  //作为是否交换顺序的标志
        position[3] = position[3] + 1;
        position[0] = position[3];
        return (position[3] == int(vc.size()) - 1) ? true : false;
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

bool SortingAlgorithm::sortingSbsQuickSort(vector<int> &vc, vector<int> &position)
{
    // position 第0位：即将检测的数字位；第1位：对比数字位；
    // 第2位:现有前置位；第3位：现有后置位；
    // 第4位及4位以后：堆；

    if (position[0] - position[1] == 1 || position[1] - position[0] == 1)
    {
        if ((position[0] -position[1]) * (vc[position[0]] - vc[position[1]]) < 0)
        {
            swap_ab(vc[position[0]], vc[position[1]]);
            swap_ab(position[0], position[1]);
        }

        if(position[1] - position[2] > 2)
        {
            position.push_back(position[3]);
            position[3] = position[1];
            position[1] = position[3] - 1;
            position[0] = position[2] + 1;
            return false;
        }
        else
        {
            if (position[3] - position[2] > 2)
            {
                position[2] = position[1];
                position[1] = position[3] - 1;
                position[0] = position[2] + 1;
                return false;
            }
            else
            {
                if (position.size() > 4)
                {
                    position[2] = position[3];
                    position[3] = *(--position.end());
                    position.erase(--position.end());
                    position[1] = position[3] - 1;
                    position[0] = position[2] + 1;
                }
                else
                {
                    return true;
                }
            }
        }
    }

    if (position[0] > position[1])
    {
        if (vc[position[0]] > vc[position[1]])
        {
            --position[0];
            return false;
        }
        else
        {
            swap_ab(vc[position[0]], vc[position[1]]);
            swap_ab(position[0], position[1]);
            ++position[0];
            return false;
        }
    }
    else
    {
        if (vc[position[1]] > vc[position[0]])
        {
            ++position[0];
            return false;
        }
        else
        {
            swap_ab(vc[position[0]], vc[position[1]]);
            swap_ab(position[0], position[1]);
            --position[0];
            return false;
        }
    }
}

bool SortingAlgorithm::sortingSbsShellSort(vector<int> &vc, vector<int> &position)
{
    vector<int> now_vc;
    vector<int> insertPosition;
    int delta = position[3];

    for (int i = position[2]; i < int(vc.size()); i = i + delta)
    {
        now_vc.push_back(vc[i]);
    }

    insertPosition = vector<int>({position[0], 0, 0, position[1]});

    bool isOnceQuickDone = sortingSbsInsertSort(now_vc, insertPosition);

    if (insertPosition[2])
    {
        for (int i = 0; i < int(now_vc.size()); ++i)
        {
            vc[position[2] + i * delta] = now_vc[i];
        }
    }

    position[0] = insertPosition[0];

    position[1] = insertPosition[3];

    if (isOnceQuickDone)
    {
        if (position[2] + 1 < delta)
        {
            ++position[2];
            position[1] = 0;
            position[0] = 0;
            return false;
        }
        else
        {
            if (delta > 1)
            {
                position[3] = position[3] / 2;
                position[2] = 0;
                position[1] = 0;
                position[0] = 0;
                return false;
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

bool SortingAlgorithm::sortingSbsHeapSort(vector<int> &vc, vector<int> &position)
{
    // position:第2个数0代表建堆，非零代表出堆
    // 第3个数建堆最新位置，第4个数代表建堆下滑位
    // 第0个数出堆最新位置，第1个数出堆插入位置

    if (!position[2])
    {
        int next_position = BuildHeapSbs(vc, position[4], vc.size() - 1);

        if (next_position == position[4])
        {
            if (position[3] > 0)
            {
                --position[3];
                position[4] = position[3];
                return false;
            }
            else
            {
                position[2] = 1;
                swap_ab(vc[0], vc[vc.size() - 1]);
                position[0] = 0;
                position[1] = vc.size() - 2;
                position[3] = -1;
                position[4] = -1;
                return false;
            }
        }
        else
        {
            position[4] = next_position;
            return false;
        }
    }
    else
    {
        int next_position = BuildHeapSbs(vc, position[0], position[1]);

        if (next_position == position[0])
        {
            if (position[1] > 2)
            {
                swap_ab(vc[0], vc[position[1]]);
                --position[1];
                position[0] = 0;
                return false;
            }
            else
            {
                swap_ab(vc[0], vc[position[1]]);
                position[0] = 0;
                position[1] = 0;
                return true;
            }
        }
        else
        {
            position[0] = next_position;
            return false;
        }
    }
}

int SortingAlgorithm::BuildHeapSbs(vector<int> &vc, int position, int boundery)
{
    // TODO 要设置vc的边界
    // position: 建堆位置， 返回值位下一步建堆位置
    int num;
    int comparePosition;

    if (2 * position + 2 <= boundery && vc[2 * position + 1] < vc[2 * position + 2])
    {
        comparePosition = position * 2 + 2;
        num = vc[2 * position +2];
    }
    else
    {
        comparePosition = position * 2 + 1;
        num = vc[2 * position +1];
    }

    bool isSwap = false;

    if (num > vc[position])
    {
        isSwap = true;
        swap_ab(vc[position], vc[comparePosition]);
    }

    if (!isSwap || (comparePosition > ((boundery - 1) / 2)))
    {
        return position;
    }

    return comparePosition;
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
