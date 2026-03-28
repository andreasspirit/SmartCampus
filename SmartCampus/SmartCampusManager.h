#ifndef SMARTCAMPUSMANAGER_H
#define SMARTCAMPUSMANAGER_H


#include <vector>
#include <memory>
#include "Device.h"
#include<string>
using namespace std;



class Room {
public:
    string room_n;
    vector<Device*>room_dev;


};
class SmartCampusManager
{
private:
    vector<unique_ptr<Device>> devices;
    vector<unique_ptr<Room>> rooms;
    unsigned int GetNextID() const;

public:
    void Run();
    void LoadFile();

    void ViewAllDevices();
    void ActivateAllDevices();
    void DeactivateAllDevices();
    void InteractAllDevices();
    void AddDevice();
    void DeleteDevice();
    void EditDevice();
    void CheckConnection();
    void SearchDevice();

    void CreateRoom();
    void ViewRooms();
    void ManageRooms();
    void DuplicateRoom();
    
};



#endif
