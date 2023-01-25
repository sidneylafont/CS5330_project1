#include <opencv2/opencv.hpp>
#include <iostream>
#include "filter.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat image;
    Mat o_image;
    image = cv::imread("turbine.jpg", IMREAD_COLOR);
    o_image = cv::imread("turbine.jpg", IMREAD_COLOR);
    if(! image.data)
        {
            std::cout<<"Could not open file" << std::endl;
            return -1;
        }

    //filter type currently applied
    char filter = 'o';

    while (true) {
        cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
        cv::imshow("img", image);
        int x = cv::waitKey(0);
        //converting picture into normal RGB
        if (x == 'o') {
            filter = 'o';
        }

        //converting picture into greyscale
        if (x == 'g') {
            filter = 'g';
        }

        //converting picture into greyscale alternative
        if (x == 'h') {
            filter = 'h';
        }

        //converting picture into blur
        if (x == 'b') {
            filter = 'b';
        }

        //converting picture into sobel horizontal
        if (x == 'x') {
            filter = 'x';
        }

        //converting picture into sobel vertical
        if (x == 'y') {
            filter = 'y';
        }

        //converting picture into gradient magnitude image from the X and Y Sobel images
        if (x == 'm') {
            filter = 'm';
        }

        //blur and quantize picture
        if (x == 'l') {
            filter = 'l';
        }

        //cartoonify picture
        if (x == 'c') {
            filter = 'c';
        }

        //negative picture
        if (x == 'n') {
            filter = 'n';
        }

        //HSV picture
        if (x == 'v') {
            filter = 'v';
        }

        //displaying the image (with filter)
        if (filter == 'g') {
            Mat g_image;
            //convert to greyscale using cvtColor
            cv::cvtColor(o_image, g_image, cv::COLOR_BGR2GRAY);
            image = g_image;
            cv::imshow("img", image);
        } else if (filter == 'h') {
            cv::Mat g_alt_image;
            //convert to greyscale with my greyscale function
            greyscale( o_image, g_alt_image );
            image = g_alt_image;
            cv::imshow("img", image); 
        } else if (filter == 'b') {
            cv::Mat g_blur;
            //blur image
            blur5x5( o_image, g_blur );
            image = g_blur;
            cv::imshow("img", image);
        } else if (filter == 'x') {
            cv::Mat x_sobel;
            sobelX3x3( o_image, x_sobel );
            cv::Mat x_sobel_abs;
            cv::convertScaleAbs(x_sobel, x_sobel_abs);
            image = x_sobel_abs;
            cv::imshow("img", image);
        } else if (filter == 'y') {
            cv::Mat y_sobel;
            sobelY3x3( o_image, y_sobel );
            cv::Mat y_sobel_abs;
            cv::convertScaleAbs(y_sobel, y_sobel_abs);
            image = y_sobel_abs;
            cv::imshow("img", image);
        } else if (filter == 'm') {
            cv::Mat x_sobel;
            sobelX3x3( o_image, x_sobel );
            cv::Mat y_sobel;
            sobelY3x3( o_image, y_sobel );

            cv::Mat g_mag;
            magnitude(x_sobel, y_sobel, g_mag);
            cv::Mat g_mag_abs;
            cv::convertScaleAbs(g_mag, g_mag_abs);
            image = g_mag_abs;

            cv::imshow("img", image);
        } else if (filter == 'l') {
            cv::Mat quant;
            blurQuantize( o_image, quant, 10 );
            image = quant;
            cv::imshow("img", image);            
        } else if (filter == 'c') {
            cv::Mat c_frame;
            cartoon( o_image, c_frame, 10, 10 );
            image = c_frame;
            cv::imshow("img", image);
        } else if (filter == 'n') {
            cv::Mat neg;
            negative( o_image, neg);
            image = neg;
            cv::imshow("img", image);
        } else if (filter == 'o') {
            //normal color image
            image = cv::imread("turbine.jpg", IMREAD_COLOR);
            cv::imshow("img", image);
        } else if (filter == 'v') {
            cv::Mat hsv;
            //convert to HSV using cvtColor
            cv::cvtColor(o_image, hsv, cv::COLOR_BGR2HSV);
            image = hsv;
            cv::imshow("img", image); 
        }
        
        //saving image
        if (x == 's') {
            imwrite("saved_img.jpg", image);
        }

        if (x == 'q') {
            return 0;
        }
    }
}

