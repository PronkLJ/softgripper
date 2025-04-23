from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    softgripper_controller = Node(
        package='softgripper_control',
        executable='softgripper_controller',
        name='softgripper_controller'
    )

    return LaunchDescription([
        softgripper_controller,
    ])
