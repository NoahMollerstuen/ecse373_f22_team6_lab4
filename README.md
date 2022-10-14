# Laboratory 4

Team 4  
Seongmin Jung  
Professor Lee  
ECSE 373  
14 October 2022  

---

This project is for learning and implementing rosbag.

## `launch` files

### 1. `first.launch`

This launch file is for running `stdr_publisher_node`.

    $ roslaunch stdr_publisher first.launch


This launch file starts `stdr_publisher_node`. This node can control robot's position.

### 2. `second.launch`

This launch file includes `first.launch`, as well as executing `stdr_launchers` and `rqt_gui`

    $ roslaunch stdr_publisher second.launch

There is one more argument in addition to the `original.launch` file, `use_previous_launch`. If this argument is `true`, the robot model from `navvis_description` package will be used. Unless, newer model from this package will be used.

---

I referred to the instruction of Laboratory #3 in ECSE 373 class.