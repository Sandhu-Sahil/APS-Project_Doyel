
#include <bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define N 10
int infinite = INT_MAX;
int mini = infinite;
int chk = 0;
int visited[N] = {0};
int initReductionCost = 0; // r cap
int reductionCost1 = 0;    // r1 cap
int reductionCost2 = 0;    // r2 cap
int parentCost = 0;        // previous parent cost
int parentCost1 = 0;       // comp1 costing
int parentCost2 = 0;       // comp2 costing
int totalCost = 0;         // final cost
string path;               // path
int comp1Cost, comp2Cost;
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
void display(int matrix[N][N])
{
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] != infinite)
                cout << matrix[i][j] << "\t";
            else
                cout << "X\t";
        }
        cout << endl << endl;
    }
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
    cout << endl;
    display(city);
    cout << endl;
    totalCost = parentCost = initReductionCost;
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
        if (mini != infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp1[i][j] != infinite)
                {
                    comp1[i][j] = comp1[i][j] - mini;
                }
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
        if (mini != infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp1[j][i] != infinite)
                {
                    comp1[j][i] = comp1[j][i] - mini;
                }
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
        if (mini != infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp2[i][j] != infinite)
                    comp2[i][j] = comp2[i][j] - mini;
            }
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
        if (mini != infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp2[j][i] != infinite)
                {
                    comp2[j][i] = comp2[j][i] - mini;
                }
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
void initialize(int comp[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            comp[i][j] = 0;
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
    comp1Cost = ReductionMatrix1();
    comp1Cost = comp1Cost + city[cno][ncno];
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
    comp2Cost = ReductionMatrix2();
    comp2Cost = parentCost2 + city[cno][ncno];
}
void copy(int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            city[i][j] = matrix[i][j];
        }
    }
}
void findPath(int cno)
{
    comp1Cost = infinite;
    comp2Cost = infinite;
    chk++;
    path = path + to_string(cno + 1);
    visited[cno] = 1;
    int i1, i2;
    for (int i = 1; i < N; i++)
    {
        if (visited[i] == 0)
        {
            if (comp1Cost > comp2Cost)
            {
                copy1(cno, i);
                i1 = i;
            }
            else
            {
                copy2(cno, i);
                i2 = i;
            }
            if (comp1Cost < comp2Cost)
            {
                initialize(comp2);
            }
            else
            {
                initialize(comp1);
            }
        }
    }
    if (comp1Cost >= 0 && comp2Cost >= 0)
    {
        parentCost = min(comp1Cost, comp2Cost);
    }
    else
    {
        parentCost = max(comp1Cost, comp2Cost);
    }
    if (comp1Cost < comp2Cost)
    {
        copy(comp1);
        initialize(comp1);
        initialize(comp2);
    }
    else
    {
        copy(comp2);
        initialize(comp1);
        initialize(comp2);
    }

    if (chk != N)
    {

        display(city);
        cout << "Total Cost = " << totalCost << endl;
        totalCost = totalCost + parentCost;
        path = path + "-->";
        if (comp1Cost < comp2Cost)
        {
            cout << endl << "The next selected city : " << i1 + 1 << endl;
            findPath(i1);
        }
        else
        {
            cout << endl << "The next selected city : " << i2 + 1 << endl;
            findPath(i2);
        }
    }
}
int main(int argc, char const *argv[])
{
    cout<<"\n\t\t\t\t\t\t\t\t*****************************"<<endl;
    cout<<"\t\t\t\t\t\t\t\tCourier Delivery Service \n"<<endl;
    cout<<"\t\t\t\t\t\t\t\t*****************************"<<endl;
    cout<<"\n\t\t\t\t\t\t\t\tMembers :\n";
    cout<<"\n\t\t\t\t\t\t\t\tDoyel Agrawal \t9920103038\n\t\t\t\t\t\t\t\tSwastik Singh \t9920103039";
    cout<<"\n\t\t\t\t\t\t\t\tNamit Atreya \t9920103045\n\t\t\t\t\t\t\t\tAmvi Sinha \t9920103048\n\n";
    cout<<"\n\t\t\t\t\t\t\t\t Press ENTER to continue";
    getchar();
    system("clear");
    cout << endl << "\t\t\tThe input distance matrix:" << endl;
    display(city);
    cout << endl << "\t\t\tThe starting city will be : " << 1 << endl;
    cout << endl << "The initially reduced distance matrix:" << endl;
    initialize(comp1);
    initialize(comp2);
    findInitCost();
    cout << endl << "\t\t\tCalculating the further efficient paths" << endl;
    findPath(0);
    cout << endl << "The total cost for this path =  " << totalCost << endl;
    cout << endl << "The The fuel efficient path will be:  =  " << path << endl;
    return 0;
}