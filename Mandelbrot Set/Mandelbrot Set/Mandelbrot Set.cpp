// Mandelbrot Set.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <thread>
using namespace std;



class Pixel
{
    public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;

};



void setPixel(int widthIndex, int heightIndex, Pixel pixel);
void setPixel(int widthIndex, int heightIndex, unsigned char red, unsigned char green, unsigned char blue);
void mapPixel(int widthIndex, int heightIndex, float* realComponent, float* imaginaryComponent);
Pixel interateZ(float realComponent, float imaginaryComponent, int iterations);
void normalize(float real, float imaginary);
void threadTest();
void threadTestLetter();
int width;
int height;
Pixel* buffer;
char* iterationBuffer;
float realCenter;
float imaginaryCenter;
float mandelbrotWidth;
float mandelbrotHeight;
float iterations;


void main()
{
    //------------------------------------Creating pixel buffer----------------------------------------------------------
    cout << "Enter height of the image" << endl;
    cin >> height;
    cout << "Enter width of the image" << endl;
    cin >> width;
    buffer = (Pixel*)malloc(width * height * 3);
    iterationBuffer = (char*)malloc(width * height);
    //------------------------------------Setting mandelbrot coordinate bounds----------------------------------------------
 
    cout << "Enter real coordinate of the center" << endl;
    cin >> realCenter;
    cout << "Enter imaginary cooridnate of the center" << endl;
    cin >> imaginaryCenter;
    cout << "Enter the width of the mandelbrot set" << endl;
    cin >> mandelbrotWidth;
    cout << "Enter how many iterations you want" << endl;
    cin >> iterations;
    mandelbrotHeight = mandelbrotWidth * (float)height / (float)width;
    
   

    float real;
    float imaginary;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mapPixel(j, i, &real, &imaginary);
            setPixel(j, i, interateZ(real, imaginary, iterations));
        }
    }

    stbi_write_png("zoom.png", width, height, 3, buffer, 3 * width);

}

void setPixel(int widthIndex, int heightIndex, Pixel pixel)
{
    buffer[(heightIndex * width + widthIndex)] = pixel;

}
void setPixel(int widthIndex, int heightIndex, unsigned char red, unsigned char green, unsigned char blue)
{
    Pixel p = { red, green, blue };
    setPixel(widthIndex, heightIndex, p);
}
void mapPixel(int widthIndex, int heightIndex, float* realComponent, float* imaginaryComponent)
{
    *realComponent = (((float)widthIndex / (float)(width - 1)) - 0.5) * mandelbrotWidth + realCenter;
    *imaginaryComponent = (((float)heightIndex / (float)(height - 1)) - 0.5) * mandelbrotHeight + imaginaryCenter;
}

/*
Pixel interateZ(float realComponent, float imaginaryComponent, int iterations, int widthIndex, int heightIndex)
{
    float zr = 0;
    float zc = 0;
    int i;
    Pixel p;
    for (i = 0; i < iterations && zr * zr + zc * zc < 4; i++)
    {
        float zrt = zr * zr - zc * zc + realComponent;
        zc = 2 * zr * zc + imaginaryComponent;
        zr = zrt;

    }
    iterationBuffer[(heightIndex * width + widthIndex)] = i;

    if (i == iterations)
    {
        p = { 0, 0, 0 };
    }
    else
    {
        p = { (unsigned char)(255 - (i * 255 / iterations)), 0, 0 };
    }
    return p;
}

void normalize(float real, float imaginary)
{
    int maxIterations = 0;
    int minIterations = iterationBuffer[(0)];
    int averageIterations;
    int totalIterations = 0;
    
    for (int i = 0; i < width * height; i++)
    {
        totalIterations = totalIterations + iterationBuffer[(i)];
        if(iterationBuffer[(i)] > maxIterations)
        {
            maxIterations = iterationBuffer[(i)];
        }
        if (iterationBuffer[(i)] < minIterations)
        {
            minIterations = iterationBuffer[(i)];
        }
    }
    averageIterations = totalIterations / (width * height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mapPixel(j, i, &real, &imaginary);
            setPixel(j, i, (255 - (i * 255 / iterationBuffer[(i * width + j)])), 0, 0);
        }
    }

    cout << minIterations << " - " << maxIterations << endl;
    cout << "Average Iterations: " << averageIterations << endl;

    
}
*/



Pixel interateZ(float realComponent, float imaginaryComponent, int iterations)
{
    float zr = 0;
    float zc = 0;
    int i;
    Pixel p;
    for (i = 0; i < iterations && zr*zr +zc*zc < 4; i++)
    {
        float zrt = zr*zr - zc*zc + realComponent;
        zc = 2 * zr * zc + imaginaryComponent;
        zr = zrt;

    }

    if (i == iterations )
    {
        p = { 0, 0, 0 };
    }
    else
    {
        p = {(unsigned char)(255 - (i*255/iterations)), 0, 50 };
    }
    
    return p;
}



