// textinfo.cpp : includes all fo the external text information I need for my game
// this includes the vectors for choices in the world, the possible answers for those, and the results
//

//#pragma once
#include "textinfo.h";
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

//initializes all of the vectors in the Strings class
void Strings::init() {
	//INIT WORLD_INTRO
	WORLD_INTRO.push_back("As you begin your quest, you leave the town to embark through the wilderness.");
	WORLD_INTRO.push_back("You enter a dark forest, hoping not to disturb the creatures that lie within.");
	WORLD_INTRO.push_back("As you continue on, you encounter a blustering, dry desert.");
	WORLD_INTRO.push_back("The desert leads into a lagoon. The atmosphere feels ominous and gloomy.");
	WORLD_INTRO.push_back("You have found a dreary castle, and you enter, hoping that the Dark Lord waits here for you.");
	WORLD_INTRO.push_back("Disappointed at not finding the Dark Lord, you use your only clue and enter the ice caverns.");
	WORLD_INTRO.push_back("Looking up, you see a very long and ascending rocky path that looks extremely dangerous.");
	WORLD_INTRO.push_back("The path ends at the top of a sweltering volcano.\n You notice a figure, clad in black, walking near the bottom of the volcano into a dark pathway.\n You carefully tread downwards, suspicious of the figure's activity.");
	WORLD_INTRO.push_back("You see a dark portal at the bottom of the volcano. Surely this must be the descent to the dark world.");
	WORLD_INTRO.push_back("You take a look at the dark castle one last time before you enter.\nIn your head, you hear the Dark Lord laughing at you mercilessly. The doors open slowly, as if he is expecting you.");

	//INIT WORLD_OUTRO
	WORLD_OUTRO.push_back("You make your way through the wilderness, and see a forest in the distance.");
	WORLD_OUTRO.push_back("You see a clearing in the forest. You are eager to move on, knowing that you are making progress.");
	WORLD_OUTRO.push_back("As you move forward, the windstorm calms down, and a pool of dark blue water emerges in the horizon.");
	WORLD_OUTRO.push_back("Just as you thought the scene could not get any darker, a casle, black as night, appears in front of you.");
	WORLD_OUTRO.push_back("You find your way to the throne room of the castle and see a figure there.\nYou say courageously, 'Dark Lord, I know you're there. Stand up and fight me!'\nYou hear an ominous voice, 'I believe you have mistaken me for another.'\n'Ah, no matter. You're not going to live to see the difference.'\nThe dark figure jumps out at you, sword in hand, ready to slice your head off.\nYou swiftly dodge out of the way, and thrust your sword in the figure's back.\nThe dark figure cries out a cry of pain, and starts to speak:\n'I am just a servant of the Dark Lord. He sent me here to make sure you never got past me.'\n'Yes, he's expecting you. He knows of your power. But you will never defeat him.'\n'The Dark Lord is all-powerful! He will crush you like a little spider! And there is nothing you can do to stop him!'\n'His rule of the eastern land will soon advance past the ice caverns and into your little, measely kingdom!'");
	WORLD_OUTRO.push_back("The ice caverns exit into a steep, rocky path up a mountain.");
	WORLD_OUTRO.push_back("After the long and gruesome haul up the steep mountain, you finally reach the top.");
	WORLD_OUTRO.push_back("You have descended to the bottom of the volcano, and you see that the dark pathway the figure entered is close.");
	WORLD_OUTRO.push_back("A very large, dark castle obscures your view of everything else. Your senses tell you that this is indeed the Dark Lord's hideout.");
	WORLD_OUTRO.push_back("The Dark Lord has fallen!\nKing: Thank you, great hero! You are now the champion of the kingdom!");

	//INIT ENEMIES
	vector<string> vs;
	vs.push_back("Antelope");
	vs.push_back("Crow");
	vs.push_back("Rat");
	vs.push_back("Wanderer");
	vs.push_back("Thief");
	vs.push_back("Jaguar");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Spider");
	vs.push_back("Monkey");
	vs.push_back("Bear");
	vs.push_back("Elephant");
	vs.push_back("Shaman");
	vs.push_back("Wolf");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Snake");
	vs.push_back("Jackal");
	vs.push_back("Camel");
	vs.push_back("Turtle");
	vs.push_back("Genie");
	vs.push_back("Vulture");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Piranha");
	vs.push_back("Large Toad");
	vs.push_back("Hippo");
	vs.push_back("Zombie");
	vs.push_back("Shark");
	vs.push_back("Witch");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Bat");
	vs.push_back("Rogue");
	vs.push_back("Guard");
	vs.push_back("Troll");
	vs.push_back("Ghost");
	vs.push_back("Knight");
	ENEMIES.push_back(vs);

	vs.clear();
	vs.push_back("Ice Dragon");
	vs.push_back("Penguin");
	vs.push_back("Yeti");
	vs.push_back("Polar Bear");
	vs.push_back("Ice Elemental");
	vs.push_back("Ice Magician");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Falcon");
	vs.push_back("Eagle");
	vs.push_back("Rock Elemental");
	vs.push_back("Giant");
	vs.push_back("Swarm of Bees");
	vs.push_back("Goblin");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Fire Dragon");
	vs.push_back("Berserker");
	vs.push_back("Lava Toad");
	vs.push_back("Magma Beast");
	vs.push_back("Fire Magician");
	vs.push_back("Fire Elemental");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Shade");
	vs.push_back("Cutthroat");
	vs.push_back("Darkness Wanderer");
	vs.push_back("Darkness Beast");
	vs.push_back("Massive Shadow");
	vs.push_back("Dark Magician");
	ENEMIES.push_back(vs);
	vs.clear();
	vs.push_back("Black Rogue");
	vs.push_back("Dark Dragon");
	vs.push_back("Dark Guard");
	vs.push_back("Dark Elemental");
	vs.push_back("Dark Apostle");
	vs.push_back("Demon");
	ENEMIES.push_back(vs);

	//INIT WORLD_QUESTIONS
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("You hear some rustling in the tall grass next to you. You proceed carefully, hoping not to bring attention to yourselves.");
	vs.push_back("As the day grows old, your team continues to wander, questioning why you accepted this lengthy quest.");
	vs.push_back("You find some tall grass. Not seeing another way, you cautiously enter, groping your way through.");
	vs.push_back("As you walk through a rocky path, one of your mercenaries almost trips himself.");
	vs.push_back("You see a house entering in the distance. Someone could be there to aid you. Attempt to enter?");
	vs.push_back("You see a beggar wandering around. Give him money?");
	vs.push_back("You see something shiny on the ground ahead. Pick it up?");
	vs.push_back("You encounter a monastery out in the middle of nowhere. Pay your respects and enter?");
	vs.push_back("There is a dying man on the ground. Help him?");
	vs.push_back("The path splits before you. Which way will you go?");
	vs.push_back("The path before you ends in a rocky cliff. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("It feels like the monkeys are laughing at you as you move along. Perhaps they know of the Dark Lord's power.");
	vs.push_back("You feel like you have been wandering in this forest for ages without making any progress.");
	vs.push_back("You encounter a clearing. You think you've been here before, but just to be sure, you mark a tree so that you know next time you come here.");
	vs.push_back("You take a small break, and sit on a tree stump. You listen to the sounds of the forest as you get ready to move on.");
	vs.push_back("You encounter a clear, blue spring. Drink from it?");
	vs.push_back("You see a young man, garbed in green, sitting on a tree stump playing a weird tune on his ocarina. Approach him?");
	vs.push_back("You see something shiny on the ground ahead. Pick it up?");
	vs.push_back("You wander around, and see a regal tombstone that says 'Here lies King Myk the Great'. Rob the tombstone?");
	vs.push_back("You encounter a child, shivering and crying in a corner. Help him?");
	vs.push_back("Wandering aimlessly, you lose track of which way you came from. Which way will you go?");
	vs.push_back("You walk along, and your current path is blocked by trees. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("You come across a paved path, and follow it. Eventually, the path loses itself in the sand, yet you keep going.");
	vs.push_back("The desert sandstorm is taking a toll on your team. You decide to pitch a tent and rest for the night.");
	vs.push_back("As far as the eye can see, there is sand. The continuous landscape of yellow makes your team eager to leave.");
	vs.push_back("You think you see a man dressed in black in the distance. Could it be the Dark Lord? Or just a mirage?\nYou wander towards it, only to see it fade away into the sandstorm.");
	vs.push_back("You see an oasis in the distance. How lucky, you thought to yourself. Walk towards it?");
	vs.push_back("You see a turbaned man on a camel walk up to you. He inquires, 'Want some water? It'll cost you 10 gold.' Buy some?");
	vs.push_back("You see something shiny on the ground ahead. Pick it up?");
	vs.push_back("A very blurry town emerges in the distance. Attempt to enter?");//TAVERN
	vs.push_back("A person is waving at you vigorously. Help him?");
	vs.push_back("Miles and miles of sand. You begin to question if you are even going the right way. Which way will you go?");
	vs.push_back("You hear sounds all around you, but not in the way you are going. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("A mosquito has been bothering you for hours. All of a sudden a long tongue comes out of nowhere and grabs it out of the air. You flinch.");
	vs.push_back("You hear the heckling voices of witches flying overhead. They laugh, 'No one shall conquer Gloom Lagoon! Hyahahahaha!'");
	vs.push_back("You hear the sounds of toads and lizards near the swamp. The swamp bubbles slowly with anticipation, ready to swallow whatever falls in.");
	vs.push_back("As you walk, you try to imagine what it would be like in the lagoon during the day. It seems the shade of night constantly envelops the area.");
	vs.push_back("Your stomachs are gurgling, not haven eating anything for days. Like magic, you see a dead toad on the ground. Eat it?");
	vs.push_back("A small man runs up to you, saying, 'Thank heaven I found someone. Could you spare 5 gold? I need to get back to the town.' Give him money?");
	vs.push_back("You see something very shiny on the ground ahead. Pick it up?");
	vs.push_back("You encounter an eerie hut, with a 'Potions' sign outside. Enter?");//SHOP
	vs.push_back("You see a man lying on the ground; frog poison seemed to have killed him. Take his gold?");
	vs.push_back("A very creaky bridge over the swamp lies in your way. You deem it isn't safe. Which way will you go?");
	vs.push_back("Ahead, you hear cackling witches. Since you don't want to be turned into a frog, you decide to change direction. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("You enter a room with an organ. You hear an ominous, yet soothing tune. But no one is playing the organ. Weird.");
	vs.push_back("A loud crash of thunder startles your team. You realize you have been ignoring the constant downpour of rain outside.");
	vs.push_back("You make your way into a modest bedroom. You begin to comtemplate who actually lived here before the castle was deserted.");
	vs.push_back("As you are walking along a red carpet, you see muddy footsteps leading into a doorway. You follow them, knowing you aren't here alone.");
	vs.push_back("You wander through an enormous kitchen. A lone potion covered in cobwebs sits in an open cabinet. Drink it?");
	vs.push_back("A figure in the shadows calls out to you, saying, 'I'm lost. Can you tell me how to leave this place?' Give him directions?");
	vs.push_back("You see something very shiny on the ground ahead. Pick it up?");
	vs.push_back("You see a door that says 'Tavern'. You are very skeptical if a tavern would even be productive here. Enter?");//TAVERN
	vs.push_back("A treasure chest sits open in an empty room. There is a sign: 'Take as much as you need.' Take some gold?");
	vs.push_back("The hallway you have taken leads to a dead end. You backtrack until you can change paths. Which way will you go?");
	vs.push_back("As you are walking along, you see a door. You open the door, only to reveal solid wall. Weird. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("You hear a loud, echoing dripping noise in the pathway ahead.");
	vs.push_back("Your mercenary kicks a rock, making a noise that echoed through the cave. You hear the whoosh of bats moving above you.");
	vs.push_back("You see your mercenaries shiver in the coldness of the cavern. They'll just have to deal with it for now.");
	vs.push_back("You trip on a rock and start sliding. You crash into a wall. You lay there for a while before getting up.");
	vs.push_back("You see a man shivering intensely in the cold. He looks at you and then looks back down. Help him?");
	vs.push_back("You see a pile of gold across a pit. There is convieniently a rope hanging above you. Use the rope to get across?");
	vs.push_back("You see something very shiny on the ground ahead. Pick it up?");
	vs.push_back("You see the shadow of a human a decent way up the cave. Investigate it?");
	vs.push_back("There is a huge pile of snow ahead. It looks like someone hid something there. Dig in the snow?");
	vs.push_back("The pathway you were travelling leads to a large, deep pit. Which way will you go?");
	vs.push_back("The wall ahead has frozen over, and you cannot get through. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you move forward, you carefully watch your step, as to not trip on a rock and fall down.");
	vs.push_back("Wandering for a long time, your feet start to hurt. However, there is no place to rest so you must continue.");
	vs.push_back("After a while, you look down. You see a forest so far below that the trees look like ants.");
	vs.push_back("You look up, wondering how much farther up you have to go to get to the top.");
	vs.push_back("You hear crumbling, and as you look up you see rocks falling from the ledge above. Move away?");
	vs.push_back("You see a strong man knock a guy down and steal his wallet. Pursue him?");
	vs.push_back("You see something very shiny on the ground ahead. Pick it up?");
	vs.push_back("You hear some goblins cackling aside a fire. Approach them?");//SHOP
	vs.push_back("You see some rocks jutting out of the mountain. You think you could climb them to get higher up the mountain. Climb?");
	vs.push_back("The pathway extends into the mountain, and splits in three. Which way will you go?");
	vs.push_back("A rock slide has blocked your path. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you move forward, you carefully watch your step, as to not trip and fall down into the volcano.");
	vs.push_back("Your mercenaries get pretty tired because of the heat. You stop to rest a bit before you move on.");
	vs.push_back("You hear a loud screech and look towards the center of the volcano.\nYou see a dragon ascend from the depths out of the volcano.");
	vs.push_back("You look down at the boiling lava, hoping today is not the day that it acts up.");
	vs.push_back("You see a small opening in the wall. It could be a secret passageway. Enter?");//TAVERN
	vs.push_back("You see an armed man walking intently forwards, like on guard duty. Hide from him?");
	vs.push_back("You see something very shiny on the ground ahead. Pick it up?");
	vs.push_back("You see a huge egg in the middle of a pile of sticks. Your team is really hungry. Eat it?");
	vs.push_back("You have been ambushed by berserkers. They are surrounding you, and moving in.\nHowever, you have planned for this. Execute your plan?");
	vs.push_back("You have been walking in circles for hours. You decide to switch directions. Which way will you go?");
	vs.push_back("The pathway you were traveling on ends. However, you see a rickety bridge across the lava to your left. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("You can feel the pressure of the darkness on your body. Apparently the atmosphere was meant to suck the life out of people.");
	vs.push_back("You continue to walk down the path. You notice that this place looks exactly like the wilderness outside the town.");
	vs.push_back("As you move forward, you see an antelope, black as night with clear white eyes, stop running and look at you.\nIt stares at you for a good three seconds, and then runs off.");
	vs.push_back("You see some ghostly figures floating a distance above you. You think you've seen them before, but you're not certain.");
	vs.push_back("You see a small, dark village in the distance to the right. Approach it?");//SHOP hometown
	vs.push_back("You see a flock of dark crows flying overhead. They could be headed to attack you.\nHowever, if you attack them with projectiles before they arrive, you will surely have the upper hand. Initiate?");
	vs.push_back("You see something very shiny and white on the ground ahead, in high constrast to the blackness around you. Pick it up?");
	vs.push_back("You see a dark figure with white eyes threatening a scared man. Help the man out?");
	vs.push_back("You see a monastery, shadowy because of the dark fog. The 'ast' and the 'r' are faded. Enter?");
	vs.push_back("The path before you ends in a rocky cliff. Which way will you go?");
	vs.push_back("The fog suddenly gets denser than before. All you can see are three white lights in different directions. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	vs.clear();
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("As you wander further, you see an enemy!");
	vs.push_back("You feel the Dark Lord messing with your brain again. You have a strong urge to give up the quest, but you nevertheless continue.");
	vs.push_back("You enter a main room, with a double staircase and a chandelier. The chandelier looks like it's about to fall any second.\nYou vainly hope the Dark Lord walks under it at the right time.");
	vs.push_back("You come across a hallway with some stained glass windows. You see a depiction of the Dark Lord ruling the land.\nNext to it, you see a picture of a valiant knight sealing the Dark Lord away.\nThe picture after that shows the Dark Lord rising again to rule the kingdom.");
	vs.push_back("You come across the same hallway with the stained glass windows. You notice one at the end that is really dusty, so you wipe it off.\nYou see a very courageous knight and his men, braving intense conditions to reach the Dark Castle and slaying the Dark Lord once and for all.");
	vs.push_back("You see the same organ that you saw in the abandoned castle. There is a figure playing a slightly more ominous and dark tune. Approach him?");
	vs.push_back("You come across a locked door that leads to a tall staircase. You are suspicious of this. Try to pick the lock?");
	vs.push_back("You see something very shiny on the ground ahead. You hear the Dark Lord in your head telling you to take it. Pick it up?");
	vs.push_back("You see a man with a shadowy face and clear eyes manning a shop stand. Approach him?");//SHOP
	vs.push_back("You see a group of guards talking at the end of the hall. You do not want to engage them. Walk quietly away?");
	vs.push_back("The hallway splits in three. Which way will you go?");
	vs.push_back("The door ahead is locked. Which way will you go?");
	WORLD_QUESTIONS.push_back(vs);
	//INIT WORLD_ANSWERS (same for every world, im not original)
	vs.clear();
	//no response required for encountering an enemy (4) or flavor (4)
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	//either 'yes' or 'no' required for (5) encounters
	vs.push_back("yes");
	vs.push_back("no");
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
	//either 'left', 'back', or 'right' required for (2) encounters
	//it doesnt matter what you choose here
	vs.clear();
	vs.push_back("left");
	vs.push_back("back");
	vs.push_back("right");
	WORLD_ANSWERS.push_back(vs);
	WORLD_ANSWERS.push_back(vs);
};

//is the given result a question?
//the first 8 dont require a response
bool Strings::question(int r) {
	//return (r > 7);
	return (WORLD_ANSWERS[r].size() != 0);
};

//given which world the event was in, the event itself, and what the player chose, it generates the result
//(AKA what should happen to the player) in a vector of size 2
//FIRST INDEX: "gold", "health", "tavern", "goldforhealth"(lose gold to get health), "shop"(not implemented yet), or ""
//SECOND INDEX: integer in the form of a string, or ""
//represents how much of something you lose or gain (only utilized for gold and health)
vector<string> Strings::interp(int world, int r, string s) {
	srand(time(NULL));
	int ra = (rand() % 2);
	vector<string> v;
	//indexes [0,1,2,3,4,5,6,7,8,9][8,9,10,11,12]
	if (s == "yes") {
		//more negative results first
		if (ra == 0) {
			//house beggar shiny monastery dying
			if (world == 1) {
				if (r == 8) {
					cout<<"You approach the house, and yell 'Hello?', but no one answers."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You give him 5 gold, and the beggar says, 'Thank you so much! God bless you!'"<<endl;
					v.push_back("gold");
					v.push_back("-5");
				}
				else if (r == 10) {
					cout<<"It turned out to be worthless foil paper."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You visit the monastery, and pray for God's help on your quest."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"As you help the man up, he reaches for your wallet and runs away, saying, 'I showed you!'.\n You find yourself with 5 less gold."<<endl;
					v.push_back("gold");
					v.push_back("-5");
				}
			}
			//spring guy shiny tombstone child
			else if (world == 2) {
				if (r == 8) {
					cout<<"You drink from the spring. It tasted horrible. Your mercenaries lost 2 HP."<<endl;
					v.push_back("health");
					v.push_back("-2");
				}
				else if (r == 9) {
					cout<<"You approach the man, and he stops playing his ocarina and runs away."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"It turned out to be a yellow flower, wet and shiny with water."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You take 5 gold. As you turn around to leave, a branch falls on your mercenaries' heads.\n They all lose 5 HP."<<endl;
					v.push_back("goldforhealth");
					v.push_back("-5");
				}
				else if (r == 12) {
					cout<<"You cuddle the child, and he stops crying.\n You move along on your quest, and notice that you have been robbed of 5 gold."<<endl;
					v.push_back("gold");
					v.push_back("-5");
				}
			}
			//oasis turban shiny town person
			else if (world == 3) {
				if (r == 8) {
					cout<<"As you wander towards the oasis, it disappears. What a time for a mirage."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"The man says, 'Thanks for the gold! Oh, looks like I'm out of water. Bye!' and rides off."<<endl;
					v.push_back("gold");
					v.push_back("-10");
				}
				else if (r == 10) {
					cout<<"You somehow manage to find 10 gold in the sand."<<endl;
					v.push_back("gold");
					v.push_back("10");
				}
				else if (r == 11) {
					cout<<"Looks like the town was a mirage. Your mercenaries lose 4 HP for walking all the way here."<<endl;
					v.push_back("health");
					v.push_back("-4");
				}
				else if (r == 12) {
					cout<<"The person turned out to be a cactus. Oh well."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//toad man shiny potions gold
			else if (world == 4) {
				if (r == 8) {
					cout<<"You eat the toad, not knowing that it was poisonous. Your mercenaries lose 5 HP."<<endl;
					v.push_back("health");
					v.push_back("-5");
				}
				else if (r == 9) {
					cout<<"The man says, 'Thanks alot!' and runs off."<<endl;
					v.push_back("gold");
					v.push_back("-5");
				}
				else if (r == 10) {
					cout<<"It turned out to be an opened lock."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You enter the witch's hut, and she gives you a free sample. You all drink it and you all lose 4 HP."<<endl;
					v.push_back("health");
					v.push_back("-4");
				}
				else if (r == 12) {
					cout<<"As you reach over to take the gold, the man rises up and punches you all. Your mercenaries lose 3 HP."<<endl;
					v.push_back("health");
					v.push_back("-3");
				}
			}
			//potion lost shiny tavern chest
			else if (world == 5) {
				if (r == 8) {
					cout<<"You drink the old potion. Your mercenaries heal 10 HP."<<endl;
					v.push_back("health");
					v.push_back("10");
				}
				else if (r == 9) {
					cout<<"You tell him directions, and he thanks you and leaves."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You find a Potion."<<endl;
					v.push_back("item");
					v.push_back("Potion");
				}
				else if (r == 11) {
					cout<<"The door opens to a wall. Weird."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You take 8 gold pieces. Arrows fly at you from the openings in the wall. Your mercenaries lose 8 HP."<<endl;
					v.push_back("goldforhealth");
					v.push_back("-8");
				}
			}
			//shivering, gold, shiny, shadow, snow
			else if (world == 6) {
				if (r == 8) {
					cout<<"You help the man out of the cave. He silently walks away."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You run and try to grab the rope to swing to the gold. You slip, miss the rope, and fall in the pit. Your mercenaries lose 7 HP."<<endl;
					v.push_back("health");
					v.push_back("-7");
				}
				else if (r == 10) {
					cout<<"You find a bee encased in ice. How worthless."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You approach the man. The man turns out to be a servant of the Dark Lord, guarding the cave. He attacks you. Your mercenaries lose 4 HP."<<endl;
					v.push_back("health");
					v.push_back("-4");
				}
				else if (r == 12) {
					cout<<"You dig and dig in the snow, and you find 15 gold."<<endl;
					v.push_back("gold");
					v.push_back("15");
				}
			}
			//rockslide, wallet, shiny, goblins, climb
			else if (world == 7) {
				if (r == 8) {
					cout<<"You roll out of the way, not seeing the other half of the rock slide fall on you. Your mercenaries lose 7 HP."<<endl;
					v.push_back("health");
					v.push_back("-7");
				}
				else if (r == 9) {
					cout<<"You run towards the strong man, and prepare to attack him. He gives you back the wallet. You return it."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"It turns out to be fool's gold."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You walk towards the goblin band, and they start attacking you. You manage to kill them and loot 20 gold from them."<<endl;
					v.push_back("gold");
					v.push_back("20");
				}
				else if (r == 12) {
					cout<<"You climb the rocks, but you grab a loose rock and you fall. Your mercenaries lose 5 HP."<<endl;
					v.push_back("health");
					v.push_back("-5");
				}
			}
			//passage, guard, shiny, egg, berserkers
			else if (world == 8) {
				if (r == 8) {
					cout<<"You take the passageway, and you end up at a lower location then before."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You hide from the guard. As he passes you, he turns in your direction and says, 'Nice try!'.\nYou push him out of the way and into the lava, but not before he damages your mercenaries by 10 HP."<<endl;
					v.push_back("health");
					v.push_back("-10");
				}
				else if (r == 10) {
					cout<<"It turned out to be a rock, hot from the lava. It burns your hands. Your mercenaries lose 5 HP."<<endl;
					v.push_back("health");
					v.push_back("-5");
				}
				else if (r == 11) {
					cout<<"You eat the egg. It was delicious. A dragon comes out of nowhere and attacks you.\nYour mercenaries lost the health they gained from eating the egg."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You execute your secret plan. You all do a spin attack, and knock the berserkers away."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//village, crows, shiny, figure, monastery
			else if (world == 9) {
				if (r == 8) {
					cout<<"As you get closer to the village, you realize it was your hometown, devoured by darkness.\nAll of the inhabitants are ghosts. You feel an increased rage at the Dark Lord."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You throw stones at the crows. They get angry, and charge towards you now. Your mercenaries lose 15 HP."<<endl;
					v.push_back("health");
					v.push_back("-15");
				}
				else if (r == 10) {
					cout<<"You find 25 gold."<<endl;
					v.push_back("gold");
					v.push_back("25");
				}
				else if (r == 11) {
					cout<<"You kill the dark figure. The man thanks you and runs away.\nApparently, the man stole 15 gold from your wallet. What a way to repay you."<<endl;
					v.push_back("gold");
					v.push_back("-15");
				}
				else if (r == 12) {
					cout<<"You enter the monastery. The head priest, robed in black, says, 'You will get salvation, only if you pay.'\nYou pay 10 gold, and the monks heal your mercenaries by 10 HP."<<endl;
					v.push_back("goldforhealth");
					v.push_back("10");
				}
			}
			//organ, locked, shiny, shop, guards
			else if (world == 10) {
				if (r == 8) {
					cout<<"You approach the organ player, and he turns around. The figure looks like the Dark Lord, so you attack him.\nHe disappears in a puff of smoke, laughing at you."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You try to pick the lock, and the guards hear you and attack you. Your mercenaries lose 15 HP."<<endl;
					v.push_back("health");
					v.push_back("-15");
				}
				else if (r == 10) {
					cout<<"It turned out to be picture, of you and your family. How that got into the castle, you don't know. You grow even angrier at the Dark Lord."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You walk towards the man, and he says, 'Whatcha buying?'"<<endl;
					v.push_back("shop");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You quietly walk away from the guards, but they hear you. They rush towards you and attack you. Your mercenaries lose 10 HP."<<endl;
					v.push_back("health");
					v.push_back("-10");
				}
			}
		}
		else {
			//positive results second
			//house beggar shiny monastery dying
			if (world == 1) {
				if (r == 8) {
					cout<<"You approach the house, and an old couple greets you. They give you 5 gold to help you on your quest."<<endl;
					v.push_back("gold");
					v.push_back("5");
				}
				else if (r == 9) {
					cout<<"You give him 5 gold, and the beggar says, 'Thank you so much! God bless you! Take this food I have!'\nYour mercenaries heal 2 HP."<<endl;
					v.push_back("health");
					v.push_back("2");
				}
				else if (r == 10) {
					cout<<"You found 5 gold lying on the ground."<<endl;
					v.push_back("gold");
					v.push_back("5");
				}
				else if (r == 11) {
					cout<<"You visit the monastery, and pray for God's help on your quest. The monks there heal your mercenaries by 3 HP"<<endl;
					v.push_back("health");
					v.push_back("3");
				}
				else if (r == 12) {
					cout<<"You help the man up and give him some food. He thanks you and walks away."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//spring guy shiny tombstone child
			else if (world == 2) {
				if (r == 8) {
					cout<<"You drink from the spring. You feel your soul was cleansed. Your mercenaries heal 3 HP."<<endl;
					v.push_back("health");
					v.push_back("3");
				}
				else if (r == 9) {
					cout<<"You approach the man, and he stops playing his ocarina.\nHe hands you a bottle of water and nods intently. Then, he rushes off."<<endl;
					v.push_back("item");
					v.push_back("Water");
				}
				else if (r == 10) {
					cout<<"You found 5 gold."<<endl;
					v.push_back("gold");
					v.push_back("5");
				}
				else if (r == 11) {
					cout<<"You take all the gold you could find. As you turn around to leave, a branch falls on your mercenaries' heads.\n They all lose 5 HP."<<endl;
					v.push_back("goldforhealth");
					v.push_back("-5");
				}
				else if (r == 12) {
					cout<<"You cuddle the child, and he stops crying. You move along your quest."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//oasis turban shiny town person
			else if (world == 3) {
				if (r == 8) {
					cout<<"You wander towards the oasis, and drink from it. Your mercenaries heal 5 HP"<<endl;
					v.push_back("health");
					v.push_back("5");
				}
				else if (r == 9) {
					cout<<"The man says, 'Thanks for the gold! Here's some water!' and rides off."<<endl;
					v.push_back("itempay");
					v.push_back("Water");
				}
				else if (r == 10) {
					cout<<"You find 10 gold in the sand."<<endl;
					v.push_back("gold");
					v.push_back("10");
				}
				else if (r == 11) {
					cout<<"You enter the town and come across a tavern."<<endl;
					v.push_back("tavern");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You run towards the person, and he asks for directions. You tell him that you don't know. He thanks you and walks off."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//toad man shiny potions gold
			else if (world == 4) {
				if (r == 8) {
					cout<<"You eat the toad. Mmm, tastes like chicken. Your mercenaries heal 5 HP."<<endl;
					v.push_back("health");
					v.push_back("5");
				}
				else if (r == 9) {
					cout<<"The man says, 'Thanks alot!' and runs off. In his haste, he drops some food. Your mercenaries heal 5 HP."<<endl;
					v.push_back("goldforhealth");
					v.push_back("5");
				}
				else if (r == 10) {
					cout<<"You found a potion and drank it. It tasted disgusting. Your mercenaries lose 4 HP."<<endl;
					v.push_back("health");
					v.push_back("-4");
				}
				else if (r == 11) {
					cout<<"You enter the witch's hut."<<endl;
					v.push_back("shop");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You manage to loot 10 gold from his body."<<endl;
					v.push_back("gold");
					v.push_back("10");
				}
			}
			//potion lost shiny tavern chest
			else if (world == 5) {
				if (r == 8) {
					cout<<"You drink the old potion. Your mercenaries heal 8 HP."<<endl;
					v.push_back("health");
					v.push_back("8");
				}
				else if (r == 9) {
					cout<<"You tell him directions, and he gives you 15 gold as a reward."<<endl;
					v.push_back("gold");
					v.push_back("15");
				}
				else if (r == 10) {
					cout<<"You find 30 gold."<<endl;
					v.push_back("gold");
					v.push_back("30");
				}
				else if (r == 11) {
					cout<<"Much to your surprise, the door opens to bustling tavern."<<endl;
					v.push_back("tavern");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You manage to take 15 gold pieces."<<endl;
					v.push_back("gold");
					v.push_back("15");
				}
			}
			//shivering, gold, shiny, shadow, snow
			else if (world == 6) {
				if (r == 8) {
					cout<<"You help the man out of the cave. He gives you 20 gold for your troubles."<<endl;
					v.push_back("gold");
					v.push_back("20");
				}
				else if (r == 9) {
					cout<<"You run, jump, grab the rope, and swing to the other side. You are rewarded with 25 gold."<<endl;
					v.push_back("gold");
					v.push_back("25");
				}
				else if (r == 10) {
					cout<<"You find a Mega Potion."<<endl;
					v.push_back("item");
					v.push_back("Mega Potion");
				}
				else if (r == 11) {
					cout<<"You approach the man. He happened to know the way out of the cave, and he gives you directions."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You dig and dig in the snow, and you find a Potion."<<endl;
					v.push_back("item");
					v.push_back("Potion");
				}
			}
			//rockslide, wallet, shiny, goblins, climb
			else if (world == 7) {
				if (r == 8) {
					cout<<"You dodge the rocks safely."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You run towards the strong man, kill him, and give the wallet back. The man gives you 25 gold for your troubles."<<endl;
					v.push_back("gold");
					v.push_back("25");
				}
				else if (r == 10) {
					cout<<"It turns out to be a Potion."<<endl;
					v.push_back("item");
					v.push_back("Potion");
				}
				else if (r == 11) {
					cout<<"You walk towards the goblin band, and you realize they are the proprietors of a shop."<<endl;
					v.push_back("shop");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You climb the rocks and you manage to get higher up the mountain."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//passage, guard, shiny, egg, berserkers
			else if (world == 8) {
				if (r == 8) {
					cout<<"You take the passageway, and it leads to a tavern. You wonder why they put taverns in the weirdest places."<<endl;
					v.push_back("tavern");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You hide from the guard. As he passes you, you turn and knock him out. You steal 25 gold from his body."<<endl;
					v.push_back("gold");
					v.push_back("25");
				}
				else if (r == 10) {
					cout<<"It turned out to be 40 gold."<<endl;
					v.push_back("gold");
					v.push_back("40");
				}
				else if (r == 11) {
					cout<<"You eat the egg. Your mercenaries heal 10 HP."<<endl;
					v.push_back("health");
					v.push_back("10");
				}
				else if (r == 12) {
					cout<<"You execute your secret plan. You all do a spin attack, and knock the berserkers away.\nYou loot some food from their bodies. Your mercenaries heal 8 HP."<<endl;
					v.push_back("health");
					v.push_back("8");
				}
			}
			//village, crows, shiny, figure, monastery
			else if (world == 9) {
				if (r == 8) {
					cout<<"As you get closer to the village, you realize it was your hometown, devoured by darkness.\nAll of the inhabitants are ghosts. You find the local shop."<<endl;
					v.push_back("shop");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You throw stones at the crows. They charge towards you, but you kill them before they get to you."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You find a Revive."<<endl;
					v.push_back("item");
					v.push_back("Revive");
				}
				else if (r == 11) {
					cout<<"You kill the dark figure. The man thanks you, and gives you some food. Your mercenaries heal 12 HP."<<endl;
					v.push_back("health");
					v.push_back("12");
				}
				else if (r == 12) {
					cout<<"You enter the monastery. The head priest, robed in black, says, 'You will get salvation, only if you pay.'\nYou donate blood. Your mercenaries lose 5 HP."<<endl;
					v.push_back("health");
					v.push_back("-5");
				}
			}
			//organ, locked, shiny, shop, guards
			else if (world == 10) {
				if (r == 8) {
					cout<<"You approach the organ player, and he turns around.\nHe says he was hired by the Dark Lord to play this music, and he tells you about the secrets of the castle, and then continues playing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You pick the lock and move up the stairs."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"It turned out to be a Master Potion. How lucky."<<endl;
					v.push_back("item");
					v.push_back("Master Potion");
				}
				else if (r == 11) {
					cout<<"You walk towards the man, and he says, 'Whatcha buying?'"<<endl;
					v.push_back("shop");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You quietly walk away from the guards."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
		}
	}
	else if (s == "no") {
		//more negative results first
		if (ra == 0) {
			//house beggar shiny monastery dying
			if (world == 1) {
				if (r == 8) {
					cout<<"You wander past the old house"<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You continue on your way, ignoring the beggar"<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the monastery. Out of nowhere, rocks fly at your heads. Your mercenaries lose 3 HP."<<endl;
					v.push_back("health");
					v.push_back("-3");
				}
				else if (r == 12) {
					cout<<"You leave the dying man to fend for himself."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//spring guy shiny tombstone child
			else if (world == 2) {
				if (r == 8) {
					cout<<"You pass by the spring."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You pass by the man. He stares at you as you leave."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You say a prayer and leave the tomb."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You let the child continue crying."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//oasis turban shiny town person
			else if (world == 3) {
				if (r == 8) {
					cout<<"You don't check out the oasis."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"The man says, 'Oh well, your loss.', and rides off."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing. It turned out to be a scorpion, and it attacked you. Your mercenaries lose 2 HP."<<endl;
					v.push_back("health");
					v.push_back("-2");
				}
				else if (r == 11) {
					cout<<"You pass by the town."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You pretend to not notice the person, and walk away."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//toad man shiny potions gold
			else if (world == 4) {
				if (r == 8) {
					cout<<"You pass by the dead toad."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"The man punches you and runs off.Your mercenaries lose 4 HP"<<endl;
					v.push_back("health");
					v.push_back("-4");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the witch's hut."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You let the dead man rot along with his gold."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//potion lost shiny tavern chest
			else if (world == 5) {
				if (r == 8) {
					cout<<"You leave the kitchen without drinking the potion."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You walk away. Eventually you notice that your wallet has 10 less gold."<<endl;
					v.push_back("gold");
					v.push_back("-10");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the tavern."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You have a strong suspicion about the chest, so you walk away."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//shivering, gold, shiny, shadow, snow
			else if (world == 6) {
				if (r == 8) {
					cout<<"You walk away from the man."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You ignore the rope. However, you slip and fall in the pit. Your mercenaries lose 7 HP."<<endl;
					v.push_back("health");
					v.push_back("-7");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You ignore the human shadow."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You pass by the pile of snow."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//rockslide, wallet, shiny, goblins, climb
			else if (world == 7) {
				if (r == 8) {
					cout<<"You crouch and shield your head. The rocks fall on top of you. Your mercenaries lose 7 HP."<<endl;
					v.push_back("health");
					v.push_back("-7");
				}
				else if (r == 9) {
					cout<<"You ignore the situation. The strong man walks up to you and secretly hands you 15 gold."<<endl;
					v.push_back("gold");
					v.push_back("15");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pay no attention to the goblins."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You do not climb the rocks."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//passage, guard, shiny, egg, berserkers
			else if (world == 8) {
				if (r == 8) {
					cout<<"You do not take the passageway."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You continue walking. The guard attacks you. Your mercenaries lose 10 HP."<<endl;
					v.push_back("health");
					v.push_back("-10");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the egg."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You fight regularly. Your mercenaries lose 6 HP."<<endl;
					v.push_back("health");
					v.push_back("-6");
				}
			}
			//village, crows, shiny, figure, monastery
			else if (world == 9) {
				if (r == 8) {
					cout<<"You pass by the village."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You ignore the crows. They swoop by and attack you. Your mercenaries lose 10 HP."<<endl;
					v.push_back("health");
					v.push_back("-10");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You let the man fend for himself."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You pass by the monastery. You feel eyes staring at you from inside."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//organ, locked, shiny, shop, guards
			else if (world == 10) {
				if (r == 8) {
					cout<<"You continue on your way."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You pass by the door."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You ignore the shop."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You run and attack the guards. You kill them and loot 30 gold from them."<<endl;
					v.push_back("gold");
					v.push_back("30");
				}
			}
		}
		else {
			//positive results second
			//house beggar shiny monastery dying
			if (world == 1) {
				if (r == 8) {
					cout<<"You wander past the old house"<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You continue on your way, ignoring the beggar"<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the monastery."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You leave the dying man to fend for himself."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//spring guy shiny tombstone child
			else if (world == 2) {
				if (r == 8) {
					cout<<"You pass by the spring."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You pass by the man. He stares at you as you leave."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You say a prayer and leave the tomb. An aura emanates from the tomb. Your mercenareis heal 3 HP."<<endl;
					v.push_back("health");
					v.push_back("3");
				}
				else if (r == 12) {
					cout<<"You let the child continue crying."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//oasis turban shiny town person
			else if (world == 3) {
				if (r == 8) {
					cout<<"You don't check out the oasis."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"The man says, 'Oh well, your loss.', and rides off."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the town."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You pretend to not notice the person, and walk away."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//toad man shiny potions gold
			else if (world == 4) {
				if (r == 8) {
					cout<<"You pass by the dead toad."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"The man runs off to find someone else to ask."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the witch's hut."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You let the dead man rot along with his gold."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//potion lost shiny tavern chest
			else if (world == 5) {
				if (r == 8) {
					cout<<"You leave the kitchen without drinking the potion."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You walk away."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the tavern."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You have a strong suspicion about the chest, so you walk away."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//shivering, gold, shiny, shadow, snow
			else if (world == 6) {
				if (r == 8) {
					cout<<"You walk away from the man."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You ignore the rope."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You ignore the human shadow."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You pass by the pile of snow."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//rockslide, wallet, shiny, goblins, climb
			else if (world == 7) {
				if (r == 8) {
					cout<<"You crouch and shield your head. Like a miracle, you are not harmed."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You ignore the situation."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pay no attention to the goblins."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You do not climb the rocks."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//passage, guard, shiny, egg, berserkers
			else if (world == 8) {
				if (r == 8) {
					cout<<"You do not take the passageway."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You continue walking. The man happens to ignore you."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You pass by the egg."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You fight regularly. Your mercenaries lose 10 HP, but you kill them and get 10 gold."<<endl;
					v.push_back("goldforhealth");
					v.push_back("-10");
				}
			}
			//village, crows, shiny, figure, monastery
			else if (world == 9) {
				if (r == 8) {
					cout<<"You pass by the village."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You ignore the crows."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You let the man fend for himself."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You pass by the monastery. You feel eyes staring at you from inside."<<endl;
					v.push_back("");
					v.push_back("");
				}
			}
			//organ, locked, shiny, shop, guards
			else if (world == 10) {
				if (r == 8) {
					cout<<"You continue on your way."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 9) {
					cout<<"You pass by the door."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 10) {
					cout<<"You don't bother to check out the shiny thing."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 11) {
					cout<<"You ignore the shop."<<endl;
					v.push_back("");
					v.push_back("");
				}
				else if (r == 12) {
					cout<<"You continue walking. The guards attack you. Your mercenaries lose 8 HP."<<endl;
					v.push_back("health");
					v.push_back("-8");
				}
			}
		}
	}
	else {
		//chose a path, doesn't matter
		v.push_back("");
		v.push_back("");
	}

	return v;
};
