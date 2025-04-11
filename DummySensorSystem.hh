
#ifndef DUMMYSENSORSYSTEM_HH_
#define DUMMYSENSORSYSTEM_HH_

#include <gz/sim/System.hh>
#include <gz/sensors/Sensor.hh>
#include <gz/transport/Node.hh>

namespace custom
{
 
  class DummySensorSystem:
    public gz::sim::System,
    public gz::sim::ISystemPreUpdate,
    public gz::sim::ISystemPostUpdate
  {
    
    public: void PreUpdate(const gz::sim::UpdateInfo &_info,
        gz::sim::EntityComponentManager &_ecm) final;

  
    public: void PostUpdate(const gz::sim::UpdateInfo &_info,
        const gz::sim::EntityComponentManager &_ecm) final;

    
    private: void RemoveSensorEntities(
        const gz::sim::EntityComponentManager &_ecm);

  
    private: std::unordered_map<gz::sim::Entity,
        std::shared_ptr<DummySensor>> entitySensorMap;
  };
}
#endif