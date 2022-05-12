#include<bits/stdc++.h>
using namespace std;
int infinite = INT_MAX;
int minCost=0;//minimum of all paths
int visited[10]={0};
int initReductionCost=0;//r cap
int count=0;//flag
int countInfinite=0;//to check if entire row or column is infinite
int parentCost=0;//previous parent cost
int city[10][10] = {
    {infinite, 5, 2, 7, 3, 8, 1, 5, 7, 3},
    {5, infinite, 4, 8, 11, 2, 9, 5, 1, 6},
    {2, 4, infinite, 3, 5, 1, infinite, 2, 6, infinite},
    {7, 8, 3, infinite, 1, 5, 6, 7, infinite, 3},
    {3, 11, 5, 1, infinite, 4, 1, 3, 2, 9},
    {8, 2, 1, 5, 4, infinite, 9, 6, 4, 5},
    {1, 9, infinite, 6, 1, 9, infinite, 3, 1, 2},
    {5, 5, 2, 7, 3, 6, 3, infinite, 5, 4},
    {7, 1, 6, infinite, 2, 4, 1, 5, infinite, 9},
    {3, 6, infinite, 3, 9, 5, 2, 4, 9, infinite}
    };
int comp1[10][10],comp2[10][10];
void display()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<comp1[i][j]<<" \t";
        }
        cout<<endl;
    }
    cout<<"Initial reduction Cost = "<<initReductionCost<<endl;
}
void findInitCost()
{
    for(int i=0;i<10;i++)
    {
        countInfinite=0;
        int min=10000;
        for(int j=0;j<10;j++)
        {
            if(city[i][j]>=infinite-10)
            {
                countInfinite++;
            }
            if(city[i][j]<min&&!(city[i][j]>=infinite-10))
            {
                min=city[i][j];
            }
        }
        if(countInfinite==10)
        {
            min=0;
        }
        for(int j=0;j<10;j++)
        {
            city[i][j]=city[i][j]-min;
        }
        initReductionCost=initReductionCost+min;
    }
    for(int i=0;i<10;i++)
    {
        countInfinite=0;
        int min=10000;
        for(int j=0;j<10;j++)
        {
            if(city[j][i]<min&&!(city[j][i]>=infinite-10))
            {
                min=city[j][i];
            }
        }
        if (countInfinite == 10)
        {
            min = 0;
        }
        for(int j=0;j<10;j++)
        {
            city[j][i]=city[j][i]-min;
        }
        initReductionCost=initReductionCost+min;
    }
    parentCost=parentCost+initReductionCost;
}
void initializeComp1()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            comp1[i][j]=0;
        }
    }
}
void initializeComp2()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            comp2[i][j] = 0;
        }
    }
}
void copy(int cno,int ncno)
{
    for(int i=0;i<10;i++)
    {
        comp1[cno][i]=infinite;
        comp1[i][ncno]=infinite;
    }
    comp1[ncno][0]=infinite;
    comp1[ncno][cno]=infinite;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(comp1[i][j]==0)
            {
                comp1[i][j]=city[i][j];
            }
        }
    }
    display();
}
void findPath(int cno)
{
    cout<<cno+1<<"-->";
    visited[cno]=1;
    for(int i=1;i<10;i++)
    {
        if(visited[i]==0)
        {
            copy(cno,i);
        }
        break;
    }
}
int main(int argc, char const *argv[])
{
    int noOfCouriers[10];
    int choice;
    cout<<endl<<"Select your preference:"<<endl<<endl;
    cout<<"Press 1 for fuel efficient path:"<<endl<<endl;
    cout<<"Press 2 for proirity based path:"<<endl<<endl;
    cout<<"Enter choice:";
    cin>>choice;
    if(choice==1)//TSP
    {
        cout<<"The fuel efficient path will be: "<<endl;
        initializeComp1();
        initializeComp2();
        findInitCost();
        findPath(0);
    }
    else if(choice==2)//Flloyd Warshall
    {
        cout<<endl<<"Enter the number of couriers to be delivered in the following cities:"<<endl<<endl;
        for (int i = 1; i <= 10; i++)
        {
            cout<<endl<<"Enter number of couriers for city "<<i<<":";
            cin>>noOfCouriers[i-1];
        }
    }
    else
    {
        cout<<"Invalid Choice:";
    }
    cin>>choice;
    return 0;
}