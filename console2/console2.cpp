#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int **matrix;
int *way;                   // массив путей
bool *mark;                 // посещенные
string mf_name;             // matrix file name
string wf_name = "way.txt"; // matrix way name
ofstream wfout(wf_name);

void get_matrix(int &n)
{
    ifstream mfin(mf_name);
    mfin >> n;
    matrix = new int *[n];

    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
            mfin >> matrix[i][j];
    }
    mfin.close();

    mark = new bool[n];
    way = new int[n];

    for (int i = 0; i < n; i++)
    {
        mark[i] = 0;
        way[i] = -1;
    }
}

// рекурсия поиска путей
void dfs(int &v, int &w, int &n, int k)
{
    mark[v] = 1;
    way[k] = v;
    if (v == w)
    {
        int i = 0;
        string save = "";
        while (way[i] != -1 && i != n)
        {
            save += to_string(way[i]) + " ";
            i++;
        }
        wfout << save << endl;
    }
    else
        for (int j = 0; j < n; j++)
            if (matrix[v][j] == 1 && mark[j] == 0)
                dfs(j, w, n, k + 1);

    mark[v] = 0;
    way[k] = -1;
}

int main()
{
    system("cls");
    cout << "File name: ";
    cin >> mf_name;
    int n;
    int k = 0;
    int v, w;
    get_matrix(n);

    cout << "First vertex: ";
    cin >> v;
    cout << "Second vertex: ";
    cin >> w;

    dfs(v, w, n, k);
    wfout.close();

    ifstream wfin(wf_name);
    string s;
    cout << "\nSimple ways: \n";
    while (!wfin.eof())
    {
        if (!wfin.eof())
        {
            getline(wfin, s);
            cout << s << endl;
        }
    }
    wfin.close();
}