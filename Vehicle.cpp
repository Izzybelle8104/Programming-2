//
// Created by ISABE on 1/23/2024.
//

#include "Vehicle.h"
#include <string>
#include <iostream>


// Constructor
Vehicle::Vehicle(std::string make, std::string model, int year, float price, int mileage)
    : v_make(make), v_model(model), v_year(year), v_price(price), v_miles(mileage) {

}

//Prints out vehicle info on one line
void Vehicle::Display() {
    std::cout << v_year << " " << v_make << " " << v_model << " " << "$" << v_price << " " << v_miles << std::endl;

}
//Year make model
std::string Vehicle::GetYearMakeModel() const {

    std::string ymm = std::to_string(v_year) + " " + v_make + " " + v_model;
    return ymm;

}
//price
float Vehicle::GetPrice() const {
    return v_price;

}

