# DummySensor Plugin for Gazebo Harmonic

**[⚡ Watch Demo Video ⚡](https://youtu.be/oGc9NSYwBGg)**

A simple sensor plugin for Gazebo Harmonic that publishes a "Hello World" message when loaded.

## Overview

This repository contains a custom sensor plugin implementation for Gazebo Harmonic. The `DummySensor` is a basic example that demonstrates how to create and integrate a custom sensor with the Gazebo simulation environment. When loaded, it publishes a single "Hello World" message to a specified topic.

## Features

- Minimal custom sensor implementation for Gazebo Harmonic
- Publishes a single "Hello World" message at load time
- Example of creating custom sensors that integrate with Gazebo's Entity-Component-Manager (ECM)
- Reference for creating more complex sensor plugins

## Requirements

- Gazebo Harmonic (Garden/Sim version 8.x)
- Ubuntu 24.04 or compatible OS
- CMake 3.11 or higher
- C++17 compatible compiler

## Installation

1. Clone this repository:

```bash
git clone https://github.com/your-username/DummySensorSystem.git
cd DummySensorSystem
```

2. Create a build directory and compile:

```bash
mkdir build
cd build
cmake ..
make
```

3. Set up environment variables to make the plugin visible to Gazebo:

```bash
export GZ_SIM_SYSTEM_PLUGIN_PATH=$PWD:$GZ_SIM_SYSTEM_PLUGIN_PATH
export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
```

## Usage

### Testing with a standalone SDF file

Create an SDF file `model_with_dummysensor.sdf` with the following content:

```xml
<?xml version="1.0" ?>
<sdf version="1.6">
  <world name="dummysensor_world">
    
    <!-- The DummySensor system plugin -->
    <plugin
      filename="DummySensorSystem"
      name="custom::DummySensorSystem">
    </plugin>
    
    <!-- Standard world elements -->
    
    
    <model name="model_with_dummysensor">
      <pose>0 0 0.05 0 0 0</pose>
      <link name="link">
        <inertial>
          <mass>0.1</mass>
          <inertia>
            <ixx>0.000166667</ixx>
            <iyy>0.000166667</iyy>
            <izz>0.000166667</izz>
          </inertia>
        </inertial>
        <collision name="collision">
          <geometry>
            <box>
              <size>0.1 0.1 0.1</size>
            </box>
          </geometry>
        </collision>
        <visual name="visual">
          <geometry>
            <box>
              <size>0.1 0.1 0.1</size>
            </box>
          </geometry>
        </visual>
        
        <!-- Our custom dummy sensor -->
        <sensor name="dummy_sensor" type="custom" gz:type="dummysensor">
          <always_on>1</always_on>
          <update_rate>1</update_rate>
          <visualize>true</visualize>
          <topic>dummy_sensor_topic</topic>
          <gz:dummysensor>
            <message>Hello World from SDF!</message>
          </gz:dummysensor>
        </sensor>
      </link>
    </model>
  </world>
</sdf>
```

Run Gazebo with this SDF file:

```bash
gz sim -v 4 model_with_dummysensor.sdf
```

### Integration with ROS 2

To use this sensor with ROS 2 and URDF/Xacro models, add this section to your robot description file:

```xml
<!-- Make sure to include the namespace -->
<robot xmlns:xacro="http://www.ros.org/wiki/xacro"
       xmlns:gz="http://gazebosim.org/xmlschema">

  <!-- DummySensor plugin -->
  <gazebo reference="base_link">
    <sensor name="dummy_sensor" type="custom" gz:type="dummysensor">
      <always_on>1</always_on>
      <update_rate>1</update_rate>
      <visualize>true</visualize>
      <topic>dummy_sensor_topic</topic>
      <gz:dummysensor>
        <message>Hello World from URDF!</message>
      </gz:dummysensor>
    </sensor>
  </gazebo>

</robot>
```

## Verification

To verify that the sensor is working properly, listen for messages on the topic:

```bash
gz topic -e -t /dummy_sensor_topic
```

You should see the "Hello World from DummySensor!" message appear when the sensor loads.

## Project Structure

- `DummySensor.hh` & `DummySensor.cc`: The implementation of the custom sensor
- `DummySensorSystem.hh` & `DummySensorSystem.cc`: Integration with Gazebo's Entity-Component-Manager
- `CMakeLists.txt`: Build configuration

## License

This project is licensed under the Apache License 2.0 - see the license headers in the source files for details.

## Acknowledgments

This plugin is based on the custom sensor examples from the Gazebo Harmonic documentation and the Odometer example from the Gazebo Sensors repository.