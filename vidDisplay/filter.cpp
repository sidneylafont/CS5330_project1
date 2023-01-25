/* 
Filter library
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>
#include "filter.h"

using namespace cv;
using namespace std;

// src: input image
// dst: output image, input image converted to greyscale
int greyscale( cv::Mat &src, cv::Mat &dst ) {

    //allocate dst image
    dst = cv::Mat::zeros( src.size(), src.type());

    //loop through input image rows and convert to greyscale
    for(int i=0; i<src.rows; i++) {
        //src row pointer
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);

        //destination pointer
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);

        // loop through column in src
        for(int j=0;j<src.cols;j++) {

            int B = rptr[j][0];
            int R = rptr[j][1];
            int G = rptr[j][2];

            //converting to greyscale using the average color
            int avg_color = (B + R + G) / 3;


            dptr[j][0] = avg_color;
            dptr[j][1] = avg_color;
            dptr[j][2] = avg_color;
    }
  }

    //returns 0 if completed without error
    return (0);

}


// src: input image
// dst: output image, input image with 5X5 gaussian blur applied
int blur5x5( cv::Mat &src, cv::Mat &dst ) {

    //allocating dst image
    dst = cv::Mat::zeros( src.size(), src.type() );
    cv::Mat temp = dst.clone();

    //seperable filter
    int filter[] = {1,2,4,2,1};
    


    // applying filter across rows
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                int sum = 0;
                if ((i > src.rows - 3) || (j > src.cols - 3) || (i < 3) || (j < 3)) {
                    temp.at<cv::Vec3b>(i,j)[c] = src.at<cv::Vec3b>(i,j)[c];
                } else {
                    for(int x=-2;x<=2;x++) {
                        sum = sum + (filter[x+2] * src.at<cv::Vec3b>(i-x,j)[c]);
                    }
                    temp.at<cv::Vec3b>(i,j)[c] = sum / 10;
                }
            }
        }
    }

    // applying filter across cols
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                int sum = 0;
                if ((i > src.rows - 3) || (j > src.cols - 3) || (i < 3) || (j < 3)) {
                    dst.at<cv::Vec3b>(i,j)[c] = src.at<cv::Vec3b>(i,j)[c];
                } else {
                    for(int x=-2;x<=2;x++) {
                        sum = sum + (filter[x+2] * temp.at<cv::Vec3b>(i,j-x)[c]);
                    }
                    dst.at<cv::Vec3b>(i,j)[c] = sum / 10;
                }
            }
        }
    }

    //returns 0 if completed without error
    return (0);
}


// src: input image
// dst: output image, input image with 3X3 horizonatal sobel filter applied
int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {
    //allocating dst image
    dst = cv::Mat::zeros( src.size(), CV_16SC3 );
    cv::Mat temp = dst.clone();

    //seperable filters
    int filter_h[] = {-1,0,1};
    int filter_v[] = {1,2,1};


    // applying filter across rows
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                int sum = 0;
                if ((i > src.rows - 2) || (j > src.cols - 2) || (i < 2) || (j < 2)) {
                    temp.at<cv::Vec3s>(i,j)[c] = 0;
                } else {
                    for(int x=-1;x<=1;x++) {
                        sum = sum + (filter_h[x+1] * src.at<cv::Vec3b>(i-x,j)[c]);
                    }
                    temp.at<cv::Vec3s>(i,j)[c] = sum / 4;
                }
            }
        }
    }

    // applying filter across cols
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                int sum = 0;
                if ((i > src.rows - 2) || (j > src.cols - 2) || (i < 2) || (j < 2)) {
                    dst.at<cv::Vec3s>(i,j)[c] = 0;
                } else {
                    for(int x=-1;x<=1;x++) {
                        sum = sum + (filter_v[x+1] * temp.at<cv::Vec3s>(i,j-x)[c]);
                    }
                    dst.at<cv::Vec3s>(i,j)[c] = sum;
                }
            }
        }
    }

    //returns 0 if completed without error
    return (0);
}


// src: input image
// dst: output image, input image with 3X3 vertical sobel filter applied
int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
    //allocating dst image
    dst = cv::Mat::zeros( src.size(), CV_16SC3 );
    cv::Mat temp = dst.clone();

    //seperable filters
    int filter_h[] = {1,2,1};
    int filter_v[] = {1,0,-1};
    


    // applying filter across rows
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                int sum = 0;
                if ((i > src.rows - 2) || (j > src.cols - 2) || (i < 2) || (j < 2)) {
                    temp.at<cv::Vec3s>(i,j)[c] = 0;
                } else {
                    for(int x=-1;x<=1;x++) {
                        sum = sum + (filter_h[x+1] * src.at<cv::Vec3b>(i-x,j)[c]);
                    }
                    temp.at<cv::Vec3s>(i,j)[c] = sum / 4;
                }
            }
        }
    }

    // applying filter across cols
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                int sum = 0;
                if ((i > src.rows - 2) || (j > src.cols - 2) || (i < 2) || (j < 2)) {
                    dst.at<cv::Vec3s>(i,j)[c] = 0;
                } else {
                    for(int x=-1;x<=1;x++) {
                        sum = sum + (filter_v[x+1] * temp.at<cv::Vec3s>(i,j-x)[c]);
                    }
                    dst.at<cv::Vec3s>(i,j)[c] = sum;
                }
            }
        }
    }

    //returns 0 if completed without error
    return (0);
}


// function that generates a gradient magnitude image from the X and Y Sobel images
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {

    //allocating dst image
    dst = cv::Mat::zeros( sx.size(), CV_16UC3 );

    for(int i=0;i<sx.rows;i++){
        for(int j=0;j<sx.cols;j++){
            for(int c=0;c<3;c++)  {
                signed short x = sx.at<cv::Vec3s>(i,j)[c];
                signed short y = sy.at<cv::Vec3s>(i,j)[c];
                dst.at<cv::Vec3s>(i,j)[c] = sqrt((x*x) + (y*y));
            }
        }
    }

    //returns 0 if completed without error
    return (0);
}

// function to blur and quantize inputted image to the inputted level
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ) {

    //allocating dst image
    dst = cv::Mat::zeros( src.size(), src.type() );

    //blurring image
    cv::Mat g_blur;
    blur5x5( src, g_blur );

    int b = 255 / levels;

    for(int i=0;i<g_blur.rows;i++){
        for(int j=0;j<g_blur.cols;j++){
            for(int c=0;c<3;c++)  {
                int x_t = g_blur.at<cv::Vec3b>(i,j)[c] / b;
                int x_f = x_t * b;
                dst.at<cv::Vec3b>(i,j)[c] = x_f;
            }
        }
    }

    //returns 0 if completed without error
    return (0);
}


// function to cartoonify an inputted image
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ) {

    //allocating dst image
    dst = cv::Mat::zeros( src.size(), src.type() );

    cv::Mat x_sobel;
    sobelX3x3( src, x_sobel );
    cv::Mat y_sobel;
    sobelY3x3( src, y_sobel );

    cv::Mat g_mag;
    magnitude(x_sobel, y_sobel, g_mag);
    cv::Mat g_mag_abs;
    cv::convertScaleAbs(g_mag, g_mag_abs);

    blurQuantize( src, dst, levels);

    for(int i=0;i<g_mag_abs.rows;i++){
        for(int j=0;j<g_mag_abs.cols;j++){
            if ((g_mag_abs.at<cv::Vec3b>(i,j)[0] > magThreshold) && (g_mag_abs.at<cv::Vec3b>(i,j)[1] > magThreshold) && (g_mag_abs.at<cv::Vec3b>(i,j)[2] > magThreshold)) {
                dst.at<cv::Vec3b>(i,j)[0] = 0;
                dst.at<cv::Vec3b>(i,j)[1] = 0;
                dst.at<cv::Vec3b>(i,j)[2] = 0;
            }
        }
    }

    //returns 0 if completed without error
    return (0);
}


// makes a negative of the inputted (src) image
int negative( cv::Mat &src, cv::Mat &dst ) {

    //allocating dst image
    dst = cv::Mat::zeros( src.size(), src.type() );

    for(int i=0;i<src.rows;i++){

        //src row pointer
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);

        //destination pointer
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);

        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++)  {
                dptr[j][c] = 255 - rptr[j][c];
            }
        }
    }

    //returns 0 if completed without error
    return (0);

}

