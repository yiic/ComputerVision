//============================================================
//  File:       vector_median.cpp
//  Purpose:    Implements solution to CSCE 5683 Fall 2010 hw#6
//  Author:     John Gauch
//  Date:       Fall 2010
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include "limits.h"

bool debug = true;

//============================================================
void adjust_hue_sat(im_color &Input, int hue, float sat)
{
   // Check parameters
   hue = (hue % 360 + 360) % 360;
   sat = fabs(sat);

   // Convert RGB to HSI
   Input.RGBtoHSI();

   // Adjust image
   int ydim = Input.R.Ydim;
   int xdim = Input.R.Xdim;
   for (int y=0; y<ydim; y++)
   for (int x=0; x<xdim; x++)
   {
      Input.R.Data2D[y][x] = (Input.R.Data2D[y][x] + hue) % 360; 
      Input.G.Data2D[y][x] = Input.G.Data2D[y][x] * sat; 
      if (Input.G.Data2D[y][x] > 255)
         Input.G.Data2D[y][x] = 255;
   }
   
   // Convert HSI to RGB
   Input.HSItoRGB();
}

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
void part1(char *Name1)
{
   im_color Image1;
   char Name2[STRLEN];

   // Adjust hue 
   int hue[10] = {-50, -20, -10, -5, -1, 1, 5, 10, 20, 50};
   for (int i=0; i<10; i++)
   {
      Image1.ReadJpg(Name1);
      adjust_hue_sat(Image1, hue[i], 1.0);
      sprintf(Name2, "hue%d.jpg", hue[i]);
      Image1.WriteJpg(Name2);
   }

   // Adjust sat 
   float sat[10] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.1, 1.2, 1.3, 1.4, 1.5};
   for (int i=0; i<10; i++)
   {
      Image1.ReadJpg(Name1);
      adjust_hue_sat(Image1, 0, sat[i]);
      sprintf(Name2, "sat%3.1f.jpg", sat[i]);
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void part2(char *Name1, int radius)
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
   Image1.Median(2*radius+1,2*radius+1);
   Image1.WriteJpg((char *)"rgb-median.jpg");

   // Calculate vector median in HSI
   Image1.ReadJpg(Name1);
   Image1.RGBtoHSI();
   vector_median(Image1, Image2, radius);
   Image2.HSItoRGB();
   Image2.WriteJpg((char *)"hsi-vmedian.jpg");

   // Calculate scalar median in HSI
   Image1.Median(2*radius+1,2*radius+1);
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

   // part1(Name1);
   part2(Name1, radius);
}

