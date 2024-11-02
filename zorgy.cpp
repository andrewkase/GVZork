#include <iostream>
#include <vector>

//Create the Tree class
class Item{
             
    public:
        std::string name;
        std::string description;
        int weight; 
        int calories;

    
        Item(std::string n, int c, int w, std::string d){
            name = n;
            calories = c;
            weight = w;
            description = d;
            //std::cout << name << " (" << calories << " calories) - " << weight << " lb - " << description << "\n\n";

        }

    private:
    
};

class NPC{
             
    public:
        std::string name;
        std::string description;
        int message_number; 
        std::vector<std::string> messages;

    
        NPC(std::string n, std::string d, int m_n, std::vector<std::string> m){
            name = n;
            description = d;
            message_number = m_n;
            messages = m;
            //std::cout << "I am a " << name << " (" << description << ") - Message Number " << message_number << " has to tell you: ";

            //int tmp = 0;
            //while (tmp < messages.size()){
                //std::cout << " " << messages[tmp]; tmp++;}

            //std::cout  << " \n\n";

        }

    private:
    
};


class Location{
             
    public:
        std::string name;
        std::string description;
        bool visited; 
        std::vector<NPC> room_npcs;
        std::vector<Item> room_items;

        Location(std::string n, std::string d, bool v, std::vector<NPC> N, std::vector<Item> I){
            name = n;
            description = d;
            visited = v; 
            room_npcs = N;
            room_items = I;
            
            std::cout <<  name << " - " << description << "\n\n";

            std::cout << "You see the following NPCS:\n\t";

            int tmp = 0;
            while (tmp < room_npcs.size()){
                std::cout << "- " << room_npcs[tmp].name << "\n\t"; tmp++;}
            std::cout << "\n";

            std::cout << "You see the following items:\n\t";
            tmp = 0;
            while (tmp < room_items.size()){
                std::cout << "- " << room_items[tmp].name << "\n\t"; tmp++;}

        }
        void print_room(){
            

        }

    private:
    
};


class Game{
    
    public:
        int player_weight = 0;
        std::vector<Location> all_locations;
        std::vector<Item> player_items;
        Location current_location;
        int calories_left = 500;
        bool game = true;

    private:
    
};


int main(){
    Item sword("Sword", 0, 5, "It cuts things up good");
    Item stick("Stick", 0, 5, "It hits real good");
    NPC gaurdian("Gaurdian", "I will try my hardest to stop you", 1, {"Get out of here!", "I don't want to hurt you."});
    NPC slayer("Slayer", "I kill", 1, {"You die!", "I want to hurt you."});
    Location bedroom("The Bedroom", "Many die here.", true, {gaurdian, slayer}, {sword, stick});
    return 0;
}