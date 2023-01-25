/* 
Filter library
Include file
*/

// function converting inputted Mat into greyscale
int greyscale( cv::Mat &src, cv::Mat &dst );

// function (gaussian) blurring inputted Mat
int blur5x5( cv::Mat &src, cv::Mat &dst );

// function that applies 3X3 horizontal sobel filter (positive is right)
int sobelX3x3( cv::Mat &src, cv::Mat &dst );

// function that applies 3X3 vertical sobel filter (positive is top)
int sobelY3x3( cv::Mat &src, cv::Mat &dst );

// function that generates a gradient magnitude image from the X and Y Sobel images
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );

// function to blur and quantize inputted image to the inputted level
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );

// function to cartoonify an inputted image
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold );

// makes a negative of the inputted (src) image
int negative( cv::Mat &src, cv::Mat &dst );
