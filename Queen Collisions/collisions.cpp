// Queens Collisions
// Micaiah Soto
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct position {
	int x;
	int y;
	position(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

const int MAX_QUEENS = 29999;

void placeQueens(vector<position>&, int, int, int, int, int);

void main() {
	ifstream fin("collisions.in");
	if (fin.is_open()) {
		ofstream fout("collisions.out");

		int boardSize, patternCount, k, x, y, s, t;
		fin >> boardSize;
		vector<position> queenPositions;

		while (boardSize != 0) {

			fin >> patternCount;
			for (int i = 0; i < patternCount; i++) {
				fin >> k >> x >> y >> s >> t;
				placeQueens(queenPositions, k, x, y, s, t);
			}

			fin >> boardSize;
		}
		
		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}

void placeQueens(vector<position>& queenPositions, int k, int x, int y, int s, int t) {
	position newPosition(0, 0);
	if (k == 1) {
		newPosition.y = y;
		newPosition.x = x;	
		queenPositions.push_back(newPosition);
	}
	for (int i = 0; i < k; i++) {
		newPosition.y = y + i * t;
		newPosition.x = x + i * s;
		queenPositions.push_back(newPosition);
	}

}