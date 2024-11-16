#ifndef __H__CLASSES__
#define __H__CLASSES__

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
    Input();

    std::vector<std::string> split(int i);
private:

};



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


class Location {
public:
    Location(std::string n = "", std::string d = "", bool v = false, std::vector<NPC> N = {}, std::vector<Item> I = {});

    //Getters
    std::string get_name() const;
    std::string get_description() const;
    bool is_visited() const;
    std::vector<NPC> get_room_npcs() const;
    std::vector<Item> get_room_items() const;

    //Setters
    void set_name(const std::string& n);
    void set_description(const std::string& d);
    void set_visited(bool v);
    void set_room_npcs(const std::vector<NPC>& N);
    void set_room_items(const std::vector<Item>& I);
    void remove_room_item(int i);
    void print_room() const;

private:
    std::string name;
    std::string description;
    bool visited;
    std::vector<NPC> room_npcs;
    std::vector<Item> room_items;
};






#endif







#endif
