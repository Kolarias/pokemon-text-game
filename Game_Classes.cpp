#include <iostream>
using namespace std;

class Pokemon
{
	private:
		string name;
		int max_health;
		int current_health;
		int attack;
	public:
		Pokemon()
		{
			name = "";
			max_health = 0;
			current_health = 0;
			attack = 0;
		}
		Pokemon(string in_name, int in_max_health, int in_attack)
		{
			name = in_name;
			max_health = in_max_health;
			current_health = max_health;
			attack = in_attack;
		}
		void set_current_health(int in_health){current_health = in_health;};
		string get_name(){return name;};
		int get_max_health(){return max_health;};
		int get_current_health(){return current_health;};
		int get_attack(){return attack;};
};

class Map_tile
{
	private:
		int num;
		string name;
		string desc;
		Pokemon wild_mon;
		bool mon_defeated;
	public:
		Map_tile()
		{
			num = 255;
			name = "";
			desc = "";
			wild_mon = Pokemon();
			mon_defeated = false;
		}
		Map_tile(int in_num, string in_name, string in_desc, Pokemon in_mon)
		{
			num = in_num;
			name = in_name;
			desc = in_desc;
			wild_mon = in_mon;
			mon_defeated = false;
		}
		void set_mon_defeated(){ mon_defeated = true;};
		int get_num(){ return num;};
		string get_name(){ return name;};
		string get_desc(){ return desc;};
		Pokemon get_wild_mon(){ return wild_mon;};
		bool get_mon_defeated(){ return mon_defeated;};
};

Map_tile map[24] = 
{
	Map_tile(0, "Entrance", "After beating the elite four, you finally were allowed into this cave. The entrance is just behind you, and to your north and east you see the vague shadows of stalactites, stalagmites, a bit of sunlight, and Pokemon. To your south and west are cave walls - the cave is like one massive room, and you are in the bottem left corner of it. And though you can't see it, you sense an immense power even further east.", Pokemon("Missingno", 0, 0)),
	Map_tile(1, "Zubat Nest", "There's a bunch of stalactites here, and you see the silohouettes of a bunch of bat Pokemon on ceiling. You still sense that power coming from the east, and there's a wall to your south.", Pokemon("Zubat", 50, 10)),
	Map_tile(2, "Zubat Nest", "There's a bunch of stalactites here, and you see the silohouettes of a bunch of bat Pokemon on ceiling. You still sense that power coming from the east, and there's a wall to your south.", Pokemon("Zubat", 50, 10)),
	Map_tile(3, "Rocks", "You've come across a rocky area with many pillars of stone reaching from the floor to the ceiling. You now see a visible blue barrier surrounding a small island in the distance to your east, and there's a wall to your south.", Pokemon("Rhydon", 150, 50)),
	Map_tile(4, "Below a Ledge", "You've reached the blue barrier that surrounds a small island and the water it rests in. Near you, before you hit the water, is a high ledge with the material of a large nest just peeking out of the top of it. Whatever's in the nest is mad that it can't breach the barrier.", Pokemon("Dragonite", 150, 75)),
	Map_tile(5, "Small Island", "After passing through the aura barrier, you surf to a small island and see a strange looking Pokemon with its eyes closed seemingly meditating in the middle of it. It's slightly pink, with a purple tail, and you can tell it has immense power. This will be an unforgettable battle.", Pokemon("Mewtwo", 275, 100)),
	Map_tile(6, "Grassy Area", "There's some grass here thats grown from the small amount of sunlight coming from the entrance of the cave. Its rustles, like there's something in it. There's a wall to your west.", Pokemon("Rattata", 50, 10)),
	Map_tile(7, "Zubat Nest", "There's a bunch of stalactites here, and you see the silohouettes of a bunch of bat Pokemon on ceiling. One silohouette is especially large.", Pokemon("Golbat", 75, 30)),
	Map_tile(8, "Rocks", "You've come across a rocky area with many pillars of stone reaching from the floor to the ceiling.", Pokemon("Rhyhorn", 75, 30)),
	Map_tile(9, "Grassy Area", "There's some grass here thats grown from a small amount of sunlight coming from an opening in the ceiling of the cave. There are large Pokemon grazing in it.", Pokemon("Tauros", 100, 75)),
	Map_tile(10, "Pond", "The water dripping from stalactites in the cave have formed a small pond here. You sense Pokemon around it.", Pokemon("Slowking", 150, 50)),
	Map_tile(11, "Small Clearing", "This part of the cave is fairly empty - just dirt, stone, and space. It's particularly warm here, for some reason. South of you is a blue barrier surrounding an island and the water it rests in.", Pokemon("Moltres", 175, 85)),
	Map_tile(12, "Zubat Nest", "There's a bunch of stalactites here, and you see the silohouettes of a bunch of bat Pokemon on ceiling. There's a wall to your west.", Pokemon("Zubat", 50, 10)),
	Map_tile(13, "Mud", "Water dripping from stalactites onto dirt below have made this area especially muddy.", Pokemon("Diglett", 50, 10)),
	Map_tile(14, "Zubat Nest", "There's a bunch of stalactites here, and you see the silohouettes of a bunch of bat Pokemon on ceiling.", Pokemon("Zubat", 50, 10)),
	Map_tile(15, "Fungus", "This area has a bunch of mushrooms growing from the ground. Maybe there were plants here at some point.", Pokemon("Parasect", 75, 30)),
	Map_tile(16, "Grassy Area", "There's some grass here thats grown from a small amount of sunlight coming from an opening in the ceiling of the cave. Is that a tree in the middle there?", Pokemon("Exeggutor", 125, 60)),
	Map_tile(17, "Rocks", "You've come across a rocky area with many pillars of stone reaching from the floor to the ceiling. There's a wall to your east.'", Pokemon("Golem", 125, 60)),
	Map_tile(18, "Pond", "The water dripping from stalactites have formed a small pond here in this corner of the cave. You sense Pokemon around it. There's a wall to your west.", Pokemon("Kingler", 100, 75)),
	Map_tile(19, "Clearing", "This part of the cave is fairly empty - just dirt, stone, and space. The clearing extends to multiple rooms along the back wall of the cave.", Pokemon("Chansey", 400, 10)),
	Map_tile(20, "Clearing", "This part of the cave is fairly empty - just dirt, stone, and space. The clearing extends to multiple rooms along the back wall of the cave.", Pokemon("Lickitung", 100, 40)),
	Map_tile(21, "Clearing", "This part of the cave is fairly empty - just dirt, stone, and space. The clearing extends to multiple rooms along the back wall of the cave.", Pokemon("Persian", 75, 50)),
	Map_tile(22, "Dead Tree", "There's somehow a dead tree lying in this part of the cave. You see bugs have taken residence in it.", Pokemon("Venemoth", 70, 30)),
	Map_tile(23, "Rocks", "You've come across a rocky area with many pillars of stone reaching from the floor to the ceiling, some of which form part of the back corner of the cave.", Pokemon("Rhydon", 150, 50)),
};
