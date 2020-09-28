/*

/odom:

header: 
  seq: 354
  stamp: 
    secs: 1496242658
    nsecs: 172391901
  frame_id: odom
child_frame_id: base_link
pose: 
  pose: 
    position: 
      x: 3.67305326462
      y: 0.00525344582275
      z: 0.0
    orientation: 
      x: 0.0
      y: 0.0
      z: -0.881353139877
      w: 0.472458064556
  covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
twist: 
  twist: 
    linear: 
      x: -0.00104427337646
      y: -0.00156980007887
      z: 0.0
    angular: 
      x: 0.0
      y: 0.0
      z: -0.627348423004
  covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

  
  /tf:
  
  transforms: 
  - 
    header: 
      seq: 0
      stamp: 
        secs: 1496242658
        nsecs: 175391901
      frame_id: odom
    child_frame_id: base_link
    transform: 
      translation: 
        x: 3.67305326462
        y: 0.00525344582275
        z: 0.0
      rotation: 
        x: 0.0
        y: 0.0
        z: -0.881353139877
        w: 0.472458064556
*/

#include <ros/ros.h>
#include <tf/transform_broadcaster.h> //tf
#include <nav_msgs/Odometry.h>	// odom

tf::TransformBroadcaster *tb;
bool ignore_child_frame_id;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    
    //ROS_INFO("Odom received. Publish TF.");

    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = msg->header.stamp;
    odom_trans.header.frame_id = msg->header.frame_id;
    
    if(ignore_child_frame_id){
        odom_trans.child_frame_id = "bobcat_base";
    }else{
        odom_trans.child_frame_id = msg->child_frame_id; //get the one from the odom topic
    }
    
    odom_trans.transform.translation.x = msg->pose.pose.position.x;
    odom_trans.transform.translation.y = msg->pose.pose.position.y;
    odom_trans.transform.translation.z = msg->pose.pose.position.z;
    odom_trans.transform.rotation.x = msg->pose.pose.orientation.x;
    odom_trans.transform.rotation.y = msg->pose.pose.orientation.y;
    odom_trans.transform.rotation.z = msg->pose.pose.orientation.z;
    odom_trans.transform.rotation.w = msg->pose.pose.orientation.w;
    tb->sendTransform(odom_trans);    
}


int main(int argc, char** argv){
    
	ros::init(argc, argv, "subscribe_odom_publish_tf");
        
	ros::NodeHandle n;
        ros::NodeHandle pp("~"); //private parameters
  
        pp.param<bool>("ignore_child_frame_id", ignore_child_frame_id, false);  //false: use the one from odom topic, true: use bobcat_base
        
        tb = new tf::TransformBroadcaster();
        ros::Subscriber odom_sub = n.subscribe<nav_msgs::Odometry>("odom", 100, &odomCallback); 

        ros::spin();   
        
        return 0;
};