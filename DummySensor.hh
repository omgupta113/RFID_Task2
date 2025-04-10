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
  /// \brief A simple dummy sensor that publishes a "Hello World" message when loaded
  class DummySensor : public gz::sensors::Sensor
  {
    /// \brief Load the sensor with SDF parameters.
    /// \param[in] _sdf SDF Sensor parameters.
    /// \return True if loading was successful
    public: virtual bool Load(const sdf::Sensor &_sdf) override;

    /// \brief Update the sensor and generate data
    /// \param[in] _now The current time
    /// \return True if the update was successful
    public: virtual bool Update(
      const std::chrono::steady_clock::duration &_now) override;

    /// \brief Node for communication
    private: gz::transport::Node node;

    /// \brief Publishes sensor data
    private: gz::transport::Node::Publisher pub;
  };
}

#endif