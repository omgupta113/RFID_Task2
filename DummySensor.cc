

#include <gz/msgs/stringmsg.pb.h>

#include <gz/common/Console.hh>
#include <gz/msgs/Utility.hh>
#include <gz/sensors/Util.hh>

#include "DummySensor.hh"

using namespace custom;

bool DummySensor::Load(const sdf::Sensor &_sdf)
{
  auto type = gz::sensors::customType(_sdf);
  if ("dummysensor" != type)
  {
    gzerr << "Trying to load [dummysensor] sensor, but got type ["
           << type << "] instead." << std::endl;
    return false;
  }

  gz::sensors::Sensor::Load(_sdf);


  if (this->Topic().empty())
  {
    gzerr << "DummySensor has empty topic, cannot publish!" << std::endl;
    return false;
  }


  this->pub = this->node.Advertise<gz::msgs::StringMsg>(this->Topic());


  std::this_thread::sleep_for(std::chrono::milliseconds(100));


  gz::msgs::StringMsg msg;
  msg.set_data("Hello World from DummySensor!");
  
  // Debug output
  gzmsg << "DummySensor publishing 'Hello World' on topic: " 
        << this->Topic() << std::endl;
  

  bool success = this->pub.Publish(msg);
  if (success) {
    gzmsg << "Message successfully published" << std::endl;
  } else {
    gzerr << "Failed to publish message" << std::endl;
  }

  return true;
}


bool DummySensor::Update(const std::chrono::steady_clock::duration &_now)
{
  // Do nothing in Update 
  return true;
}