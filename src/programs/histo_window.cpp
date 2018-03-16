//============================================================
//  File:       histo_window.cpp
//  Purpose:    Implements solution to CSCE 5683 Fall 2010 hw#2
//  Author:     John Gauch
//  Date:       Fall 2010
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"

//============================================================
void histo_print(im_short &Image, 
   int x1, int y1, int x2, int y2, char *Name)
{
   // Calculate min and max
   int min = Image.Data2D[y1][x1];
   int max = Image.Data2D[y1][x1];
   for (int y=y1; y<y2; y++)
   for (int x=x1; x<x2; x++)
   {
      if (min > Image.Data2D[y][x])
         min = Image.Data2D[y][x];
      if (max < Image.Data2D[y][x])
         max = Image.Data2D[y][x];
   }

   // Calculate histogram
   int range = max - min + 1;
   int histo[range];
   for (int i=0; i<range; i++)
      histo[i] = 0;
   for (int y=y1; y<y2; y++)
   for (int x=x1; x<x2; x++)
      histo[ Image.Data2D[y][x]-min ]++;
   
   // Print histogram
   FILE *fd = fopen(Name, "w");
   for (int i=0; i<range; i++)
      fprintf(fd, "%d %d\n", i+min, histo[i]);
   fclose(fd);
}

//============================================================
void histo_window(im_short &Image, 
   int x1, int y1, int x2, int y2, float fraction)
{
   // Calculate min and max
   int min = Image.Data2D[y1][x1];
   int max = Image.Data2D[y1][x1];
   for (int y=y1; y<y2; y++)
   for (int x=x1; x<x2; x++)
   {
      if (min > Image.Data2D[y][x])
         min = Image.Data2D[y][x];
      if (max < Image.Data2D[y][x])
         max = Image.Data2D[y][x];
   }

   // Calculate histogram
   int range = max - min + 1;
   int histo[range];
   for (int i=0; i<range; i++)
      histo[i] = 0;
   for (int y=y1; y<y2; y++)
   for (int x=x1; x<x2; x++)
      histo[ Image.Data2D[y][x]-min ]++;
   
   // Calculate window range
   int cutoff = (x2-x1)*(y2-y1)*fraction;
   int low = 0;
   int low_sum = 0;
   int high = range-1;
   int high_sum = 0;
   while ((low < range) && (low_sum < cutoff))
      low_sum += histo[low++];
   low += min;
   while ((high > 0) && (high_sum < cutoff))
      high_sum += histo[high--];
   high += min;

   // Perform intensity windowing
   for (int y=y1; y<y2; y++)
   for (int x=x1; x<x2; x++)
   {
      // Window intensity to [low..high] range
      if (Image.Data2D[y][x] < low)
         Image.Data2D[y][x] = low;
      if (Image.Data2D[y][x] > high)
         Image.Data2D[y][x] = high;

      // Scale intensity to [0..255] range
      Image.Data2D[y][x] = (255*(Image.Data2D[y][x]-low))/(high-low);
   }

   // Print debug info
   printf("min %d, max %d\n", min, max);
   printf("low %d, high %d\n", low, high);
}

//============================================================
int main(int argc, char *argv[])
{
   // Get input file name
   char Name1[STRLEN];
   if (argc == 2)
      strcpy(Name1, argv[1]);
   else
   {
      printf("Enter name of input image: ");
      if (scanf("%s", Name1) != 1);
   }
   
   // Print global histogram
   im_short Image;
   Image.ReadJpg(Name1);
   histo_print(Image, 0, 0, Image.Xdim, Image.Ydim, (char *)"histo.txt");

   // Global histogram windowing
   histo_window(Image, 0, 0, Image.Xdim, Image.Ydim, 0.05);
   Image.WriteJpg((char *)"global_window.jpg");

   // Print local histograms
   Image.ReadJpg(Name1);
   histo_print(Image, 0, 0, Image.Xdim/2, Image.Ydim/2, (char *)"histoUL.txt");
   histo_print(Image, 0, Image.Ydim/2, Image.Xdim/2, Image.Ydim, (char *)"histoLL.txt");
   histo_print(Image, Image.Xdim/2, 0, Image.Xdim, Image.Ydim/2, (char *)"histoUR.txt");
   histo_print(Image, Image.Xdim/2, Image.Ydim/2, Image.Xdim, Image.Ydim, (char *)"histoLR.txt");

   // Local histogram windowing
   histo_window(Image, 0, 0, Image.Xdim/2, Image.Ydim/2, 0.05);
   histo_window(Image, 0, Image.Ydim/2, Image.Xdim/2, Image.Ydim, 0.05);
   histo_window(Image, Image.Xdim/2, 0, Image.Xdim, Image.Ydim/2, 0.05);
   histo_window(Image, Image.Xdim/2, Image.Ydim/2, Image.Xdim, Image.Ydim, 0.05);
   Image.WriteJpg((char *)"local_window.jpg");
}
