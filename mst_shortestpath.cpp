#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <string.h> 
#include <string> 
#include <stack>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <deque>
#include <vector>
#include <sstream>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct edge {
	int weight;
	int start;
	int end;
	bool operator< (edge e) {
		return weight < e.weight;
	}
};

//Minimum spanning tree
int parent[20];
int visualLink[17][17];
int find(int x);
void uni(int x, int y);

//Shortest path
int spath[17];
int visited[17];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	/////////////////////////
	//Minimum spanning tree//
	/////////////////////////

	vector<edge> v;

	/*USER INPUT*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**/v.push_back({ 3,1,2 }); v.push_back({ 1,2,3 }); v.push_back({ 4,3,4 }); v.push_back({ 1,5,6 }); v.push_back({ 5,6,7 }); v.push_back({ 8,7,8 });            /**/
	/**/v.push_back({ 2,9,10 }); v.push_back({ 4,10,11 }); v.push_back({ 6,11,12 }); v.push_back({ 3,13,14 }); v.push_back({ 5,14,15 }); v.push_back({ 7,15,16 }); /**/
	/**/v.push_back({ 2,1,5 }); v.push_back({ 5,2,6 }); v.push_back({ 1,3,7 }); v.push_back({ 6,4,8 }); v.push_back({ 3,5,9 }); v.push_back({ 4,6,10 });           /**/
	/**/v.push_back({ 2,7,11 }); v.push_back({ 6,8,12 }); v.push_back({ 2,9,13 }); v.push_back({ 6,10,14 }); v.push_back({ 4,11,15 }); v.push_back({ 4,12,16 });   /**/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Set initial parent value
	for (int i = 1; i <= 16; i++)parent[i] = i;

	//Sort by weight
	sort(v.begin(), v.end());

	//Kruskal Algorithm
	int size = v.size();
	int answer = 0;
	for (int i = 0; i < size; i++)
	{
		if (find(v[i].start) == find(v[i].end))continue;
		uni(v[i].start, v[i].end);
		printf("Link between %-2d and %-2d\n", v[i].start, v[i].end);
		answer += v[i].weight;
	}
	string spaces = "|                                 ";
	cout << "\n\nMinimum Length : " << answer << "\n\n";
	cout << " ________________________Visualization of Minimum Spanning Tree____________________ \n";
	cout << "|                                                                                  |\n";
	cout << "|                                                                                  |\n";
	for (int i = 1; i <= 4; i++)
	{
		cout << spaces;
		for (int j = 1; j <= 4; j++)
		{
			printf("%2d", (i - 1) * 4 + j);
			if (j == 4)continue;
			else if (visualLink[(i - 1) * 4 + j][(i - 1) * 4 + j + 1] == 1)cout << "--";
			else cout << "  ";
		}
		cout << "                                   |\n";
		if (i != 4)cout << spaces;
		if (i < 4)
		{
			for (int j = 1; j <= 4; j++)
			{
				if (visualLink[(i - 1) * 4 + j][(i - 1) * 4 + j + 4] == 1)cout << " |  ";
				else cout << "    ";
			}
			cout << "                                 |\n";
		}
	}
	cout << "|                                                                                  |\n";
	cout << "|                                                                                  |\n";
	cout << "|__________________________________________________________________________________|\n";
	cout << "\n\n";






	/////////////////
	//Shortest path//
	/////////////////

	vector<pair<int, int> > vv[17];
	//Set every distance infinite
	int dist[20];
	for (int i = 0; i < 20; i++)dist[i] = 210000000;
	/*USER INPUT*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**/vv[1].emplace_back(2, 3);vv[1].emplace_back(5, 2);vv[2].emplace_back(1, 3);vv[2].emplace_back(3, 1);vv[2].emplace_back(6, 5);vv[3].emplace_back(2, 1);		      /**/
	/**/vv[3].emplace_back(4, 4);vv[3].emplace_back(7, 1);vv[4].emplace_back(3, 4);vv[4].emplace_back(8, 6);vv[5].emplace_back(1, 2);vv[5].emplace_back(6, 1);		      /**/
	/**/vv[5].emplace_back(9, 3); vv[6].emplace_back(2, 5); vv[6].emplace_back(5, 1); vv[6].emplace_back(7, 5);vv[6].emplace_back(10, 4);vv[7].emplace_back(3, 1);	      /**/
	/**/vv[7].emplace_back(6, 5);vv[7].emplace_back(8, 8);vv[7].emplace_back(11, 2);vv[8].emplace_back(4, 6);vv[8].emplace_back(7, 8);vv[8].emplace_back(12, 6);	      /**/
	/**/vv[9].emplace_back(5, 3);vv[9].emplace_back(10, 2);vv[9].emplace_back(13, 2);vv[10].emplace_back(6, 4);vv[10].emplace_back(9, 2);vv[10].emplace_back(11, 4);	  /**/
	/**/vv[10].emplace_back(14, 6);vv[11].emplace_back(7, 2);vv[11].emplace_back(10, 4);vv[11].emplace_back(12, 6);vv[11].emplace_back(15, 4);vv[12].emplace_back(8, 6);  /**/
	/**/vv[12].emplace_back(11, 6);vv[12].emplace_back(16, 4);vv[13].emplace_back(9, 2);vv[13].emplace_back(14, 3);vv[14].emplace_back(10, 6);vv[14].emplace_back(13, 3); /**/
	/**/vv[14].emplace_back(15, 5);vv[15].emplace_back(11, 4);vv[15].emplace_back(14, 5);vv[15].emplace_back(16, 7);vv[16].emplace_back(12, 4);vv[16].emplace_back(15, 7);/**/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	priority_queue<pair<int, int> > pq;
	dist[1] = 0;
	pq.emplace(0, 1);
	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int point = pq.top().second;
		pq.pop();
		for (auto i : vv[point])
		{
			if (dist[i.first] > i.second + dist[point])
			{
				dist[i.first] = i.second + dist[point];
				pq.emplace(-dist[i.first], i.first);
			}	
		}
	}
	stack<int> st;
	for (int i = 1; i <= 16; i++)
	{
		cout << "from 1 to " << i << "   shortest distance : " << dist[i] << "\n";
		int currentP = i;
		st.push(currentP);
		while (currentP != 1)
		{
			for (auto i : vv[currentP])
			{
				if (dist[i.first] + i.second == dist[currentP])
				{
					currentP = i.first;
					st.push(currentP);
				}
			}
		}
		cout << "path : ";
		while (!st.empty())
		{
			cout << st.top() << " ";
			st.pop();
		}
		cout << "\n\n";
	}
	system("pause");
	return 0;
}
int find(int x)
{
	if (parent[x] == x)return x;
	return parent[x] = find(parent[x]);
}
void uni(int x, int y)
{
	visualLink[x][y] = 1;
	x = find(x);
	y = find(y);
	parent[y] = x;
}