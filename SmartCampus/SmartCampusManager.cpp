#include "SmartCampusManager.h"
#include "SecurityCamera.h"
#include "AirConditioning.h"
#include "Projector.h"
#include "RoomLighting.h"
#include "DoorLock.h"
#include "Device.h"

#include <iostream>
#include <fstream>
#include<sstream>
#include <limits>
using namespace std;


//To run the program unique pointers were implemented to manage memory and add devices into a vector using push_back
void SmartCampusManager::Run()
{

    LoadFile(); //Load the devices of the file smartcampus.txt

    if (devices.empty()) {
        devices.push_back(make_unique<SecurityCamera>(1,"Security-Camera","LOGITECH","FULL HD","180 WAT"));
        devices.push_back(make_unique<AirConditioning>(2, "Air-Conditioning", "CARRIER",20));
        devices.push_back(make_unique<Projector>(3,"Projector","SONY","HDMI", 25));
        devices.push_back(make_unique<RoomLighting>(4, "Room-Lighting", "PHILIPS",50));
        devices.push_back(make_unique<DoorLock>(5,"DoorLock", "SIMPSON",true,"Andrew"));

    }


    //User enters the choice of each action
    int choice=-1;

    do
    {
        cout << "\n========== Smart Campus ==========\n";
        cout << "1) View all devices\n";
        cout << "2) Activate all devices\n";
        cout << "3) Deactivate all devices\n";
        cout << "4) Interact all devices\n";
        cout << "5) Add device\n";
        cout << "6) Delete device\n";
        cout << "7) Edit device\n";
        cout << "8) Check connections\n";
        cout << "9) Search device\n";
        cout << "10) Create room\n";
        cout << "11) View rooms\n";
        cout << "12) Manage room\n";
        cout << "13) Duplicate room\n";
        cout << "0) Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: ViewAllDevices(); break;
        case 2: ActivateAllDevices(); break;
        case 3: DeactivateAllDevices(); break;
        case 4: InteractAllDevices(); break;
        case 5: AddDevice(); break;
        case 6: DeleteDevice(); break;
        case 7: EditDevice(); break;
        case 8: CheckConnection(); break;
        case 9: SearchDevice(); break;
        case 10: CreateRoom(); break;
        case 11: ViewRooms(); break;
        case 12: ManageRooms(); break;
        case 13: DuplicateRoom(); break;
        case 0: cout << "Exiting.\n"; return; break;
        default: cout << "[ERROR] Invalid choice.\n"; break;
        }

    } while (choice != 0);
}

//DESIGN PATTERN:
//To load the file the factory method design pattern is used where the function acts as a factory 
//and then the system takes information from the file
void SmartCampusManager::LoadFile()
{
    ifstream fin("smartcampus.txt");
    if (!fin.is_open())
    {
        cout << "ERROR: smartcampus.txt not found" << endl;
        return;
    }

    string line;
    int loadedCount = 0;

    while (getline(fin, line))
    {
        if (line.empty()) continue;

        // File txt expected:
        // DEVICE,ID,Type,Name,Manufacturer,Extra1,Extra2
        stringstream ss(line);
        string tag, id_s, type, name, brand, extra_info, extra2;

        getline(ss, tag, ',');
        getline(ss, id_s, ',');
        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, brand, ',');
        getline(ss, extra_info, ',');
        getline(ss, extra2, ',');

        if (tag != "DEVICE") continue;

        int dev_ID = 0;
        try { dev_ID = stoi(id_s); }
        catch (...) { cout << "Invalid ID skipped: " << id_s << endl; continue; }

        if (name.empty()) name = type + "_" + to_string(dev_ID);

        // duplicate ID check
        bool duplicate = false;
        for (auto& d : devices)
        {
            if ((int)d->GetID() == dev_ID) { duplicate = true; break; }
        }
        if (duplicate) continue;

        string place = "Unassigned";
        Room* room_place = nullptr;

        //Search for room
        for (auto& r : rooms)
        {
            if (r->room_n == place) { room_place = r.get(); break; }
        }
        if (!room_place)
        {
            rooms.push_back(unique_ptr<Room>(new Room()));
            rooms.back()->room_n = place;
            room_place = rooms.back().get();
        }

        if (type == "SecurityCamera")
        {
            devices.push_back(make_unique<SecurityCamera>((unsigned int)dev_ID, name, brand, extra_info, extra2));
        }
        else if (type == "AirConditioning")
        {
            int temp = 0;
            try { temp = stoi(extra_info); }
            catch (...) { continue; }

            devices.push_back(make_unique<AirConditioning>((unsigned int)dev_ID, name, brand, (unsigned int)temp));
        }
        else if (type == "Projector")
        {
            int bright = 0;
            try { bright = stoi(extra2); }
            catch (...) { continue; }

            devices.push_back(make_unique<Projector>((unsigned int)dev_ID, name, brand, extra_info, (unsigned int)bright));
        }
        else if (type == "RoomLighting")
        {
            int light = 0;
            try { light = stoi(extra_info); }
            catch (...) { continue; }

            devices.push_back(make_unique<RoomLighting>((unsigned int)dev_ID, name, brand, light));
        }
        else if (type == "DoorLock")
        {
            bool locked = (extra_info == "1" || extra_info == "true" || extra_info == "TRUE");
            devices.push_back(make_unique<DoorLock>((unsigned int)dev_ID, name, brand, locked, extra2));
        }
        else
        {
            continue;
        }

        room_place->room_dev.push_back(devices.back().get());
        loadedCount++;
    }

    fin.close();
    cout << "File loaded. Type 1 to view the devices" << endl; //Message on top of the program
}



    

void SmartCampusManager::ViewAllDevices()
{


    cout << "\n--- Devices ---\n";
    cout << endl;
    //if not found devices
    if (devices.empty())
    {
        cout << "No devices found.\n";
        return;
    }  

    //get info of devices from file and uses the Devices ViewInfo 
    for (const auto& d : devices)
    {

        d->ViewInfo();
    }
}


void SmartCampusManager::ActivateAllDevices()
{
    if (devices.empty())
    {
        cout << "No devices to activate.\n";
        return;
    }

    for (auto& d : devices)
    {
        d->Activate();
    }

    cout << "\nAll devices are activated!\n";
}

void SmartCampusManager::DeactivateAllDevices()
{
    if (devices.empty())
    {
        cout << "No devices to deactivate.\n";
        return;
    }
    for (auto& d : devices) {
        d->Deactivate();
    }
 cout<<"\nAll devices are deactivated.\n";
}

void SmartCampusManager::InteractAllDevices() {
    if (devices.empty()) {
        cout << "No devices to interact with.\n";
        return;
    }
    cout << "\n--- Interacting with all devices ---\n";
    for (auto& d : devices)
    {
        cout << "\n[Device ID " << d->GetID() << " - " << d->GetName() << "]\n";
        d->Interaction_Event();
    }
    cout << "\n--- Done ---\n";
}

void SmartCampusManager::AddDevice() {
     int dev_type,id;
     string name, brand, place;

     //choose device type
     cout << "\n--- Add a Device ---\n";
     cout << "1.SecutiryCamera\n";
     cout << "2.AirConditioning\n";
     cout << "3.Projector\n";
     cout << "4.RoomLighting\n";
     cout << "5.DoorLock\n";
     cout << "Choose device type: ";
     cin >> dev_type;

     cout << "Enter device ID: ";
     cin >> id;


     //check if there could be a duplication of IDs
     for (const auto& d : devices) {
         if (d->GetID() == id) {
             cout << "ERROR: This ID already exists!\n";
             return;
         }
     }

     cout << "Enter device name: ";
     cin >> name;
     cout << "Enter device manufacturer: ";
     cin >> brand;
     cout << "Enter the room name: ";
     cin >> place;


     // find room
     Room* room_place = nullptr;
     for (auto& r : rooms)
     {
         if (r->room_n == place)
         {
             room_place = r.get();
             break;
         }
     }

     if (room_place == nullptr)
     {
         rooms.push_back(unique_ptr<Room>(new Room()));
         rooms.back()->room_n = place;
         room_place = rooms.back().get();
     }

     if (dev_type == 1) {
         string quality, power;
         cout << "Enter the camera quality (720p/1080p/4k): ";
         cin >> quality;
         cout << "Enter the camera power (mains/battery): ";
         cin >> power;
         devices.push_back(make_unique<SecurityCamera>(id, name, brand, quality, power));
     }
     else if (dev_type == 2) {
         unsigned int temp;
         cout << "Enter the target aircondition temperature: ";
         cin >> temp;
         devices.push_back(make_unique<AirConditioning>(id, name, brand, temp));
     }
     else if (dev_type == 3) {
         string input;
         unsigned int bright;
         cout << "Enter the projector input source (VGA/HDMI/Wireless): ";
         cin >> input;
         cout << "Enter brightness of projector (0-100): ";
         cin >> bright;
         devices.push_back(make_unique<Projector>(id, name, brand, input,bright));
     }

     else if (dev_type == 4) {
        
         int light;
         cout << "Enter the room lighting brightness (0-100): ";
         cin >> light;
         devices.push_back(make_unique<RoomLighting>(id, name, brand,light));
     }

     else if (dev_type == 5) {
         string lastUser;
         int lockedIn;
         cout << "Locked Door? 1=true 0=false: ";
         cin >> lockedIn;
         cout << "Enter the last user that opened the door: ";
         cin >> lastUser;

        
         bool locked = (lockedIn == 1);
        
         devices.push_back(make_unique<DoorLock>(id, name, brand, locked, lastUser));
     }


     else {
         cout << "ERROR:Invalid device type choice. \n";
         return;
     }
     // Add pointer into room
     room_place->room_dev.push_back(devices.back().get());

     cout << "Device added successfully.\n";

}

void SmartCampusManager::DeleteDevice() {
    if (devices.empty()) {
        cout << "No devices to delete! \n";
        return;
    }

    unsigned int id;

    //choose device type
    cout << "\n--- Delete a Device ---\n";
    cout << "1.SecutiryCamera\n";
    cout << "2.AirConditioning\n";
    cout << "3.Projector\n";
    cout << "4.RoomLighting\n";
    cout << "5.DoorLock\n";
    cout << "Choose device type or the ID of that device to delete: ";
    cin >> id;


    //remove the device from rooms
    for (auto& r:rooms) {
        //Gets deference to the device iterator to get the unique pointer
        for (auto dev = r->room_dev.begin(); dev != r->room_dev.end();) {
            if ((*dev)->GetID() == id)
                dev = r->room_dev.erase(dev);  //delete device
            else
                dev++;
        }
    }
    //Gets deference to the device iterator to get the unique pointer
    for (auto dev=devices.begin(); dev !=devices.end();) {
        
        if ((*dev)->GetID() == id)
        {
            dev = devices.erase(dev);//delete device
            cout << "The device with the ID: " << id << " deleted succesfully."<<endl;
        }
        else {
            dev++;
        }
     }
    
     
}

void SmartCampusManager::EditDevice() {
    //check if there are no devices to edit
    if (devices.empty()) {
        cout << "No devices to edit! \n";
        return;
    }

    unsigned int id;
    //choose device type
    cout << "\n--- Edit a Device ---\n";
    cout << "1.SecutiryCamera\n";
    cout << "2.AirConditioning\n";
    cout << "3.Projector\n";
    cout << "4.RoomLighting\n";
    cout << "5.DoorLock\n";
    cout << "Choose device type to edit: ";
    cin >> id;


    //Gets edit attributes from devices EditAttributes function
    for (auto& dev : devices) {
        if (dev->GetID() == id) {
            dev->EditAttributes();
            cout << "Device edited successfully." << endl;
        }
    }

}

void SmartCampusManager::CheckConnection() {  
    cout << "\nChecking connection of devices:\n";
    cout << "---Connected Devices---" << endl;
    for (auto& d : devices) {
        if (d->CheckConnection())
            cout << d->GetID() << " | " << d->GetName() << endl;

    }
    cout << endl;
    cout << "---Disconnected Devices---" << endl;
    for(auto& d: devices){
        if (!d->CheckConnection()) 
            cout << d->GetID() << " | " << d->GetName() << endl;
    
    }


    unsigned int ch_con;
    cout << endl;
    cout << "Change the connection of the devices. Press 1 to connect a device and 0 to disconnect: "<<endl;
    cin >> ch_con;

        unsigned int id;
        bool state=true;//all devices are connected at the start
        cout << "Enter the device ID you want to change connection: "<<endl;
        cin >> id;

    if (ch_con == 1) {
         state;
        for (auto& d : devices) {
            if (d->GetID() == id) {
                d->SetConnection(state);
                cout << "Device with the ID: " << d->GetID() << " is connected" << endl;
            }
        }

    }
    if (ch_con == 0) {
        for (auto& d : devices) {
            state = false;//sets connection to disconnected
            if (d->GetID() == id) {
                d->SetConnection(state);
                cout << "Device with the ID: " << d->GetID() << " is disconnected" << endl;
            }
        }

    }

}


void SmartCampusManager::SearchDevice() {
    unsigned int id;
    cout << "\nEnter device ID you want to search: \n" ;
    cin >> id;

    Device* search = nullptr;

    //checks if there is a device with that ID
    for (auto& d : devices) {
        if (d->GetID() == id) {
            search = d.get();  //points to that device
            break;
        }
         
    }
    //Checks that device if there is in a room
    if (search!=nullptr) {
        for (auto& r : rooms) {
            for (auto& d : r->room_dev) {
                if (d->GetID() == id) {
                    search = d;  //points to the device
                    cout << "This device is found in: " << r->room_n << endl;
                   
                }
            }
        }
    }
    if (!search) {
        cout << "Device is not found." << endl;
        return;
    }
    if (search != nullptr) {
        unsigned int search_ch;
        //Interaction with the devices 
        cout << "Device found: "<<search->GetName()<<endl;
        cout << "1.Activate Device\n";
        cout << "2.Deactivate Device\n";
        cout << "3.Check Connection of the Device\n";
        cout << "4.Interact with device\n";
        cout << "5.View info of the device\n";
        cout << "Choose an option: ";
        cin >> search_ch;

        if (search_ch == 1) {
            search->Activate();
        }
        else if (search_ch == 2) {
            search->Deactivate();
        }
        else if (search_ch == 3) {
            search->CheckConnection();
        }
        else if (search_ch == 4) {
            search->Interaction_Event();
        }
        else if (search_ch == 5) {
            search->ViewInfo();
        }
        else {
            cout << "Wrong option " << endl;
        }
    }


}



void SmartCampusManager::CreateRoom() {
    string rName;

    cout << "Enter the room name you want to create: "<<endl;
    cin >> rName;

    for (auto& r : rooms) {
        if (r->room_n == rName) {
            cout << "This room already exists.\n";
            return;
        }
    }

    rooms.push_back(unique_ptr<Room>(new Room()));
    rooms.back()->room_n = rName;
    cout << "Room " << rName << " created\n";
}



void SmartCampusManager::ViewRooms() {
    cout << "\n ---Viewing Rooms---\n";

    if (rooms.empty()) {
        cout << "There are no rooms created.\n";
        return;
    }

    for (auto& r : rooms) {
        cout << "Viewing Devices in the room: " << r->room_n << "\n";

        if (r->room_dev.empty()) {
            cout << "This room has no devices assigned yet." << endl;
        }
        else {
            for (auto& dev : r->room_dev) {
                dev->ViewInfo();
                cout << endl;
            }
        }
    }

}


//DESIGN PATTERN: Composite pattern
//The rooms acts as a container of the devices as a "composite" group and the system
// can perform the device's operations on a room such as Activate,Deactivate,Edit,View by iterating devices in that room
// This benefits to enable scalable grouping of the devices each room has and to make it easy to add a new room without changing the device classes
//

void SmartCampusManager::ManageRooms()
{
    if (rooms.empty())
    {
        cout << "No rooms available.\n";
        return;
    }
    string roomName;
    cout << "Enter room name to manage: ";
    cin >> roomName;

    Room* room = nullptr;
    for (auto& r : rooms)
    {
        if (r->room_n == roomName)
        {
            room = r.get();
            break;
        }
    }

    if (!room)
    {
        cout << "Room not found.\n";
        return;
    }

    int choice = -1;
    do
    {
        //Interaction in the Room
        cout << "\n--- Managing Room " << room->room_n << " ---\n";
        cout << "1) View devices in room\n";
        cout << "2) Add existing device to room\n";
        cout << "3) Remove device from room\n";
        cout << "4) Activate all room devices\n";
        cout << "5) Deactivate all room devices\n";
        cout << "6) Edit Device from room\n";
        cout << "0) Go Back\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (room->room_dev.empty())
            {
                cout << "No devices in this room.\n";
            }
            else
            {
                for (auto* d : room->room_dev)
                {
                    cout << d->GetID() << " | " << d->GetName()
                        << " | " << d->GetManufacturer() << "\n";
                }
            }
        }
        else if (choice == 2)
        {
            unsigned int id;
            cout << "Enter device ID to add: ";
            cin >> id;

            // find device in campus list
            Device* found = nullptr;
            for (auto& d : devices)
            {
                if (d->GetID() == id)
                {
                    found = d.get();
                    break;
                }
            }

            if (!found)
            {
                cout << "Device not found.\n";
                continue;
            }

            // check not already in this room
            bool is = false;
            for (auto* d : room->room_dev)
            {
                if (d->GetID() == id) { is = true; break; }
            }
            if (is)
            {
                cout << "Device already in this room.\n";
                continue;
            }

            // remove from any other room first if there is in other room
            for (auto& r : rooms)
            {
                for (auto other = r->room_dev.begin(); other != r->room_dev.end(); )
                {
                    if ((*other)->GetID() == id) other = r->room_dev.erase(other);
                    else ++other;
                }
            }

            room->room_dev.push_back(found);
            cout << "Device added to room.\n";
        }
        else if (choice == 3)
        {
            unsigned int id;
            cout << "Enter device ID to remove: ";
            cin >> id;

            bool removed = false;
            for (auto other = room->room_dev.begin(); other != room->room_dev.end(); )
            {
                if ((*other)->GetID() == id)
                {
                    other = room->room_dev.erase(other);
                    removed = true;
                    break;
                }
                else ++other;
            }

            if (removed) cout << "Device removed from room.\n";
            else cout << "Device not found in this room.\n";
        }
        else if (choice == 4)
        {
            for (auto* d : room->room_dev) d->Activate();
            cout << "Room devices activated.\n";
        }
        else if (choice == 5)
        {
            for (auto* d : room->room_dev) d->Deactivate();
            cout << "Room devices deactivated.\n";
        }
        //User can edit a device through manage room
        else if (choice == 6) {
            for (auto* d : room->room_dev) d->EditAttributes();
            cout << "Room device edited.\n";
        }
        else if (choice == 0)
        {
            break;
        }

        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}


//Helper function for finding the next available ID
unsigned int SmartCampusManager::GetNextID() const
{
    unsigned int id = 1;
    while (true)
    {
        bool usedid = false;
        for (const auto& d : devices)
        {
            if (d->GetID() == id) 
            { 
                usedid = true;
                break; 
            }
        }
        if (!usedid) 
        return id;
        id++;
    }
}


//DESIGN PATTERN: Prototype pattern
//Cloning the rooms is a prototype method that allows the devices to be duplicated to another room using polymorphism
//and it copies the device's attributes into a new device and just changing the ID of the device and adds a new name to the room
//
//

void SmartCampusManager::DuplicateRoom()
{
    if (rooms.empty())
    {
        cout << "No rooms available to duplicate. Create a room first.\n";
        return;
    }

    string oldName;
    cout << "Enter room name to duplicate: ";
    cin >> oldName;

    Room* oldRoom = nullptr;
    for (auto& r : rooms)
    {
        if (r->room_n == oldName)
        {
            oldRoom = r.get();
            break;
        }
    }

    //Check if there is the typed room in the system
    if (!oldRoom)
    {
        cout << "Room not found.\n";
        return;
    }

    // create new room name
    string newRoomName = oldRoom->room_n + "_copy";

    // prevent duplicates
    for (auto& r : rooms)
    {
        if (r->room_n == newRoomName)
        {
            cout << "A copy of the room already exists: " << newRoomName << "\n";
            return;
        }
    }

    rooms.push_back(unique_ptr<Room>(new Room()));
    rooms.back()->room_n = newRoomName;


    Room* newRoom = rooms.back().get();

    // duplicate each device
    for (Device* dev : oldRoom->room_dev)
    {
        if (!dev) continue;

        unsigned int newID = GetNextID();
        string nName = dev->GetName() + "_copy";

        // polymorphic clone (Prototype)
        unique_ptr<Device> cloned = dev->Clone(newID, nName);

        devices.push_back(move(cloned));
        newRoom->room_dev.push_back(devices.back().get());
    }

    cout << "Room duplicated: " << newRoomName << "\n";
}
