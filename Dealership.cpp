//
// Created by ISABE on 1/23/2024.
//
#include "Vehicle.h"
#include "Dealership.h"
#include <string>
#include <iostream>

//vector<Showroom> d_showroom;
//std::string d_name;
//unsigned int d_capacity;


//constructor
Dealership::Dealership(std::string name, unsigned int capacity){
    d_name = name;
    d_capacity = capacity;

}

//Behaviors
void Dealership::AddShowroom(Showroom s) {
    if (d_showroom.size() == d_capacity) {
        std::cout << "Dealership is full, can't add another showroom!" << std::endl;
    }
    else {
        d_showroom.push_back(s);

    }
}
float Dealership::GetAveragePrice(){ 
    float s_total = 0;   
    float s_amount = 0;
    for (int i = 0; i < d_showroom.size(); i++) {
      s_total += d_showroom[i].GetInventoryValue();
      s_amount += d_showroom[i].GetVehicleList().size();
    }
    float s_average = s_total / s_amount;

  return s_average;

}

void Dealership::ShowInventory(){
    float ss_total;
    float ss_amount;
    float ss_average;
      if (d_showroom.size() != 0){
        for (int i = 0; i < d_showroom.size(); i++) {
          std::cout << "Vehicles in " << d_showroom[i].GetShowcaseName() << std::endl;
          
          std::vector<Vehicle> vehiclesInShowroom = d_showroom[i].GetVehicleList();
          for(int j = 0; j < d_showroom[i].GetVehicleList().size(); j++){
            d_showroom[i].GetVehicleList()[j].Display();
          }

          std::cout << std::endl;
          // ss_total = d_showroom[i].GetInventoryValue();
          // ss_amount = d_showroom[i].GetVehicleList().size();
          // ss_average = ss_total / ss_amount;
    }

      std::cout << "Average car price: $" << Dealership::GetAveragePrice();

      }
      else {
        std::cout << d_name << " is empty!" << std::endl;
        std::cout << "Average car price: $0.00";
      }

}
      


