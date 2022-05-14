#include <bits/stdc++.h>
using namespace std;
#define N 10
int infinite = INT_MAX;
int mini = infinite;
int chk = 0;
int visited[N] = {0};
int initReductionCost = 0; // r cap
int reductionCost1 = 0;
int reductionCost2 = 0; // r1 cap
int parentCost = 0;     // previous parent cost
int parentCost1 = 0;
int parentCost2 = 0;
int totalCost = 0;
int cost1cost = infinite;
int cost2cost = infinite;
int city[N][N] = {
    {infinite, 5, 2, 7, 3, 8, 1, 5, 7, 3},
    {5, infinite, 4, 8, 11, 2, 9, 5, 1, 6},
    {2, 4, infinite, 3, 5, 1, infinite, 2, 6, infinite},
    {7, 8, 3, infinite, 1, 5, 6, 7, infinite, 3},
    {3, 11, 5, 1, infinite, 4, 1, 3, 2, 9},
    {8, 2, 1, 5, 4, infinite, 9, 6, 4, 5},
    {1, 9, infinite, 6, 1, 9, infinite, 3, 1, 2},
    {5, 5, 2, 7, 3, 6, 3, infinite, 5, 4},
    {7, 1, 6, infinite, 2, 4, 1, 5, infinite, 9},
    {3, 6, infinite, 3, 9, 5, 2, 4, 9, infinite}};
int comp1[N][N], comp2[N][N];
void display()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << comp1[i][j] << " \t";
        }
        cout << endl;
    }
    cout << "Initial reduction Cost = " << initReductionCost << endl;
}
void findInitCost() // For initial reduction
{
    for (int i = 0; i < N; i++)
    {
        mini = infinite;
        for (int j = 0; j < N; j++)
        {
            if (city[i][j] < mini)
            {
                mini = city[i][j];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (city[i][j] != infinite)
                city[i][j] = city[i][j] - mini;
        }
        initReductionCost = initReductionCost + mini;
    }
    for (int i = 0; i < N; i++)
    {
        mini = infinite;
        for (int j = 0; j < N; j++)
        {
            if (city[j][i] < mini)
            {
                mini = city[j][i];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (city[j][i] != infinite)
                city[j][i] = city[j][i] - mini;
        }
        initReductionCost = initReductionCost + mini;
    }
    parentCost = initReductionCost;
    totalCost = totalCost + parentCost;
    cout << endl
         << "Initial Reduction:" << initReductionCost << endl;
    cout << "Parent Cost:" << parentCost << endl;
    cout << "Total Cost:" << totalCost << endl;
}
int ReductionMatrix1()
{
    reductionCost1 = 0;
    for (int i = 0; i < N; i++)
    {
        mini = infinite;
        for (int j = 0; j < N; j++)
        {
            if (comp1[i][j] < mini)
            {
                mini = comp1[i][j];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (comp1[i][j] != infinite)
            {
                comp1[i][j] = comp1[i][j] - mini;
            }
        }
        if (mini == infinite)
        {
            mini = 0;
        }
        reductionCost1 = reductionCost1 + mini;
    }
    for (int i = 0; i < N; i++)
    {
        mini = infinite;
        for (int j = 0; j < N; j++)
        {
            if (comp1[j][i] < mini)
            {
                mini = comp1[j][i];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (comp1[j][i] != infinite)
            {
                comp1[j][i] = comp1[j][i] - mini;
            }
        }
        if (mini == infinite)
        {
            mini = 0;
        }
        reductionCost1 = reductionCost1 + mini;
    }
    parentCost1 = parentCost + reductionCost1;
    return parentCost1;
}
int ReductionMatrix2()
{
    reductionCost2 = 0;
    for (int i = 0; i < N; i++)
    {
        mini = infinite;
        for (int j = 0; j < N; j++)
        {
            if (comp2[i][j] < mini)
            {
                mini = comp2[i][j];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (comp2[i][j] != infinite)
                comp2[i][j] = comp2[i][j] - mini;
        }
        if (mini == infinite)
        {
            mini = 0;
        }
        reductionCost2 = reductionCost2 + mini;
    }
    for (int i = 0; i < N; i++)
    {
        mini = infinite;
        for (int j = 0; j < N; j++)
        {
            if (comp2[j][i] < mini)
            {
                mini = comp2[j][i];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (comp2[j][i] != infinite)
            {
                comp2[j][i] = comp2[j][i] - mini;
            }
        }
        if (mini == infinite)
        {
            mini = 0;
        }
        reductionCost2 = reductionCost2 + mini;
    }
    parentCost2 = parentCost + reductionCost2;
    return parentCost2;
}
void initializeComp1()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            comp1[i][j] = 0;
        }
    }
}
void initializeComp2()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            comp2[i][j] = 0;
        }
    }
}
void copy1(int cno, int ncno)
{
    for (int i = 0; i < N; i++)
    {
        comp1[cno][i] = infinite;
        comp1[i][ncno] = infinite;
    }
    comp1[ncno][0] = infinite;
    // comp1[ncno][cno]=infinite;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (comp1[i][j] == 0)
            {
                comp1[i][j] = city[i][j];
            }
        }
    }
    cost1cost = ReductionMatrix1();
    cost1cost = cost1cost + city[cno][ncno];
}
void copy2(int cno, int ncno)
{
    for (int i = 0; i < N; i++)
    {
        comp2[cno][i] = infinite;
        comp2[i][ncno] = infinite;
    }
    comp2[ncno][0] = infinite;
    // comp2[ncno][cno]=infinite;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (comp2[i][j] == 0)
            {
                comp2[i][j] = city[i][j];
            }
        }
    }
    cost2cost = ReductionMatrix2();
    cost2cost = parentCost2 + city[cno][ncno];
}
void copyCity1()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            city[i][j] = comp1[i][j];
        }
    }
}
void copyCity2()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            city[i][j] = comp2[i][j];
        }
    }
}
void findPath(int cno)
{
    cost1cost = infinite;
    cost2cost = infinite;
    chk++;
    cout << cno + 1;
    visited[cno] = 1;
    int i1, i2;
    for (int i = 1; i < N; i++)
    {
        if (visited[i] == 0)
        {
            if (cost1cost > cost2cost)
            {
                copy1(cno, i);
                i1 = i;
            }
            else
            {
                copy2(cno, i);
                i2 = i;
            }
            if (cost1cost < cost2cost)
            {
                initializeComp2();
            }
            else
            {
                initializeComp1();
            }
        }
    }
    parentCost = min(cost1cost, cost2cost);
    // cout<<endl<<"Parent Cost = "<<parentCost<<endl;
    totalCost = totalCost + parentCost;
    if (cost1cost < cost2cost)
    {
        copyCity1();
        initializeComp1();
        initializeComp2();
    }
    else
    {
        copyCity2();
        initializeComp1();
        initializeComp2();
    }
    if (chk != 10)
    {
        cout << "-->";
        if (cost1cost < cost2cost)
        {
            findPath(i1);
        }
        else
        {
            findPath(i2);
        }
    }
}
int main(int argc, char const *argv[])
{
    int noOfCouriers[10];
    int choice;
    cout << endl
         << "Select your preference:" << endl
         << endl;
    cout << "Press 1 for fuel efficient path:" << endl
         << endl;
    cout << "Press 2 for proirity based path:" << endl
         << endl;
    cout << "Enter choice:";
    cin >> choice;
    if (choice == 1) // TSP
    {
        cout << "The fuel efficient path will be: " << endl;
        initializeComp1();
        initializeComp2();
        findInitCost();
        findPath(0);
        cout << endl
             << "The total cost for this path =  " << totalCost << endl;
    }
    else if (choice == 2) // Flloyd Warshall
    {
        cout << endl
             << "Enter the number of couriers to be delivered in the following cities:" << endl
             << endl;
        for (int i = 0; i < N; i++)
        {
            cout << endl
                 << "Enter number of couriers for city " << i + 1 << ":";
            cin >> noOfCouriers[i];
        }
    }
    else
    {
        cout << "Invalid Choice:";
    }
    cin >> choice;
    return 0;
}