# Laboratory 4

Team 6  
Seongmin Jung, Noah Mollerstuen, Rafay Chaudhry  
Professor Lee  
ECSE 373  
14 October 2022  
Last modified: 20 October 2022  

---

This project is for learning and implementing stdr.

## `launch` files

### 1. `first.launch`

This launch file is for running `stdr_publisher_node`.

    $ roslaunch stdr_publisher first.launch


This launch file starts `stdr_publisher_node`. This node can control robot's position.

### 2. `second.launch`

This launch file includes `first.launch`, as well as executing `stdr_launchers` and `rqt_gui`

    $ roslaunch stdr_publisher second.launch

In order to run multiple robots, first you have to add one more robot at stdr_launcher. Next, you have to run one more stdr_publisher_node manually at another terminal as well as second.launch file.

    $ rosrun stdr_publisher stdr_publisher_node __ns:=robot1

You have to specify the namespace with `__ns` parameter. For example, the value of the first robot is `robot0`, the second robot is `robot1`, and so on.

---

I referred to the instruction of Laboratory #4 in ECSE 373 class.
