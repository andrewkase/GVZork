#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime> // for time()

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
        name = n;
    }

    void set_calories(int c) {
        calories = c;
    }

    void set_weight(float w) {
        weight = w;
    }

    void set_description(const std::string& d) {
        description = d;
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
    Game() {
        create_world();
        player_weight = 0.0;
        current_location = random_location();
        calories_left = 500;
        game_status = true;
    }

    void create_world() {
        Item sword("Sword", 0, 5.3, "It cuts things up good");
        Item stick("Stick", 0, 1.0, "It hits real good");
        NPC guardian("Guardian", "I will try my hardest to stop you", 1, {"Get out of here!", "I don't want to hurt you."});
        NPC slayer("Slayer", "I kill", 1, {"You die!", "I want to hurt you."});
        Location bedroom("The Bedroom", "Many die here.", true, {guardian, slayer}, {sword, stick});
        all_locations.push_back(bedroom);
    }

    Location random_location() {
        int random = rand() % all_locations.size();
        return all_locations[random];
    }

    // Getters
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
    gamer.get_current_location().print_room();
    return 0;
}
