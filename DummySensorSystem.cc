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

 #include <string>
 #include <unordered_map>
 #include <utility>
 
 #include <gz/common/Profiler.hh>
 #include <gz/plugin/Register.hh>
 #include <gz/sensors/SensorFactory.hh>
 
 #include <sdf/Sensor.hh>
 
 #include <gz/sim/components/CustomSensor.hh>
 #include <gz/sim/components/Name.hh>
 #include <gz/sim/components/ParentEntity.hh>
 #include <gz/sim/components/Sensor.hh>
 #include <gz/sim/components/World.hh>
 #include <gz/sim/EntityComponentManager.hh>
 #include <gz/sim/Util.hh>
 
 #include "DummySensor.hh"
 #include "DummySensorSystem.hh"
 
 using namespace custom;
 
 //////////////////////////////////////////////////
 void DummySensorSystem::PreUpdate(const gz::sim::UpdateInfo &,
     gz::sim::EntityComponentManager &_ecm)
 {
   _ecm.EachNew<gz::sim::components::CustomSensor,
                gz::sim::components::ParentEntity>(
     [&](const gz::sim::Entity &_entity,
         const gz::sim::components::CustomSensor *_custom,
         const gz::sim::components::ParentEntity *_parent)->bool
       {
         // Get sensor's scoped name without the world
         auto sensorScopedName = gz::sim::removeParentScope(
             gz::sim::scopedName(_entity, _ecm, "::", false), "::");
         sdf::Sensor data = _custom->Data();
         data.SetName(sensorScopedName);
 
         // Default to scoped name as topic
         if (data.Topic().empty())
         {
           std::string topic = gz::sim::scopedName(_entity, _ecm) + "/dummysensor";
           data.SetTopic(topic);
         }
 
         gz::sensors::SensorFactory sensorFactory;
         auto sensor = sensorFactory.CreateSensor<custom::DummySensor>(data);
         if (nullptr == sensor)
         {
           gzerr << "Failed to create dummy sensor [" << sensorScopedName << "]"
                  << std::endl;
           return false;
         }
 
         // Set sensor parent
         auto parentName = _ecm.Component<gz::sim::components::Name>(
             _parent->Data())->Data();
         sensor->SetParent(parentName);
 
         // Set topic on Gazebo
         _ecm.CreateComponent(_entity,
             gz::sim::components::SensorTopic(sensor->Topic()));
 
         // Keep track of this sensor
         this->entitySensorMap.insert(std::make_pair(_entity,
             std::move(sensor)));
 
         return true;
       });
 }
 
 //////////////////////////////////////////////////
 void DummySensorSystem::PostUpdate(const gz::sim::UpdateInfo &_info,
     const gz::sim::EntityComponentManager &_ecm)
 {
   // Only update and publish if not paused.
   if (!_info.paused)
   {
     for (auto &[entity, sensor] : this->entitySensorMap)
     {
       sensor->Update(_info.simTime);
     }
   }
 
   this->RemoveSensorEntities(_ecm);
 }
 
 //////////////////////////////////////////////////
 void DummySensorSystem::RemoveSensorEntities(
     const gz::sim::EntityComponentManager &_ecm)
 {
   _ecm.EachRemoved<gz::sim::components::CustomSensor>(
     [&](const gz::sim::Entity &_entity,
         const gz::sim::components::CustomSensor *)->bool
       {
         if (this->entitySensorMap.erase(_entity) == 0)
         {
           gzerr << "Internal error, missing dummy sensor for entity ["
                          << _entity << "]" << std::endl;
         }
         return true;
       });
 }
 
 GZ_ADD_PLUGIN(DummySensorSystem, gz::sim::System,
   DummySensorSystem::ISystemPreUpdate,
   DummySensorSystem::ISystemPostUpdate
 )
 
 GZ_ADD_PLUGIN_ALIAS(DummySensorSystem, "custom::DummySensorSystem")