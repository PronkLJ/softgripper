# Softgripper packages for ROS2 simulation
The packages in this repository allow for the digital representation of the softgripper fingers.

Tested in ROS2 Humble Hawksbill.

## Content
This repository currently includes the following package:
* softgripper_control: contains nodes for physically controlling the softgrippers.
* softgripper_description: describes the softgrippers.

## Package installation

To install the packages from inside your workspace:
```console
cd src
git clone https://github.com/PronkLJ/softgripper
```
## Control softgrippers
In terminal 1:
```console
ros2 launch softgripper_control softgripper_control.launch.py 
```
If port access is denied, try:
```console
sudo chmod a+rw /dev/ttyACM0
```

In terminal 2:

Closing the softgrippers:
```console
ros2 topic pub --once /voltage std_msgs/msg/Float32 "{data: 1.5}" 
```

Opening the softgrippers:
```console
ros2 topic pub --once /voltage std_msgs/msg/Float32 "{data: 0.0}" 
```

## Simulation - view in RViz
```console
ros2 launch softgripper_description view_softgrippers.launch.py
```
## To-do
- [x] Add physical control of the softgrippers
    - [x] Create ROS2 node that sends commands via serial.
    - [x] Create Arduino script that can receive commands via serial.
    - [x] Test for one LED.
    - [x] Test for one pressure valve.
    - [x] Test for multiple pressure valves.
- [ ] (Optional) implement bending of fingers in simulation


