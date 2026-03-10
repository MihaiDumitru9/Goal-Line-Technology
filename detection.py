import cv2
import matplotlib.pyplot as plt
import cvlib as cv
import numpy as np
from cvlib.object_detection import draw_bbox
import threading
import urllib.request

# Your ESP32-CAM stream URL (update IP as needed)
url = 'http://192.168.1.141/cam-lo.jpg'

def get_frame_from_url():
    try:
        img_resp = urllib.request.urlopen(url)
        imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
        frame = cv2.imdecode(imgnp, -1)
        return frame
    except Exception as e:
        print("Error fetching frame:", e)
        return None


def run1():
    cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)
    while True:
        frame = get_frame_from_url()
        if frame is None:
            continue

        # Resize frame to 416x416
        frame = cv2.resize(frame, (416, 416))

        cv2.imshow('live transmission', frame)
        key = cv2.waitKey(1)
        if key == ord('q'):
            break

    cv2.destroyWindow("live transmission")


def run2():
    cv2.namedWindow("detection", cv2.WINDOW_AUTOSIZE)
    while True:
        frame = get_frame_from_url()
        if frame is None:
            continue

        # Resize for detection
        frame = cv2.resize(frame, (640, 480))

        bbox, label, conf = cv.detect_common_objects(frame)
        for i, l in enumerate(label):
            if l == "sports ball":
                x_center = (bbox[i][0] + bbox[i][2]) / 2
                if x_center > frame.shape[1] / 2:
                    print("Ball passed middle of screen")
                    try:
                        urllib.request.urlopen("http://192.168.1.141/goal")
                    except Exception as e:
                        print("Error triggering goal:", e)

        out = draw_bbox(frame, bbox, label, conf)

        cv2.imshow('detection', out)
        key = cv2.waitKey(1)
        if key == ord('q'):
            break


    cv2.destroyWindow("detection")


if __name__ == '__main__':
    print("Started")

    #t1 = threading.Thread(target=run1)
    t2 = threading.Thread(target=run2)

    #t1.start()
    t2.start()

    #t1.join()
    t2.join()

    print("Finished")
