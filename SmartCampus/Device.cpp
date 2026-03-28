#include "Device.h"

#include<string>
#include<iostream>
using namespace std;

//Constructor for parameters that devices include
    Device::Device(unsigned int id, string name, string manufacturer)
        : unique_ID(id), device_name(name), manufacturer(manufacturer), status(false), connected(true) {}


    //Activation check
    void Device::Activate()
    {
        status = true;
        cout << device_name << " is activated..." << endl;

    }

    //Deactivation Check
    void Device::Deactivate()
    {
        status = false;
        cout << device_name << " is deactivated..." << endl;
    }


    bool Device::IsActive() const
    {
        return status;
    }

    //gets the IDs for each device stored in the constructor
    unsigned int Device::GetID() const
    {
        return unique_ID;
    }

    //gets the Name for each device stored in the constructor
    string Device::GetName() const
    {
        return device_name;
    }

    //gets the manufacturer for each device stored in the constructor
    string Device::GetManufacturer() const
    {
        return manufacturer;
    }

    //Check Connection of devices
    bool Device::CheckConnection() const{
        return connected;
    }

    void Device::SetConnection(bool state)
    {
        connected = state;
    }

    //Check each Device's information using polymorphism
    void Device::ViewInfo() const
    {
        cout << "ID: " << unique_ID << "\n";
        cout << "Name: " << device_name << "\n";
        cout << "Manufacturer: " << manufacturer << "\n";
        cout << "Status: " << (status ? "Active" : "Inactive") << "\n";
        cout << "Connected: " << (connected ? "true" : "false") << "\n";
    }
