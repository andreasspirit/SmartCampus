#ifndef PROJECTOR_H
#define PROJECTOR_H

#include "Device.h"
#include <string>
#include <memory>
using namespace std;

class Projector : public Device
{
private:
	string input_source;
	unsigned int brightnessProjector;
public:

	//Constructor for Projector attributes and inherits from device class
	Projector(unsigned int id, string name, string manufacturer, string inputSource, unsigned int brightnessPr);

	void Interaction_Event() override;
	void ViewInfo() const override;
	void EditAttributes() override;


	unique_ptr<Device>Clone(unsigned int newID, string nName) const override;
};



#endif