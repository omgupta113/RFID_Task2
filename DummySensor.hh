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
#ifndef DUMMYSENSOR_HH_
#define DUMMYSENSOR_HH_

#include <gz/sensors/Sensor.hh>
#include <gz/sensors/SensorTypes.hh>
#include <gz/transport/Node.hh>

namespace custom
{
  class DummySensor : public gz::sensors::Sensor
  {
   
    public: virtual bool Load(const sdf::Sensor &_sdf) override;

   
    public: virtual bool Update(
      const std::chrono::steady_clock::duration &_now) override;

    
    private: gz::transport::Node node;

   
    private: gz::transport::Node::Publisher pub;
  };
}

#endif