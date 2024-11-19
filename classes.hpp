/*
Vinny Nittolo and Andrew Kase
Prof. Woodring
CIS 343-01
*/

#ifndef __H__CLASSES__
#define __H__CLASSES__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib> // for rand()
#include <ctime> // for time()
#include <functional>

//defines the input class
class Input{
public:
    std::string command_input;
    Input();

    std::vector<std::string> split(int i);
private:

};


//defines the item class
class Item {
public:
    Item(std::string n = "", int c = 0, float w = 0.0, std::string d = "");

    //getters
    std::string get_name() const;
    int get_calories() const;
    float get_weight() const;
    std::string get_description() const;

    //setters
    void set_name(const std::string& n);
    void set_calories(int c);
    void set_weight(float w);
    void set_description(const std::string& d);

private:
    std::string name;
    std::string description;
    float weight;
    int calories;
};

//defines the NPC class
class NPC {
public:
    NPC(std::string n = "", std::string d = "", int m_n = 0, std::vector<std::string> m = {});

    //Getters
    std::string get_name() const;
    std::string get_description() const;
    int get_message_number() const;
    std::vector<std::string> get_messages() const;

    //Setters
    void set_name(const std::string& n);
    void set_description(const std::string& d);
    void set_message_number(int m_n);
    void set_messages(const std::vector<std::string>& m);

private:
    std::string name;
    std::string description;
    int message_number;
    std::vector<std::string> messages;
};


//defines the Location class
class Location {
public:
    std::vector<Location> neighbors;
    // Constructor
    Location(std::string n = "", std::string d = "", bool v = false, 
             std::vector<NPC> N = {}, std::vector<Item> I = {}, int r_n = 0);

    // Getters
    std::string get_name() const;
    std::string get_description() const;
    bool is_visited() const;
    std::vector<NPC>& get_room_npcs();
    std::vector<Item>& get_room_items();
    int get_room_num() const;

    // Setters
    void set_name(const std::string& n);
    void set_room_num(int n);
    void set_description(const std::string& d);
    void set_visited(bool v);
    void set_room_npcs(const std::vector<NPC>& N);
    void set_room_items(const std::vector<Item>& I);
    void remove_room_item(int i);

    // Prints the room's information
    void print_room() const;

private:
    std::string name;              // Name of the location
    std::string description;       // Description of the location
    bool visited;                  // Whether the location has been visited
    std::vector<NPC> room_npcs;    // NPCs present in the room
    std::vector<Item> room_items;  // Items present in the room
    int room_num;                  // Room number (identifier)
    //std::vector<Location> neighbors; // List of neighboring locations
};

//defines the Game class
class Game {
public:
    std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
    Game();
    
    static void show_help(std::vector<std::string> tokens);
    void pick_up(std::vector<std::string> tokens);
    void room(std::vector<std::string> tokens);
    void items(std::vector<std::string> tokens);
    void talk(std::vector<std::string> tokens);
    void meet(std::vector<std::string> tokens);
    void travel(std::vector<std::string> tokens);
    void quit(std::vector<std::string> tokens);

    void setup_commands();
    
    void create_world();
    Location random_location();

    //Getters
    float get_player_weight() const;
    std::vector<Item> get_player_items() const;
    Location* get_current_location();
    int get_calories_left() const;
    bool get_game_status() const;
    std::vector<Location>* get_all_locations();
    Location* get_new_location(int i);

    //Setters
    void set_player_weight(float w);
    void set_player_items(const std::vector<Item>& i);
    void set_current_location(Location& l);
    void set_calories_left(int l);
    void set_game_status(bool b);

private:
    //std::map<std::string, std::vector<std::string>> commands;
    float player_weight;
    std::vector<Location> all_locations;
    std::vector<Item> player_items;
    Location current_location;
    int calories_left;
    bool game_status;

};






#endif
