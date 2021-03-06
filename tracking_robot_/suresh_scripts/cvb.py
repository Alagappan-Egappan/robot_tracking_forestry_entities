#!/usr/bin/env python
import numpy as np
import roslib
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

start = False

class image_converter:
    
    def __init__(self):
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/new_image_raw", Image, self.callback)

    def callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        self.frame_width = cv_image.shape[0]
        self.frame_height = cv_image.shape[1]

        global start, frame1, frame2
        if not start:
			frame1 = cv_image
			frame2 = cv_image
			print("here")
			start = True
        diff = cv2.absdiff(frame1, frame2)
        gray = cv2.cvtColor(diff, cv2.COLOR_BGR2GRAY)
	    # blur = cv2.GaussianBlur(gray, (5,5), 0)
        blur = cv2.medianBlur(gray, 15)
        _, thresh = cv2.threshold(blur, 20, 255, cv2.THRESH_BINARY)
        dilated = cv2.dilate(thresh, None, iterations=3)
        contours, _ = cv2.findContours(dilated, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)      

        for contour in contours:
            (x, y, w, h) = cv2.boundingRect(contour)
            if cv2.contourArea(contour) > 900:
                print("Area : {}".format(cv2.contourArea(contour)))
            cv2.rectangle(frame1, (x, y), (x+w, y+h), (0, 255, 0), 2)
        image = cv2.resize(frame1, (1280,720))
        # cv2.imshow("feed", thresh)

        cv2.imshow("feed", gray)
        frame1 = frame2
        frame2 = cv_image
        cv2.waitKey(1)

def main(args):
    ic = image_converter()
    rospy.init_node('image_converter', anonymous=True)
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)



