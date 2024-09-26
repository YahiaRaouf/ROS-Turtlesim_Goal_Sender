# ROS-Turtlesim_Goal_Sender

## overview
This package provides a ROS node that allows users to interactively send goal positions to the turtle in the Turtlesim simulator. The node continuously takes user input for a goal position (x, y), and the turtle first aligns its orientation towards the goal before moving forward. After reaching the goal, the user is prompted to input a new goal, making it an interactive control mechanism.

## Features
- Interactive Goal Setting: Users can provide goal positions, and the turtle will move to the specified position.
- Two-Phase Movement: The turtle first adjusts its orientation to face the goal and then moves towards it.
- Continuous Operation: Once the turtle reaches the goal, it waits for a new goal position from the user.
- Angular Adjustment: The turtle ensures efficient rotation by minimizing angular errors, adjusting in all directions (left or right) depending on the shortest angle to the goal.

## Launch
the launch file launches the sendGoal node and the turtlesim node:
```bash
roslaunch send_goal sendGoal.launch
```
and this window should appear
![26 09 2024_02 31 17_REC](https://github.com/user-attachments/assets/6a1e32d1-3213-4676-a69c-1fe42071bb3f)

if it doesnt then you need to install turtle sim using this link 
[ROSWiki](http://wiki.ros.org/turtlesim)

the Goal node publishes the goal to the turtle node through /turtle1/cmd_vel topic using the geometry_msg/Twist
msg and at the same time subscribes to the turtle node through the topic /turtle1/pose topic using the geometry_msg/Pose msg to get feedback of the current turtle position on the window.

![26 09 2024_02 37 03_REC](https://github.com/user-attachments/assets/47ee46a8-2ed3-4361-a68f-b3091bbf55ca)

to send a goal to the turtle node you need to input the X & y coordinate and wait for the turtle to reach its goal
and then you can reenter a new goal for the turtle

