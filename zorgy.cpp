#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib> // for rand()
#include <ctime> // for time()
#include <functional>

class Input{
    public:
        std::string command_input;
        Input (){
        }

        std::vector<std::string> split(int i){
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
            return {};
    }

    private:

};

class Item {
public:
    Item(std::string n = "", int c = 0, float w = 0.0, std::string d = "")
        : name(n), calories(c), weight(w), description(d) {}

    // Getters
    std::string get_name() const {
        return name;
    }

    int get_calories() const {
        return calories;
    }

    float get_weight() const {
        return weight;
    }

    std::string get_description() const {
        return description;
    }

    // Setters
    void set_name(const std::string& n) {
        try {
            if (n == "") {
                throw std::invalid_argument("Name cannot be blank!");
            }
            name = n;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void set_calories(int c) {
        try {

            //need to figure out how to check for type still

            if (c < 0 || c > 1000) {
                throw std::invalid_argument("Calories must be in range 0-1000!");
            }
            calories = c;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void set_weight(float w) {
        try {
            if (w < 0 || w > 500) {
                throw std::invalid_argument("Weight must be in range 0-500!");
            }
            weight = w;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void set_description(const std::string& d) {
        try {
            if (d == "") {
                throw std::invalid_argument("Description cannot be blank!");
            }
            description = d;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
    std::string name;
    std::string description;
    float weight;
    int calories;
};

class NPC {
public:
    NPC(std::string n = "", std::string d = "", int m_n = 0, std::vector<std::string> m = {})
        : name(n), description(d), message_number(m_n), messages(m) {}

    // Getters
    std::string get_name() const {
        return name;
    }

    std::string get_description() const {
        return description;
    }

    int get_message_number() const {
        return message_number;
    }

    std::vector<std::string> get_messages() const {
        return messages;
    }

    // Setters
    void set_name(const std::string& n) {
        name = n;
    }

    void set_description(const std::string& d) {
        description = d;
    }

    void set_message_number(int m_n) {
        message_number = m_n;
    }

    void set_messages(const std::vector<std::string>& m) {
        messages = m;
    }

private:
    std::string name;
    std::string description;
    int message_number;
    std::vector<std::string> messages;
};

class Location {
public:
    Location(std::string n = "", std::string d = "", bool v = false, std::vector<NPC> N = {}, std::vector<Item> I = {})
        : name(n), description(d), visited(v), room_npcs(N), room_items(I) {}

    // Getters
    std::string get_name() const {
        return name;
    }

    std::string get_description() const {
        return description;
    }

    bool is_visited() const {
        return visited;
    }

    std::vector<NPC> get_room_npcs() const {
        return room_npcs;
    }

    std::vector<Item> get_room_items() const {
        return room_items;
    }

    // Setters
    void set_name(const std::string& n) {
        name = n;
    }

    void set_description(const std::string& d) {
        description = d;
    }

    void set_visited(bool v) {
        visited = v;
    }

    void set_room_npcs(const std::vector<NPC>& N) {
        room_npcs = N;
    }

    void set_room_items(const std::vector<Item>& I) {
        room_items = I;
    }

    void remove_room_item(int i){
        room_items.erase(room_items.begin() + i);
    }

    void print_room() const {
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
    }

private:
    std::string name;
    std::string description;
    bool visited;
    std::vector<NPC> room_npcs;
    std::vector<Item> room_items;
};

class Game {
public:
    
    //std::map<std::string, std::function<void(*)(std::vector<std::string>)>> commands;
    std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
    Game() {
        create_world();
        player_weight = 0.0;
        current_location = random_location();
        calories_left = 500;
        game_status = true;
        setup_commands();
    }
    
    static void show_help(std::vector<std::string> tokens){
        std::cout << "You needed help?\n\n";
    }

    void pick_up(std::vector<std::string> tokens){
        if (tokens.empty()){
            std::cout << "What will you pick up?\n\n";
        }
        else{
            //std::cout << "You picked up: ";
            for (auto word : tokens){
                int temp = 0;
                for (auto item : current_location.get_room_items()){
                    temp += 1;
                    if (item.get_name() == word) {

                        player_items.push_back(item);
                        std::cout << "You picked up " << item.get_name() << "!\n\n";
                        current_location.remove_room_item(temp-1);
                    } 
                }
            }
        }
    }

    void room(std::vector<std::string> tokens){
        current_location.print_room();

    }

    void items(std::vector<std::string> tokens){
            std::cout << "All items: ";
            for (auto item : player_items){
                    std::cout << item.get_name() << " ";

        }
            std::cout << "\n\n";
    }
    
    

    /*static void talk(std::vector<std::string> tokens){
        if (tokens.empty()){
            std::cout << "Who will you talk to?\n\n";
        }
        else{
            std::cout << "You talked to someone!\n\n";
        }   
    }*/

    void talk(std::vector<std::string> tokens){
        if (tokens.empty()){
            std::cout << "Who will you talk to?\n\n";
        }
        else{
            for (auto word : tokens){
                int temp = 0;
                for (auto npc : current_location.get_room_npcs()){
                    temp += 1;
                    if (npc.get_name() == word) {
                        std::cout << npc.get_messages()[npc.get_message_number()] << "!\n\n";
                        npc.set_message_number(npc.get_message_number() + 1);
                    }
                }
            }
        }
    }

    void setup_commands(){
        commands["help"] = show_help;
        commands["take"] = [this](std::vector<std::string> tokens) { this->pick_up(tokens); };
        commands["grab"] = [this](std::vector<std::string> tokens) { this->pick_up(tokens); };
        commands["talk"] = [this](std::vector<std::string> tokens) { this->talk(tokens); };
        commands["speak"] = [this](std::vector<std::string> tokens) { this->talk(tokens); };
        commands["room"] = [this](std::vector<std::string> tokens) { this->room(tokens); };
        commands["items"] = [this](std::vector<std::string> tokens) { this->items(tokens); };
    }

    void create_world() {
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
        NPC ira("Ira_Woodring", "The guider of knowledge.", 0, {"You must feed the elf!", "Find food around campus!"});
        NPC lunch_lady("Lunch_Lady", "The giver of foods.", 0, {"You look hungry!", "I hope you have meal swipes left!"});
        NPC friend_from_highschool("Friend_From_Highschool", "You do not want to talk to them.", 0, {"It's been a while!", "We should hang out sometime!"});
        NPC dean("The_Dean", "Spreads fear among the land", 0, {"What is your name?", "Try out our new majors next year!"});
        NPC fellow_students("Fellow_Students", "You only talk to them if you are in class.", 0, {".....", "....hm...."});

        //Created Locations
        Location kirkhof("Kirkhof Center", "We have food.", true, {lunch_lady, fellow_students, friend_from_highschool}, {chinese, coffee, sandwich, burrito, pasta, burger});
        all_locations.push_back(kirkhof);

        Location mackinac("Mackinac Hall", "Your computer science hub.", true, {ira, fellow_students}, {coffee, snacks});
        all_locations.push_back(mackinac);

        Location blue_connection("Blue Connection", "We have food.", true, {lunch_lady, fellow_students}, {sandwich, burger, desert});
        all_locations.push_back(blue_connection);

        Location kleiner("Kleiner", "Home of the Dish.", true, {lunch_lady, fellow_students}, {sandwich, breakfast, desert, pasta});
        all_locations.push_back(kleiner);

        Location holton_hooker("Holton-Hooker", "Home of Einstein Bros. Bagels.", true, {lunch_lady}, {bagel, coffee, breakfast});
        all_locations.push_back(holton_hooker);

        Location marketplace("Marketplace", "Home of Bento.", true, {fellow_students}, {chinese, coffee});
        all_locations.push_back(marketplace);

        Location commons("Commons", "Home of Fresh Food co.", true, {lunch_lady}, {sandwich, breakfast, desert, bagel});
        all_locations.push_back(commons);

        Location library("Library", "Home of GV Brew.", true, {fellow_students}, {coffee, snacks});
        all_locations.push_back(library);
    }

    Location random_location() {
        int random = rand() % all_locations.size();
        return all_locations[random];
    }

    // Getters
    /*std::map<std::string, std::vector<std::string>> get_commands(){
        return commands;
    }*/

    float get_player_weight() const {
        return player_weight;
    }

    std::vector<Item> get_player_items() const {
        return player_items;
    }
    
    Location get_current_location() const {
        return current_location;
    }

    int get_calories_left() const {
        return calories_left;
    }

    bool get_game_status() const {
        return game_status;
    }

    // Setters
    /*void set_command(std::map<std::string, std::vector<std::string>>& c){
        commands = c;
    }*/

    void set_player_weight(float w) {
        player_weight = w;
    }

    void set_player_items(const std::vector<Item>& i) {
        player_items = i;
    }
    
    void set_current_location(const Location& l) {
        current_location = l;
    }

    void set_calories_left(int l) {
        calories_left = l;
    }

    void set_game_status(bool b) {
        game_status = b;
    }

private:
    //std::map<std::string, std::vector<std::string>> commands;
    float player_weight;
    std::vector<Location> all_locations;
    std::vector<Item> player_items;
    Location current_location;
    int calories_left;
    bool game_status;
};



int main() {
    srand(time(0)); // Seed the random number generator
    Game gamer;
    std::vector<std::string> tokens;
    std::string command;
    Input user_response;

    
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
