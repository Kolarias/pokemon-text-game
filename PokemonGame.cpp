#include <iostream>
#include <algorithm>
#include "Game_Classes.cpp"
using namespace std;

void menu(string list_commands[], string input_array[], int length);
void help(string all_commands[], int length);
int move(int in_position, string in_command[], int in_xp);
bool battle(Pokemon enemy, Pokemon team[], int &xp, int &potions, int position, Map_tile map[]);

int main()
{
	// Set initial game conditions
	int position = 0;
	int xp = 0;
	int potions = 5;
	bool team_alive = true;
	string valid_commands[] = {"help", "quit", "move", "battle"};
	string command[] = {"","","",""};
	string useless_command;
	const int commands_length = 4;
	map[0].set_mon_defeated();
	
	// Set team
	Pokemon team[3] = {Pokemon("Squirtle", 100, 50), Pokemon("Ivysaur", 150, 75), Pokemon("Charizard", 200, 100)};
	 
	// Game Loop
	while(command[0] != "quit")
	{
		// Cout current position and player information
		cout << "\n\n" << map[position].get_name() << " (Room " << position << ")" <<endl;
		cout << "\n" << map[position].get_desc() << endl;
		if (!map[position].get_mon_defeated())
			cout << "\nPokemon Available to Battle: " << map[position].get_wild_mon().get_name() << endl;
		else
			cout << "\nThere are no Pokemon to battle here." << endl;
		cout << "\nCurrent XP is " << xp << ". Current amount of Potions is " << potions << "." << endl;
		
		// Get command
		menu(valid_commands, command, commands_length);
		
		// Perform command
		if (command[0] == "help")
			help(valid_commands, commands_length);
		else if (command[0] == "move")
			position = move(position, command, xp);
		else if (command[0] == "battle" && team_alive)
			if (!map[position].get_mon_defeated())
				team_alive = battle(map[position].get_wild_mon(), team, xp, potions, position, map);
			else
				cout << "\nThere are no Pokemon to battle here!" << endl;
		
		// If team dies, quit	
		if (!team_alive)
			{
				cout << "\nYour whole team is dead! Hit enter to quit. ";
				getline(cin, useless_command);
				command[0] = "quit";
			}
		
		// If defeated Mewtwo, quit
		if (map[5].get_mon_defeated() == true)
			{
				cout << "\nCongrats! You defeated Mewtwo! Thank you for playing this game. Hit enter to quit. ";
				getline(cin, useless_command);
				command[0] = "quit";
			}
	}
	
	return 0;
}

void menu(string list_commands[], string input_array[], int length)
{
	string input;
	bool is_valid = false;
	
	// Priming read for validation while loop
	cout << "\nEnter a command: ";
	getline(cin, input);
	
	// Convert input string to lower case
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	// Convert string to array of words
	string temp_word = "";
	int i = 0;
	for(auto x: input)
	{
		if (x == ' ')
		{
			input_array[i] = temp_word;
			i++;
			temp_word = "";
		}
		else
		{
			temp_word = temp_word + x;
		}
	}
	input_array[i] = temp_word;
	
	for(int i = 0; i < length ; i++)
	{
		if (input_array[0] == list_commands[i])
			is_valid = true;
	}
	
	// While not valid
	while(!is_valid)
	{
		cout << "\nInvalid command. Type \"help\" for a list of commands." << endl;
		
		cout << "\nEnter a command: ";
		getline(cin, input);
	
		// Convert input string to lower case
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		
		// Convert string to array of words
		string temp_word = "";
		int i = 0;
		for(auto x: input)
		{
			if (x == ' ')
			{
				input_array[i] = temp_word;
				i++;
				temp_word = "";
			}
			else
			{
				temp_word = temp_word + x;
			}
		}
		input_array[i] = temp_word;
		
		for(int i = 0; i < length ; i++)
		{
			if (input_array[0] == list_commands[i])
				is_valid = true;
		}
	}
}

void help(string all_commands[], int length)
{
	cout << "\nThe available commands are: ";
	
	for(int i = 0; i < (length-1) ; i++)
	{
		cout << all_commands[i] << ", ";
	}
	
	cout << "and " << all_commands[length-1] << "." << endl;
}

int move(int in_position, string in_command[], int in_xp)
{
	// Self explanitory, really
	int out_position = in_position;
	
	if(in_command[1] == "north" || in_command[1] == "up")
	{
		if(in_position >= 18 && in_position <= 23)
			cout << "\nYou cannot move north here." << endl;
		else
			out_position = in_position + 6;
	}
	else if(in_command[1] == "south" || in_command[1] == "down")
	{
		if(in_position >= 0 && in_position <= 5)
			cout << "\nYou cannot move south here." << endl;
		if(in_position == 11 && in_xp < 15)
			cout << "\nYou cannot move through the blue barrier! You sense that you may not be XPerienced enough." << endl;
		else
			out_position = in_position - 6;
	}
	else if(in_command[1] == "east" || in_command[1] == "right")
	{
		if(in_position == 5 || in_position == 11 || in_position == 17 || in_position == 23)
			cout << "\nYou cannot move east here." << endl;
		if(in_position == 4 && in_xp < 15)
			cout << "\nYou cannot move through the blue barrier! You sense that you may not be XPerienced enough." << endl;
		else
			out_position = in_position + 1;
	}
	else if(in_command[1] == "west" || in_command[1] == "left")
	{
		if(in_position == 0 || in_position == 6 || in_position == 12 || in_position == 18)
			cout << "\nYou cannot west east here." << endl;
		else
			out_position = in_position - 1;
	}
	else
		cout << "\nThat is not a valid movement command!" << endl;
	 
	return out_position;
}

bool battle(Pokemon enemy, Pokemon team[], int &xp, int &potions, int position, Map_tile map[])
{
	bool result;
	bool enemy_dead = false;
	bool team_dead = false;
	int num_team;
	char yes_no;
	Pokemon temp_pokemon = Pokemon("Missingo", 1000, 1000);
	string valid_commands_battle[] = {"attack", "switch", "item", "run", "help"};
	string commands[] = {"","","",""};
	const int commands_length_battle = 5;
	
	// Battle start test
	cout << "\nA wild " << enemy.get_name() << " appeared!" << endl;
	cout << "You sent out " << team[0].get_name() << "!" << endl;
	
	// While you haven't run, enemy isn't dead, and your team isnt dead
	while(commands[0] != "run" && !enemy_dead && !team_dead)
	{
		// Cout current Pokemon and enemy stats
		cout << "\nEnemy: " << enemy.get_name() << " (Health: " << enemy.get_current_health() << "/" << enemy.get_max_health() << ", Attack: " << enemy.get_attack() << ")" << endl;
		cout << "Your Pokemon: " << team[0].get_name() << " (Health: " << team[0].get_current_health() << "/" << team[0].get_max_health() << ", Attack: " << team[0].get_attack() << ")" << endl;
		
		// Get option selection
		menu(valid_commands_battle, commands, commands_length_battle);
		
		// If choose attack
		if (commands[0] == "attack")
			{
				// Dont battle if current pokemon is dead
				if (team[0].get_current_health() == 0)
					cout << "\nYour current Pokemon has fainted! Use an item to heal it or switch to a different Pokemon!" << endl;
				// If current pokemon is alive
				else
				{
					// Attack Pokemon, subtracting current pokemon attack from their health
					cout << "\n" << team[0].get_name() << " attacks " << enemy.get_name() << "! " << team[0].get_attack() << " damage dealt!" << endl;
					
					if (enemy.get_current_health() > team[0].get_attack())
						enemy.set_current_health(enemy.get_current_health() - team[0].get_attack());
					else
						{
							// Set enemy dead to true if attack is greater than enemy current health
							enemy.set_current_health(0);
							enemy_dead = true;
						}
						
					// If enemy isnt dead, they attack back
					if (enemy.get_current_health() != 0)
					{
						cout << "\n" << enemy.get_name() << " attacks " << team[0].get_name() << "! " << enemy.get_attack() << " damage dealt!" << endl;
						
						if (team[0].get_current_health() > enemy.get_attack())
							team[0].set_current_health(team[0].get_current_health() - enemy.get_attack());
						else
							{
								// If their attack is greater than current health, say current pokemon has fainted
								team[0].set_current_health(0);
								cout << team[0].get_name() << " has fainted!" << endl;
								
								// If pokemon has fainted, check if whole team is dead
								if (team[0].get_current_health() == 0 && team[1].get_current_health() == 0 && team[2].get_current_health() == 0)
									team_dead = true;
						 	}
					}
				}
			}
		// If choose switch
		else if (commands[0] == "switch")
			{
				// Get which pokemon to switch to (not including current)
				cout << "\nChoose which Pokemon to switch to:\n1. " << team[1].get_name() << "\n2. " << team[2].get_name() << endl;
				cout << "Enter which Pokemon to switch to number: ";
				cin >> num_team;
				
				// Validate it
				while (num_team > 2 || num_team < 1)
					{
						cout << "Invalid option." << endl;
						cout << "Enter which Pokemon to switch to number: ";
						cin >> num_team;
					}
				
				// Switch
				temp_pokemon = team[0];
				team[0] = team[num_team];
				team[num_team] = temp_pokemon;
				
				cin.ignore();
			}
		// If choose item
		else if (commands[0] == "item")
			{
				// If current pokemon is not full health and there are potions remaining
				if (potions != 0 && team[0].get_current_health() != team[0].get_max_health())
					{
						// Ask if they want to use a potion
						cout << "\n" << potions << " Max Potion(s) remaining. Do you wish to use one? (y/n) " << endl;
						cin >> yes_no;
						
						// If they say yes, use one
						if (yes_no == 'y')
							{
								team[0].set_current_health(team[0].get_max_health());
								potions = potions - 1;
							}
						else
							cout << "No potions were used." << endl;
							
						cin.ignore();
					}
				// Otherwise tell them why they can't use a potion
				else if (team[0].get_current_health() == team[0].get_max_health())
					cout << "\nYour current Pokemon has full health!" << endl;
				else
					cout << "\nYou have no potions remaining!" << endl;
			}
		// If choose help
		else if (commands[0] == "help")
			help(valid_commands_battle, commands_length_battle);
	}
	
	// End battle text, award xp if applicable, return whether team is dead
	if (commands[0] == "run")
		{	
			cout << "\nSuccessfully ran away! No XP rewarded." << endl;
			result = true;
		}
	else if (enemy_dead)
		{
			cout << "\n" << enemy.get_name() << " was defeated! 3 XP rewarded." << endl;
			xp = xp + 3;
			map[position].set_mon_defeated();
			result = true;
		}
	else if (team_dead)
		{
			cout << "\nAll of your Pokemon have fainted! You whited out!" << endl;
			result = false;
		}
	
	return result;
}
