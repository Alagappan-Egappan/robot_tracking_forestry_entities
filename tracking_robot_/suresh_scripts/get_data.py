import rospy
from sensor_msgs.msg import CompressedImage


def get_data_callback(data):
    print data.format
    pass


def init():
    rospy.init_node("get_data")
    rospy.Subscriber("/dalsa_camera_720p/compressed", CompressedImage, get_data_callback)

if __name__ == "__main__":
    #starting node
    init()
    rospy.spin()
    pass


