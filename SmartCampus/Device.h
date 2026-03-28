#ifndef DEVICE_H
#define DEVICE_H

#include<string>
#include<iostream>
#include<memory>
using namespace std;


class Device
{
protected:
    unsigned int unique_ID;
    string device_name;
    string manufacturer;
    bool status;
    bool connected;

public:

    //Constructor for parameters that devices include
    Device(unsigned int id, string name, string manufacturer);

    //Constructor for polymorphic deletion
    virtual ~Device() = default;

      unsigned int GetID() const;
      string GetName() const;
      string GetManufacturer() const;

    void Activate();
    void Deactivate();
    bool IsActive() const;
  

    //Handling connection
    bool CheckConnection() const;
    void SetConnection(bool state);

    //DESIGN PATTERN: Strategy pattern which is using polymorphism
    //This class(device) acts as the Strategy interface and it defines the default operations
    //such as Interaction_Event, ViewInfo and EditAttributes to virtual methods.
    //Then each derived device type acts as a Concrete Strategy that providdes its own behavior for those three operations.
    //This benefits the system to treat all devices through this class and not needing to change those operations every time.
    // 
    //Method for Interaction for each device
    virtual void Interaction_Event() =0;

    //Method for Viewing the information of each device
    virtual void ViewInfo() const = 0;
    
    //Method for Editing the attributes of each device
    virtual void EditAttributes() = 0;




    //Method for duplicating room and the devices within
    virtual unique_ptr<Device> Clone(unsigned int newID, string nName) const = 0;
};



#endif