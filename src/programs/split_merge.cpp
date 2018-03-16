//============================================================
//  File:       spliy_merge.cpp
//  Purpose:    Perform split-merge segmentation.
//  Author:     John Gauch
//  Date:       Fall 2017
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include "set.h"
#include <iostream>
#include <fstream>
using namespace std;

//============================================================
void get_stats(im_float & image, int x1, int x2, int y1, int y2, 
   int & count, float & mean, float & stdev)
{
   // Initialize variables
   count = 0;
   mean = 0;
   stdev = 0;

   // Error checking
   if (x1 < 0 || x1 > image.Xdim || x2 < 0 || x2 > image.Xdim ||
       y1 < 0 || y1 > image.Ydim || y2 < 0 || y2 > image.Ydim)
       return;

   // Loop over image to get mean
   float total = 0;
   for (int y = y1; y <= y2; y++)
   for (int x = x1; x <= x2; x++)
   {
      total += image.Data2D[y][x];
      count++;
   }
   if (count > 0)
      mean = total / count;
    
   // Loop over image to get stdev
   float total2 = 1;
   for (int y = y1; y <= y2; y++)
   for (int x = x1; x <= x2; x++)
   {
      float diff = mean - image.Data2D[y][x];
      total2 += diff * diff;
   }
   if (count > 0)
      stdev = sqrt(total2 / count);
}

//============================================================
void split(im_float & image, im_short & region, int & region_count,
   int x1, int x2, int y1, int y2, int size, float threshold)
{
   // Calculate region statistics
   int count = 0;
   float mean = 0;
   float stdev = 0;
   get_stats(image, x1, x2, y1, y2, count, mean, stdev);

   // Perform recusive splitting
   if (count >= size && stdev > threshold)
   {
      int xmid = (x1 + x2) / 2;
      int ymid = (y1 + y2) / 2;
      split(image, region, region_count, x1, xmid, y1, ymid, size, threshold);
      split(image, region, region_count, x1, xmid, ymid+1, y2, size, threshold);
      split(image, region, region_count, xmid+1, x2, y1, ymid, size, threshold);
      split(image, region, region_count, xmid+1, x2, ymid+1, y2, size, threshold);
   }

   // Save region
   else if (count > 0)
   {
      for (int y = y1; y <= y2; y++)
      for (int x = x1; x <= x2; x++)
      {
         image.Data2D[y][x] = mean;
         region.Data2D[y][x] = region_count;
      }
      if (region_count < 30000)
         region_count++;
   }
}

//============================================================
void process(string Name1, string Name2)
{
   // Read parameters from user
   cout << "Enter size of Gaussian blur filter: ";
   float Sigma = 0;
   cin >> Sigma;
   if (Sigma < 0) Sigma = 0;
   cout << "Enter minumum region size: ";
   int Size = 0;
   cin >> Size;
   if (Size < 1) Size = 1;
   cout << "Enter maximum region stdev: ";
   float Threshold = 0;
   cin >> Threshold;
   if (Threshold < 1) Threshold = 1;

   // Read input image
   im_float Input;
   Input.ReadJpg((char *)Name1.c_str());
   Input.Gaussian(Sigma);
   int Xdim = Input.Xdim;
   int Ydim = Input.Ydim;

   // Create ouput image
   int RegionCount = 1;
   im_short Region(Xdim, Ydim);

   // Perform recursive region splitting
   split(Input, Region, RegionCount, 0, Xdim-1, 0, Ydim-1, Size, Threshold);

   // ADD REGION MERGING HERE

   // Write outout images
   im_short Boundary(Region);
   Boundary.RegionBoundary(255);
   Input.WriteJpg((char *)"mean.jpg");
   Region.WriteJpg((char *)"region.jpg");
   Boundary.WriteJpg((char *)"boundary.jpg");
   cout << "Number of regions: " << RegionCount << endl;
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
