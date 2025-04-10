

#include <gz/msgs/stringmsg.pb.h>

#include <gz/common/Console.hh>
#include <gz/msgs/Utility.hh>
#include <gz/sensors/Util.hh>

#include "DummySensor.hh"

using namespace custom;


bool DummySensor::Load(const sdf::Sensor &_sdf)
{
  auto type = gz::sensors::customType(_sdf);
  if ("dummy" != type)
  {
    gzerr << "Trying to load [dummy] sensor, but got type ["
           << type << "] instead." << std::endl;
    return false;
  }

  gz::sensors::Sensor::Load(_sdf);


  this->pub = this->node.Advertise<gz::msgs::StringMsg>(this->Topic());

  if (!_sdf.Element()->HasElement("gz:dummy"))
  {
    gzdbg << "No custom configuration for [" << this->Topic() << "]"
           << std::endl;
    return true;
  }

  // Load custom sensor params
  auto customElem = _sdf.Element()->GetElement("gz:dummy");

  if (customElem->HasElement("message"))
  {
    this->message = customElem->Get<std::string>("message");
    gzdbg << "Custom message for [" << this->Topic() << "]: " 
          << this->message << std::endl;
  }

  return true;
}


bool DummySensor::Update(const std::chrono::steady_clock::duration &_now)
{
  gz::msgs::StringMsg msg;
  *msg.mutable_header()->mutable_stamp() = gz::msgs::Convert(_now);
  auto frame = msg.mutable_header()->add_data();
  frame->set_key("frame_id");
  frame->add_value(this->Name());

  msg.set_data(this->message);

  this->AddSequence(msg.mutable_header());
  this->pub.Publish(msg);

  return true;
}


void DummySensor::SetMessage(const std::string &_msg)
{
  this->message = _msg;
}


const std::string &DummySensor::Message() const
{
  return this->message;
}