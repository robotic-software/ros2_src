
#!/usr/bin/python3

import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    param_node = Node(
        package='cpp_parameters', 
        node_executable='parameter_node', 
        output='screen',  
        prefix=['stdbuf -o L'],
        parameters=[
            {"my_parameter": "foo"}
        ]          
    )
    ld.add_action(param_node)
    return ld