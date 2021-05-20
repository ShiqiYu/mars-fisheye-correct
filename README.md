# Correct Fisheye Distortion for the first Chinese Mars Image
热烈祝贺中国首次火星探测天问一号任务探测器发回火星照片

## Requirements
* A C++ compiler
* OpenCV

## How to compile
```bash
cmake .
make
```
## How to run
If you compiled the program successfully, you can run it:
```bash
./fisheye-correct chinese-1st-mars-image.jpg
```
The result file will be stored in the current directory.

## The result and the input image
![Result](/result.jpg "Corrected image")
![Mars Image](/chinese-1st-mars-image.jpg "Mars Image")

## Related article
[我为中国火星第一图做鱼眼矫正](https://mp.weixin.qq.com/s/RK33OLCS_8XyPkLWzB5VsQ)
