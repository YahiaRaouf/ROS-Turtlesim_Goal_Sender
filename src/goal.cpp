#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
#include <math.h>
using namespace std;

turtlesim::Pose currentPose;
void callback(const turtlesim::Pose::ConstPtr &Pose)
{
    currentPose = *Pose;
    ROS_INFO("current position: x = [%f] , y = [%f]", currentPose.x, currentPose.y);
    ROS_INFO("Current angle: theta = [%f]", currentPose.theta);
}

// double normalizeAngle(double angle)
// {
//     while (angle > M_PI) angle -= 2 * M_PI;
//     while (angle < -M_PI) angle += 2 * M_PI;
//     return angle;
// }

void moveToGoal()
{
    unsigned char rotatedFlag = 0;

    turtlesim::Pose goalPose;
    geometry_msgs::Twist vel_msg;

    float xGoal = 0.0;
    float yGoal = 0.0;
    float distance = 0;
    float angleToGoal = 0;
    float theta = 0;
    bool goalReached = true;

    ros::NodeHandle handle_obj;

    // creating a pub node to turtlesim to give it a goal
    ros::Publisher goal_pub =
        handle_obj.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // making the same node also sub to turtle sim to get feedback pose
    ros::Subscriber pose_sub =
        handle_obj.subscribe<turtlesim::Pose>("/turtle1/pose", 10, callback);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        if(goalReached){    
            cout << "X: ";
            cin >> xGoal;
            cout << "Y: ";
            cin >> yGoal;
        }
         
        goalReached = false;

        goalPose.x = xGoal;
        goalPose.y = yGoal;

        distance = sqrt(pow((goalPose.x - currentPose.x), 2) + pow(((goalPose.y - currentPose.y)), 2));
        angleToGoal = atan2((goalPose.y - currentPose.y), (goalPose.x - currentPose.x));
        theta = angleToGoal - currentPose.theta;

        vel_msg.angular.z = 3.0 * theta;

        if (fabs(theta) <= 0.1)
        {
            vel_msg.angular.z = 0;
            vel_msg.linear.x = 1 * distance;
            if (distance <= 0.1)
            {
                vel_msg.linear.x = 0;
                goal_pub.publish(vel_msg);
                goalReached = true;
            }
        }

        goal_pub.publish(vel_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "goal");
    moveToGoal();
}
