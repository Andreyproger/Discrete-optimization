#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1000000000;
//const int N = 50, M = 50;
vector<vector<pair<int, int>>> g;
int N;
vector<int> d, p;
vector<char> used;

void bfs(){
	queue<int> q;
	for (int u = 0; u < N; u++){
		for (int j = 0; j < g[u].size(); j++){
			int v = g[u][j].first;
			int w = g[u][j].second;
			if (w == 0){
				q.push(v);
				used[v] = true;
				p[v] = u;
				d[v] = 0;
			}
		}
	}

	while (!q.empty()){
		int u = q.front();
		q.pop();
		for (int i = 0; i < g[u].size(); i++){
			int v = g[u][i].first;
			if (used[v])
				continue;
			q.push(v);
			used[v] = true;
			p[v] = u;
			d[v] = 0;
		}
	}
}

void dijecstra(){
	for (int ii = 0; ii < N; ii++){
		int v = -1;
		for (int jj = 0; jj < N; ++jj)
			if (!used[jj] && (v == -1 || d[jj] < d[v]))
				v = jj;
		if (v == -1 || d[v] == INF)
			break;
		used[v] = true;
		for (int j = 0; j < g[v].size(); j++){
			int to = g[v][j].first, len = g[v][j].second;
			if (d[v] * len < d[to]){ // åñëè íàéäåí ïóòü êîðî÷å
				d[to] = d[v] * len;
				p[to] = v;
			}
		}
	}
	
}

int main() {
	ifstream input_file("in.txt");
	ofstream output_file("out.txt");

	input_file >> N;
	g.assign(N, vector<pair<int, int>>()); //
	int start, end;
	for (int i = 0; i < N; i++){
		int e = -1, w = -1;
		while (true){
			input_file >> e;
			if (e == 0)
				break;
			input_file >> w;
			g[e - 1].push_back(make_pair(i, w));
		}
	}
	input_file >> start >> end;
	start--;
	end--;
	d.assign(N, INF);
	p.assign(N, -1);
	d[start] = 1;
	used.assign(N, 0);
	bfs();
	dijecstra();
	d[start] = 0;// êàêîìó çíà÷åíèþ äîëæíî áûòü ðàâíî, íà÷èíàÿ ñ ýòîé ñòðîêè
	vector<int> path;
	for (int v = end;; v = p[v]){
		if (v == start)
			break;
		if (v == -1){
			output_file << "N" << endl;
			return 0;
		}
		path.push_back(v);

		
	}
	path.push_back(start);
	reverse(path.begin(), path.end());

	
	output_file << "Y" << endl;
	for (int i = 0; i < path.size(); i++){
		output_file << (path[i] + 1) << " ";
	}
	output_file << endl;
	output_file << d[end];

	return 0;
}
