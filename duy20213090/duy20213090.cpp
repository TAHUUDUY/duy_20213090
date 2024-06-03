#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> SortIn(vector<vector<int>> rank) {
	vector<int> temp;

	for (int i = 0; i < rank.size() - 1; ++i) {
		if (rank[i][1] > rank[i + 1][1]) {
			temp = rank[i];
			rank[i] = rank[i + 1];
			rank[i + 1] = temp;

			return SortIn(rank);
		}
	}
	return rank;
}

vector<vector<int>> SortOut(vector<vector<int>> rank) {
	vector<int> temp;

	for (int i = 0; i < rank.size() - 1; ++i) {
		if ((rank[i][2] > rank[i + 1][2]) && (rank[i][1] == rank[i + 1][1])) {
			temp = rank[i];
			rank[i] = rank[i + 1];
			rank[i + 1] = temp;

			return SortOut(rank);
		}
	}
	return rank;
}

vector<vector<int>> SortRank(vector<vector<int>> rank) {
	rank = SortIn(rank);
	rank = SortOut(rank);
	return rank;
}

vector<vector<int>> getRankGraph(int** matrix_G, int size) {
	vector<vector<int>> rank_G;
	vector<int> in;
	vector<int> out;
	for (int i = 0; i < size; ++i) {
		int count = 0;
		for (int j = 0; j < size; ++j) {
			if (matrix_G[j][i] == 1) count++;
		}

		in.push_back(count);
	}

	for (int i = 0; i < size; ++i) {
		int count = 0;
		for (int j = 0; j < size; ++j) {
			if (matrix_G[i][j] == 1) count++;
		}

		out.push_back(count);
	}

	for (int i = 0; i < size; ++i) {
		rank_G.push_back({ i, in[i], out[i] });
	}

	return SortRank(rank_G);
}

int** crMatrix(vector<vector<int>> G) {
	int G_size = G.size();
	int** matrix_G;
	matrix_G = new int* [G_size];
	for (int i = 0; i < G_size; ++i)
		matrix_G[i] = new int[G_size];

	for (int i = 0; i < G_size; ++i)
		for (int j = 0; j < G_size; ++j)
			matrix_G[i][j] = 0;

	for (int i = 0; i < G_size; ++i) {
		for (auto x : G[i])
			matrix_G[i][x - 1] = 1;
	}

	return matrix_G;
}

int getNumOfEdge(int** matrix, int size) {
	int edge = 0;

	for (int j = 0; j < size; ++j) {
		for (int i = 0; i < size; ++i) {
			if (matrix[i][j] == 1)
				edge++;
		}
	}
	return edge;
}

bool isormorphic(vector<vector<int>> G1, vector<vector<int>> G2) {

	if (G1.size() != G2.size()) {
		cout << "Size\n";
		return false;
	}

	int** matrix_G1 = crMatrix(G1);
	int** matrix_G2 = crMatrix(G2);

	if (getNumOfEdge(matrix_G1, G1.size()) != getNumOfEdge(matrix_G2, G2.size())) {
		cout << "Edge\n";
		return false;
	}

	int G1_size = G1.size();
	int G2_size = G2.size();

	vector<vector<int>> rank_G1 = getRankGraph(matrix_G1, G1_size);
	vector<vector<int>> rank_G2 = getRankGraph(matrix_G2, G2_size);

	if (rank_G1.size() != rank_G2.size()) {
		cout << "Rank Size\n";
		return false;
	}

	for (int i = 0; i < rank_G1.size(); ++i) {
		if (rank_G1[i].size() != rank_G2[i].size()) {
			cout << "In Rank Size\n";
			return false;
		}
		else
			for (int j = 1; j < rank_G1.size(); ++j)
				if (rank_G1[i][j] != rank_G2[i][j]) {
					cout << "Value Rank\n";
					return false;
				}
	}

	return true;
}

int main()
{
	vector<vector<int>> G1 = {
		{2, 3},
		{3, 4},
		{4},
		{}
	};

	vector<vector<int>> G2 = {
		{3, 4},
		{},
		{2},
		{2, 3}
	};

	if (isormorphic(G1, G2))
		cout << "True";
	else
		cout << "False";

	int** matrix = crMatrix(G2);
	cout << getNumOfEdge(matrix, G2.size());
	for (int i = 0; i < G1.size(); ++i) {
		for (int j = 0; j < G1.size(); ++j) {
			cout << matrix[i][j] << " ";
		}

		cout << endl;
	}

	vector<vector<int>> rank = getRankGraph(matrix, G2.size());
	for (int i = 0; i < rank.size(); ++i) {
		for (int j = 0; j < rank[i].size(); ++j) {
			cout << rank[i][j] << " ";
		}

		cout << endl;
	}
	cout << endl;
	rank = SortRank(rank);
	for (int i = 0; i < rank.size(); ++i) {
		for (int j = 0; j < rank[i].size(); ++j) {
			cout << rank[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}