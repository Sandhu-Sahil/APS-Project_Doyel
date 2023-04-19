#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// const int INF = numeric_limits<int>::max(); // infinite cost
const int INF = 1e9; // infinite cost

int N; // number of cities
int final_res = INF; // final result

#define MAXN 100

int dis[MAXN][MAXN]; // distance matrix
int Next[MAXN][MAXN]; // next city matrix

void print_matrix(vector<vector<int>> & adj) {
    cout << "Distance matrix:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (adj[i][j] != INF) {
                cout << adj[i][j] << "\t";
            } else {
                cout << "X\t";
            }
        }
        cout << endl;
    }
}

void copyToFinal(int curr_path[], int final_path[])
{
    for (int i=0; i<N; i++){
        final_path[i] = curr_path[i] + 1;
    }
    final_path[N] = curr_path[0] + 1;
}

int firstMin(vector<vector<int>> & adj, int i)
{
    int min = INT_MAX;
    for (int k=0; k<N; k++){
        if (adj[i][k]<min && i != k){
            min = adj[i][k];
        }
    }
    return min;
}

int secondMin(vector<vector<int>> & adj, int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<N; j++)
    {
        if (i == j){
            continue;
        }
        if (adj[i][j] <= first)
        {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] <= second && adj[i][j] != first){
            second = adj[i][j];
        }
    }
    return second;
}

void TSPRec(vector<vector<int>> & adj, int curr_bound, int curr_weight, int level, int curr_path[], bool visited[], int final_path[])
{
    if (level==N)
    {
        if (adj[curr_path[level-1]][curr_path[0]] != 0)
        {
            int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];

            if (curr_res < final_res)
            {
                copyToFinal(curr_path, final_path);
                final_res = curr_res;
            }
        }
        return;
    }
 
    for (int i=0; i<N; i++)
    {
        if (adj[curr_path[level-1]][i] != 0 && visited[i] == false)
        {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level-1]][i];
 
            if (level==1){
              curr_bound -= ((firstMin(adj, curr_path[level-1]) + firstMin(adj, i))/2);
            }
            else{
              curr_bound -= ((secondMin(adj, curr_path[level-1]) + firstMin(adj, i))/2);
            }
            
            if (curr_bound + curr_weight < final_res)
            {
                curr_path[level] = i;
                visited[i] = true;
 
                // call TSPRec for the next level
                TSPRec(adj, curr_bound, curr_weight, level+1, curr_path, visited, final_path);
            }
 
            curr_weight -= adj[curr_path[level-1]][i];
            curr_bound = temp;
 
            // Also reset the visited array
            memset(visited, false, sizeof(visited));
            for (int j=0; j<=level-1; j++){
                visited[curr_path[j]] = true;
            }
        }
    }
}

void TSP(vector<vector<int>> & adj, int final_path[], bool visited[])
{
    int curr_path[N+1];
 
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));
 
    // Compute initial bound
    for (int i=0; i<N; i++){
        curr_bound += (firstMin(adj, i) + secondMin(adj, i));
    }

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;
 
    visited[0] = true;
    curr_path[0] = 0;
 
    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(adj, curr_bound, 0, 1, curr_path, visited, final_path);
}

void tspUsingBranchAndBound(){
    system("clear");
    cout<<"\n\t\t\t\t\t\t******************************"<<endl;
    cout<<"\t\t\t\t\t\t  TSP Using Branch and Bound \n"<<endl;
    cout<<"\t\t\t\t\t\t******************************"<<endl;
    
    // Read the input
    cout << "Enter the number of cities: ";
    cin >> N;
    cout<<endl;

    vector<vector<int> > adj;
    adj.resize(N, vector<int>(N));

    int final_path[N+1];
    bool visited[N];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Enter the distance between city " << i + 1 << " and city " << j + 1 << ": ";
            int dist;
            cin >> dist;
            if (dist == -1) { // if input is -1, treat it as infinite distance
                adj[i][j] = INF;
            } else {
                adj[i][j] = dist;
            }
        }
    }

    // Print the distance matrix
    print_matrix(adj);

    // // Run the depth-first search algorithm
    TSP(adj, final_path, visited);

    // Print the minimum cost
    cout<<endl;
    cout<<endl;

    cout << endl << "Minimum cost: " << final_res << endl;
    printf("Path Taken : ");
    for (int i=0; i<=N; i++){
        printf("%d ", final_path[i]);
    }

    cout<<"\n\t\t\t\t\t\t   Press ENTER to continue";
    cout<<"\n\t\t\t\t\t\t*****************************"<<endl;
    getchar();
    getchar();
}

void initialise(int V, vector<vector<int> >& graph)
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dis[i][j] = graph[i][j];

            if (graph[i][j] == INF){
                Next[i][j] = -1;
            }
            else{
                Next[i][j] = j;
            }
        }
    }
}

vector<int> constructPath(int u, int v)
{
    if (Next[u][v] == -1){
        return {};
    }
 
    // Storing the path in a vector
    vector<int> path = { u };
    while (u != v) {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}

void floydWarshall(int V)
{
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                if (dis[i][k] == INF || dis[k][j] == INF){
                    continue;
                    }
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
}

void printPath(vector<int>& path)
{
    int n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << " -> ";
    cout << path[n - 1] << endl;
}

void floydWarshellStart(){
    system("clear");
    cout<<"\n\t\t\t\t\t\t******************************"<<endl;
    cout<<"\t\t\t\t\t\t  TSP Using Floyd Warshell \n"<<endl;
    cout<<"\t\t\t\t\t\t******************************"<<endl;
   
    int V;
    cout << "Enter the number of cities: ";
    cin >> V;

    vector<vector<int> > graph;

    graph.resize(V, vector<int>(V));

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << "Enter the distance between city " << i + 1 << " and city " << j + 1 << ": ";
            int dist;
            cin >> dist;
            if (dist == -1) { // if input is -1, treat it as infinite distance
                graph[i][j] = INF;
            } else {
                graph[i][j] = dist;
            }
        }
    }

    initialise(V, graph);

    floydWarshall(V);
    vector<int> path;

    int choice=0;
    while (choice != 2)
    {
        cout << endl;
        cout << "Enter the choice: \n";
        cout << "1. Find the shortest path between two vertices\n";
        cout << "2. Exit\n";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << endl <<"Enter the source vertex: ";
                int u;
                cin >> u;
                cout << "Enter the destination vertex: ";
                int v;
                cin >> v;
                path = constructPath(u, v);
                if (path.size() == 0){
                    cout << "No path exists between " << u << " and " << v << endl;
                }
                else{
                    cout << "Shortest path between " << u << " and " << v << " is: ";
                    printPath(path);
                }
                break;
            case 2:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }
    }
    

    cout<<"\n\t\t\t\t\t\t   Press ENTER to continue";
    cout<<"\n\t\t\t\t\t\t*****************************"<<endl;
    getchar();
    getchar();
}

int main() {
    system("clear");
    cout<<"\n\t\t\t\t\t\t***********************************"<<endl;
    cout<<"\t\t\t\t\t\t     Courier Delivery Service \n"<<endl;
    cout<<"\t\t\t\t\t\t***********************************"<<endl;
    cout<<"\n\t\t\t\t\t\tMembers :\n";
    cout<<"\n\t\t\t\t\t\tSahilsher Singh   \t9921103131\n\t\t\t\t\t\tPraveen Raj     \t9921103121";
    cout<<"\n\t\t\t\t\t\tSarthak Chawla    \t9921103132\n\t\t\t\t\t\tAman Dixit      \t9921103133\n\n";
    cout<<"\n\t\t\t\t\t\t      Press ENTER to continue";
    cout<<"\n\t\t\t\t\t\t***********************************"<<endl;
    getchar();
    system("clear");
    cout<<"\n\t\t\t\t\t\t*****************************"<<endl;
    cout<<"\t\t\t\t\t\t  Courier Delivery Service \n"<<endl;
    cout<<"\t\t\t\t\t\t*****************************"<<endl;
    
    char choice;
    while(choice!='3')
    {
        cout<<"Enter the choice \n";
        cout<<"1. Press 1 for fuel efficient path:\n";
        cout<<"2. Press 2 for proirity based path:\n";
        cout<<"3. Press 3 Exit\n";
        cin>>choice;
        switch(choice)
        {
            case '1':
                tspUsingBranchAndBound();
                break;
            case '2':
                floydWarshellStart();
                break;
            case '3':
                cout<<"Exiting.... \n";
                break;
            default:
                cout<<endl;
                cout<<"Invalid choice\n";
                cout<<endl;
                break;
        }
    }

    return 0;
}