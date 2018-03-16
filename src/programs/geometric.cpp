//============================================================
//  File:       geometric.cpp
//  Purpose:	Implements solution to CSCE 5683 Fall 2010 hw#1 
//  Author:     John Gauch
//  Date:       Fall 2010
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"

//============================================================
void translate(char *Name1, char *Name2, int Tx, int Ty)
{
   // Read input image
   im_short Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_short Image2(Image1.Xdim, Image1.Ydim);

   // Perform operation
   for (int y2=0; y2<Image2.Ydim; y2++)
   for (int x2=0; x2<Image2.Xdim; x2++)
   {
      int x1 = (int)(0.5 + x2 - Tx);
      int y1 = (int)(0.5 + y2 - Ty);
      if ((x1 >= 0) && (x1 < Image1.Xdim) && 
          (y1 >= 0) && (y1 < Image1.Ydim))
         Image2.Data2D[y2][x2] = Image1.Data2D[y1][x1];
   }

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
void scale(char *Name1, char *Name2, float Sx, float Sy)
{
   // Read input image
   im_short Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_short Image2(Image1.Xdim, Image1.Ydim);

   // Perform operation
   if ((Sx != 0) && (Sy != 0))
   for (int y2=0; y2<Image2.Ydim; y2++)
   for (int x2=0; x2<Image2.Xdim; x2++)
   {
      int x1 = (int)(0.5 + x2 / Sx);
      int y1 = (int)(0.5 + y2 / Sy);
      if ((x1 >= 0) && (x1 < Image1.Xdim) && 
          (y1 >= 0) && (y1 < Image1.Ydim))
         Image2.Data2D[y2][x2] = Image1.Data2D[y1][x1];
   }

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
void shear(char *Name1, char *Name2, float Hx, float Hy)
{
   // Read input image
   im_short Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_short Image2(Image1.Xdim, Image1.Ydim);

   // Perform operation
   for (int y2=0; y2<Image2.Ydim; y2++)
   for (int x2=0; x2<Image2.Xdim; x2++)
   {
      int x1 = (int)(0.5 + x2 + y2 * Hx);
      int y1 = (int)(0.5 + y2 + x2 * Hy);
      if ((x1 >= 0) && (x1 < Image1.Xdim) && 
          (y1 >= 0) && (y1 < Image1.Ydim))
         Image2.Data2D[y2][x2] = Image1.Data2D[y1][x1];
   }

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
void rotate(char *Name1, char *Name2, float angle)
{
   // Read input image
   im_short Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_short Image2(Image1.Xdim, Image1.Ydim);

   // Calculate rotation parameters
   angle = M_PI * angle / 180;
   float sin_angle = (float) sin(angle);
   float cos_angle = (float) cos(angle);

   // Perform operation
   for (int y2=0; y2<Image2.Ydim; y2++)
   for (int x2=0; x2<Image2.Xdim; x2++)
   {
      int x1 = (int)(0.5 + x2*cos_angle - y2*sin_angle);
      int y1 = (int)(0.5 + x2*sin_angle + y2*cos_angle);
      if ((x1 >= 0) && (x1 < Image1.Xdim) && 
          (y1 >= 0) && (y1 < Image1.Ydim))
         Image2.Data2D[y2][x2] = Image1.Data2D[y1][x1];
   }

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
void scale(char *Name1, char *Name2, float Sx, float Sy, int Cx, int Cy)
{
   // Read input image
   im_color Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_color Image2(Image1.R.Xdim, Image1.R.Ydim);

   // Perform operation
   if ((Sx != 0) && (Sy != 0))
   for (int y2=0; y2<Image2.R.Ydim; y2++)
   for (int x2=0; x2<Image2.R.Xdim; x2++)
   {
      int x1 = (int)(0.5 + (x2-Cx) / Sx + Cx);
      int y1 = (int)(0.5 + (y2-Cy) / Sy + Cy);
      if ((x1 >= 0) && (x1 < Image1.R.Xdim) && 
          (y1 >= 0) && (y1 < Image1.R.Ydim))
      {
         Image2.R.Data2D[y2][x2] = Image1.R.Data2D[y1][x1];
         Image2.G.Data2D[y2][x2] = Image1.G.Data2D[y1][x1];
         Image2.B.Data2D[y2][x2] = Image1.B.Data2D[y1][x1];
      }
   }

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
void shear(char *Name1, char *Name2, float Hx, float Hy, int Cx, int Cy)
{
   // Read input image
   im_color Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_color Image2(Image1.R.Xdim, Image1.R.Ydim);

   // Perform operation
   for (int y2=0; y2<Image2.R.Ydim; y2++)
   for (int x2=0; x2<Image2.R.Xdim; x2++)
   {
      int x1 = (int)(0.5 + (x2-Cx) + (y2-Cy) * Hx + Cx);
      int y1 = (int)(0.5 + (y2-Cy) + (x2-Cx) * Hy + Cy);
      if ((x1 >= 0) && (x1 < Image1.R.Xdim) && 
          (y1 >= 0) && (y1 < Image1.R.Ydim))
      {
         Image2.R.Data2D[y2][x2] = Image1.R.Data2D[y1][x1];
         Image2.G.Data2D[y2][x2] = Image1.G.Data2D[y1][x1];
         Image2.B.Data2D[y2][x2] = Image1.B.Data2D[y1][x1];
      }
   }

   // Write output image
   Image2.WriteJpg(Name2);
}

//============================================================
void rotate(char *Name1, char *Name2, float angle, int Cx, int Cy)
{
   // Read input image
   im_color Image1;
   Image1.ReadJpg(Name1);

   // Create output image
   im_color Image2(Image1.R.Xdim, Image1.R.Ydim);

   // Calculate rotation parameters
   angle = M_PI * angle / 180;
   float sin_angle = (float) sin(angle);
   float cos_angle = (float) cos(angle);

   // Perform operation
   for (int y2=0; y2<Image2.R.Ydim; y2++)
   for (int x2=0; x2<Image2.R.Xdim; x2++)
   {
      int x1 = (int)(0.5 + (x2-Cx)*cos_angle - (y2-Cy)*sin_angle + Cx);
      int y1 = (int)(0.5 + (x2-Cx)*sin_angle + (y2-Cy)*cos_angle + Cy);
      if ((x1 >= 0) && (x1 < Image1.R.Xdim) && 
          (y1 >= 0) && (y1 < Image1.R.Ydim))
      {
         Image2.R.Data2D[y2][x2] = Image1.R.Data2D[y1][x1];
         Image2.G.Data2D[y2][x2] = Image1.G.Data2D[y1][x1];
         Image2.B.Data2D[y2][x2] = Image1.B.Data2D[y1][x1];
      }
   }

   // Write output image
   Image2.WriteJpg(Name2);
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

   // Test basic operations on grey scale images
   translate(Name1, (char *)"translate.jpg", 30, 45);
   scale(Name1, (char *)"scale1.jpg", 0.9, 1.1);
   shear(Name1, (char *)"shear_x1.jpg", 0.1, 0.0);
   shear(Name1, (char *)"shear_y1.jpg", 0.0, 0.2);
   rotate(Name1, (char *)"rotate1.jpg", 10);

   // Test centered operations on color images
   scale(Name1, (char *)"scale2.jpg", 0.9, 1.1, 100, 100);
   shear(Name1, (char *)"shear_x2.jpg", 0.1, 0.0, 100, 100);
   shear(Name1, (char *)"shear_y2.jpg", 0.0, 0.2, 100, 100);
   rotate(Name1, (char *)"rotate2.jpg", 10, 100, 100);
}
