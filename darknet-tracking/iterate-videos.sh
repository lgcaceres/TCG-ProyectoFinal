#!/bin/bash

for filename in /home/tesista1/yolo/DataVicente/data/fights/*.*; do
    ./darknet detector demo -prefix "../video-out-images/$filename" cfg/coco.data cfg/yolov3.cfg ../weights/yolov3.weights $filename
done