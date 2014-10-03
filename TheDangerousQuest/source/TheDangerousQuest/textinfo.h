// textinfo.h : includes all fo the external text information I need for my game
// this includes the vectors for choices in the world, the possible answers for those, and the results
//

//#pragma once

#include <vector>
#include <string>

using namespace std;

//////CONSTANT VECTORS////////////////////////

class Strings {
public:
	vector<string> WORLD_INTRO;
	vector<string> WORLD_OUTRO;
	vector<vector<string>> ENEMIES;
	vector<vector<string>> WORLD_QUESTIONS;
	vector<vector<string>> WORLD_ANSWERS;

	void init();
	bool question(int r);
	vector<string> interp(int world, int r, string s);
};