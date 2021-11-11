
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>


using namespace std;

int V, E, Q;
int graph[4000][4000] = {};
vector<vector<int>> queries;

void printgraph(int graph[][4000], int V, ostream &out = cout){
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            out << graph[i][j];
        }
        out << endl;
    }
}

void printQ(vector<vector<int>> queries, ostream &out = cout){
    for (vector<int> q : queries) {
        for (int c : q) {
            out << c << " ";
        }
        out << "\n";
    }
}

void reader(istream& indata, int &V, int &E, int &Q, int graph[][4000], vector<vector<int>> &queries){
    string line;
    indata >> V >> E >> Q;
    int from, to;
    for (int i = 0; i < E; i++) {
        indata >> from >> to;
        graph[from][to] = 1;
    }
    indata.ignore();
    queries.resize(Q, vector<int>());
    for (int i = 0; i < Q; i++) {
        getline(indata, line);
        istringstream iss (line);
        string word;
        while (!iss.eof()){
            getline(iss, word, ' ');
            queries[i].push_back(stoi(word));
        }
    }
}

void loader(int &V, int &E, int &Q, int graph[][4000], vector<vector<int>> &queries, string filename = "") {
    
    if(filename != ""){
        ifstream file(filename);
        reader(file, V, E, Q, graph, queries);
    }
    else{
        reader(cin, V, E, Q, graph, queries);
    }
    
}

vector<vector<int>> reducer(vector<vector<int>> queries, int V){
    
    map<int,int> dic  = {{1,1}, {2, 4}, {4, 2}, {3,7}, {7,3}};
    vector<vector<int>> queries2;
    int mode[2] = {0};
    int j = -1;
    for (vector<int> q : queries) {
        
        if(q[0] == 5){
            mode[0] = !mode[0];
            continue;
        }
        if (q[0] == 6){
            mode[1] = !mode[1];
            continue;
        }
        
        queries2.push_back(vector<int>());
        j++;
        int qp;
        if (mode[1]){
            qp = dic[q[0]];
        }
        else{
            qp = q[0];
        }
        
        queries2[j].push_back(qp);
        
        if(q[0] != 1){
            if (mode[0]){
                queries2[j].push_back(q.back());
                if (q.size() == 3){
                    queries2[j].push_back(q[1]);
                }
            }else{
                queries2[j].push_back(q[1]);
                if (q.size() == 3){
                    queries2[j].push_back(q[2]);
                }
            }
        }else{
            V++;
            if(mode[1]){
                queries2.push_back(vector<int>());
                j++;
                queries2[j] = {7, V-1};
            }
        }
        
    }
    if (mode[0]){
        queries2.push_back(vector<int>({5}));
    }
    if (mode[1]){
        queries2.push_back(vector<int>({6}));
    }
    return queries2;
}

void func1(vector<int> q, int graph[][4000], int &V){
    V++;
}

void func2(vector<int> q, int graph[][4000], int &V){
    graph[q[1]][q[2]] = 1;
}

void func3(vector<int> q, int graph[][4000], int &V){
    for (int i = 0; i < V; i++) {
        graph[i][q[1]] = 0;
        graph[q[1]][i] = 0;
    }
}

void func4(vector<int> q, int graph[][4000], int &V){
    graph[q[1]][q[2]] = 0;
}

void func5(vector<int> q, int graph[][4000], int &V){
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            int temp = graph[i][j];
            graph[i][j] = graph[j][i];
            graph[j][i] = temp;
        }
    }
}

void func6(vector<int> q, int graph[][4000], int &V){
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = !graph[i][j];
        }
    }
    for (int i = 0; i < V; i++) {
        graph[i][i] = 0;
    }
}

void func7(vector<int> q, int graph[][4000], int &V){
    for (int i = 0; i < V; i++) {
        graph[i][q[1]] = 1;
        graph[q[1]][i] = 1;
    }
    graph[q[1]][q[1]] = 0;
}

void designator(vector<vector<int>> queries, int graph[][4000], int &V){
    for (vector<int> q : queries) {
        switch (q[0]) {
            case 1:
                func1(q, graph, V);
                break;
            case 2:
                func2(q, graph, V);
                break;
            case 3:
                func3(q, graph, V);
                break;
            case 4:
                func4(q, graph, V);
                break;
            case 5:
                func5(q, graph, V);
                break;
            case 6:
                func6(q, graph, V);
                break;
            case 7:
                func7(q, graph, V);
            default:
                break;
        }
    }
    
}

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}


void writer(ostream &outdata, int V, vector<int> ds, vector<int> hashes){
    outdata << V << endl;
    for (int i = 0; i < V; i++) {
        outdata << ds[i] << ' ' << hashes[i] << endl;
    }
}

void outputter(int graph[][4000], int V, string filename = ""){
    
    vector<int> ds(V, 0);
    int m = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            ds[i] += graph[i][j];
        }
        if (ds[i] > m) {
            m = ds[i];
        }
    }
    vector<long long int> sevens(m, 0);
    
    
    for (int i = 0; i < m; i++) {
        sevens[i] = modpow<long int>(7, i, 1000000007);
    }
    vector<int> hashes(V, 0);
    for (int i = 0; i < V; i++) {
        int k = 0;
        for (int j = 0; j < V; j++) {
            if(graph[i][j] == 1){
                hashes[i] = (hashes[i] + sevens[k]*j) % 1000000007;
                k++;
            }
        }
    }
    
    if (filename == ""){
        writer(cout, V, ds, hashes);
    }
    else{
        ofstream file(filename);
        writer(file, V, ds, hashes);
    }
    
}



int main(){
    loader(V, E, Q, graph, queries);
    vector<vector<int>> queries2 = reducer(queries, V);
    designator(queries2, graph, V);
    outputter(graph, V);

}
