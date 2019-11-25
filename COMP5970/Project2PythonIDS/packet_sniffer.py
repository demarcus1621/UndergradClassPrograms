'''
Authors: James Barr, Demarcus Campbell, Tucker Simpson
Inspired By: Silver Moon (m00n.silv3r@gmail.com)
'''

from struct import unpack
import socket
import sys

try:
    sckt = socket.socket(socket.AF_PACKET,socket.SOCK_RAW,socket.ntohs(0x0003))
except socket.error, msg:
    print("Error", msg[0]": ",msg[1])
    sys.exit()

'''    
def get_packet():
    global sckt
    
    packet = sckt.recv(65535)    # Maximum packet size (65535)
    
    frame_header = packet[:14]
    frame_protocol = sckt.ntohs(
'''