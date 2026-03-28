#ifndef AIRCONDITIONING_H
#define AIRCONDITIONING_H

#include<iostream>
#include "Device.h"
#include <memory>

class AirConditioning : public Device
{
private:
	unsigned int temperature;
public:
	//Constructor for aircondition attributes and inherits from device class
	AirConditioning(unsigned int id, string name, string manufacturer,unsigned int temp);

	void Interaction_Event() override;
	void ViewInfo() const override;
	void EditAttributes() override;
	
    unique_ptr<Device>Clone(unsigned int newID, string nName) const override;

};

#endif