#include"DoorLock.h"
#include <iostream>
#include <memory>
using namespace std;


DoorLock::DoorLock(unsigned int id,string name,string manufacturer,bool locked,string last_opened)
	:Device(id,name,manufacturer), locked(locked), last_opened(last_opened){}


void DoorLock::Interaction_Event() {
	if (!status) {
		cout << "Device is inactive. Activate it first." << endl;
		return;
	}
	cout << "Door status: "<<(locked ? "Locked":"Unlocked") << endl;

	int choice;
	cout << "Enter 1 to lock the door or 2 to unlock it: " << endl;
	cin >> choice;
	if (choice == 1) {
		locked = true;
		cout << "The door is locked" << endl;
	}
	else if (choice == 2) {
		locked = false;
		cout <<"Enter the username that unlocked the door: " << endl;
		cin >> last_opened;
		
	}

}

void DoorLock::ViewInfo() const {

	cout << "[  Door Lock Info:  ]" << endl;
	Device::ViewInfo();//View Info call from the device class so every device displays the default device information
	cout << "Locked:" << (locked ? "Yes" : "No") << endl;
	cout << "Last opened by: " << last_opened << endl;
	cout << endl;

}


void DoorLock::EditAttributes() {
	int choice;
	cout << "Editing device DoorLock" << endl;
	cout << "Enter a new device name if needed: " << endl;
	cin >> device_name;
	cout << "Enter a new manufacturer if needed: " << endl;
	cin >> manufacturer;
	cout << "Enter 1 to lock the door or 2 to changed the last opened by user and to unlock the door" << endl;
	cin >> choice;
	if (choice == 1) {
		locked = true;
		cout << "Door is: " << (locked ? "Locked" : "Unlocked")<< endl;
	}
	else if (choice == 2) {
		locked = false;
		cout << "Enter the username that unlocked the door: " << endl;
		cin >> last_opened;

	}

	cout << "New device: " << device_name << " New manufacturer: " << manufacturer << " Door is: " <<locked<< " Last opened by: "
		<<last_opened << endl;
}

unique_ptr<Device> DoorLock::Clone(unsigned int newID, string nName) const {
	auto _copy = make_unique<DoorLock>(newID, nName, manufacturer, locked,last_opened);
	_copy->SetConnection(connected);
	if (status) _copy->Activate();
	return _copy;
}