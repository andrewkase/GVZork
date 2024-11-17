#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib> // for rand()
#include <ctime> // for time()
#include <functional>

#include "classes.hpp"

Input::Input() {}

std::vector<std::string> Input::split(int i) {
    std::string command_input_2;
    std::string first;
    std::vector<std::string> rest_of_input;
    int word_count = 0;
    if (i == 1){
        getline(std::cin, command_input);
    }
    
    for (int i = 0; i < command_input.length(); i++) { 

    if (command_input[i] != ' '){
        if (word_count == 0){
            first += command_input[i];
        }
        command_input_2 += command_input[i];
    }
    if (command_input[i] == ' ' || i == command_input.length()-1){
        if (word_count != 0){
            rest_of_input.push_back(command_input_2);
        }
        word_count += 1;
        command_input_2 = "";
    }
    }
    if (i == 1){
        return {first};
    }
    else if (i == 2){
        return rest_of_input;
    }
    return {};  // Return an empty vector if neither condition is met
}



Item::Item(std::string n, int c, float w, std::string d)
    : name(n), calories(c), weight(w), description(d) {}

// Getters
std::string Item::get_name() const {
    return name;
}

int Item::get_calories() const {
    return calories;
}

float Item::get_weight() const {
    return weight;
}

std::string Item::get_description() const {
    return description;
}

// Setters
void Item::set_name(const std::string& n) {
    try {
        if (n.empty()) {
            throw std::invalid_argument("Name cannot be blank!");
        }
        name = n;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Item::set_calories(int c) {
    try {
        if (c < 0 || c > 1000) {
            throw std::invalid_argument("Calories must be in the range 0-1000!");
        }
        calories = c;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Item::set_weight(float w) {
    try {
        if (w < 0 || w > 500) {
            throw std::invalid_argument("Weight must be in the range 0-500!");
        }
        weight = w;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Item::set_description(const std::string& d) {
    try {
        if (d.empty()) {
            throw std::invalid_argument("Description cannot be blank!");
        }
        description = d;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}





NPC::NPC(std::string n, std::string d, int m_n, std::vector<std::string> m)
    : name(n), description(d), message_number(m_n), messages(m) {}

// Getters
std::string NPC::get_name() const {
    return name;
}

std::string NPC::get_description() const {
    return description;
}

int NPC::get_message_number() const {
    return message_number;
}

std::vector<std::string> NPC::get_messages() const {
    return messages;
}

// Setters
void NPC::set_name(const std::string& n) {
    name = n;
}

void NPC::set_description(const std::string& d) {
    description = d;
}

void NPC::set_message_number(int m_n) {
    // Make sure to handle the bounds of the message list
    if (m_n >= 0 && m_n < messages.size()) {
        message_number = m_n;
    } else {
        // Optionally handle out-of-bounds errors or wrap around
        message_number = 0; // Wrap around to the first message if out of bounds
    }
}

void NPC::set_messages(const std::vector<std::string>& m) {
    messages = m;
}






Location::Location(std::string n, std::string d, bool v, 
                   std::vector<NPC> N, std::vector<Item> I, int r_n)
    : name(n), description(d), visited(v), room_npcs(N), room_items(I), room_num(r_n) {}

// Getter for the location's name
std::string Location::get_name() const {
    return name;
}

// Getter for the location's description
std::string Location::get_description() const {
    return description;
}

// Getter for whether the location has been visited
bool Location::is_visited() const {
    return visited;
}

// Getter for the room's NPCs
std::vector<NPC>& Location::get_room_npcs() {
    return room_npcs;
}

// Getter for the room's items
std::vector<Item>& Location::get_room_items() {
    return room_items;
}

// Getter for the room's number
int Location::get_room_num() const {
    return room_num;
}

// Setter for the location's name
void Location::set_name(const std::string& n) {
    name = n;
}

// Setter for the location's number
void Location::set_room_num(int n) {
    room_num = n;
}

// Setter for the location's description
void Location::set_description(const std::string& d) {
    description = d;
}

// Setter for whether the location has been visited
void Location::set_visited(bool v) {
    visited = v;
}

// Setter for the NPCs in the room
void Location::set_room_npcs(const std::vector<NPC>& N) {
    room_npcs = N;
}

// Setter for the items in the room
void Location::set_room_items(const std::vector<Item>& I) {
    room_items = I;
}

// Removes an item from the room's list of items at a specified index
void Location::remove_room_item(int i) {
    if (i >= 0 && i < room_items.size()) {
        room_items.erase(room_items.begin() + i);
    }
}

// Prints the details of the room (name, description, NPCs, items, neighbors)
void Location::print_room() const {
    std::cout << name << " - " << description << "\n\n";

    std::cout << "You see the following NPCS:\n\t";

    int tmp = 0;
    while (tmp < room_npcs.size()) {
        std::cout << "- " << room_npcs[tmp].get_name() << "\n\t";
        tmp++;
    }
    std::cout << "\n";

    std::cout << "You see the following items:\n\t";
    tmp = 0;
    while (tmp < room_items.size()) {
        std::cout << "- " << room_items[tmp].get_name() << "\n\t";
        tmp++;
    }
    std::cout << "\n";

    std::cout << "You can visit the following places from here:\n\t";
    tmp = 0;
    while (tmp < neighbors.size()) {
        std::cout << "- " << neighbors[tmp].get_name() << "\n\t";
        tmp++;
    }
    std::cout << "\n";
}




Game::Game() {
    create_world();
    player_weight = 0.0;
    current_location = random_location();
    calories_left = 500;
    game_status = true;
    setup_commands();
}
    
    
void Game::show_help(std::vector<std::string> tokens){
    std::cout << "These are the commands you may use\n\n";
    std::cout << "\"help\"\n";

    std::cout << "\"take\" or ";
    std::cout << "\"grab\"\n";

    std::cout << "\"talk\" or ";
    std::cout << "\"speak\" or ";
    std::cout << "\"meet\"\n";

    std::cout << "\"room\" or ";
    std::cout << "\"place\" or ";
    std::cout << "\"info\"\n";

    std::cout << "\"items\" or ";
    std::cout << "\"inventory\"\n";

    std::cout << "\"travel\" or ";
    std::cout << "\"go\" or ";
    std::cout << "\"walk\" or ";
    std::cout << "\"visit\"\n";

    std::cout << "\"feed\"\n";

    std::cout << "\"tp\" or ";
    std::cout << "\"teleport\"\n";

    std::cout << "\"quit\" or ";
    std::cout << "\"exit\"\n\n";
}

void Game::pick_up(std::vector<std::string> tokens) {
bool found = false;
    if (tokens.empty()) {
        std::cout << "What will you pick up?\n\n";
    } 
    else {
        for (auto word : tokens) {
            for (size_t i = 0; i < current_location.get_room_items().size(); ++i) {
                auto& item = current_location.get_room_items()[i];
                if (item.get_name() == word) {
                    if(item.get_weight() + get_player_weight() < 100){
                        found = true;
                        player_items.push_back(item);
                        std::cout << "You picked up " << item.get_name() << "!\n\n";
                        current_location.remove_room_item(i);
                        set_player_weight(get_player_weight() + item.get_weight());

                        // Update the corresponding location in all_locations
                        for (auto& loc : all_locations) {
                            if (loc.get_room_num() == current_location.get_room_num()) {
                                loc = current_location;
                                break;
                            }
                        }
                    }
                    else{
                        std::cout << "You cannot pick this up now, feed the Zorg first.\n";
                        std::cout << item.get_weight() + get_player_weight();
                    }
                    
                    break;
                }
            }
        }
    }
    if (found == false){
        std::cout << "There are no items that match that description here.\n\n";
    }
}

void Game::room(std::vector<std::string> tokens){
    current_location.print_room();

}

void Game::items(std::vector<std::string> tokens){
        std::cout << "All items: ";
        for (auto item : player_items){
                std::cout << item.get_name() << " ";

    }
        std::cout << "\nTotal weight: " << get_player_weight() << "\n\n";
}


void Game::talk(std::vector<std::string> tokens){
    if (tokens.empty()){
        std::cout << "Who will you talk to?\n\n";
    }
    else{
        for (auto word : tokens){
            int temp = 0;
            for (auto& npc : current_location.get_room_npcs()){
                if (npc.get_name() == word) {
                    NPC* temperary = &current_location.get_room_npcs()[temp];
                    std::cout << temperary->get_name() << " ";
                    std::cout << temperary->get_messages()[temperary->get_message_number()] << "\n\n";
                    temperary->set_message_number(temperary->get_message_number() + 1);
                }
                temp += 1;
            }
        }
    }
}

void Game::meet(std::vector<std::string> tokens){
    if (tokens.empty()){
        std::cout << "Who do you want to meet?\n\n";
    }
    else{
        for (auto word : tokens){
            int temp = 0;
            for (auto& npc : current_location.get_room_npcs()){
                if (npc.get_name() == word) {
                    NPC* temperary = &current_location.get_room_npcs()[temp];
                    std::cout << temperary->get_name() << ": ";
                    std::cout << temperary->get_description() << "\n\n";
                }
                temp += 1;
            }
        }
    }
}

void Game::travel(std::vector<std::string> tokens) {
    if (tokens.empty()) {
        std::cout << "Where will you go?\n\n";
    } 
    else {
        for (auto word : tokens) {
            for (auto& place : current_location.neighbors) {
                if (place.get_name() == word) {
                    std::cout << "You went to " << place.get_name() << "!\n\n";
                    // Update current_location with the actual location in all_locations
                    for (auto& loc : all_locations) {
                        if (loc.get_room_num() == place.get_room_num()) {
                            set_current_location(loc);
                            break;
                        }
                    }
                        return;
                }
            }
        }
            std::cout << "You cannot go there!\n\n";
    }
}

void Game::quit(std::vector<std::string> tokens){
    set_game_status(false);
    std::cout << "\n\nPlease play again!\n\n";

}

void Game::setup_commands(){
    commands["help"] = show_help;
    commands["take"] = [this](std::vector<std::string> tokens) { this->pick_up(tokens); };
    commands["grab"] = [this](std::vector<std::string> tokens) { this->pick_up(tokens); };
    commands["talk"] = [this](std::vector<std::string> tokens) { this->talk(tokens); };
    commands["speak"] = [this](std::vector<std::string> tokens) { this->talk(tokens); };
    commands["meet"] = [this](std::vector<std::string> tokens) { this->meet(tokens); };
    commands["room"] = [this](std::vector<std::string> tokens) { this->room(tokens); };
    commands["items"] = [this](std::vector<std::string> tokens) { this->items(tokens); };
    commands["travel"] = [this](std::vector<std::string> tokens) { this->travel(tokens); };
    commands["go"] = [this](std::vector<std::string> tokens) { this->travel(tokens); };
    commands["walk"] = [this](std::vector<std::string> tokens) { this->travel(tokens); };
    commands["visit"] = [this](std::vector<std::string> tokens) { this->travel(tokens); };
    commands["quit"] = [this](std::vector<std::string> tokens) { this->quit(tokens); };
    commands["exit"] = [this](std::vector<std::string> tokens) { this->quit(tokens); };
}

void Game::create_world() {
    //Created Items
    Item chinese("Chinese", 50, 5.3, "Muy delicioso! Oops wrong food.");
    Item sandwich("Sandwich", 40, 3.0, "It's unfortunately not a footlong.");
    Item bagel("Bagel", 20, 2.0, "They respect the shmear.");
    Item coffee("Coffee", 60, 15.0, "Contains mostly sugar.");
    Item burrito("Burrito", 40, 7.3, "Muy delicioso!");
    Item pasta("Pasta", 50, 7.0, "So noodly, my favorite.");
    Item burger("Burger", 70, 15.0, "Not very good, but it's food.");
    Item snacks("Snacks", 40, 5.0, "Some say empty calories, I say tasty.");
    Item breakfast("Breakfast", 50, 5.3, "Pancakes galore.");
    Item desert("Desert", 40, 3.0, "Oooh, ice cream, fits so nice in my pockets.");

    //Created NPCs
    NPC ira("Ira", "The guider of knowledge.", 0, {"You must feed the elf!", "Find food around campus!"});
    NPC lunch_lady("Lunch_Lady", "The giver of foods.", 0, {"You look hungry!", "I hope you have meal swipes left!"});
    NPC friend_from_highschool("Friend", "You do not want to talk to them.", 0, {"It's been a while!", "We should hang out sometime!"});
    NPC dean("Dean", "Spreads fear among the land", 0, {"What is your name?", "Try out our new majors next year!"});
    NPC fellow_students("Students", "You only talk to them if you are in class.", 0, {".....", "....hm...."});
    NPC zorg("Zorg", "I am very hungy.", 0, {"You must feed me as I am lazy!", "I will save the world ... once I'm full."});

    //Created Locations
    Location kirkhof("Kirkhof", "We have food.", true, {lunch_lady, fellow_students, friend_from_highschool}, {chinese, coffee, sandwich, burrito, pasta, burger}, 0);

    Location mackinac("Mackinac", "Your computer science hub.", true, {ira, fellow_students}, {coffee, snacks}, 1);

    Location blue("Blue", "We have food.", true, {lunch_lady, fellow_students}, {sandwich, burger, desert}, 2);

    Location kleiner("Kleiner", "Home of the Dish.", true, {lunch_lady, fellow_students}, {sandwich, breakfast, desert, pasta}, 3);

    Location holton_hooker("Holton", "Home of Einstein Bros. Bagels.", true, {lunch_lady}, {bagel, coffee, breakfast}, 4);

    Location marketplace("Marketplace", "Home of Bento.", true, {fellow_students}, {chinese, coffee}, 5);

    Location commons("Commons", "Home of Fresh Food co.", true, {lunch_lady}, {sandwich, breakfast, desert, bagel}, 6);

    Location library("Library", "Home of GV Brew.", true, {fellow_students}, {coffee, snacks}, 7);

    Location woods("Woods", "Home of the Ork.", true, {zorg}, {}, 8);
    

    kirkhof.neighbors.push_back(mackinac);
    kirkhof.neighbors.push_back(woods);

    mackinac.neighbors.push_back(kirkhof);
    mackinac.neighbors.push_back(blue);

    blue.neighbors.push_back(mackinac);
    blue.neighbors.push_back(kleiner);

    kleiner.neighbors.push_back(blue);
    kleiner.neighbors.push_back(holton_hooker);

    holton_hooker.neighbors.push_back(kleiner);
    holton_hooker.neighbors.push_back(marketplace);

    marketplace.neighbors.push_back(holton_hooker);
    marketplace.neighbors.push_back(commons);

    commons.neighbors.push_back(marketplace);
    commons.neighbors.push_back(library);

    library.neighbors.push_back(commons);
    library.neighbors.push_back(woods);

    woods.neighbors.push_back(library);
    woods.neighbors.push_back(kirkhof);

    all_locations.push_back(kirkhof);
    all_locations.push_back(mackinac);
    all_locations.push_back(blue);
    all_locations.push_back(kleiner);
    all_locations.push_back(holton_hooker);
    all_locations.push_back(marketplace);
    all_locations.push_back(commons);
    all_locations.push_back(library);
    all_locations.push_back(woods);
}

Location Game::random_location() {
    int random = rand() % all_locations.size();
    return all_locations[random];
}

// Getters
/*std::map<std::string, std::vector<std::string>> get_commands(){
    return commands;
}*/

float Game::get_player_weight() const {
    return player_weight;
}

std::vector<Item> Game::get_player_items() const {
    return player_items;
}

Location* Game::get_current_location(){
    return &current_location;
}

int Game::get_calories_left() const {
    return calories_left;
}

bool Game::get_game_status() const {
    return game_status;
}

std::vector<Location>* Game::get_all_locations(){
    return &all_locations;
}

Location* Game::get_new_location(int i){
    return &all_locations[i];
}

// Setters
/*void set_command(std::map<std::string, std::vector<std::string>>& c){
    commands = c;
}*/

void Game::set_player_weight(float w) {
    player_weight = w;
}

void Game::set_player_items(const std::vector<Item>& i) {
    player_items = i;
}

void Game::set_current_location(Location& l) {
    current_location = l;
}

void Game::set_calories_left(int l) {
    calories_left = l;
}

void Game::set_game_status(bool b) {
    game_status = b;
}






int main() {
    srand(time(0)); // Seed the random number generator
    Game gamer;
    std::vector<std::string> tokens;
    std::string command;
    Input user_response;

    std::cout << "You are the chosen one! You must feed the Zorg enough food for him to save the world!\n";
    std::cout << "This is all I can tell you as of now, as I have a dentist appointment soon. Good Luck.\n";
    std::cout << "For list of commands, type \"help\".\n\n";
    while (gamer.get_game_status() == true){
        command = user_response.split(1)[0];
        tokens = user_response.split(2);
        if (gamer.commands.find(command) != gamer.commands.end()) {
            gamer.commands[command](tokens);
        }
        else{
            std::cout << "Please enter a valid command!\n\n";
        }
    
    }
    
    return 0;
}

