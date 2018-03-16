//============================================================
//  File:       vector_median2.cpp
//  Purpose:    Implements solution to CSCE 5683 Fall 2012 hw#5
//  Author:     John Gauch
//  Date:       Fall 2012
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include "limits.h"

bool debug = true;

//============================================================
void vector_median(im_color &Input, im_color &Output, int radius)
{
   // Perform filtering
   int ydim = Input.R.Ydim;
   int xdim = Input.R.Xdim;
   for (int y=0; y<ydim; y++)
   for (int x=0; x<xdim; x++)
   {
      // Initialize vector median
      int bestR = 0;
      int bestG = 0;
      int bestB = 0;
      double bestDist = INT_MAX;

      // Loop over neighborhood
      for (int y1 = y-radius; y1 <= y+radius; y1++)
      for (int x1 = x-radius; x1 <= x+radius; x1++)
      if ((x1 >= 0) && (x1 < xdim) && (y1 >= 0) && (y1 < ydim))
      {
         int R1 = Input.R.Data2D[y1][x1];
         int G1 = Input.G.Data2D[y1][x1];
         int B1 = Input.B.Data2D[y1][x1];
      
         // Loop over neighborhood
         double Dist = 0;
         for (int y2 = y-radius; y2 <= y+radius; y2++)
         for (int x2 = x-radius; x2 <= x+radius; x2++)
         if ((x2 >= 0) && (x2 < xdim) && (y2 >= 0) && (y2 < ydim))
         {
            int R2 = Input.R.Data2D[y2][x2];
            int G2 = Input.G.Data2D[y2][x2];
            int B2 = Input.B.Data2D[y2][x2];
            Dist += sqrt( (R1-R2)*(R1-R2) + (G1-G2)*(G1-G2) + (B1-B2)*(B1-B2) );
         }

         // Update vector median
         if (Dist < bestDist)
         {
            bestR = R1;
            bestG = G1;
            bestB = B1;
            bestDist = Dist;
         }
      }

      // Save vector median
      Output.R.Data2D[y][x] = bestR;
      Output.G.Data2D[y][x] = bestG;
      Output.B.Data2D[y][x] = bestB;
   }
}

//============================================================
void experiment(char *Name1, int radius)
{
   // Read input image
   im_color Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   int ydim = Image1.R.Ydim;
   int xdim = Image1.R.Xdim;
   im_color Image2(xdim, ydim);

   // Calculate vector median in RGB
   vector_median(Image1, Image2, radius);
   Image2.WriteJpg((char *)"rgb-vmedian.jpg");

   // Calculate scalar median in RGB
   Image1.Median(2*radius+1, 2*radius+1);
   Image1.WriteJpg((char *)"rgb-median.jpg");

   // Calculate vector median in HSI
   Image1.ReadJpg(Name1);
   Image1.RGBtoHSI();
   vector_median(Image1, Image2, radius);
   Image2.HSItoRGB();
   Image2.WriteJpg((char *)"hsi-vmedian.jpg");

   // Calculate scalar median in HSI
   Image1.Median(2*radius+1, 2*radius+1);
   Image1.HSItoRGB();
   Image1.WriteJpg((char *)"hsi-median.jpg");
}

//============================================================
int main(int argc, char *argv[])
{
   // Get input file name
   char Name1[STRLEN];
   int radius = 0;
   if (argc == 3)
   {
      strcpy(Name1, argv[1]);
      radius = atoi(argv[2]);
   }
   else
   {
      printf("Enter name of input image: ");
      if (scanf("%s", Name1) != 1);
      printf("Enter radius: ");
      if (scanf("%d", &radius) != 1);
   }

   experiment(Name1, radius);
}

