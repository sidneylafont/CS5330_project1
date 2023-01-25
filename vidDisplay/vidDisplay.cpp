#include <opencv2/opencv.hpp>
#include <iostream>
#include "filter.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
        cv::VideoCapture *capdev;

        // open the video device
        capdev = new cv::VideoCapture(0);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }

        // get some properties of the image
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                        (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);

        cv::namedWindow("Video", 1); // identifies a window
        cv::Mat frame;

        //filter type currently applied
        char filter = 'o';

        //stuff for saving video 
        bool video = false;
        VideoWriter video_writer("video.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, refS);

        for(;;) {
                *capdev >> frame; // get a new frame from the camera, treat as a stream
                if( frame.empty() ) {
                    printf("frame is empty\n");
                    break;
                }   
                
                // see if there is a waiting keystroke
                char key = cv::waitKey(10);

                //converting stream into normal RGB
                if (key == 'o') {
                    filter = 'o';
                }

                //converting stream into greyscale
                if (key == 'g') {
                    filter = 'g';
                }

                //converting stream into greyscale alternative
                if (key == 'h') {
                    filter = 'h';
                }

                //converting stream into blur
                if (key == 'b') {
                    filter = 'b';
                }

                //converting stream into sobel horizontal
                if (key == 'x') {
                    filter = 'x';
                }

                //converting stream into sobel vertical
                if (key == 'y') {
                    filter = 'y';
                }

                //converting stream into gradient magnitude image from the X and Y Sobel images
                if (key == 'm') {
                    filter = 'm';
                }

                //blur and quantize stream
                if (key == 'l') {
                    filter = 'l';
                }

                //cartoonify stream
                if (key == 'c') {
                    filter = 'c';
                }

                //negative stream
                if (key == 'n') {
                    filter = 'n';
                }

                //HSV stream
                if (key == 'v') {
                    filter = 'v';
                }


                //saving video
                if( key == 'r') {
                    video = !video;
                }

                //displays frame
                if (filter == 'g') {
                    Mat g_image;
                    //convert to greyscale using cvtColor
                    cv::cvtColor(frame, g_image, cv::COLOR_BGR2GRAY);
                    cv::imshow("Video", g_image);

                    //convert back into video saving format
                    Mat g_image_save;
                    //convert to greyscale using cvtColor
                    greyscale( frame, g_image_save );
                    frame = g_image_save;


                } else if (filter == 'h') {
                    cv::Mat g_alt_image;
                    //convert to greyscale with my greyscale function
                    greyscale( frame, g_alt_image );
                    frame = g_alt_image;
                    cv::imshow("Video", frame); 
                } else if (filter == 'b') {
                    cv::Mat g_blur;
                    //blur image
                    blur5x5( frame, g_blur );
                    frame = g_blur;
                    cv::imshow("Video", frame);
                    
                } else if (filter == 'x') {
                    cv::Mat x_sobel;
                    sobelX3x3( frame, x_sobel );
                    cv::Mat x_sobel_abs;
                    cv::convertScaleAbs(x_sobel, x_sobel_abs);
                    frame = x_sobel_abs;
                    cv::imshow("Video", frame);
                    
                } else if (filter == 'y') {
                    cv::Mat y_sobel;
                    sobelY3x3( frame, y_sobel );
                    cv::Mat y_sobel_abs;
                    cv::convertScaleAbs(y_sobel, y_sobel_abs);
                    frame = y_sobel_abs;
                    cv::imshow("Video", frame);
                    
                } else if (filter == 'm') {
                    cv::Mat x_sobel;
                    sobelX3x3( frame, x_sobel );
                    cv::Mat y_sobel;
                    sobelY3x3( frame, y_sobel );

                    cv::Mat g_mag;
                    magnitude(x_sobel, y_sobel, g_mag);
                    cv::Mat g_mag_abs;
                    cv::convertScaleAbs(g_mag, g_mag_abs);
                    frame = g_mag_abs;

                    cv::imshow("Video", frame);
                    
                } else if (filter == 'l') {
                    cv::Mat quant;
                    blurQuantize( frame, quant, 10 );
                    frame = quant;
                    cv::imshow("Video", frame);
                    
                } else if (filter == 'c') {
                    cv::Mat c_frame;
                    cartoon( frame, c_frame, 10, 10 );
                    frame = c_frame;
                    cv::imshow("Video", frame);
                    
                } else if (filter == 'n') {
                    cv::Mat neg;
                    negative( frame, neg);
                    frame = neg;
                    cv::imshow("Video", frame);
                    
                } else if (filter == 'o') {
                    //normal color frame
                    cv::imshow("Video", frame);
                } else if (filter == 'v') {
                    cv::Mat hsv;
                    //convert to HSV using cvtColor
                    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
                    frame = hsv;
                    cv::imshow("Video", frame); 
                }

                if (video) {
                    video_writer.write(frame);
                }          

                //quit video
                if( key == 'q') {
                    break;
                }

                //saving image
                if (key == 's') {
                    imwrite("saved_img.jpg", frame);
                }
        }

        video_writer.release();
        delete capdev;
        return(0);
}