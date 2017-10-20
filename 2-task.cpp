#include <cmath>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>      // std::pair
using namespace std;

struct Point{
	int x, y;
	int dist(Point b){
		return abs(x - b.x) + abs(y - b.y);
	}
};
int n;
vector<int> parent;

int findSet(int v){
	if (v == parent[v])
		return v;
	return parent[v] = findSet(parent[v]);
}

void makeSets(){
	for (int i = 0; i < n; i++)
		parent[i] = i;
}

void uniteSets(int u, int v){
	u = findSet(u);
	v = findSet(v);
	parent[u] = v;
}

int Distance(Point p1, Point p2){
	//(d(M,N)=|XM-XN|+|YM-YN|).
	return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}

void main(){
	ifstream input_file("in.txt");
	ofstream output_file("out.txt");
	
	input_file >> n;
	//cout << n;
	parent.assign(n, -1);
	//vector <pair <int, int>> result;
	vector <pair<int, int>> edges;
	vector<Point> coords(n);
	vector<vector<int>> result(n, vector<int>()); 

	for (int i = 0; i < n; i++){
		input_file >> coords[i].x >> coords[i].y;
	}


	makeSets();

	for (int u = 0, i = 0; u < n; u++, i++){
		for (int v = u + 1; v < n; v++){
			edges.push_back(make_pair(u,v));
		}
	}

	sort(
		edges.begin(),
		edges.end(),
		//lambda function
		[&](pair<int, int> a, pair<int, int> b){
			return Distance(coords[a.first],coords[a.second])
				<
				Distance(coords[b.first], coords[b.second]);
		}
	);
	
	for (int i = 0; i < edges.size(); i++){ //n*(n-1)/2
		int u = edges[i].first;
		int v = edges[i].second;
		if (findSet(u) == findSet(v)){ continue; }
		result[u].push_back(v);
		result[v].push_back(u);
		uniteSets(u, v);
	}
	//output
	int sum = 0;
	for (int v = 0; v < n; v++){
		sort(result[v].begin(), result[v].end());
		for (int j = 0; j < result[v].size(); j++){
			int w = result[v][j];
			sum += Distance(coords[v],coords[w])/2;
			output_file << (w + 1) << " ";

		}
		output_file << "0\n";
	}
	output_file << sum;
	//return 0;
}
