#ifndef ROOMLIGHTING_H
#define ROOMLIGHTING_H

#include "Device.h"
#include<memory>
using namespace std;


class RoomLighting : public Device {

private:
	unsigned int brightness;

public:

	//Constructor for room lighting attributes and inherits from device class
	RoomLighting(unsigned int id, string name, string manufacturer,unsigned int brightness_level);

	void Interaction_Event() override;
	void ViewInfo() const override;
	void EditAttributes() override;

	unique_ptr<Device>Clone(unsigned int newID, string nName) const override;
};



#endif 


