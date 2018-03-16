//============================================================
//  File:       color_histogram.cpp
//  Purpose:    Use color histogram for image similarity.
//  Author:     John Gauch
//  Date:       Fall 2016
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include "limits.h"

const int SIZE = 8;
class color_histo
{
   public:
      color_histo();
      ~color_histo();
      void clear();
      void print();
      void calculate(im_color im);
      void calculate(im_color im,
         int xmin, int xmax, int ymin, int ymax);
      float match(im_color im,
         int xmin, int xmax, int ymin, int ymax);

   private:
      int count[SIZE][SIZE][SIZE];
};

//============================================================
color_histo::color_histo()
{
   clear();
}

//============================================================
color_histo::~color_histo()
{
   clear();
}

//============================================================
void color_histo::clear()
{
   for (int r=0; r<SIZE; r++)
   for (int g=0; g<SIZE; g++)
   for (int b=0; b<SIZE; b++)
      count[r][g][b] = 0;
}

//============================================================
void color_histo::print()
{
   for (int r=0; r<SIZE; r++)
   for (int g=0; g<SIZE; g++)
   for (int b=0; b<SIZE; b++)
      printf("%d ", count[r][g][b]);
   printf("\n");
}

//============================================================
void color_histo::calculate(im_color im)
{
   int ydim = im.R.Ydim;
   int xdim = im.R.Xdim;
   for (int y=0; y<ydim; y++)
   for (int x=0; x<xdim; x++)
   {
      int r = im.R.Data2D[y][x] * SIZE / 256;
      int g = im.G.Data2D[y][x] * SIZE / 256;
      int b = im.B.Data2D[y][x] * SIZE / 256;
      count[r][g][b]++;
   }
}

//============================================================
void color_histo::calculate(im_color im,
   int xmin, int xmax, int ymin, int ymax)
{
   if (xmin < 0) xmin = 0;
   if (ymin < 0) ymin = 0;
   if (xmax > im.R.Xdim) xmax = im.R.Xdim;
   if (ymax > im.R.Ydim) ymax = im.R.Ydim;
   for (int y=ymin; y<ymax; y++)
   for (int x=ymin; x<xmax; x++)
   {
      int r = im.R.Data2D[y][x] * SIZE / 256;
      int g = im.G.Data2D[y][x] * SIZE / 256;
      int b = im.B.Data2D[y][x] * SIZE / 256;
      count[r][g][b]++;
   }
}

//============================================================
float color_histo::match(im_color im,
   int xmin, int xmax, int ymin, int ymax)
{
   float sum = 0;
   if (xmin < 0) xmin = 0;
   if (ymin < 0) ymin = 0;
   if (xmax > im.R.Xdim) xmax = im.R.Xdim;
   if (ymax > im.R.Ydim) ymax = im.R.Ydim;
   for (int y=ymin; y<ymax; y++)
   for (int x=xmin; x<xmax; x++)
   {
      int r = im.R.Data2D[y][x] * SIZE / 256;
      int g = im.G.Data2D[y][x] * SIZE / 256;
      int b = im.B.Data2D[y][x] * SIZE / 256;
      sum += count[r][g][b];
   }
   return sum/((xmax-xmin+1)*(ymax-ymin+1));
}

//============================================================
void process(char *Name1, char *Name2)
{
   // Read input image
   im_color input;
   input.ReadJpg(Name1);
   int ydim = input.R.Ydim;
   int xdim = input.R.Xdim;

   // Initialize color histogram 
   color_histo histo;
   histo.calculate(input);
   histo.print();

   // Create output image
   xdim /= SIZE;
   ydim /= SIZE;
   im_float output(xdim, ydim);
   for (int y=0; y<ydim; y++)
   for (int x=0; x<xdim; x++)
      output.Data2D[y][x] = histo.match(input, 
         x*SIZE, (x+1)*SIZE, y*SIZE, (y+1)*SIZE);

   // Save output image
   output.Interpolate(xdim*SIZE, ydim*SIZE);
   output.WriteJpg(Name2);
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

   // Perform operation
   process(Name1, Name2);
}

