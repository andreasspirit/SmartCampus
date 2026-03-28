#ifndef DOORLOCK_H
#define DOORLOCK_H

#include "Device.h"
#include <memory>
using namespace std;


class DoorLock : public Device {

private:
	bool locked;
	string last_opened;
public:
	//Constructor for door lock attributes and inherits from device class
	DoorLock(unsigned int id, string name, string manufacturer, bool locked,string last_opened);

	void Interaction_Event() override;
	void ViewInfo() const override;
	void EditAttributes() override;
	
	unique_ptr<Device>Clone(unsigned int newID, string nName) const override;
};



#endif 