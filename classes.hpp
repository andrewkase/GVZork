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










#endif