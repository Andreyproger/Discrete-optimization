#include <vector>
//#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

int white = 0, red = 1, blue = 2;

bool dfs(int v, vector <vector<int>> &g, vector<int> &color, int prevcolor){
	if (color[v] != white){
		return color[v] != prevcolor;
	}
	color[v] = prevcolor == red ? blue : red;
	for (int i = 0; i < g[v].size(); i++){
		int w = g[v][i];
		//cout << w << endl;
		if (!dfs(w, g, color, color[v])){
			return false;
		}
	}
	return true;
}

/*bool dfs(int v)
{
	
	for (int i = 1; i<g[v].size(); ++i)
	{
		if (color[g[v][i]] == 1 && color[v] == 1 ||
			color[g[v][i]] == 2 && color[v] == 2)
			return false;
		else if (color[v] == 1) {
			if (g[v][i]!=0)
				continue;
			color[g[v][i]] = 2;
			if (!dfs(g[v][i])) return false;
		}
		else {
			if (g[v][i] != 0)
				continue;
			color[g[v][i]] = 1;
			if (!dfs(g[v][i])) return false;
		}
		//return dfs(g[v][i]);
	}
	return true;
}*/



int main(){
	ifstream input_file("in.txt");
	ofstream output_file("out.txt");
	

	; // цвет вершины (0, 1, или 2)
	int n;
	input_file >> n;
	vector <int> color(n, white);
	vector < vector<int> > g(n, vector<int>());

	for (int i = 0; i < n; i++){
		int t = -1;
		while (true)
		{
			input_file >> t;
			if (t == 0)
				break;
			g[i].push_back(t - 1);
		}
	}

	bool ok = true;
	for (int v = 0; v < n && ok; v++) {
		ok = dfs(v, g, color, white);
	}

	//cout << ok << endl;
	if (ok)
	{
		output_file << "Y" << endl; //добавить вывод вершин входящих в доли графа
		vector<int> reds, blues;
		for (int i = 0; i < n; i++)
			if (color[i] == red)
				reds.push_back(i);
			else
				blues.push_back(i);

		sort(reds.begin(), reds.end());
		sort(blues.begin(), blues.end());

		if ((reds.size() > 0 && blues.size() > 0 && blues[0] < reds[0]) || (blues.size() > 0 && reds.size() == 0)) {
			reds.swap(blues);
		}
		
		for (int i = 0; i<reds.size(); i++)
			output_file << reds[i]+1 << " ";
		output_file << "0";

		for (int i = 0; i<blues.size(); i++)
			output_file << blues[i]+1 << " ";
		output_file << "0" << endl;
	}
	else
		output_file << "N"; //добавить вывод вершин входящих в доли графа
	return 0;
}
