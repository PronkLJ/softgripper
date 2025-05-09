from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    arduino_communication = Node(
        package='softgripper_control',
        executable='arduino_communication',
        name='arduino_communication',
    )

    return LaunchDescription([
        arduino_communication,
    ])
