#include<bits/stdc++.h>
using namespace std;
int infinite = INT_MAX;
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
int main(int argc, char const *argv[])
{
    int noOfCouriers[10];
    int choice;
    cout<<endl<<"Enter the number of couriers to be delivered in the following cities:"<<endl<<endl;
    for(int i=1;i<=10;i++)
    {
        cout<<endl<<"Enter number of couriers for city "<<i<<":";
        cin>>noOfCouriers[i-1];
    }
    cout<<endl<<"Select your preference:"<<endl<<endl;
    cout<<"Press 1 for fuel efficient path:"<<endl<<endl;
    cout<<"Press 2 for proirity based path:"<<endl<<endl;
    cout<<"Enter choice:";
    if(choice==1)//TSP
    {

    }
    else if(choice==2)//Flloyd Warshall
    {

    }
    else
    {
        cout<<"Invalid Choice:";
    }
    cin>>choice;
    return 0;
}