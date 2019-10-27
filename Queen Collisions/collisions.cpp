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

	bool collideN = false;
	bool collideS = false;
	bool collideW = false;
	bool collideE = false;
	bool collideNW = false;
	bool collideNE = false;
	bool collideSW = false;
	bool collideSE = false;
};

const int MAX_QUEENS = 29999;

void placeQueens(vector<position>&, int, int, int, int, int);
int countCollisions(vector<position>&);

void main() {
	ifstream fin("collisions.in");
	if (fin.is_open()) {
		ofstream fout("collisions.out");

		int boardSize, patternCount, k, x, y, s, t, collisions;
		fin >> boardSize;
		vector<position> queenPositions;

		while (boardSize != 0) {

			fin >> patternCount;
			for (int i = 0; i < patternCount; i++) {
				fin >> k >> x >> y >> s >> t;
				placeQueens(queenPositions, k, x, y, s, t);
				
			}
			collisions = countCollisions(queenPositions);
			fout << collisions;
			fin >> boardSize;
			if (boardSize != 0) {
				fout << endl;
			}
			queenPositions.clear();
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
	else {
		for (int i = 0; i < k; i++) {
			newPosition.y = y + i * t;
			newPosition.x = x + i * s;
			queenPositions.push_back(newPosition);
		}
	}
}

int countCollisions(vector<position>& queenPositions) {
	int collisions = 0;

	//loop through queens, compare each to all others
	//if colliding, mark collision type in associated position bool
	//continue looping
	for (int ofInterest = 0; ofInterest < queenPositions.size(); ofInterest++) {
		for (int toCheck = 0; toCheck < queenPositions.size(); toCheck++) {
			if (toCheck == ofInterest)
				continue;
			//colliding horizontally?
			if (queenPositions[ofInterest].y == queenPositions[toCheck].y) {
				
				//check west
				if (queenPositions[ofInterest].x > queenPositions[toCheck].x && queenPositions[ofInterest].collideW == false) {
					queenPositions[ofInterest].collideW = true;
					queenPositions[toCheck].collideE = true;
					collisions++;
				}
				//check east
				else if (queenPositions[ofInterest].x < queenPositions[toCheck].x && queenPositions[ofInterest].collideE == false) {
					queenPositions[ofInterest].collideE = true;
					queenPositions[toCheck].collideW = true;
					collisions++;
				}

			}

			//colliding vertically?
			else if (queenPositions[ofInterest].x == queenPositions[toCheck].x) {
				
				//check south
				if (queenPositions[ofInterest].y > queenPositions[toCheck].y && queenPositions[ofInterest].collideS == false) {
					queenPositions[ofInterest].collideS = true;
					queenPositions[toCheck].collideN = true;
					collisions++;
				}
				//check north
				else if (queenPositions[ofInterest].y < queenPositions[toCheck].y && queenPositions[ofInterest].collideN == false) {
					queenPositions[ofInterest].collideN = true;
					queenPositions[toCheck].collideS = true;
					collisions++;
				}

			}

			//colliding diagonally?
			else if (abs(queenPositions[ofInterest].x - queenPositions[toCheck].x) == abs(queenPositions[ofInterest].y - queenPositions[toCheck].y)) {

				//check north east
				if (queenPositions[ofInterest].y < queenPositions[toCheck].y && queenPositions[ofInterest].x < queenPositions[toCheck].x &&
					queenPositions[ofInterest].collideNE == false) {
					queenPositions[ofInterest].collideNE = true;
					queenPositions[toCheck].collideSW = true;
					collisions++;
				}
				//check south east
				else if (queenPositions[ofInterest].y > queenPositions[toCheck].y && queenPositions[ofInterest].x < queenPositions[toCheck].x &&
					queenPositions[ofInterest].collideSE == false) {
					queenPositions[ofInterest].collideSE = true;
					queenPositions[toCheck].collideNW = true;
					collisions++;
				}
				//check north west
				else if (queenPositions[ofInterest].y < queenPositions[toCheck].y && queenPositions[ofInterest].x > queenPositions[toCheck].x &&
					queenPositions[ofInterest].collideNW == false) {
					queenPositions[ofInterest].collideNW = true;
					queenPositions[toCheck].collideSE = true;
					collisions++;
				}
				//check south west
				else if (queenPositions[ofInterest].y > queenPositions[toCheck].y && queenPositions[ofInterest].x > queenPositions[toCheck].x &&
					queenPositions[ofInterest].collideSW == false) {
					queenPositions[ofInterest].collideSW = true;
					queenPositions[toCheck].collideNE = true;
					collisions++;
				}
			}

		}
	}

	return collisions;
}