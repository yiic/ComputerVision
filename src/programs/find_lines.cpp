//============================================================
//  File:       find_lines.cpp
//  Purpose:    Find line equations for edge points in an image. 
//  Author:     John Gauch
//  Date:       Fall 2017
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include <iostream>
#include <fstream>
using namespace std;

const float INLIER_DISTANCE = 5.0;
const int NUM_ITERATIONS = 10000;

//============================================================
float point_line_distance(float x, float y, float M, float B)
{  
   // Calculate distance from point to line
   return fabs(B + M * x - y) / sqrt(1 + M * M);
}

//============================================================
float average_line_distance(float x[], float y[], int count, 
   float M, float B)
{  
   // Calculate distance from point to line
   float total = 0;
   for (int i=0; i<count; i++)
      total += point_line_distance(x[i], y[i], M, B);
   return total / count;
}

//============================================================
void bounding_box_line(float x[], float y[], int count, 
   float &M, float &B)
{  
   // Calculate min and max (x,y) values
   int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
   for (int i=1; i<count; i++)
   {  
      if (x[min_x] > x[i]) min_x = i;
      if (x[max_x] < x[i]) max_x = i;
      if (y[min_y] > y[i]) min_y = i;
      if (y[max_y] < y[i]) max_y = i;
   }
   
   // Calculate line equation 
   float size_x = x[max_x] - x[min_x];
   float size_y = y[max_y] - y[min_y];
   if ((size_x > size_y) && (x[max_x] != x[min_x]))
   {  
      M = (y[max_x] - y[min_x]) / (x[max_x] - x[min_x]);
      B = y[min_x] - M * x[min_x];
   }
   else if (x[max_y] != x[min_y])
   {  
      M = (y[max_y] - y[min_y]) / (x[max_y] - x[min_y]);
      B = y[min_y] - M * x[min_y];
   }
}

//============================================================
void least_square_line(float x[], float y[], int count, 
   float &M, float &B)
{
   // Calculate sums of (x,y) values
   float Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
   for (int i=0; i<count; i++)
   {
      Sx += x[i];
      Sy += y[i];
      Sxx += x[i] * x[i];
      Sxy += x[i] * y[i];
   }
  
   // Calculate line equation
   float denominator = count * Sxx - Sx * Sx;
   if (denominator != 0)
   {
      M = (-Sx * Sy + count * Sxy) / denominator;
      B = (Sxx * Sy - Sx * Sxy) / denominator;
   }
}

//============================================================
void random_line(float x[], float y[], int count,
   float &M, float &B, int &inlier_count, float &inlier_distance) 
{
   // Choose two points at random
   int index1 = random() % count;
   int index2 = random() % count;

   // Calulate line equation from two points
   M = (y[index2] - y[index1]) / (x[index2] - x[index1]);
   B = y[index1] - M * x[index1];

   // Select points that are close to line
   inlier_count = 0;
   float inlier_x[count];
   float inlier_y[count];
   for (int i=0; i<count; i++)
   {
      if (point_line_distance(x[i], y[i], M, B) <= INLIER_DISTANCE)
      {
         inlier_x[inlier_count] = x[i];
         inlier_y[inlier_count] = y[i];
         inlier_count++;
      }
   }

   // Calculate least squares line equation
   least_square_line(inlier_x, inlier_y, inlier_count, M, B);

   // Calculate distance from points to line
   inlier_distance = average_line_distance(inlier_x, inlier_y, 
      inlier_count, M, B);
}

//============================================================
void process(string Name1, string Name2)
{
   // Read parameters from user
   cout << "Enter size of Gaussian blur filter: ";
   float Sigma = 0;
   cin >> Sigma;
   cout << "Enter gradient threshold: ";
   float Threshold = 0;
   cin >> Threshold;
   cout << "Enter maximum inlier pixel distance: ";
   float InlierDistance = 0;
   cin >> InlierDistance;
   cout << "Enter minimum inlier pixel count: ";
   float InlierCount = 0;
   cin >> InlierCount;

   // Read input image
   im_float Input;
   Input.ReadJpg((char *)Name1.c_str());
   int Xdim = Input.Xdim;
   int Ydim = Input.Ydim;

   // Create ouput image
   im_color Output;
   Output.ReadJpg((char *)Name1.c_str());

   // Perform Gaussian smoothing
   Input.Gaussian(Sigma);

   // Create gradient image
   im_float Gradient(Input);
   Gradient.Gradient();
   Gradient.WriteJpg((char *)"gradient.jpg");

   // Create edge image
   im_short Edge(Gradient);
   Edge.Threshold(Threshold);
   Edge.WriteJpg((char *)"edge.jpg");

   // Find collection of line equations
   float X[Xdim*Ydim];
   float Y[Xdim*Ydim];
   for (int i = 0; i < NUM_ITERATIONS; i++)
   {
      // Loop over gradient image to find edges
      int Count = 0;
      for (int y = 1; y < Ydim - 1; y++)
      for (int x = 1; x < Xdim - 1; x++)
      if (Gradient.Data2D[y][x] >= Threshold)
      {
         X[Count] = x;
         Y[Count] = y;
         Count++;
      }
   
      // Fit line equation to the data
      int inlier_count = 0;
      float M = 0, B = 0, inlier_distance = 0;
      random_line(X, Y, Count, M, B, inlier_count, inlier_distance);

      // Keep only the good lines
      if ((inlier_count > InlierCount) && (inlier_distance < InlierDistance))
      {
         // Print line information
         cout << endl << "Number of edge pixels found: " << Count << endl;
         cout << "Inlier pixel count: " << inlier_count << endl;
         cout << "Inlier pixel distance: " << inlier_distance << endl;
         cout << "Line equation: y = " << M << "x + " << B << endl;

         // Draw line in output image
         Output.DrawLine(M, B, 2, 0, 0, 255);

         // Remove points from gradient image
         Gradient.DrawLine(M, B, INLIER_DISTANCE, 0);
      }
   }

   // Write outout images
   Output.WriteJpg((char *)Name2.c_str());
}

//============================================================
int main(int argc, char *argv[])
{
   // Get input file name
   string Name1;
   string Name2;
   if (argc == 3)
   {
      Name1 = argv[1];
      Name2 = argv[2];
   }
   else
   {
      cout << "Enter name of input image: ";
      cin >> Name1;
      cout << "Enter name of output image: ";
      cin >> Name2;
   }

   // Process input image
   process(Name1, Name2);
}
