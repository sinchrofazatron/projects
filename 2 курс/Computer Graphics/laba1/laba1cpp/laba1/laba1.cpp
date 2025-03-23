#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <math.h>
#include <fstream>
using namespace std;
using namespace cv;

void black(Mat img, String windowName) {
    namedWindow(windowName);
    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star(Mat img, String windowName) {
    int x1 = 100, y1 = 100;
    int count = 5;
    float step = 1.0 / count;

    for (int k = 0; k < 13; k++) {
        int x2 = 100 + 95 * cos(2 * CV_PI * k / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * k / 13);

        for (float t = 0; t < 1; t += step) {
            int x = round((1 - t) * x1 + t * x2);
            int y = round((1 - t) * y1 + t * y2);
            img.at<Vec3b>(Point(x, y)) = 255;
        }
    }

    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star1.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star2(Mat img, String windowName) {

    int x1 = 100, y1 = 100;

    for (int i = 0; i < 13; i++) {
        int x2 = 100 + 95 * cos(2 * CV_PI * i / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * i / 13);

        float count = sqrt((x1 - x2)^2 + (y1 - y2)^2);

        float step = 1.0 / count;
        for (float t = 0; t < 1; t += step) {
            int x = round((1 - t) * x1 + t * x2);
            int y = round((1 - t) * y1 + t * y2);
            img.at<Vec3b>(Point(x, y)) = 255;
        }
    }
    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star2.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star3(Mat img, String windowName) {
    int x1 = 100, y1 = 100;

    for (int i = 0; i < 13; i++) {
        int x2 = 100 + 95 * cos(2 * CV_PI * i / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * i / 13);
        
        cout << i;

        for (int x = x1; x < x2; x++) {
            float t = (x - x1)*1.0 / (x2 - x1);
            int y = round((1 - t) * y1 + t * y2);
            img.at<Vec3b>(Point(x, y)) = 255;
        }
    }
    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star3.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star3fix(Mat img, String windowName) {
    int x1 = 100, y1 = 100;

    for (int i = 0; i < 13; i++) {
        int x2 = 100 + 95 * cos(2 * CV_PI * i / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * i / 13);

        for (int x = x1; x < x2; x++) {
            if (x1 > x2) {
                int a = x1;
                x1 = x2;
                x2 = a;

                int b = y1;
                y1 = y2;
                y2 = b;
            }

            float t = (x - x1)*1.0 / (x2 - x1);
            int y = round((1 - t) * y1 + t * y2);
            img.at<Vec3b>(Point(x, y)) = 255;
        }
    }
    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star3fix.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star3fix2(Mat img, String windowName) {
    int x1 = 100, y1 = 100;

    for (int i = 0; i < 13; i++) {
        int x2 = 100 + 95 * cos(2 * CV_PI * i / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * i / 13);

        bool xchange = false;
        if (abs(x1 - x2) < abs(y1 - y2)) {
            int a = x1;
            x1 = y1;
            y1 = a;

            int b = x2;
            x2 = y2;
            y2 = b;
            xchange = true;
        }

        for (int x = x1; x < x2; x++) {

            if (x1 > x2) {
                int a = x1;
                x1 = x2;
                x2 = a;

                int b = y1;
                y1 = y2;
                y2 = b;
            }          

            float t = (x - x1)*1.0 / (x2 - x1);
            int y = round((1 - t) * y1 + t * y2);            
            if (xchange) {
                img.at<Vec3b>(Point(x, y)) = 255;
            }
            else 
            { 
                img.at<Vec3b>(Point(y, x)) = 255; 
            }
        }
    }
    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star3fix2.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star4(Mat img, String windowName) {
    
    for (int i = 0; i < 13; i++) {
        int x1 = 100, y1 = 100;
        int x2 = 100 + 95 * cos(2 * CV_PI * i / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * i / 13);

        bool xchange = false;
        if (abs(x1 - x2) < abs(y1 - y2)) {
            int a = x1;
            x1 = y1;
            y1 = a;

            int b = x2;
            x2 = y2;
            y2 = b;
            xchange = true;
        }

        if (x1 > x2) {
            int a = x1;
            x1 = x2;
            x2 = a;

            int b = y1;
            y1 = y2;
            y2 = b;
        }

        int y = y1;
        float dy = 2.0*(x2 - x1)*abs((y2-y1)*1.0/(x2-x1));
        float derror = 0.0;
        int y_update;

        if (y2 > y1) {
            y_update = 1;
        }
        else {
            y_update = -1;
        }       

        for (int x = x1; x < x2; x++) {
            if (xchange) {
                img.at<Vec3b>(Point(x, y)) = 255;
            }
            else
            {
                img.at<Vec3b>(Point(y, x)) = 255;
            }

            derror += dy;
            if (derror > 2.0 * (x2 - x1)*0.5) {
                derror -= 2.0 * (x2 - x1)*1.0;
                y += y_update;
            }
        }  
    }
    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star4.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

void star5(Mat img, String windowName) {

    for (int i = 0; i < 13; i++) {
        int x1 = 100, y1 = 100;
        int x2 = 100 + 95 * cos(2 * CV_PI * i / 13);
        int y2 = 100 + 95 * sin(2 * CV_PI * i / 13);

        bool xchange = false;
        if (abs(x1 - x2) < abs(y1 - y2)) {
            int a = x1;
            x1 = y1;
            y1 = a;

            int b = x2;
            x2 = y2;
            y2 = b;
            xchange = true;
        }

        if (x1 > x2) {
            int a = x1;
            x1 = x2;
            x2 = a;

            int b = y1;
            y1 = y2;
            y2 = b;
        }

        int y = y1;
        float dy = 2.0 * abs((y2 - y1) * 1.0);
        float derror = 0.0;
        int y_update;

        if (y2 > y1) {
            y_update = 1;
        }
        else {
            y_update = -1;
        }

        for (int x = x1; x < x2; x++) {
            if (xchange) {
                img.at<Vec3b>(Point(x, y)) = 255;
            }
            else
            {
                img.at<Vec3b>(Point(y, x)) = 255;
            }

            derror += dy;
            if (derror > (x2 - x1)) {
                derror -= 2.0 * (x2 - x1) * 1.0;
                y += y_update;
            }
        }
    }
    bool write = imwrite("C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1cpp/star5.jpg", img);

    imshow(windowName, img);
    waitKey(0);
    destroyWindow(windowName);
}

int main()
{
    Mat img(200, 200, CV_8UC3, Scalar(0, 0, 0));
    String windowName = "Star1";
    //String filename = "C:/Users/vadav/Desktop/Лабы/2 курс/Компьютерная графика/laba1/model_1.obj";

    //black(img, windowName);
    //star(img, windowName);
    //star2(img, windowName);
    //star3(img, windowName);
    //star3fix(img, windowName);
    //star3fix2(img, windowName);
    //star4(img, windowName);
    star5(img, windowName);
    return 0;
    

}

