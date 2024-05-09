//
// Created by ISABE on 1/23/2024.
//

#include "Showroom.h"
#include <string>
#include <iostream>


//Constructor
Showroom::Showroom(std::string name, unsigned int capacity) {
    sr_name = name;
    sr_cap = capacity;
}

//Accessor
std::vector<Vehicle> Showroom::GetVehicleList() {
    return sr_vehicles;
}
//Behaviors

void Showroom::AddVehicle(Vehicle v) {
    if (sr_vehicles.size() == sr_cap) {
        std::cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << std::endl;
    } else {
        sr_vehicles.push_back(v);

    }
}

void Showroom::ShowInventory() {
  if (sr_vehicles.size() != 0) {
    std::cout << "Vehicles in" << sr_name << std::endl;
    for (int i = 0; i < sr_vehicles.size(); i++) {
        sr_vehicles[i].Display();
    }
  } else{
      std::cout << "Unnamed Showroom is empty!" << std::endl;

  }
}

float Showroom::GetInventoryValue() {
    float inventory_value = 0.0;
    for (int i = 0; i < sr_vehicles.size(); i++) {
        inventory_value += sr_vehicles[i].GetPrice();
    }
    
  return inventory_value;

}

std::string Showroom::GetShowcaseName(){
  return sr_name;
}


