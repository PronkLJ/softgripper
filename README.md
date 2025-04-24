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

## Simulation - view in RViz
```console
ros2 launch softgripper_description view_softgrippers.launch.py
```
## To-do
- [ ] Add physical control of the softgrippers
    - [ ] Create ROS2 node that sends commands via serial.
    - [ ] Create Arduino script that can receive commands via serial.
    - [ ] Test for multiple pressure valves.
- [ ] (Optional) implement bending of fingers in simulation


