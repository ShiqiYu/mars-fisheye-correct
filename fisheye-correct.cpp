#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// map the fisheye image position to the rectilinear image position
// input:  src_x, src_y, center_x, center_y, R,
// output: dst_x, dst_y
int rectxy2fisheyexy(double src_x, double src_y, 
					  double *dst_x, double *dst_y,
					  double center_x, double center_y,
					  int image_width,
					  double R)
{
	double phi;
	double theta;
	double D = sqrt( R * R - image_width*image_width/4);

	src_x -= center_x;
	src_y -= center_y;

	phi = atan( sqrt( double(src_x*src_x+src_y*src_y))/ D );
	theta = atan2(src_y, src_x);

	*dst_x = R * sin(phi) * cos(theta) + center_x;
	*dst_y = R * sin(phi) * sin(theta) + center_y;

	return 0;
}
int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " filename.jpg" << endl;
        return -1;
    }
	// read a fisheye image
    Mat input = imread(argv[1]);
	if(input.empty())
	{
		cerr << "Cannot read input image file " << argv[1] << endl;
		return -1;
	}
	double fisheye_radius = 1500; //you can adjust the parameter in range [1500, +INF]
    int input_width = input.cols;
    int input_height = input.rows;
	// the output image is 1.25x large
    int output_width = cvRound(input_width*1.25);
    int output_height = cvRound(input_height*1.25);
    Mat output(output_height, output_width, input.type(), Scalar(0,0,0));
	// copy each pixel from the fisheye image
	// the current implementation is using NN
	// bilinear interpolation can make the result more smooth
    for ( int r = 0; r < output.rows; r++)
        for ( int c = 0; c < output.cols; c++)
        {
            double src_r = 0;
            double src_c = 0;
            rectxy2fisheyexy(c-(output_width-input_width)/2 , r-(output_height-input_width)/2, &src_c, &src_r,
					  input_width/2.0, input_height/2.0,
                      input_width, fisheye_radius);
            // copy the current pixel if it's in the range
            if ( src_r > 0 && src_r < input_height-1 && src_c > 0 && src_c < input_width-1)
				//using pointer nor at() functioin can gain better performance
                output.at<Vec3b>(r, c) = input.at<Vec3b>( cvRound(src_r), cvRound(src_c));
        }
	// save the result and show it in a window
    imwrite("result.jpg", output);
    imshow("result", output);
    waitKey(0);
    return 0;
}
