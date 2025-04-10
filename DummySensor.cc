/*
 * Copyright (C) 2025 Your Organization
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gz/msgs/stringmsg.pb.h>

#include <gz/common/Console.hh>
#include <gz/msgs/Utility.hh>
#include <gz/sensors/Util.hh>

#include "DummySensor.hh"

using namespace custom;

//////////////////////////////////////////////////
bool DummySensor::Load(const sdf::Sensor &_sdf)
{
  auto type = gz::sensors::customType(_sdf);
  if ("dummysensor" != type)
  {
    gzerr << "Trying to load [dummysensor] sensor, but got type ["
           << type << "] instead." << std::endl;
    return false;
  }

  // Load common sensor params
  gz::sensors::Sensor::Load(_sdf);

  // Make sure we have a valid topic to publish on
  if (this->Topic().empty())
  {
    gzerr << "DummySensor has empty topic, cannot publish!" << std::endl;
    return false;
  }

  // Advertise topic where data will be published
  this->pub = this->node.Advertise<gz::msgs::StringMsg>(this->Topic());

  // Give the publisher a moment to establish connections
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Create and publish message - only once
  gz::msgs::StringMsg msg;
  msg.set_data("Hello World from DummySensor!");
  
  // Debug output
  gzmsg << "DummySensor publishing 'Hello World' on topic: " 
        << this->Topic() << std::endl;
  
  // Publish the message once
  bool success = this->pub.Publish(msg);
  if (success) {
    gzmsg << "Message successfully published" << std::endl;
  } else {
    gzerr << "Failed to publish message" << std::endl;
  }

  return true;
}

//////////////////////////////////////////////////
bool DummySensor::Update(const std::chrono::steady_clock::duration &_now)
{
  // Do nothing in Update - we only publish at load time
  return true;
}