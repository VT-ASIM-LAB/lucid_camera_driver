#! /usr/bin/env python

# This script creates a ROS node that looks for nodes that publish Image
# messages and advertises to a camera_control_msgs/SetSleeping service. If it
# finds any, it assumes the found camera is an Arena camera and sends it
# either to sleep or wakes it up, depending on the argument. It will turn
# on/off all cameras at the same time. Best used as an alias in bashrc:
#
# alias arenaon='rosrun arena_camera toggle_camera 0' # turns cameras off
# alias arenaoff='rosrun arena_camera toggle_camera 1' # turns cameras on
#
# Valid arguments: 1 wakes cameras up, every other integer puts cameras to
# sleep.
  
import rospy

from camera_control_msgs.srv import SetSleeping

if __name__ == '__main__':
    argument = rospy.myargv()[1:]
    
    try:
        sleep_param = int(argument[0]) == 0
    except Exception:
        print('Usage: ./toggle_camera [0,1]')
        
        exit(1)
        
    service_suffix = "/set_sleeping"

    cameras = set()
    
    p_topics = rospy.get_published_topics()
    system_state = rospy.get_master().getSystemState()
    
    for published_topic, published_type in p_topics:
        node_name = published_topic.split('/')[1]
        
        if published_type == 'sensor_msgs/Image':
            for service_name, listener_list in system_state[2][2]:
                if service_name == "/" + node_name + service_suffix:
                    cameras.add(node_name)

    if not cameras:
        print('No cameras found!')

        exit(0)
        
    for camera in cameras:
        try:
            sleep_name = camera + service_suffix
            service_proxy = rospy.ServiceProxy(sleep_name, SetSleeping)
            res = service_proxy(sleep_param)
            
            print("Toggling camera '" + camera + "'.")
        except rospy.ServiceException as e:
            print("Service call failed for %s: %s" % (camera, e))