import rclpy
from rclpy.node import Node

import sys
import os
import time

import serial
import serial.tools.list_ports
from xcar_msg.msg import Servo

class SubscriberNode(Node):

    def __init__(self, name):
        super().__init__(name)                             # ROS2节点父类初始化
        self.sub = self.create_subscription(
            Servo , "servo", self.listener_callback, 10) # 创建订阅者对象（消息类型、话题名、订阅者回调函数、队列长度）

    def listener_callback(self, msg):
        #test_data = "a" + string()
        #ser.write(test_data.encode('UTF-8'))
        print(msg.x)

def main(args=None):
    rclpy.init(args=args)

    try:
        ser = serial.Serial("/dev/ttyS3",9600, timeout=1) # 1s timeout
    except Exception as e:
        print("open serial failed!\n")

    node = SubscriberNode("servo")  # 创建ROS2节点对象并进行初始化
    rclpy.spin(node) 

    ser.close()
    node.destroy_node()
    rclpy.shutdown() 
