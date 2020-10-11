# yolov3 will be needing python3 so we have to compile the whole package using python3
# We need cv_bridge for getting the data from ros messages to yolov3
# So we need to compile the cv_bridge also with python3
#*************************************************************#
Here is the installation for cv_bridge
#*************************************************************#
# install these dependencies 

# `python-catkin-tools` is needed for catkin tool
# `python3-dev` and `python3-catkin-pkg-modules` is needed to build cv_bridge
# `python3-numpy` and `python3-yaml` is cv_bridge dependencies
# `ros-kinetic-cv-bridge` is needed to install a lot of cv_bridge deps. Probaply you already have it installed.
sudo apt-get install python-catkin-tools python3-dev python3-catkin-pkg-modules python3-numpy python3-yaml ros-kinetic-cv-bridge
# Create catkin workspace
mkdir catkin_workspace
cd catkin_workspace
catkin init
# Instruct catkin to set cmake variables
catkin config -DPYTHON_EXECUTABLE=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m -DPYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.6m.so
# Instruct catkin to install built packages into install place. It is $CATKIN_WORKSPACE/install folder
catkin config --install
# Clone cv_bridge src
git clone https://github.com/ros-perception/vision_opencv.git src/vision_opencv
# Find version of cv_bridge in your repository
apt-cache show ros-kinetic-cv-bridge | grep Version
    Version: 1.12.8-0xenial-20180416-143935-0800
# Checkout right version in git repo. In our case it is 1.12.8
cd src/vision_opencv/
git checkout 1.12.8
cd ../../
# Build
catkin build cv_bridge
# Extend environment with new package
source install/setup.bash --extend


#*************************************************************#
Here is the link for downloading the weights for yolov3
Download and put inside /yolov3_deepsort/weights folder
#*************************************************************#

https://pjreddie.com/media/files/yolov3.weights

# run "python3 object_tracker.py"
# It will take the image data from "/new_image_raw" topic
# So make sure before running object_tracker.py , roscore is running and /new_image_raw topic is published either by rosbag or seperatly. 

##############################################
        Run tracking 
##############################################

run ---> run_dataset.launch file from semfire_dataset_ntu package
run ---> converter.launch  from tacking_robot package : This will convert dalsa_camera_720p to new_image_raw topic and readable to cv_bridge
Now we can run the object_tracker.py file from yolo_v3_deepsort packge. Read the README.md file there for compilation and more information`
