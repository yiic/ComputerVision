//============================================================
//  File:       notch.cpp
//  Purpose:    Implements solution to CSCE 5683 Fall 2010 hw#4
//  Author:     John Gauch
//  Date:       Fall 2010
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"

bool debug = true;

//============================================================
void rectangular_notch(char *Name1, char *Name2)
{
   // Read input image
   im_float Input;
   Input.ReadJpg(Name1);
   im_complex Image(Input);

   // Perform FFT
   Image.FastFT();

   // Get user input
   int u1, v1, u2, v2;
   printf("Enter u1 v1 coordinates: ");
   if (scanf("%d %d", &u1, &v1) != 2);
   printf("Enter u2 v2 coordinates: ");
   if (scanf("%d %d", &u2, &v2) != 2);

   // Perform filtering
   int ydim = Image.Re.Ydim;
   int xdim = Image.Re.Xdim;
   for (int u=u1; u<=u2; u++)
   for (int v=v1; v<=v2; v++)
   if ((u >= 0) && (u < xdim) && (v >= 0) && (v < ydim))
   {
      Image.Re.Data2D[v][u] = 0;
      Image.Im.Data2D[v][u] = 0;
      Image.Re.Data2D[ydim-v][xdim-u] = 0;
      Image.Im.Data2D[ydim-v][xdim-u] = 0;
   }

   // Write filter image
   im_float Temp;
   Image.GetAmplitude(Temp);
   Temp.WriteJpg((char *)"temp.jpg");

   // Perform inverse FFT
   Image.FastIFT();

   // Write output image
   Image.Re.WriteJpg(Name2);
}

//============================================================
void gaussian_notch(char *Name1, char *Name2)
{
   // Read input image
   im_float Input;
   Input.ReadJpg(Name1);
   im_complex Image(Input);

   // Perform FFT
   Image.FastFT();

   // Get user input
   int cu, cv;
   float freq;
   printf("Enter center u v coordinates: ");
   if (scanf("%d %d", &cu, &cv) != 2);
   printf("Enter filter width: ");
   if (scanf("%f", &freq) != 1);

   // Perform filtering
   int ydim = Image.Re.Ydim;
   int xdim = Image.Re.Xdim;
   for (int v = 0; v < ydim; v++)
      for (int u = 0; u < xdim; u++)
      {
	 // Calculate distance to center
	 int dv = (v < ydim / 2) ? v : v - ydim;
	 int du = (u < xdim / 2) ? u : u - xdim;
	 float dist1 = (float) ((cv-dv) * (cv-dv) + (cu-du) * (cu-du));
	 float dist2 = (float) ((-cv-dv) * (-cv-dv) + (-cu-du) * (-cu-du));

	 // Apply filter
	 float filter1 = exp(dist1 / (-2 * freq * freq));
	 float filter2 = exp(dist2 / (-2 * freq * freq));
	 Image.Re.Data2D[v][u] *= (1 - filter1) * (1 - filter2);
	 Image.Im.Data2D[v][u] *= (1 - filter1) * (1 - filter2);
      }

   // Write filter image
   im_float Temp;
   Image.GetAmplitude(Temp);
   Temp.WriteJpg((char *)"temp.jpg");

   // Perform inverse FFT
   Image.FastIFT();

   // Write output image
   Image.Re.WriteJpg(Name2);
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
   
   // Perform notch filter
   char Filter[STRLEN];
   printf("Gaussian notch filter or Rectangular notch filter? (g/r):");
   if (scanf("%s", Filter) != 1);
   if (Filter[0] == 'r' || Filter[0] == 'R')
      rectangular_notch(Name1, Name2);
   if (Filter[0] == 'g' || Filter[0] == 'G')
      gaussian_notch(Name1, Name2);
}

