//============================================================
//  File:       enhance.cpp
//  Purpose:    Implements solution to CSCE 5683 Fall 2012 hw#1
//  Author:     John Gauch
//  Date:       Fall 2012
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"

//============================================================
void enhance(char *Name1, char *Name2)
{
   // Read input image
   im_short Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_short Image2(Image1.Xdim, Image1.Ydim);

   // Initialize min, max, ave
   int min = Image1.Data2D[0][0];
   int max = Image1.Data2D[0][0];
   int ave = 0;

   // Calculate min, max, ave
   for (int y=0; y<Image1.Ydim; y++)
   for (int x=0; x<Image1.Xdim; x++)
   {
      if (min > Image1.Data2D[y][x])
         min = Image1.Data2D[y][x];
      if (max < Image1.Data2D[y][x])
         max = Image1.Data2D[y][x];
      ave += Image1.Data2D[y][x];
   }
   ave /= (Image1.Xdim * Image1.Ydim);
   printf("min = %d\n", min);
   printf("max = %d\n", max);
   printf("ave = %d\n", ave);
   
   // Define mapping function
   int *map = new int[max+1];
   for (int i = min; i <= ave; i++)
      map[i] = 0 + (127 - 0) * (i - min) / (ave - min);
   for (int i = ave + 1; i <= max; i++)
      map[i] = 128 + (255 - 128) * (i - ave - 1) / (max - ave - 1);

   // Enhance input image
   for (int y=0; y<Image1.Ydim; y++)
   for (int x=0; x<Image1.Xdim; x++)
      Image2.Data2D[y][x] = map[ Image1.Data2D[y][x] ];

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
int main(int argc, char *argv[])
{
   // Get input file name
   char Name1[STRLEN];
   char Name2[STRLEN];
   if (argc == 3)
   {
      strcpy(Name1, argv[1]);
      strcpy(Name2, argv[2]);
   }
   else
   {
      printf("Enter name of input image: ");
      if (scanf("%s", Name1) != 1);
      printf("Enter name of output image: ");
      if (scanf("%s", Name2) != 1);
   }

   // Enhance input image
   enhance(Name1, Name2);
}
