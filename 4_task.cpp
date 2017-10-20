#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

//infinity
const int inf = 1000 * 1000; //const int inf = 1000 * 1000 * 1000;

typedef vector<int> graf_line; // typedef can t use for encapsulation
typedef vector<graf_line> graf; // vector of vectors

typedef vector<int> vint;
typedef vector<vint> vvint;

int main(){
	fstream in("in.txt");
	fstream out("out.txt");
	int n;
	in >> n;
	vvint c(n, vint(n));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			in >> c[i][j];
		}
	}
	//read source >> drain (исток, сток)
	int source, drain;
	in >> source >> drain;
	source--;
	drain--;
	vvint f(n, vint(n));
	for (;;){ // cycle without condition
		vint from(n, -1);
		vint queue(n);
		int h = 0, t = 0;
		queue[t++] = source;
		from[source] = source;

		for (int cur; h < t;){
			cur = queue[h++];
			for (int v = 0; v < n; v++)
				if (from[v] == -1 && c[cur][v] - f[cur][v] > 0){
				queue[t++] = v;
				from[v] = cur;
				}
		}
		//if path doesn't exist, then stop
		if (from[drain] == -1)
			break;
		//поиск ребра минимальной пропусной способности в найденном пути
		int cf = inf;
		for (int cur = drain; cur != source;){
			int prev = from[cur];
			cf = min(cf, c[prev][cur] - f[prev][cur]);
			cur = prev;
		}
		//пропускание потока величины cf по данному пути
		for (int cur = drain; cur != source;){
			int prev = from[cur];
			f[prev][cur] += cf;
			f[cur][prev] -= cf;
			cur = prev;
		}
	}
	//вычисление значения максимального потока
	int flow = 0;
	for (int i = 0; i < n; i++)
		if (c[0][i])
			flow += f[0][i];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			out << c[i][j] << " ";
		out << endl;
	}
	out << flow;
	return 0;
}
