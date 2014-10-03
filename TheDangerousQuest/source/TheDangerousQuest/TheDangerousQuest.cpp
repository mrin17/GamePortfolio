// TheDangerousQuest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "textinfo.cpp"
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>//for random numbers
#include <assert.h>
#include <time.h>//for random number generation
#include <sstream>


using namespace std;

class Game;
class World;
class PlayerInput;
class Player;
class Person;
class Mercenary;
class Fighter;
class Mage;
class Buff;
class Enemy;
class BattleHandler;

////////////////CONSTANT CLASS//////////////////////
Strings STRS;

//////////GAME CLASS//////////////// - handles the gameplay
class Game {
private:
	vector<Player*> vp; //the vector of current players in the game

public:
	Game();
	~Game();
	void addplayer(Player &p) { // adds a player to the list
		vp.push_back(&p);
		assert(vp.size() > 0);
	}
	vector<Player*> getvp() {return vp;} //accessor for the vector of players
	void explore(Player &p, int i);
	void tavern(Player &p);
	void shop(Player &p);
	void joust(Player &p);
};

//////WORLD CLASS////////////////// - represents the world that the player is in
class World {
private:
	Player *p; // the current player exploring the world
	int lastvisited; // the last scenario visited
	int world; // the number of the world that you are in
	int defeated; // the number of enemies defeated in this world

public:
	World();
	World(Player *pl);
	~World();
	bool died();
	bool clear();
	void move();
	void enemy();
	void boss();
	void interp(vector<string> vs);
	void start(int i);
	int randlevel();
	Enemy* randenemy();
};

///////////PLAYER INPUT//////////////// - handles all player input
class PlayerInput {
public:
	PlayerInput();
	~PlayerInput();
	static string ask(string q, vector<string> a);
	static int getint(string q);
	static string getstr(string q);
	static int badanswer(string r, vector<string> a);
	static string toLower(string s);
};

///////PLAYER///////////////////// - represents you!
class Player {
private:
	vector<Mercenary*> chars; // the vector of characters in your party
	string name; // your name
	int prestige; // the number of levels you beat
	vector<string> items; // the vector of items you have
	string password; // your password
	int gold; // your gold

public:
	Player();
	Player(string s, string p);
	~Player();
	void addMercenary(Mercenary &m);
	void subscribe(Game &g);
	void levelAll(int exp);
	void healAll();
	bool diedAll();
	bool allLivingShields();
	void removeMercenary(int i);
	int getLowestDefense();
	void cleargold() {gold = 0;} // resets your gold
	int getgold() {return gold;} // accessor for gold
	string getpassword() {return password;} //accessor for password
	void addgold(int g) { // adds the given gold amount to your gold
		gold += g;
		if (gold < 0)
			gold = 0;
	}
	void addhealth(int h);
	int getprestige() {return prestige;} // accessor for prestige
	void addprestige(int world) { // increases prestige if you beat a new world
		if (world > prestige)
			prestige++;
	}
	string getname() {return name;} // accessor for name
	vector<Mercenary*> getchars() {return chars;} // accessor for chars
	vector<string> getItems() {return items;} // accessor for items
	void addItem(string item);
	bool useItem(string item);
	bool removeItem(string item);
	void displayItems(vector<string> loi, bool goldvals);
	void clearItems();
	void viewchars();

};

/////////PERSON CLASS//////////////// - represents a character - friend or foe
class Person {
protected:
	int ATK;
	int DEF;
	int HP;
	int MAXHP;
	int LV;
	int EXP;
	int SPD;
	string name;

public:
	virtual int defend(Person &p, int i) = 0;
	Person();
	void buildchar(string n, string c, int lv);
	void attack(Person &p);
	~Person();
	bool died() {return (HP <= 0);} // did you die?
	void takeDamage(int x) { // sets your health based on the damage taken
		HP -= x;
		if (HP < 0)
			HP = 0;
		if (HP > MAXHP)
			HP = MAXHP;
	}
	void displayStats();
	void displayHP();
	//accessors for the above variables
	int getATK() {return ATK;}
	int getDEF() {return DEF;}
	int getHP() {return HP;}
	int getMAXHP() {return MAXHP;}
	int getLV() {return LV;}
	int getEXP() {return EXP;}
	int getSPD() {return SPD;}
	string getName() {return name;}

};

/////MERCENARY CLASS//////////////////
class Mercenary : public Person {
public:
	virtual void attack_sp(Person &p) = 0;
	virtual int defend(Person &p, int i) = 0;

	Mercenary();
	~Mercenary();
	void defend_sp();
	void attack(Person &p);
	void levelUp();
	void heal() { // completely heals this mercenary, and resets its special meter
		HP = MAXHP;
		SPTURNS = 5;
		DEFTURNS = 0;
	}
	void addEXP(int e) { // adds the given experience, and checks if you leveled up
		EXP += e;
		levelUp();
	}
	//accessors for SPTURNS and DEFTURNS
	int getSPTURNS() {return SPTURNS;}
	int getDEFTURNS() {return DEFTURNS;}
	void displayStats();

protected:
	int SPTURNS; // the number of turns that has passed after you used your special
	int DEFTURNS; // the number of turns that you have under your defense special
};

//////////FIGHTER CLASS//////////////// - represents a Fighter mercenary, high speed
class Fighter : public Mercenary {

public:
	Fighter();
	~Fighter();
	void attack_sp(Person &p);
	int defend(Person &p, int i);
};

//////////BUFF CLASS//////////////// - represents a Buff mercenary, high defense
class Buff : public Mercenary {

public:
	Buff();
	~Buff();
	void attack_sp(Person &p);
	int defend(Person &p, int i);
};

//////////MAGE CLASS//////////////// - represents a Mage mercenary, high attack
class Mage : public Mercenary {

public:
	Mage();
	~Mage();
	void attack_sp(Person &p);
	int defend(Person &p, int i);
};

////////////ENEMY CLASS/////////// - represents an Enemy, with a specified intelligence
class Enemy : public Person {
private:
	string intelligence;

public:
	Enemy();
	~Enemy();
	Enemy(string n, string c, int l);
	int defend(Person &p, int i);
	string getIntelligence() {return intelligence;}
};

/////BATTLE HANDLER//////////////// - handles the battles and combat system
class BattleHandler {
private:
	Player* p; // current player
	vector<Enemy*> enemies; // vector of enemies
	vector<int> turnorder; // the turn order, represented as indexes, characters with higher speed move first
	bool PVP; // is this a PVP match?
	Player* ep; // enemy player, if its a PVP match

public:
	BattleHandler();
	BattleHandler(Player* p, vector<Enemy*> e);
	BattleHandler(Player* p, Player* p2);
	~BattleHandler();
	vector<int> setTurnOrder(vector<Mercenary*> m, vector<Person*> e);
	bool youwon();
	bool youdied();
	void battle();
	void displayStats();
	void handle(Mercenary* m, string name);
	void handleEnemy(Enemy* e);
	void attacktext(string a, string d, string type, int hp);
};



//METHOD IMPLEMENTATION//////////////////////////////
/////////////////////GAME CLASS//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Game::Game() {

}

//delete the vector of players
Game::~Game() {
	for(int i = 0; i < vp.size(); i++) {
		delete vp[i];
	}
}

//This function takes the given player and sends him/her out to explore the given world
void Game::explore(Player &p, int i) {
	World w = World(&p);
	assert(!w.clear() && !w.died());
	//this is the number of world you will enter
	w.start(i);
}

//sends the player to the shop to buy items
void Game::shop(Player &p) {
	cout<<"You have entered the shop."<<endl;
	cout<<"It is full all sorts of items and potions."<<endl;
	cout<<"You have "<<p.getgold()<<" gold."<<endl;
	PlayerInput plin = PlayerInput();
	vector<string> v;
	//fill the shop
	v.push_back("Water");
	v.push_back("Potion");
	v.push_back("Mega Potion");
	v.push_back("Master Potion");
	v.push_back("Revive");
	v.push_back("Master Revive");
	p.displayItems(v, true);
	v.push_back("Leave");
	//ask them to buy something
	string s = plin.ask("What would you like to buy?", v);

	int gold;
	//if they didnt leave, they bought something. repeat until they leave
	while(s != "Leave") {
		if (s == "Water") {
			gold = 10;
		}
		else if (s == "Potion") {
			gold = 20;
		}
		else if (s == "Mega Potion") {
			gold = 50;
		}
		else if (s == "Master Potion") {
			gold = 150;
		}
		else if (s == "Revive") {
			gold = 200;
		}
		else if (s == "Master Revive") {
			gold = 350;
		}
		if (p.getgold() >= gold) {
			cout<<"You bought the "<<s<<"."<<endl;
			p.addgold(-gold);
			p.addItem(s);
		}
		else {
			cout<<"You don't have enough money for that!"<<endl;
		}
		cout<<"You have "<<p.getgold()<<" gold."<<endl;
		s = plin.ask("What would you like to do?", v);
	}
	assert(p.getItems().size() >= 0 && p.getItems().size() <= 6);
}

//This function takes the given player and sends him/her to the tavern. 
//where he or she can buy mercenaries of a specific level and class unless the party size is 3
//he or she can also abandon mercenaries in his or her party unless the party size is 1
//he or she can also leave
void Game::tavern(Player &p) {
	cout<<"You have entered the tavern."<<endl;
	cout<<"It is full of mercenaries of all types and levels, ready for hire."<<endl;
	cout<<"You have "<<p.getgold()<<" gold. Mercenaries cost 25 gold per level to hire."<<endl;
	PlayerInput plin = PlayerInput();
	vector<string> v;
	v.push_back("Hire");
	v.push_back("Abandon");
	v.push_back("Leave");
	string s = plin.ask("What would you like to do?", v);

	//HIRE
	vector<string> c;
	c.push_back("Buff");
	c.push_back("Mage");
	c.push_back("Fighter");
	string cl;
	int lv;

	//ABANDON
	vector<string> y;
	stringstream in;
	stringstream ab;
	string aban;
	int num;

	//BOTH
	vector<string> a;
	a.push_back("yes");
	a.push_back("no");
	
	//if you did not leave,
	while(s != "Leave") {
		//and you want to hire a mercenary
		if (s == "Hire") {
			if (p.getchars().size() == 3) {
				cout<<"You cannot hire another mercenary. You can only have 3 at a time."<<endl;
			}
			else {
				//ask for class and level
				cl = plin.ask("Which class would you like to hire?", c);
				lv = plin.getint("What level "+cl+" are you looking for?");
				cout<<"Hiring this mercenary will cost "<<(lv*25)<<" gold."<<endl;
				if (lv*25 > p.getgold()) {
					cout<<"You don't have enough money for that mercenary."<<endl;
				}
				//confirmation that you are willing to spend the money
				else if (plin.ask("Will you do it?", a) == "yes") {
					if (cl == "Buff") {
						Buff* ch = new Buff();
						p.addgold(-(lv*25));
						ch->buildchar(cl, cl, lv);
						p.addMercenary(*ch);
						cout<<"A LV "<<lv<<" "<<cl<<" has joined your party."<<endl;
					}
					else if (cl == "Mage") {
						Mage* ch = new Mage();
						p.addgold(-(lv*25));
						ch->buildchar(cl, cl, lv);
						p.addMercenary(*ch);
						cout<<"A LV "<<lv<<" "<<cl<<" has joined your party."<<endl;
					}
					else if (cl == "Fighter") {
						Fighter* ch = new Fighter();
						p.addgold(-(lv*25));
						ch->buildchar(cl, cl, lv);
						p.addMercenary(*ch);
						cout<<"A LV "<<lv<<" "<<cl<<" has joined your party."<<endl;
					}
					assert(p.getchars().size() > 1);
				}
			}
		}
		//if you want to abandon a mercenary
		else if (s == "Abandon") {
			if (p.getchars().size() == 1) {
				cout<<"You cannot abandon your only mercenary."<<endl;
			}
			else {
				cout<<"Your current mercenaries: ";
				//get your current mercenaries
				for(int i = 1; i < p.getchars().size()+1; i++) {
					cout<<(i)<<") LV"<<p.getchars()[i-1]->getLV()<<" "<<p.getchars()[i-1]->getName()<<"  ";
					in.str("");
					in << i;
					y.push_back(in.str());
				}
				cout<<endl;
				y.push_back("none");
				//ask which one you want to abandon
				aban = plin.ask("Which mercenary would you like to abandon?", y);
				if (aban != "none") {
						num = atoi(aban.c_str());
						cout<<"Your LV " <<p.getchars()[num-1]->getLV()<<" "<< p.getchars()[num-1]->getName() << " has left the party."<<endl;
						p.removeMercenary((num-1));
						assert(p.getchars().size() < 3);
				}

			}
		}
		cout<<"You have "<<p.getgold()<<" gold. Mercenaries cost 25 gold per level to hire."<<endl;
		s = plin.ask("What would you like to do?", v);
	}
	assert(p.getchars().size() >= 1 && p.getchars().size() <= 3);
}

//sends the given player to the jousting arena to challenge other players
//can only challenge registered players
void Game::joust(Player &p) {
	PlayerInput plin = PlayerInput();
	vector<string> yon;
	yon.push_back("yes");
	yon.push_back("no");
	//challenge a player?
	if (plin.ask("Would you like to challenge another player to a battle?", yon) == "yes") {
		//get the other players
		vector<string> names;
		for (int i = 0; i < vp.size(); i++) {
			if (p.getname() != vp[i]->getname())
				names.push_back(vp[i]->getname());
		}
		if (names.size() == 0)
			cout<<"There aren't any other players in this town to challenge."<<endl;
		else {
			//ask for the other player
			string name = plin.ask("Which player would you like to challenge?", names);
			//the other player needs to enter his/her password to battle you
			for (int i = 0; i < vp.size(); i++) {
				if (vp[i]->getname() == name) {
					if (plin.getstr(name+", someone is challenging you! Type in your password to enter the town and accept this challenge:") == vp[i]->getpassword()) {
						cout<<"King: Let the battle between "<<p.getname()<<" and "<<name<<" commence!"<<endl;
						BattleHandler b = BattleHandler(&p, vp[i]);
						b.battle();
						p.healAll();
						vp[i]->healAll();
					}
					else {
						cout<<"The password was incorrect, so we cannot let "<<name<<" into the town."<<endl;
					}
				}
			}	
		}
	}
}

////////////////WORLD CLASS///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
World::World() {

}

//sets the player to the given player, sets the number of enemies defeated to 0, and sets lastvisited to 15
//so you can get all 15 options on the first event
World::World(Player *pl) {
	p = pl;
	defeated = 0;
	lastvisited = 15;
}

//destructor
World::~World() {

}

//Did all of the Mercenaries involved die?
bool World::died() {
	return p->diedAll();
}

//Did you clear the world?
bool World::clear() {
	return (defeated >= 10);
}

//Moves from section to section.
//Right now, this method just results in you fighting enemies.
void World::move() {
	//0-14 index, because 15 options
	int r = (rand() % 15);
	//just so you cannot get the same option twice
	while(lastvisited == r)
		r = (rand() % 15);
	lastvisited = r;
	//response necessary
	if (STRS.question(r)) {
		PlayerInput plin = PlayerInput();
		interp(STRS.interp(world, r, plin.ask(STRS.WORLD_QUESTIONS[world-1][r], STRS.WORLD_ANSWERS[r])));
	}
	else {
		//you encountered an enemy
		if (r < 4) {
			cout<<STRS.WORLD_QUESTIONS[world-1][r]<<endl;
			if (defeated == 9 && world == 10) // epic boss battle for the last world
				boss();
			else
				enemy();
		}
		//just an event
		else {
			cout<<STRS.WORLD_QUESTIONS[world-1][r]<<endl;
		}
		
	}
}

//interprets the given vector and changes the player based on it
//FIRST INDEX: "gold", "health", "tavern", "goldforhealth"(lose gold to get health), "shop", "item", "itempay", or ""
//SECOND INDEX: integer in the form of a string, or "", or an item
//represents how much of something you lose or gain (only utilized for gold and health)
//(or the item you get)
void World::interp(vector<string> vs) {
	if (vs[0] == "gold") {
		p->addgold(atoi(vs[1].c_str()));
	}
	else if (vs[0] == "health") {
		p->addhealth(atoi(vs[1].c_str()));
	}
	else if (vs[0] == "goldforhealth") {
		p->addgold(-(atoi(vs[1].c_str())));
		p->addhealth(atoi(vs[1].c_str()));
	}
	else if (vs[0] == "tavern") {
		Game g = Game();
		g.tavern(*p);
	}
	else if (vs[0] == "shop") {
		Game g = Game();
		g.shop(*p);
	}
	else if (vs[0] == "item") {
		p->addItem(vs[1]);
	}
	else if (vs[0] == "itempay") {
		if (vs[1] == "Water")
			p->addgold(-10);
		p->addItem(vs[1]);
	}
	cout<<endl;
}

//creates a random enemy, gives it to a battlehandler, and battles the player.
//If the enemy died, the number of enemies you beat increases by 1.
void World::enemy() {
	vector<Enemy*> v;
	cout<<endl<<"You have encountered a ";
	//list all the enemies
	for (int i = 0; i < p->getchars().size(); i++) {
		v.push_back(randenemy());
		if (i == 0)
			cout<<v[i]->getName();
		else
			cout<<" and a "<<v[i]->getName();
		//for testing
		//v[i]->displayStats();
	}
	cout<<"!"<<endl;
	assert(!v.size() == 0);
	//creates a battlehandler and battles
	BattleHandler b = BattleHandler(p, v);
	b.battle();
	cout<<endl;
	if (!died()) {
		defeated++;
	}
	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}
}
//creates a boss, gives it to a battlehandler, and battles the player.
//If the enemy died, the number of enemies you beat increases by 1.
//epic boss battle for the last world
void World::boss() {
	vector<Enemy*> v;
	cout<<endl<<"You get to the throne room. Sitting atop the regal throne is the Dark Lord himself."<<endl;
	cout<<"Dark Lord: Well, well, "<<p->getname()<<". You've come a long way."<<endl;
	cout<<"Dark Lord: Too bad there is nothing you can do to stop me!\nJust like your little village, the kingdom will fall into my hands!"<<endl;
	cout<<"Dark Lord: And I'll take you out just like I did with the rest of them."<<endl;
	cout<<endl<<"You have encountered the Dark Lord";
	//creates the dark lord based on your first mercenary's stats
	for (int i = 0; i < p->getchars().size(); i++) {
		if (i == 0) {
			if (p->getchars()[0]->getName() == "Mage")
				v.push_back(new Enemy("Dark Lord", "Fighter", randlevel()+5));
			else if (p->getchars()[0]->getName() == "Fighter")
				v.push_back(new Enemy("Dark Lord", "Buff", randlevel()+5));
			else
				v.push_back(new Enemy("Dark Lord", "Mage", randlevel()+5));
		}
		//and other random enemies
		else {
			v.push_back(randenemy());
			cout<<" and a "<<v[i]->getName();
		}
		//for testing
		//v[i]->displayStats();
	}
	cout<<"!"<<endl;
	assert(!v.size() == 0);
	//handles the battle
	BattleHandler b = BattleHandler(p, v);
	b.battle();
	cout<<endl;
	if (!died()) {
		defeated++;
		cout<<"Dark Lord: NOOOOOO! How could you manage to defeat me?"<<endl;
		cout<<"The Dark Lord writhes in pain in the ground, and his body disappears."<<endl;
		cout<<"Outside, the scene got lighter. The dark fog went away."<<endl;
	}
	else {
		cout<<"Dark Lord: HAHAHAHA!! No one shall ever defeat the Dark Lord!!!!!"<<endl;
	}
	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}
}
//a random number chooses which enemy you will fight.
Enemy* World::randenemy() {
	int r = (rand() % 6) + 1;
	Enemy* e;
	if (r == 1 || r == 2)
		e = new Enemy(STRS.ENEMIES[world-1][r-1], "Fighter", randlevel());
	if (r == 3 || r == 4)
		e = new Enemy(STRS.ENEMIES[world-1][r-1], "Buff", randlevel());
	if (r == 5 || r == 6)
		e = new Enemy(STRS.ENEMIES[world-1][r-1], "Mage", randlevel());
	return e;
}

//gives back a random level for a random enemy.
//it is between (world-1)*5 and (world)*5
int World::randlevel() {
	int r = 0;
	if (defeated == 0 || defeated == 1)
		r = 1;
	else if (defeated == 2)
		r = (rand() % 2)+1;
	else if (defeated == 3 || defeated == 5 || defeated == 7)
		r = (rand() % 2)+1+((defeated-3)/2);
	else if (defeated == 4 || defeated == 6 || defeated == 8)
		r = (rand() % 3)+1+((defeated-4)/2);
	else if (defeated == 9)
		r = 5;
	assert(r < 6);
	assert(!r == 0);
	return r+(world-1)*5;
}

//Starts your journey into world i. 
//No matter what, your characters are healed at the end
void World::start(int i) {
	world = i;
	srand(time(NULL));
	cout<<STRS.WORLD_INTRO[i-1]<<endl;
	//While you didn't win and you didn't die, you move.
	while(!clear() && !died()) {
		assert(defeated < 10);
		assert(!died());
		move();
	}
	//If you won, you get gold and EXP bonuses and you go back to the town.
	if (clear()) {
		cout<<STRS.WORLD_OUTRO[i-1]<<endl;
		cout<<"You cleared world "<<world<<"! All mercenaries get "<<world*4<<" EXP and you get "<<world*10<<" gold!"<<endl;
		p->addgold(world*10);
		p->addprestige(world);
		p->levelAll(world*4);
		p->healAll();
		assert(p->getgold() > 0);
		assert(!p->getprestige() == 0);
	}
	//If you lost, you lose all your gold (and items) and go back to town.
	else if (died()) {
		cout<<"Your mercenaries have died in World "<<world<<". You lost all of your gold and items."<<endl<<"You were forced to retreat to the town."<<endl;
		p->healAll();
		//you always have at least one character
		assert(p->getchars()[0]->getHP() == p->getchars()[0]->getMAXHP());
		p->cleargold();
		p->clearItems();
		assert(!p->getgold() > 0);
	}
}

///////////////////PLAYER INPUT CLASS/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
PlayerInput::PlayerInput() {

}

//destructor
PlayerInput::~PlayerInput() {

}

//the backbone method of my code
//given a question q and a list of answers a, this function outputs which answer the player chose
//uses a while loop to account for bad input
string PlayerInput::ask(string q, vector<string> a) {
	string res = "";
	cout<<q<<" "<<endl;
	//print answers
	for(int i = 0; i<a.size(); i++) {
		if (i == 0)
			cout<<a[i];
		else
			cout<<", "<<a[i];
	}
	if (a.size() > 0) {
		cout<<": ";
		//ask for answer
		std::getline(cin, res);
		//loop until the answer is good
		while(badanswer(toLower(res), a) == -1) {
			cout<<"Incorrect input. Please try again: ";
			std::getline(cin, res);
		}
		int index = badanswer(toLower(res), a);
		assert(!(res == "") && !(index == -1));
		return a[index];
	}
	return res;
}

//gets an integer larger than 0 from the user and returns that int
int PlayerInput::getint(string q) {
	string s = "";
	int result = 0;
	cout<<q<<" ";
	std::getline(cin, s);
	result = atoi(s.c_str());
	//loop until the input is valid
	while(result <= 0) {
		cout<<"Incorrect input. Please try again: ";
		std::getline(cin, s);
		result = atoi(s.c_str());
	}
	return result;
}

//gets a non-empty string from the user and returns that string
string PlayerInput::getstr(string q) {
	cout<<q<<" ";
	string s = "";
	std::getline(cin, s);
	//loop until the input is valid
	while(s == "") {
		cout<<"Incorrect input. Please try again: ";
		std::getline(cin, s);
	}
	assert(s.length() > 0);
	return s;
}

//Is the string r not in the vector a?
int PlayerInput::badanswer(string r, vector<string> a) {
	for(int i = 0; i<a.size(); i++) {
		if (toLower(a[i]) == r)
			return i;
	}
	return -1;
}

//takes a string and makes it lowercase
string PlayerInput::toLower(string s) {
	const char* c = s.c_str();
	string res = "";
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (c[i] >= 'A' && c[i] <= 'Z')
			res += c[i] - 'A' + 'a';
		else
			res += c[i];
	}
	return res;
}

////////////////PLAYER CLASS/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Player::Player() {

}

//constructor
//when a player is constructed, they are given a long, introductory dialogue and a chance to choose from 1 of 3 classes.
//you start with 20 gold at level 3 with water
Player::Player(string s, string p) {
	name = s;
	password = p;
	cout<<"Guard: Ok, "<<name<<", if you don't mind, I'm referring you to the King immediately. We're in need of heroes like you."<<endl;
	cout<<"The Guard takes you to a regal castle, and walks with you up the red carpet to the King."<<endl;
	cout<<"King: Our kingdom is under a dangerous threat, "<<name<<". The Dark Lord has risen once again, and he needs to be stopped."<<endl;
	cout<<"King: I have sent many Knights and Dames on a quest to stop the Dark Lord, but none of them have returned."<<endl;
	cout<<"King: You, "<<name<<", may very well be our only hope."<<endl;
	cout<<"King: Just as I have with the others, I will entrust you with one mercenary to accompany you on this quest. Choose wisely."<<endl;
	cout<<"King: The Mage has high attack, the Buff has high defense, and the Fighter has high speed."<<endl;
	vector<string> v;
	v.push_back("Mage");
	v.push_back("Buff");
	v.push_back("Fighter");
	PlayerInput plin = PlayerInput();
	//what class are you?
	string c = plin.ask("Which class will you choose?", v);
	cout<<"King: Ah, the "<<c<<". Good choice. Gather your necessary supplies in the town, and then embark on your dangerous quest."<<endl;
	cout<<"King: The kingdom is in your hands, "<<name<<". Make haste!"<<endl;
	if (c == "Mage") {
		chars.push_back(new Mage());
	}
	else if (c == "Buff") {
		chars.push_back(new Buff());
	}
	else if (c == "Fighter") {
		chars.push_back(new Fighter());
	}
	assert(!chars.size() == 0);
	gold = 20;
	prestige = 0;
	items.push_back("Water");
}

//clears the chars list
Player::~Player() {
	for(int i = 0; i < chars.size(); i++) {
		delete chars[i];
	}
}

//adds a mercenary if you have less than 3 party members
void Player::addMercenary(Mercenary &m) {
	if (chars.size() >= 3)
		cout<<"You cannot have more than 3 members in a party."<<endl;
	else {
		chars.push_back(&m);
		assert(!chars.size() == 0);
	}
}

//removes a mercenary if you have more than 1 member in your party
void Player::removeMercenary(int i) {
	if (chars.size() == 1)
		cout<<"You cannot have less than 1 member in a party."<<endl;
	else {
		int test = chars.size();
		vector<Mercenary*>::iterator it;
		int num = i;
		it = chars.begin();
		while(num > 1) {
			num--;
			it++;
		}
		it++;
		chars.erase(it);
		assert(chars.size() == (test-1));
	}
}

//given an EXP value, gives it to each member of the party
void Player::levelAll(int exp) {
	for(int i = 0; i < chars.size(); i++) {
		int lvtest = chars[i]->getLV();
		chars[i]->addEXP(exp);
		assert(chars[i]->getEXP() > 0 || chars[i]->getLV() > lvtest);
	}
}

//sets all mercenaries' HP to their MAXHP
void Player::healAll() {
	for(int i = 0; i < chars.size(); i++) {
		chars[i]->heal();
		assert(chars[i]->getHP() == chars[i]->getMAXHP());
		assert(!chars[i]->getHP() == 0);
	}
}

//gives all of your mercenaries the given number of health
void Player::addhealth(int h) {
	for(int i = 0; i < chars.size(); i++) {
		chars[i]->takeDamage(-h);
	}
}

//did all of your characters die?
bool Player::diedAll() {
	for(int i = 0; i < chars.size(); i++) {
		if (!chars[i]->died())
			return false;
	}
	return true;
}

//do all living players have shields up?
bool Player::allLivingShields() {
	for(int i = 0; i < chars.size(); i++) {
		if ((!chars[i]->died()) && chars[i]->getDEFTURNS() == 0)
			return false;
	}
	return true;
}

//gets the living char with the lowest defense, (without a shield), randomizing if there is a tie
//used for enemies deciding who to attack
int Player::getLowestDefense() {
	bool shields = allLivingShields();
	int def = -1;
	for(int i = 0; i < chars.size(); i++) {
		if ((!chars[i]->died())) {
			if (def == -1) {
				if (shields)
					def = i;
				else if (chars[i]->getDEFTURNS() == 0)
					def = i;
			}
			else if (chars[i]->getDEF() < chars[def]->getDEF()) {
				if (shields)
					def = i;
				else if (chars[i]->getDEFTURNS() == 0)
					def = i;
			}
			else if (chars[i]->getDEF() == chars[def]->getDEF() && (rand() % 2) == 0)
				if (shields)
					def = i;
				else if (chars[i]->getDEFTURNS() == 0)
					def = i;
		}
	}
	assert(def >= 0 && def <= 2);
	return def;
}

//display's your player's and your characters' stats on screen.
void Player::viewchars() {
	cout<<endl;
	cout<<name<<"'s party. You have "<<gold<<" gold to spend. Number of worlds beat: "<<prestige<<endl;
	for(int i = 0; i < chars.size(); i++) {
		chars[i]->displayStats();
	}
	if (items.size() > 0) {
		cout<<"Items"<<endl;
		displayItems(items, false);
	}
	cout<<endl;
}

//adds the given item to your inventory,
//asking you if you want to replace a current item if your inventory is full
void Player::addItem(string item) {
	if (items.size() >= 6) {
		cout<<"You cannot carry any more items."<<endl;
		vector<string> v;
		v.push_back("yes");
		v.push_back("no");
		PlayerInput plin = PlayerInput();
		if (plin.ask("Would you like to drop an item?", v) == "yes") {
			string s = plin.ask("Which item would you like to drop?", items);
			removeItem(s);
			cout<<"The "<<s<<" was removed from your inventory."<<endl;
			cout<<"The "<<item<<" was added to your inventory."<<endl;
			items.push_back(item);
		}
	}
	else {
		cout<<"The "<<item<<" was added to your inventory."<<endl;
		items.push_back(item);
	}
}

//given an item, this function uses it on the mercenary that you want
//returns true if this item was successfully used. This method assumes
//that the item has already been removed from the inventory, and 
//adds this item back again if you cannot use it
bool Player::useItem(string item) {
	PlayerInput plin = PlayerInput();
	if (removeItem(item)) {
        vector<string> y;
        stringstream in;
        string aban;
        int num;
        //displays and asks for mercenary to use item on
        cout<<"Your current mercenaries: ";
        for(int i = 1; i < chars.size()+1; i++) {
            cout<<(i)<<") LV"<<chars[i-1]->getLV()<<" "<<chars[i-1]->getName()<<"  ";
            in.str("");
            in << i;
            y.push_back(in.str());
        }
        cout<<endl;
        aban = plin.ask("Which mercenary would you like to use this on?", y);
        num = atoi(aban.c_str());
		num--;
        if (item == "Water") {
            if (chars[num]->died()) {
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" is dead."<<endl;
				items.push_back(item);
                return false;
            }
            else {
                chars[num]->takeDamage(-10);
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has healed 10 health."<<endl;
                return true;
            }
        }
        if (item == "Potion") {
            if (chars[num]->died()) {
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" is dead."<<endl;
                items.push_back(item);
				return false;
            }
            else {
                chars[num]->takeDamage(-20);
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has healed 20 health."<<endl;
                return true;
            }
        }
        else if (item == "Mega Potion") {
            if (chars[num]->died()) {
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" is dead."<<endl;
                items.push_back(item);
				return false;
            }
            else {
                chars[num]->takeDamage(-50);
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has healed 50 health."<<endl;
                return true;
            }
        }
        else if (item == "Master Potion") {
            if (chars[num]->died()) {
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" is dead."<<endl;
                items.push_back(item);
				return false;
            }
            else {
                chars[num]->heal();
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has healed all of his health."<<endl;
                return true;
            }
        }
        else if (item == "Revive") {
            if (chars[num]->died()) {
                chars[num]->takeDamage(-((int) (chars[num]->getMAXHP()/2)));
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has been revived at half health."<<endl;
                return true;
            }
            else {
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has not died."<<endl;
                items.push_back(item);
				return false;
            }
        }
		else if (item == "Master Revive") {
            if (chars[num]->died()) {
                chars[num]->heal();
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has been revived at full health."<<endl;
                return true;
            }
            else {
                cout<<"Your LV"<<chars[num]->getLV()<<" "<<chars[num]->getName()<<" has not died."<<endl;
                items.push_back(item);
				return false;
            }
        }
	}
}

//given an item, this function removes the first instance of that item from your inventory
//returns true if it was successful, false otherwise
bool Player::removeItem(string item) {
	for(int i = 0; i < items.size(); i++) {
		if (items[i] == item) {
			if (i == items.size() - 1) {
				items.pop_back();
				return true;
			}
			else {
				string temp = items[i+1];
				items[i+1] = item;
				items[i] = temp;
			}
		}
	}
	cout<<"You do not have that item."<<endl;
	return false;
}

//displays your items on the screen
void Player::displayItems(vector<string> loi, bool goldvals) {
	string s = "";
	for (int i = 0; i < loi.size(); i++) {
		cout<<loi[i]<<": ";
		if (loi[i] == "Water") {
			cout<<"Heals 10 health on a single mercenary";
			s = "10 gold";
		}
		else if (loi[i] == "Potion") {
			cout<<"Heals 20 health on a single mercenary";
			s = "20 gold";
		}
		else if (loi[i] == "Mega Potion") {
			cout<<"Heals 50 health on a single mercenary";
			s = "50 gold";
		}
		else if (loi[i] == "Master Potion") {
			cout<<"Heals all health on a single mercenary";
			s = "150 gold";
		}
		else if (loi[i] == "Revive") {
			cout<<"Revives a single mercenary at half health";
			s = "200 gold";
		}
		else if (loi[i] == "Master Revive") {
			cout<<"Revives a single mercenary at full health";
			s = "350 gold";
		}
		if (goldvals)
			cout<<"  COST: "<<s;
		cout<<endl;
	}
}

//resets your items (for dying)
void Player::clearItems() {
	items.clear();
	assert(items.size() == 0);
}

///////////////////////////PERSON CLASS/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Person::Person() {

}

//randomly creates a person based on a class, name and level
//used for enemies, and buying mercenaries
//becasue both have the same stat boosting mechanic based on level
void Person::buildchar(string n, string c, int l) {	
	name = n;
	LV = l;
	if (n == "Mage" || n == "Buff" || n == "Fighter")
		MAXHP = 15 + (l-1)*2;
	else
		MAXHP = 5 + (l-1)*2;
	HP = MAXHP;
	if (c == "Fighter") {
		ATK = 2;
		DEF = 2;
		SPD = 3;
	}
	else if (c == "Mage") {
		ATK = 4;
		DEF = 1;
		SPD = 2;
	}
	else {
		ATK = 1;
		DEF = 5;
		SPD = 1;
	}

	int points = (l-1)*2;
	int atkp = 0;
	int defp = 0;
	int spdp = 0;
	int r = 0;
	srand(time(NULL));
	for(int i = 0; i < points; i++) {
		
		r = (rand() % 7) + 1;
		if (r <= ATK) 
			atkp++;
		else if (r <= (ATK+DEF))
			defp++;
		else
			spdp++;
	}

	assert(atkp + defp + spdp == points);
	ATK += atkp;
	DEF += defp;
	SPD += spdp;
	assert(!(ATK + DEF + SPD > points+7) && !(ATK + DEF + SPD < points+7));
	EXP = 0;
}

//destructor
Person::~Person() {

}

//basic attacking function
//your attack minus their defense plus a random int from 0 to 3
//they have a chance to defend, and if the damage is less than 0, it gets set to 1.
void Person::attack(Person &p) {
	int damage = ATK + (rand() % 4) - p.getDEF();
	damage = p.defend(*this, damage);
	int hptest = p.getHP();
	if (damage <= 0)
		p.takeDamage(1);
	else
		p.takeDamage(damage);
	assert(p.getHP() < hptest);
}

//display's the character's stats
void Person::displayStats() {
	cout<<"LV "<<LV<<" ";
	displayHP();
	cout<<endl;
	cout<<"ATK "<<ATK<<endl;
	cout<<"DEF "<<DEF<<endl;
	cout<<"SPD "<<SPD<<endl;
	cout<<"EXP "<<EXP<<"/"<<LV*3<<endl;
}

//display's the character's name and HP/MAXHP
void Person::displayHP() {
	cout<<name<<": "<<HP<<"/"<<MAXHP<<" HP";
}

///////////////////MERCENARY CLASS//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Mercenary::Mercenary() {

}

//destructor
Mercenary::~Mercenary() {

}

//if you can defend, do so.
//This uses your energy so you cannot use a special/defend move for 5 turns
void Mercenary::defend_sp() {
	if (SPTURNS  >= 5) {
		SPTURNS = 0;
		DEFTURNS = 5;
		cout<<"Using this move drained your "<<name<<"'s energy for 5 turns."<<endl;
	}
}

//while your experience is larger than your level * 2, then you level up
void Mercenary::levelUp() {
	while (LV * 2 <= EXP) {
		//if so, it decreases your EXP, increases your level, increases your MAXHP by 2, and heals 2 of your health.
		EXP -= LV * 2;
		LV += 1;
		MAXHP += 2;
		HP += 2;
		cout<<"Your "<<name<< " has leveled up to level "<<LV<<". You get 2 stat points."<<endl;
		vector<string> v;
		v.push_back("ATK");
		v.push_back("DEF");
		v.push_back("SPD");
		string stat;
		int atktest = ATK;
		int deftest = DEF;
		int spdtest = SPD;
		//It asks you which 2 stats you want to level up and increases them accordingly
		PlayerInput plin = PlayerInput();
		for(int i = 0; i < 2; i++) {
			stat = plin.ask("Increase which stat by one?", v);
			if (stat == "ATK")
				ATK++;
			else if (stat == "DEF")
				DEF++;
			else if (stat == "SPD")
				SPD++;
		}
		assert(ATK > atktest || DEF > deftest || SPD > spdtest);
	}
}

//executes the Person attack method, but increases SPTURNS by 1
//so you can use your special/defend every 5 turns
void Mercenary::attack(Person &p) {
	int hptest = p.getHP();
	Person::attack(p);
	assert(p.getHP() < hptest);
	SPTURNS++;
	if (DEFTURNS > 0) {
		DEFTURNS--;
		if (DEFTURNS == 0)
			cout<<"Your defend has worn off."<<endl;
	}
}

//Displays stats, and what special attack and defend do
void Mercenary::displayStats() {
	Person::displayStats();
	if (name == "Fighter") {
		cout<<"Special Attack: Deals damage based on ATK+SPD against the enemy's ATK."<<endl;
		cout<<"Defend: For 5 turns, enemies have a 2/3 chance to miss with their attack, dealing 1 damage."<<endl;
	}
	else if (name == "Buff") {
		cout<<"Special Attack: Deals damage based on DEF instead of ATK."<<endl;
		cout<<"Defend: For 5 turns, if an enemy attacks you, they are dealt half the damage they deal to you."<<endl;
	}
	else if (name == "Mage") {
		cout<<"Special Attack: Deals damage based on enemy's ATK instead of their DEF."<<endl;
		cout<<"Defend: For 5 turns, damage dealt to you is reduced by half."<<endl;
	}
}

/////////////////////FIGHTER CLASS//////////////////////// start at level 3 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Fighter::Fighter() {
	ATK = 2+1;
	DEF = 2+1;
	SPD = 3+2;
	HP = 15+4;
	MAXHP = 15+4;
	LV = 3;

	EXP = 0;
	SPTURNS = 5;
	DEFTURNS = 0;
	name = "Fighter";
}

//destructor
Fighter::~Fighter() {

}

//Fighter's special attack
//deals damage based on ATK+SPD instead of ATK against the enemy's ATK
void Fighter::attack_sp(Person &p) {
	int hptest = p.getHP();
	if (SPTURNS >= 5) {
		SPTURNS = 0;
		int damage = ATK + SPD + (rand() % 4)- p.getATK();
		damage = p.defend(*this, damage);
		if (damage <= 0)
			p.takeDamage(1);
		else
			p.takeDamage(damage);
	}
	if (DEFTURNS > 0) {
		DEFTURNS--;
		if (DEFTURNS == 0)
			cout<<"Your defend has worn off."<<endl;
	}
	assert(p.getHP() < hptest);
	cout<<"Using this move drained your Fighter's energy for 5 turns."<<endl;
}

//Fighter's defend.
//If your defend is up, you have a 2/3 chance
//to take 1 damage instead of the normal damage
int Fighter::defend(Person &p, int i) {
	if (DEFTURNS > 0) {
		if ((rand() % 3) < 2)
		    return 1;
	}
	return i;
}

///////////////////////BUFF CLASS//////////////////////// start at level 3 /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Buff::Buff() {
	ATK = 1+1;
	DEF = 5+2;
	SPD = 1+1;
	HP = 15+4;
	MAXHP = 15+4;
	LV = 3;

	EXP = 0;
	SPTURNS = 5;
	DEFTURNS = 0;
	name = "Buff";
}

//destructor
Buff::~Buff() {

}

//Buff's special attack
//Deals damage based on your defense instead of your attack
void Buff::attack_sp(Person &p) {
	int hptest = p.getHP();
	if (SPTURNS >= 5) {
		SPTURNS = 0;
		int damage = DEF + (rand() % 4)- p.getDEF();
		damage = p.defend(*this, damage);
		if (damage <= 0)
			p.takeDamage(1);
		else
			p.takeDamage(damage);
	}
	if (DEFTURNS > 0) {
		DEFTURNS--;
		if (DEFTURNS == 0)
			cout<<"Your defend has worn off."<<endl;
	}
	assert(p.getHP() < hptest);
	cout<<"Using this move drained your Buff's energy for 5 turns."<<endl;
}

//Buff's defend
//If defend is up, the attacker takes half the damage as recoil
int Buff::defend(Person &p, int i) {
	if (DEFTURNS > 0) {
		if (i < 0)
			p.takeDamage(1);
		else
			p.takeDamage(((int) ((i/2)+1)));
	}
	return i;
}

////////////////////////MAGE CLASS//////////////////////// start at level 3 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Mage::Mage() {
	ATK = 4+2;
	DEF = 1+1;
	SPD = 2+1;
	HP = 15+4;
	MAXHP = 15+4;
	LV = 3;

	EXP = 0;
	SPTURNS = 5;
	DEFTURNS = 0;
	name = "Mage";
}

//destructor
Mage::~Mage() {

}

//Mage's special attack
//Subtracts ATK from the enemy's ATK instead of their DEF
void Mage::attack_sp(Person &p) {
	int hptest = p.getHP();
	if (SPTURNS >= 5) {
		SPTURNS = 0;
		int damage = ATK + (rand() % 4)- p.getATK();
		damage = p.defend(*this, damage);
		if (damage <= 0)
			p.takeDamage(1);
		else
			p.takeDamage(damage);
	}
	if (DEFTURNS > 0) {
		DEFTURNS--;
		if (DEFTURNS == 0)
			cout<<"Your defend has worn off."<<endl;
	}
	assert(p.getHP() < hptest);
	cout<<"Using this move drained your Mage's energy for 5 turns."<<endl;
}

//Mage's defend.
//If defend is up, halves damage taken
int Mage::defend(Person &p, int i) {
	if (DEFTURNS > 0) {
		if (i/2 < 1)
			return 1;
		else
			return i/2;
	}
	return i;
}

//////////////////////ENEMY CLASS///////////////////////
//constructor
Enemy::Enemy() {

}

//destructor
Enemy::~Enemy() {

}

//randomly creates an enemy.
//for each level, it increases the health by 2 and gives the enemy 2 stat points
//the enemy distributes these stat points based on their base stat distribution
//IE For the Buff:
//1/7 chance of increasing ATK, 
//5/7 chance of increasing DEF,
//1/7 chance of increasing SPD.
//DUMB = attacks a random person
//AVERAGE = attacks a random person without a shield (unless forced to)
//SMART = attacks a random person with the lowest defense without a shield (unless forced to)
Enemy::Enemy(string n, string c, int l) {
	
	if (n == "Dark Lord")
		intelligence = "smart";
	else {
		int r = (rand() % 3);
		if (r == 0)
			intelligence = "dumb";
		else if (r == 1)
			intelligence = "average";
		else
			intelligence = "smart";
	}
	buildchar(n, c, l);
}

//Enemy defend
//just returns i because enemies do not have special defends
int Enemy::defend(Person &p, int i) {
	return i;
}

/////////////////////BATTLE HANDLER CLASS////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//basic constructor
BattleHandler::BattleHandler() {

}

//sets the player to the given player, sets the enemies vector to the given enemy vector, and sets the turn order
BattleHandler::BattleHandler(Player* pl, vector<Enemy*> e) {
	p = pl;
	enemies = e;
	vector<Person*> persons;
	for (int i = 0; i < e.size(); i++)
		persons.push_back(e[i]);
	PVP = false;
	ep = NULL;
	turnorder = setTurnOrder(p->getchars(), persons);

}

//sets the player to the given player, sets the enemy player to the second player, and sets the turn order
BattleHandler::BattleHandler(Player* pl, Player* p2) {
	p = pl;
	ep = p2;
	vector<Person*> persons;
	vector<Mercenary*> chars = p2->getchars();
	for (int i = 0; i < chars.size(); i++)
		persons.push_back(chars[i]);
	PVP = true;
	turnorder = setTurnOrder(p->getchars(), persons);

}

//sets the turn order. This function outputs an int vector with numbers corresponding
//to the vector indexes of the characters. (0 would be first character in m)
//(anything larger than the size of m is in e)
//This function puts everyone in a vector of persons, 
//and performs insertion sort based on SPD
//since human players are put in first, and the SPD has to be larger to replace someone,
//human players win speed ties
vector<int> BattleHandler::setTurnOrder(vector<Mercenary*> m, vector<Person*> e) {
	vector<Person*> p;
	for(int a = 0; a<m.size(); a++) {
		p.push_back(m[a]);
	}
	for(int b = 0; b<e.size(); b++) {
		p.push_back(e[b]);
	}
	assert(p.size() == m.size() + e.size());
	vector<int> v;
	v.push_back(0);
	//i = new index to be inserted
	//p = list of players to be inserted
	//j = current index of the turn order
	//v = the turn order (list of indexes of p)
	//temp = the item to be removed and replaced
	//k = current index of the turn order (checking to insert the removed element)
	for(int i = 1; i < p.size(); i++) {
		for(int j = 0; j < v.size(); j++) {
			if (p[i]->getSPD() > p[v[j]]->getSPD()) {
				int temp = v[j];
				v[j] = i;
				for(int k = j+1; k < v.size() && p[temp]->getSPD() > p[v[k]]->getSPD(); k++) {
					int temp2 = v[k];
					v[k] = temp;
					temp = temp2;
				}
				v.push_back(temp);
				break;
			}
		}
		if (v.size() <= i) {
			v.push_back(i);
		}
	}
	assert(v.size() == p.size());
	for(int j = 1; j <v.size(); j++) {
		assert(!(p[v[j-1]]->getSPD() < p[v[j]]->getSPD()));
	}
	return v;
}

//destructor
BattleHandler::~BattleHandler() {

}

//did you die?
bool BattleHandler::youdied() {
	for(int i = 0; i < p->getchars().size(); i++) {
		if (!p->getchars()[i]->died()) {
			return false;
		}
	}
	return true;
}

//did you win? (did all the enemies die?)
bool BattleHandler::youwon() {
	if (PVP) {
		for(int a = 0; a < ep->getchars().size(); a++) {
			if (!ep->getchars()[a]->died()) {
				return false;
			}
		}
	}
	else {
		for(int a = 0; a < enemies.size(); a++) {
			if (!enemies[a]->died()) {
				return false;
			}
		}
	}
	return true;
}

//handles the battling. 
void BattleHandler::battle() {
	int totsize;
	if (PVP)
		totsize = p->getchars().size() + ep->getchars().size();
	else
		totsize = p->getchars().size() + enemies.size();
	//While you didn't die and you didn't win:
	while(!youdied() && !youwon()) {
		//go through every participant in the combat (totsize)
		for(int j = 0; j < totsize; j++) {
			//and handles their actions based on the turn order set by setTurnOrder
			if (turnorder[j] >= p->getchars().size()) {
				if (PVP)
					handle(ep->getchars()[turnorder[j]-p->getchars().size()], ep->getname());
				else
					handleEnemy(enemies[turnorder[j]-p->getchars().size()]);
			}
			else {
				handle(p->getchars()[turnorder[j]], p->getname());
			}
			if (youdied() || youwon())
				break;
		}
	}
	assert(youwon() || youdied());
	//if you won, you get EXP and gold (except PVP)
	if (youwon()) {
		if (PVP) {
			cout<<p->getname()<<" is the victor!"<<endl;
		}
		else {
			for(int i = 0; i < enemies.size(); i++) {
				int exp = enemies[i]->getLV();
				int gold = enemies[i]->getLV()*2+(rand() % enemies[i]->getLV());
				cout<<"You have defeated the "<<enemies[i]->getName()<<" and got "<<exp<<" EXP and "<<gold<<" gold."<<endl;
				p->addgold(gold);
				p->levelAll(exp);
			}
		}
	}
	//if you lost, the world function will take you back to the town (except PVP)
	if (youdied()) {
		if (PVP)
			cout<<ep->getname()<<" is the victor!"<<endl;
		else
			cout<<"You have lost to an enemy in battle."<<endl;
	}
}

//displays text based on which action you did
void BattleHandler::attacktext(string a, string d, string type, int hp) {
	assert(type == "Attack" || type == "Defend" || type == "Special" || type == "Item");
	if (a == "Fighter") {
		if (type == "Defend")
			cout<<"Your "<<a<<" speeds up his movements, making it hard for enemies to hit him."<<endl;
		else if (type == "Attack")
			cout<<"Your "<<a<<" punches the "<<d<<", dealing "<<hp<<" damage."<<endl;
		else if (type == "Special")
			cout<<"Your "<<a<<" throws a fast, deadly punch at the "<<d<<", dealing "<<hp<<" damage."<<endl;
	}
	else if (a == "Mage") {
		if (type == "Defend")
			cout<<"Your "<<a<<" waves his wand and creates a magical barrier surrounding himself."<<endl;
		else if (type == "Attack")
			cout<<"Your "<<a<<" blasts the "<<d<<" with his wand, dealing "<<hp<<" damage."<<endl;
		else if (type == "Special")
			cout<<"Your "<<a<<" summons a lightning bolt that electrifies the "<<d<<", dealing "<<hp<<" damage."<<endl;
	}
	else if (a == "Buff") {
		if (type == "Defend")
			cout<<"Your "<<a<<" tightens his muscles, ready to retaliate at anything that comes his way."<<endl;
		else if (type == "Attack")
			cout<<"Your "<<a<<" whacks the "<<d<<", dealing "<<hp<<" damage."<<endl;
		else if (type == "Special")
			cout<<"Your "<<a<<" calls all of his strength to jump on the "<<d<<", dealing "<<hp<<" damage."<<endl;
	}
	else {
		//a is an enemy, which can only attack
		cout<<"The "<<a<<" attacked your "<<d<<", dealing "<<hp<<" damage."<<endl;
	}
}

//handle a human player's attack
//if you didn't die, asks you for which action you want to perform
//(can only special or defend if you waited 5 turns)
//executes the action, and displays the result
void BattleHandler::handle(Mercenary* m, string name) {
	if (!m->died()) {
		Player* opponent;
		Player* you;
		//sets which player is active
		if (PVP) {
			if (name == p->getname()) {
				opponent = ep;
				you = p;
			}
			else {
				opponent = p;
				you = ep;
			}
		}
		else {
			you = p;
		}
		displayStats();
		vector<string> v;
		v.push_back("Attack");
		if (m->getSPTURNS()  >= 5) {
			v.push_back("Special");
			v.push_back("Defend");
			assert(v.size() == 3);
		}
		if (you->getItems().size() > 0) {
			v.push_back("Item");
		}
		stringstream ss;
		ss << m->getLV();
		PlayerInput plin = PlayerInput();
		string s;
		//choose which attack you use
		s = plin.ask("It's "+name+"'s LV "+ss.str()+" "+m->getName()+"'s move. What will you do?", v);
		assert(s == "Attack" || s == "Defend" || s == "Special" || s == "Item");
		if (s == "Defend") {
			m->defend_sp();
			attacktext(m->getName(), "", s, 0);
		}
		else if (s == "Item") {
			you->useItem(plin.ask("Which item would you like to use?", you->getItems()));
		}
		else if (s == "Attack" || s == "Special"){
			//lists the possible targets
			string enem;
			if ((!PVP) && (!(enemies.size() == 1)) || PVP && (!(opponent->getchars().size() == 1))) {
				//cout<<"Enemies: ";
				vector<string> y;
				stringstream in;
				if (!PVP) {
					for(int i = 1; i < enemies.size()+1; i++) {
						//cout<<(i)<<") LV"<<enemies[i-1]->getLV()<<" "<<enemies[i-1]->getName()<<"  ";
						if (!enemies[i-1]->died()) {
							in.str("");
							in << i;
							y.push_back(in.str());
						}
					}
				}
				else {
					for(int i = 1; i < opponent->getchars().size()+1; i++) {
						//cout<<(i)<<") LV"<<opponent->getchars()[i-1]->getLV()<<" "<<opponent->getchars()[i-1]->getName()<<"  ";
						if (!opponent->getchars()[i-1]->died()) {
							in.str("");
							in << i;
							y.push_back(in.str());
						}
					}
				}
				//choose your target
				enem = plin.ask("Which enemy do you want to attack?", y);
			}
			else {
				enem = "1";
			}
			Person* e;
			//attack
			if (!PVP)
				e = enemies[atoi(enem.c_str())-1];
			else
				e = opponent->getchars()[atoi(enem.c_str())-1];
			int temp = e->getHP();
			
			if (s == "Special") {
				m->attack_sp(*e);
			}
			else {
				m->attack(*e);
			}
			assert(!(temp < e->getHP()));
			temp -= e->getHP();
			attacktext(m->getName(), e->getName(), s, temp);
		}

	}
	//the mercenary whose turn it was died
	else {
		cout<<name<<"'s "<<m->getName()<<" is incapable of moving."<<endl;
	}
}

//displays each participant in the combat and their health
void BattleHandler::displayStats() {
	for(int i = 0; i < p->getchars().size(); i++) {
			p->getchars()[i]->displayHP();
		if (! (i == (p->getchars().size()-1)))
			cout<<", ";
	}
	cout<<" vs ";
	if (!PVP) {
		for(int i = 0; i < enemies.size(); i++) {
				enemies[i]->displayHP();
			if (! (i == (enemies.size()-1)))
				cout<<", ";
		}
	}
	else {
		for(int i = 0; i < ep->getchars().size(); i++) {
				ep->getchars()[i]->displayHP();
			if (! (i == (ep->getchars().size()-1)))
				cout<<", ";
		}
	}
	cout<<endl;
}

//handles an enemy's attack and displays the result
void BattleHandler::handleEnemy(Enemy* e) {
	if (!(e->died())) {
		displayStats();
		int i = 0;
		//DUMB = attacks a random person
		if (e->getIntelligence() == "dumb") {
			i = (rand() % p->getchars().size());
			while(p->getchars()[i]->died()) {
				i = (rand() % p->getchars().size());
			}
		}
		//AVERAGE = attacks a random person without a shield (unless forced to)
		else if (e->getIntelligence() == "average") {
			if (p->allLivingShields()) {
				i = (rand() % p->getchars().size());
				while(p->getchars()[i]->died()) {
					i = (rand() % p->getchars().size());
				}
			}
			else {
				i = (rand() % p->getchars().size());
				while(p->getchars()[i]->died() || p->getchars()[i]->getDEFTURNS() > 0) {
					i = (rand() % p->getchars().size());
				}
			}
		}
		//SMART = attacks a random person with the lowest defense without a shield (unless forced to)
		else if (e->getIntelligence() == "smart") {
			i = p->getLowestDefense();
		}
		Mercenary* m = p->getchars()[i];
		int temp = m->getHP();
		//attack the character
		e->attack(*m);
		assert(temp > m->getHP());
		temp -= m->getHP();
		attacktext(e->getName(), m->getName(), "Attack", temp);
	}
	else {
		cout<<"The "<<e->getName()<<" is incapable of moving."<<endl;
	}
}

////////MAIN METHOD///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//while you still want to play, it asks you which player you are, and creates a new one if necessary
//then, brings you to the town, where you can either Explore or ViewStats or Leave
//if you choose leave, you go back to the main menu.
int main() {
	srand(time(NULL));
	vector<string> v;
	v.push_back("yes");
	v.push_back("no");
	string name = "";
	Player *p;
	PlayerInput plin = PlayerInput();
	stringstream ss;
	bool init = false;
	Game g = Game();
	STRS.init();
	//yay intro
	cout<<"Your village was a calm and peaceful place. You went about your daily work."<<endl;
	cout<<"One night, you were tormented by bad dreams."<<endl;
	cout<<"Someone who called himself 'The Dark Lord' had threatened your town."<<endl;
	cout<<"He called upon you to turn yourself in or else your village would be destroyed."<<endl;
	cout<<"Thinking nothing of it, you ignore it and go about your regular business."<<endl;
	cout<<"That night, it happened."<<endl;
	cout<<"You were awoke by the sounds of screaming and the smell of burning."<<endl;
	cout<<"You rush outside to see what happened."<<endl;
	cout<<"The whole town was burning. People were running around everywhere."<<endl;
	cout<<"You look up and see the figure in your dream. The Dark Lord."<<endl;
	cout<<"He looks to the left and notices you. He grins, knowing you got his message."<<endl;
	cout<<"Scared, you rushed for shelter. The next day you visit the village."<<endl;
	cout<<"Your village was destroyed."<<endl;
	cout<<"You feel an immense anger towards the Dark Lord. You vow to get revenge."<<endl;
	cout<<"Since you have no place to live, you decide to head to the town to get supplies."<<endl;
	string enter = plin.ask("Guard: You look dressed like a hero. Would you like to enter the town?", v);
	while(enter == "yes") {
		init = false;
		//if youve been here before
		if (plin.ask("Guard: Have you been here before? It's too dark to tell", v) == "yes") {
			name = plin.getstr("Guard: What's your name again? My memory is not the best.");
			for (int i = 0; i < g.getvp().size(); i++) {
				if (g.getvp()[i]->getname() == name) {
					p = g.getvp()[i];
					init = true;
				}
			}
			if (init) {
				if (plin.getstr("Guard: What's the secret word you told me before? You might be the Dark Lord in disguise.") == p->getpassword()) {
					cout<<"Guard: Oh, "<<name<<". Now I remember. You can enter the town now."<<endl;	
				}
				else {
					cout<<"Guard: I'm afraid that's the wrong password, sir. I cannot let you in."<<endl;
					init = false;
				}
			}
			else {
				cout<<"Guard: "<<name<<"? Never heard of you. You haven't been here before."<<endl;
			}
		}
		//if youre new
		else {
			name = plin.getstr("Guard: Well, what's your name then?");
			init = true;
			for (int i = 0; i < g.getvp().size(); i++) {
				if (g.getvp()[i]->getname() == name) {
					cout<<"Guard: Wait, "<<name<<"? I know you've been here before."<<endl;
					init = false;
				}
			}
			if (init) {
				init = true;
				p = new Player(name, plin.getstr("Guard: I'd also like a password from you, so we know that we can trust you. What will it be?"));
				g.addplayer(*p);
			}
		}
		//if you did not leave the town
		if (init) {
			vector<string> a;
			a.push_back("Explore");
			a.push_back("View Stats");
			a.push_back("Tavern");
			a.push_back("Shop");
			a.push_back("Joust");
			a.push_back("Leave");
			//ask for an action
			string action = plin.ask("You have entered the town. What would you like to do?", a);
			while(!(action == "Leave")) {
				if (action == "Explore") {
					vector<string> w;
					for(int i = 0; i <= p->getprestige(); i++) {
						ss.str("");
						ss << (i+1);
						if ((i+1) < 11)
							w.push_back(ss.str());
					}
					g.explore(*p, atoi((plin.ask("Which world would you like to enter?", w)).c_str()));
				}
				else if (action == "View Stats") {
					p->viewchars();
				}
				else if (action == "Tavern") {
					g.tavern(*p);
				}
				else if (action == "Shop") {
					g.shop(*p);
				}
				else if (action == "Joust") {
					g.joust(*p);
				}
				action = plin.ask("You have entered the town. What would you like to do?", a);
			}
		}
		enter = plin.ask("Guard: You look dressed like a hero. Would you like to enter the town?", v);
	}
	return 0;
};

