#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> weight;
vector<pair<int, int>> vp;
vector<vector<int>> adj;
map<int, bool> A, B;

void swp(pair<int, int>& pr) {
	A.erase(pr.first);
	B.erase(pr.second);
	A[pr.second];
	B[pr.first];
}

int main()
{
	int n, m;
	cin >> n >> m;
	adj = vector<vector<int>> (n);
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		vp.push_back({u, v});
	}
	for(int i = 0; i < n; i += 2) {
		A[i], B[i + 1];
	}

	cout << "read done" << endl;
	int G = -1;
	int cnt = 0;
	while(true) {
		cout << "cnt: " << cnt << endl;
		cnt++;
		vector<pair<int, pair<int, int>>> G_all;
		map<int, bool> locked;
		for(int i = 0; i < n; i += 2) {
			// update D
			vector<int> D = vector<int> (n);
			for(int u = 0; u < n; ++u) {
				int tmp = 0;
				for(auto& v: adj[u]) {
					if(A.find(v) != A.end()) tmp -= 1;
					else tmp += 1;
				}
				if(A.find(u) != A.end()) D[u] = tmp;
				else D[u] = -tmp;
			}

			// calculate all pair of g
			vector<pair<int, pair<int, int>>> tmp_g;
			for(auto& a: A) {
				for(auto& b: B) {
					int _g = D[a.first] + D[b.first] - 2;
					tmp_g.push_back({_g, {a.first, b.first}});
				}
			}
			
			// pick the largest g
			sort(tmp_g.begin(), tmp_g.end(), greater<pair<int, pair<int, int>>> ());
			for(auto& g: tmp_g) {
				pair<int, int> pr = g.second;
				if(!locked.count(pr.first) && !locked.count(pr.second)) {
					locked[pr.first];
					locked[pr.second];
					G_all.push_back({g.first, pr});
					break;
				}
			}
		}
		sort(G_all.begin(), G_all.end(), greater<pair<int, pair<int, int>>> ());
		int k = 0;
		for(auto& g: G_all) {
			if(g.first > 0) {
				G += g.first;
				++k;
			}
		}

		if(k) swp(G_all[k].second);
		else break;
	}
	cout << "final G is: " << G << "\n";
}
