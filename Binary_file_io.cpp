#include <iostream>
#include <fstream>
#include <vector>

#include "extrafile.h"
using namespace std;

//structs
struct Armament {
  string name;
  int power_rating;
  float power_consumption;
};

struct Ship {
    string name;
    string ship_class;
    int length;
    int shield_capacity;
    float max_warp;
    vector<Armament> armaments;

    int getTotalPowerRating(){
      int total = 0;
      for(auto i : armaments){
        total += i.power_rating;
      }

      return total;
    }

    int GetHighestPower(){
      int highest = 0;
      for(auto i : armaments){
        if (i.power_rating > highest)
          highest = i.power_rating;
      }

      return highest;
    }



};

//FUNCTIONS

//read functions
void read_data(ifstream& file, Ship& Ship){

  int nameLength;
  file.read((char*) &nameLength, sizeof(nameLength));
  //cout << "nameLength: " << nameLength << endl;

  char name[nameLength];
  file.read((char*) &name, sizeof(name));
  //cout << name << endl;
  Ship.name = string(name);

  int classLength;
  file.read((char*) &classLength, sizeof(classLength));
  //cout << "classLength " << classLength << endl;


  char ship_class[classLength];
  file.read(ship_class, classLength);
  Ship.ship_class = ship_class;
  //cout << "ship_class: " << ship_class << endl;


  //other data
  short s_length = 0;
  file.read((char*) &s_length, sizeof(s_length));
  Ship.length = s_length;
  //cout << "Ship.length: " << Ship.length << endl;
  file.read((char*) &Ship.shield_capacity, sizeof(int));
  //cout << "Ship.shield_capacity: " << Ship.shield_capacity << endl;
  file.read((char*) &Ship.max_warp, sizeof(float));
  //cout << "Ship.max_warp: " << Ship.max_warp << endl;


  //read armaments

  int weapon_num;
  file.read((char*) &weapon_num, sizeof(int));
  //cout << "weapon_num: " << weapon_num << endl;

  for (int i = 0; i < weapon_num; i++){
    Armament weapon;
    int weapon_nameLength;
    file.read((char*) &weapon_nameLength, sizeof(weapon_nameLength));
    //cout << "weapon_nameLength :" << weapon_nameLength << endl;

    char weapon_name[weapon_nameLength];
    file.read((char*) &weapon_name, sizeof(weapon_name));
    weapon.name = weapon_name;

    //cout << "weapon_name: " << weapon_name << endl;

    // char* weapon_name_buffer = new char[weapon_nameLength];

    file.read((char*) &weapon.power_rating, sizeof(int));
    //cout << "weapon.power_rating: " << weapon.power_rating << endl;
    file.read((char*) &weapon.power_consumption, sizeof(float));
    //cout << "weapon.power_consumption: " << weapon.power_rating << endl;

    Ship.armaments.push_back(weapon);
  }

}

void printingships(vector<Ship>& ships){
  //cout << "ships.size(): " << ships.size() << endl;
  for (int i = 0; i < ships.size() ; i++){
    cout << "Name: " << ships[i].name << endl;
    cout << "Class: " << ships[i].ship_class << endl;
    cout << "Length: " << ships[i].length << endl;
    cout << "Shield capacity: " << ships[i].shield_capacity << endl;
    cout << "Maximum Warp: " << ships[i].max_warp << endl;
    cout << "Armaments: " << endl;

    for(auto j : ships[i].armaments){
      cout << j.name << ", " << j.power_rating << ", " 
      << j.power_consumption << endl;
    }

      if(ships[i].armaments.size() == 0){
        cout << "Unarmed" << endl;
        continue;
      }
      else
        cout << "Total firepower: " << ships[i].getTotalPowerRating() << endl << endl;

  }
}







//option 1 function

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

  //file variables
  ifstream file_1;
  ifstream file_2;
  vector<Ship> ships;

  string friendlyships = "friendlyships.shp";
  string enemyships = "enemyships.shp";  

   // Load files here
   if (option == 1 || option == 3){
    file_1.open(friendlyships, ios::binary);
    int num_ships;
    file_1.read((char*) &num_ships, sizeof(num_ships));

    for (int i = 0; i < num_ships; ++i) {
      Ship ship;
      read_data(file_1, ship);
      ships.push_back(ship);
    }


   }
  if (option == 2 || option == 3){
    file_2.open(enemyships, ios::binary);
    int num_ships;
    file_2.read((char*) &num_ships, sizeof(num_ships));

    for (int i = 0; i < num_ships; ++i) {
      Ship ship;
      read_data(file_2, ship);
      ships.push_back(ship);
    }
  
   }


	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
		
  //EXECUTE OPTIONS
///////////////////////////////////////////////////
   //option 1
  if (option == 1){
    printingships(ships);
  }

  if (option == 2){
    int index = 0;
    int max_power = 0;

    for(int i = 0; i < ships.size(); i++){
      if(ships[i].GetHighestPower() > max_power){index = i; max_power = ships[i].GetHighestPower();}
      //cout << "Evaluating Ship: " << ships[i].name << endl;
      //cout << "if(" << ships[i].GetHighestPower() << ">" << max_power << " --> " << index << endl;
    }

    cout << "Name: " << ships[index].name << endl;
    cout << "Class: " << ships[index].ship_class << endl;
    cout << "Length: " << ships[index].length << endl;
    cout << "Shield capacity: " << ships[index].shield_capacity << endl;
    cout << "Maximum Warp: " << ships[index].max_warp << endl;
    cout << "Armaments: " << endl;
    for(auto i : ships[index].armaments){
      cout << i.name << ", " << i.power_rating << ", " << i.power_consumption << endl;
    }

    if(ships[index].armaments.size() == 0){
      cout << "Unarmed" << endl;
    }
    else
      cout << "Total firepower: " << ships[index].getTotalPowerRating() << endl << endl;

  }

  if (option == 3){
    int index = 0;
    int max_str = 0;

    for(int i = 0; i < ships.size(); i++){
      if(ships[i].getTotalPowerRating() > max_str){index = i; max_str = ships[i].getTotalPowerRating();}
      //cout << "Evaluating Ship: " << ships[i].name << endl;
      //cout << "if(" << ships[i].GetHighestPower() << ">" << max_power << " --> " << index << endl;
    }

    cout << "Name: " << ships[index].name << endl;
    cout << "Class: " << ships[index].ship_class << endl;
    cout << "Length: " << ships[index].length << endl;
    cout << "Shield capacity: " << ships[index].shield_capacity << endl;
    cout << "Maximum Warp: " << ships[index].max_warp << endl;
    cout << "Armaments: " << endl;
    for(auto i : ships[index].armaments){
      cout << i.name << ", " << i.power_rating << ", " << i.power_consumption << endl;
    }

    if(ships[index].armaments.size() == 0){
      cout << "Unarmed" << endl;
    }
    else
      cout << "Total firepower: " << ships[index].getTotalPowerRating() << endl << endl;

  }

  if (option == 4){
    int index = 0;
    int min_str = ships[0].getTotalPowerRating();

    for(int i = 0; i < ships.size(); i++){
      if(ships[i].armaments.size() == 0 ) continue;
      if(ships[i].getTotalPowerRating() < min_str){index = i; min_str = ships[i].getTotalPowerRating();}
      //cout << "Evaluating Ship: " << ships[i].name << endl;
      //cout << "if(" << ships[i].getTotalPowerRating() << "<" << min_str << " --> " << index << endl;
    }

    cout << "Name: " << ships[index].name << endl;
    cout << "Class: " << ships[index].ship_class << endl;
    cout << "Length: " << ships[index].length << endl;
    cout << "Shield capacity: " << ships[index].shield_capacity << endl;
    cout << "Maximum Warp: " << ships[index].max_warp << endl;
    cout << "Armaments: " << endl;
    for(auto i : ships[index].armaments){
      cout << i.name << ", " << i.power_rating << ", " << i.power_consumption << endl;
    }

    if(ships[index].armaments.size() == 0){
      cout << "Unarmed" << endl;
    }
    else
      cout << "Total firepower: " << ships[index].getTotalPowerRating() << endl << endl;

  }

  if(option == 5){
    for(auto i : ships){
      if(i.armaments.size() == 0){
        cout << "Name: " << i.name << endl;
        cout << "Class: " << i.ship_class << endl;
        cout << "Length: " << i.length << endl;
        cout << "Shield capacity: " << i.shield_capacity << endl;
        cout << "Maximum Warp: " << i.max_warp << endl;
        cout << "Armaments: " << endl;
        for(auto j : i.armaments){
          cout << j.name << ", " << j.power_rating << ", " << j.power_consumption << endl;
        }

        if(i.armaments.size() == 0){
          cout << "Unarmed" << endl;
        }
        else
          cout << "Total firepower: " << i.getTotalPowerRating() << endl << endl;
        }
    }
  }

   return 0;
}
