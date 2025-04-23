import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import xacro

def generate_launch_description():

    # File paths
    xacro_file = os.path.join(get_package_share_directory('softgripper_description'), 'urdf', 'softgripper.xacro')
    rviz_config_file = os.path.join(get_package_share_directory('robot_moveit_config'), 'config', 'config.rviz')

    # Process xacro 
    doc = xacro.parse(open(xacro_file))
    xacro.process_doc(doc)    

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[{'robot_description': doc.toxml()}],
    )
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="screen",
        #arguments=["-d", rviz_config_file],
    )

    return LaunchDescription([
        robot_state_publisher,
        rviz,
    ])
