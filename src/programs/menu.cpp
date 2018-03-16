//============================================================
//  File:       menu.cpp
//  Purpose:    Implements menu based interface to libim
//  Author:     John Gauch
//  Date:       Spring 2009 - Fall 2016
//============================================================

#include <sys/time.h>
#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"

//============================================================
float get_cpu_time(struct timeval begin, struct timeval end)
{
   float cpu_time = 0.0;
   cpu_time = (end.tv_sec - begin.tv_sec) * 1000.0;
   cpu_time += (end.tv_usec - begin.tv_usec) / 1000.0;
   return cpu_time / 1000.0;
}

//============================================================
void add(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Name3[STRLEN];

   if (sscanf(Input, "%s %s %s %s", Command, Name1, Name2, Name3) != 4)
      printf("Usage: add infile1 infile2 outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);
      im_color Image2;
      Image2.ReadJpg(Name2);

      // Perform operation
      Image2.Interpolate(Image1.R.Xdim, Image1.R.Ydim);
      Image1.Add(Image2);

      // Write output image
      Image1.WriteJpg(Name3);
   }
}

//============================================================
void subtract(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Name3[STRLEN];

   if (sscanf(Input, "%s %s %s %s", Command, Name1, Name2, Name3) != 4)
      printf("Usage: subtract infile1 infile2 outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);
      im_color Image2;
      Image2.ReadJpg(Name2);

      // Perform operation
      Image2.Interpolate(Image1.R.Xdim, Image1.R.Ydim);
      Image1.Subtract(Image2);

      // Write output image
      Image1.WriteJpg(Name3);
   }
}

//============================================================
void multiply(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Name3[STRLEN];

   if (sscanf(Input, "%s %s %s %s", Command, Name1, Name2, Name3) != 4)
      printf("Usage: multiply infile1 infile2 outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);
      im_color Image2;
      Image2.ReadJpg(Name2);

      // Perform operation
      Image2.Interpolate(Image1.R.Xdim, Image1.R.Ydim);
      Image1.Multiply(Image2);

      // Write output image
      Image1.WriteJpg(Name3);
   }
}

//============================================================
void divide(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Name3[STRLEN];

   if (sscanf(Input, "%s %s %s %s", Command, Name1, Name2, Name3) != 4)
      printf("Usage: divide infile1 infile2 outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);
      im_color Image2;
      Image2.ReadJpg(Name2);

      // Perform operation
      Image2.Interpolate(Image1.R.Xdim, Image1.R.Ydim);
      Image1.Divide(Image2);

      // Write output image
      Image1.WriteJpg(Name3);
   }
}

//============================================================
void threshold(char Input[])
{
   char Command[STRLEN];
   float Value;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Value, Name1, Name2) != 4)
      printf("Usage: threshold #value infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Threshold(Value, false);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void threshold_automatic(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: threshold_automatic infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.ThresholdAutomatic(false);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void window(char Input[])
{
   char Command[STRLEN];
   int Low, High;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s", Command, &Low, &High, Name1, Name2) != 5)
      printf("Usage: window #low #high infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Window(Low, High);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void trim(char Input[])
{
   char Command[STRLEN];
   float Percentage;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Percentage, Name1, Name2) != 4)
      printf("Usage: trim #percentage infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Trim(Percentage);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void greymap(char Input[])
{
   char Command[STRLEN];
   int Low, High;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s", Command, &Low, &High, Name1, Name2) != 5)
      printf("Usage: greymap #low #high infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Greymap(Low, High);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void quantize(char Input[])
{
   char Command[STRLEN];
   int Levels, Iterations;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &Levels, &Iterations, Name1, Name2) != 5)
      printf("Usage: quantize #levels #iterations infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Quantize(Levels, Iterations);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void invert(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: invert infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Invert();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void equalize(char Input[])
{
   char Command[STRLEN];
   int Regions;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %s %s", Command, &Regions, Name1, Name2) != 4)
      printf("Usage: equalize #regions infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      if (Regions <= 1)
	 Image1.Equalize();
      else
	 Image1.Equalize(Regions);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void unsharp_masking(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   float Weight;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Sigma, &Weight, Name1, Name2) != 5)
      printf("Usage: unsharp_masking #sigma #weight infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.UnsharpMasking(Sigma, Weight);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void power(char Input[])
{
   char Command[STRLEN];
   float Gamma;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Gamma, Name1, Name2) != 4)
      printf("Usage: power #gamma infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Power(Gamma);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void cubic(char Input[])
{
   char Command[STRLEN];
   float Param;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Param, Name1, Name2) != 4)
      printf("Usage: cubic #param infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Cubic(Param);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void stretch(char Input[])
{
   char Command[STRLEN];
   int r1, s1, r2, s2;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %d %d %s %s",
	      Command, &r1, &s1, &r2, &s2, Name1, Name2) != 7)
      printf("Usage: stretch #r1 #s1 #r2 #s2 infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Stretch(r1, s1, r2, s2);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void wallis(char Input[])
{
   char Command[STRLEN];
   int radius;
   float A;
   float B;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %f %f %s %s",
	      Command, &radius, &A, &B, Name1, Name2) != 6)
      printf("Usage: wallis #radius #A #B infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Wallis(radius, A, B);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void whiten(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: whiten infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Whiten();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void average(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &Xdim, &Ydim, Name1, Name2) != 5)
      printf("Usage: average #xdim #ydim infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Average(Xdim, Ydim);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void binomial(char Input[])
{
   char Command[STRLEN];
   int Number;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %s %s", Command, &Number, Name1, Name2) != 4)
      printf("Usage: binomial #iterations infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Binomial(Number);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void convolve(char Input[])
{
   char Command[STRLEN];
   char Mask[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s %s", Command, Mask, Name1, Name2) != 4)
      printf("Usage: convolve maskfile infile outfile\n");
   else
   {
      // Read mask file
      im_float MaskIm;
      MaskIm.ReadAscii(Mask);

      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Convolve(MaskIm.Xdim, MaskIm.Ydim, MaskIm.Data1D);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void median(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &Xdim, &Ydim, Name1, Name2) != 5)
      printf("Usage: median #nxdim #nydim infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Median(Xdim, Ydim);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void gaussian(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Sigma, Name1, Name2) != 4)
      printf("Usage: gaussian #sigma infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void adaptive_gaussian(char Input[])
{
   char Command[STRLEN];
   float Sigma1, Sigma2;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s", Command, &Sigma1, &Sigma2, Name1, Name2) != 5)
      printf("Usage: adaptive_gaussian #sigma1 #sigma2 infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.AdaptiveGaussian(Sigma1, Sigma2);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void outlier_removal(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim;
   float Threshold;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %f %s %s",
	      Command, &Xdim, &Ydim, &Threshold, Name1, Name2) != 6)
      printf("Usage: outlier_removal #nxdim #nydim #threshold infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.OutlierRemoval(Xdim, Ydim, Threshold);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void knn(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim, K;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %d %s %s",
	      Command, &Xdim, &Ydim, &K, Name1, Name2) != 6)
      printf("Usage: knn #nxdim #nydim #k infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.kNN(Xdim, Ydim, K);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void alpha_mean(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim, Alpha;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %d %s %s",
	      Command, &Xdim, &Ydim, &Alpha, Name1, Name2) != 6)
      printf("Usage: alpha_mean #nxdim #nydim #alpha infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.AlphaMean(Xdim, Ydim, Alpha);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void morphology(char Input[])
{
   char Command[STRLEN];
   char Commands[STRLEN];
   float Radius;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %f %s %s",
	      Command, Commands, &Radius, Name1, Name2) != 5)
      printf("Usage: morphology commands #radius infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Morphology(Commands, Radius);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void search_median(char *Name1, char *Name2, char *Name3)
{
   // Read original image
   im_color Original;
   Original.ReadJpg(Name1);

   // Read noise image
   im_color Noise;
   Noise.ReadJpg(Name2);

   // Search for best smoothing parameters
   int BestX = 0;
   int BestY = 0;
   float BestDifference = 256;
   for (int X = 1; X < 5; X++)
      for (int Y = 1; Y < 5; Y++)
      {
	 im_color Smooth(Noise);
	 Smooth.Copy(Noise);
	 Smooth.Median(X, Y);
	 float difference;
	 Smooth.Difference(Original, difference);
	 if (difference < BestDifference)
	 {
	    BestX = X;
	    BestY = Y;
	    BestDifference = difference;
	    printf("X %d, Y %d, difference %f\n", X, Y, difference);
	 }
      }

   // Save best output image
   im_color Smooth(Noise);
   Smooth.Copy(Noise);
   Smooth.Median(BestX, BestY);
   Smooth.WriteJpg(Name3);
   printf("Best = X %d, Y %d, difference %f\n", BestX, BestY, BestDifference);
}

//============================================================
void search_gaussian(char *Name1, char *Name2, char *Name3)
{
   // Read original image
   im_color Original;
   Original.ReadJpg(Name1);

   // Read noise image
   im_color Noise;
   Noise.ReadJpg(Name2);

   // Search for best smoothing parameters
   float BestS = 0;
   float BestDifference = 256;
   float Step = 1.0;
   float Center = 3.0;
   for (int Loop = 0; Loop <= 10; Loop++)
   {
      for (float S = Center - 3 * Step; S <= Center + 3 * Step; S += Step)
      {
	 im_color Smooth(Noise);
	 Smooth.Copy(Noise);
	 Smooth.Gaussian(S);
	 float difference;
	 Smooth.Difference(Original, difference);
	 if (difference < BestDifference)
	 {
	    BestS = S;
	    BestDifference = difference;
	    printf("S %f, difference %f\n", S, difference);
	 }
      }
      Step /= 4;
      Center = BestS;
   }

   // Save best output image
   im_color Smooth(Noise);
   Smooth.Copy(Noise);
   Smooth.Gaussian(BestS);
   Smooth.WriteJpg(Name3);
   printf("Best = S %f, difference %f\n", BestS, BestDifference);
}

//============================================================
void search_knn(char *Name1, char *Name2, char *Name3)
{
   // Read original image
   im_color Original;
   Original.ReadJpg(Name1);

   // Read noise image
   im_color Noise;
   Noise.ReadJpg(Name2);

   // Search for best smoothing parameters
   int BestX = 0;
   int BestY = 0;
   int BestK = 0;
   float BestDifference = 256;
   for (int X = 1; X < 5; X++)
      for (int Y = 1; Y < 5; Y++)
	 for (int K = 1; K <= X * Y; K++)
	 {
	    im_color Smooth(Noise);
	    Smooth.Copy(Noise);
	    Smooth.kNN(X, Y, K);
	    float difference;
	    Smooth.Difference(Original, difference);
	    if (difference < BestDifference)
	    {
	       BestX = X;
	       BestY = Y;
	       BestK = K;
	       BestDifference = difference;
	       printf("X %d, Y %d, K %d, difference %f\n", X, Y, K, difference);
	    }
	 }

   // Save best output image
   im_color Smooth(Noise);
   Smooth.Copy(Noise);
   Smooth.kNN(BestX, BestY, BestK);
   Smooth.WriteJpg(Name3);
   printf("Best = X %d, Y %d, K %d, difference %f\n",
	  BestX, BestY, BestK, BestDifference);
}

//============================================================
void search(char Input[])
{
   char Command[STRLEN];
   char Method[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Name3[STRLEN];

   if (sscanf(Input, "%s %s %s %s %s",
	      Command, Method, Name1, Name2, Name3) != 5)
      printf("Usage: search method infile infile outfile\n");
   else if (strcmp("median", Method) == 0)
      search_median(Name1, Name2, Name3);
   else if (strcmp("gaussian", Method) == 0)
      search_gaussian(Name1, Name2, Name3);
   else if (strcmp("knn", Method) == 0)
      search_knn(Name1, Name2, Name3);
}

//============================================================
void translate(char Input[])
{
   char Command[STRLEN];
   float Dx, Dy;
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Bound[STRLEN];

   if (sscanf(Input, "%s %s %f %f %s %s", 
      Command, Bound, &Dx, &Dy, Name1, Name2) != 6)
      printf("Usage: translate [wrap/clamp/zero] #dx #dy infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Translate(Dx, Dy, Bound[0]);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void rotate(char Input[])
{
   char Command[STRLEN];
   float Angle;
   int Cx, Cy;
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Bound[STRLEN];

   if (sscanf(Input, "%s %s %f %d %d %s %s",
      Command, Bound, &Angle, &Cx, &Cy, Name1, Name2) != 7)
      printf("Usage: rotate [wrap/clamp/zero] #angle #cx #cy infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Cx = Image1.R.Xdim/2;
      Cy = Image1.R.Ydim/2;
      Image1.Rotate(Angle, Cx, Cy, Bound[0]);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void scale(char Input[])
{
   char Command[STRLEN];
   float Sx, Sy;
   int Cx, Cy;
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Bound[STRLEN];

   if (sscanf(Input, "%s %s %f %f %d %d %s %s",
      Command, Bound, &Sx, &Sy, &Cx, &Cy, Name1, Name2) != 8)
      printf("Usage: scale [wrap/clamp/zero] #sx #sy #cx #cy infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Scale(Sx, Sy, Cx, Cy, Bound[0]);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void shear(char Input[])
{
   char Command[STRLEN];
   float Sx, Sy;
   int Cx, Cy;
   char Name1[STRLEN];
   char Name2[STRLEN];
   char Bound[STRLEN];

   if (sscanf(Input, "%s %s %f %f %d %d %s %s",
      Command, Bound, &Sx, &Sy, &Cx, &Cy, Name1, Name2) != 8)
      printf("Usage: shear [wrap/clamp/zero] #sx #sy #cx #cy infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Shear(Sx, Sy, Cx, Cy, Bound[0]);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void interpolate(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &Xdim, &Ydim, Name1, Name2) != 5)
      printf("Usage: interpolate #xdim #ydim infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Interpolate(Xdim, Ydim);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void interpolateNN(char Input[])
{
   char Command[STRLEN];
   int Xdim, Ydim;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &Xdim, &Ydim, Name1, Name2) != 5)
      printf("Usage: interpolateNN #xdim #ydim infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.InterpolateNN(Xdim, Ydim);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void extract(char Input[])
{
   char Command[STRLEN];
   int X1, Y1, X2, Y2;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %d %d %s %s",
	      Command, &X1, &X2, &Y1, &Y2, Name1, Name2) != 7)
      printf("Usage: extract #x1 #x2 #y1 #y2 infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Extract(X1, X2, Y1, Y2);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void fit_extract(char Input[])
{
   char Command[STRLEN];
   int X1, Y1, X2, Y2, Search;
   char Method;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %d %d %d %c %s %s",
	      Command, &X1, &X2, &Y1, &Y2, &Search, &Method, Name1, Name2) != 9)
      printf("Usage: fit_extract #x1 #x2 #y1 #y2 #search [g|+|-] infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.FitExtract(X1, X2, Y1, Y2, Search, Method);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void minmax(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];

   if (sscanf(Input, "%s %s", Command, Name1) != 2)
      printf("Usage: minmax infile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      short RMin, RMax, GMin, GMax, BMin, BMax;
      Image1.MinMax(RMin, RMax, GMin, GMax, BMin, BMax);

      // Write information 
      printf("R min = %d, max = %d\n", RMin, RMax);
      printf("G min = %d, max = %d\n", GMin, GMax);
      printf("B min = %d, max = %d\n", BMin, BMax);
   }
}

//============================================================
void statistics(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];

   if (sscanf(Input, "%s %s", Command, Name1) != 2)
      printf("Usage: statistics infile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      double RMean, RStdDev, RSkew;
      double GMean, GStdDev, GSkew;
      double BMean, BStdDev, BSkew;
      Image1.Statistics(RMean, RStdDev, RSkew,
			GMean, GStdDev, GSkew, BMean, BStdDev, BSkew);

      // Write information 
      printf("R %5.2lf %5.2lf %5.2lf\n", RMean, RStdDev, RSkew);
      printf("G %5.2lf %5.2lf %5.2lf\n", GMean, GStdDev, GSkew);
      printf("B %5.2lf %5.2lf %5.2lf\n", BMean, BStdDev, BSkew);
   }
}

//============================================================
void histogram(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];

   if (sscanf(Input, "%s %s", Command, Name1) != 2)
      printf("Usage: histogram infile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      int RHisto[256], GHisto[256], BHisto[256];
      Image1.Histogram(RHisto, 0, 255, GHisto, 0, 255, BHisto, 0, 255);

      // Write information 
      for (int i = 0; i < 256; i++)
	 printf("%5d %5d %5d %5d\n", i, RHisto[i], GHisto[i], BHisto[i]);
   }
}

//============================================================
void contrast(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];

   if (sscanf(Input, "%s %s", Command, Name1) != 2)
      printf("Usage: contrast infile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      printf("Contrast = %4.2f\n", Image1.Contrast());
   }
}

//============================================================
void difference(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: difference infile1 infile2\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);
      im_color Image2;
      Image2.ReadJpg(Name2);

      // Perform operation
      float difference;
      Image1.Difference(Image2, difference);
      printf("difference = %4.2f\n", difference);
   }
}

//============================================================
void gradient(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: gradient infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gradient();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void gradient_edges(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   float Threshold;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Sigma, &Threshold, Name1, Name2) != 5)
      printf("Usage: gradient_edges #sigma #threshold infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);
      Image1.GradientEdges(Threshold);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void laplacian(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: laplacian infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Laplacian();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void laplacian_edges(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   float Threshold;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Sigma, &Threshold, Name1, Name2) != 5)
      printf("Usage: laplacian_edges #sigma #threshold infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);
      Image1.LaplacianEdges(Threshold);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void canny(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: canny infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Canny();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void canny_edges(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   float Threshold;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Sigma, &Threshold, Name1, Name2) != 5)
      printf("Usage: canny_edges #sigma #threshold infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);
      Image1.CannyEdges(Threshold);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void curvature(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Sigma, Name1, Name2) != 4)
      printf("Usage: curvature #sigma infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);
      Image1.Curvature();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void extrema(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Sigma, Name1, Name2) != 4)
      printf("Usage: extrema #sigma infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);
      Image1.Extrema(2);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void corner(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Sigma, Name1, Name2) != 4)
      printf("Usage: corner #sigma infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Gaussian(Sigma);
      Image1.Corner();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void watershed(char Input[])
{
   char Command[STRLEN];
   float Sigma;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Sigma, Name1, Name2) != 4)
      printf("Usage: watershed #sigma infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);

      // Find watershed boundaries
      im_short Region;
      Image1.Watershed(Sigma, Region);

      // Save output images
      Image1.WriteJpg(Name2);
      Region.WriteJpg((char *)"region.jpg");
      Region.RegionBoundary(255);
      Region.WriteJpg((char *)"boundary.jpg");
   }
}

//============================================================
void region_grow_all(char Input[])
{
   char Command[STRLEN];
   float Threshold;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s",
	      Command, &Threshold, Name1, Name2) != 4)
      printf("Usage: region_grow_all #threshold infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.RegionGrow(Threshold);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void region_grow(char Input[])
{
   char Command[STRLEN];
   int X, Y;
   float Threshold;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %f %s %s",
	      Command, &X, &Y, &Threshold, Name1, Name2) != 6)
      printf("Usage: region_grow #x #y #threshold infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.RegionGrow(X, Y, Threshold);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void blob_color(char Input[])
{
   char Command[STRLEN];
   int Size;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %s %s", Command, &Size, Name1, Name2) != 4)
      printf("Usage: blob_color #size infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.ThresholdAutomatic(true);
      if (Size <= 0)
         Image1.BlobColor();
      else
         Image1.BlobColor(Size);
      Image1.Threshold(2,true);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void noise_uniform(char Input[])
{
   char Command[STRLEN];
   int Range;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %s %s", Command, &Range, Name1, Name2) != 4)
      printf("Usage: noise_uniform #range infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.NoiseUniform(Range);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void noise_gaussian(char Input[])
{
   char Command[STRLEN];
   float Stddev;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Stddev, Name1, Name2) != 4)
      printf("Usage: noise_gaussian #stddev infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.NoiseGaussian(Stddev);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void noise_impulse(char Input[])
{
   char Command[STRLEN];
   char Type[STRLEN];
   float Fraction;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %f %s %s",
	      Command, Type, &Fraction, Name1, Name2) != 5)
      printf("Usage: noise_impulse [s|p|b] #fraction infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.NoiseImpulse(Type[0], Fraction);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void freq_noise(char Input[])
{
   char Command[STRLEN];
   int Count;
   float Range;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %f %s %s", Command, &Count, &Range, Name1, Name2) != 5)
      printf("Usage: freq_noise #count #range infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.FreqNoise(Count, Range);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void fft(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: fft infile outfile\n");
   else
   {
      // Read input image
      im_float Image1;
      Image1.ReadJpg(Name1);
      im_complex Freq(Image1);
      Freq.FastFT();

      // Write output image
      Freq.GetAmplitude(Image1);
      // Image1.Translate(Image1.Xdim/2, Image1.Ydim/2);
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void ideal_lp(char Input[])
{
   char Command[STRLEN];
   float Freq;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Freq, Name1, Name2) != 4)
      printf("Usage: ideal_lp #freq infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.IdealLP(Freq);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void ideal_hp(char Input[])
{
   char Command[STRLEN];
   float Freq;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Freq, Name1, Name2) != 4)
      printf("Usage: ideal_hp #freq infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.IdealHP(Freq);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void ideal_bp(char Input[])
{
   char Command[STRLEN];
   float FreqL, freqH;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &FreqL, &freqH, Name1, Name2) != 5)
      printf("Usage: ideal_bp #freqL #freqH infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.IdealBP(FreqL, freqH);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void ideal_notch(char Input[])
{
   char Command[STRLEN];
   int u1, v1, u2, v2;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %d %d %s %s",
	      Command, &u1, &v1, &u2, &v2, Name1, Name2) != 7)
      printf("Usage: ideal_notch #u1 #v1 #u2 #v2 infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.IdealNotch(u1, v1, u2, v2);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void butterworth_lp(char Input[])
{
   char Command[STRLEN];
   float Freq, Power;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Freq, &Power, Name1, Name2) != 5)
      printf("Usage: butterworth_lp #freq #power infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.ButterworthLP(Freq, Power);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void butterworth_hp(char Input[])
{
   char Command[STRLEN];
   float Freq, Power, Weight;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %f %s %s",
	      Command, &Freq, &Power, &Weight, Name1, Name2) != 6)
      printf("Usage: butterworth_hp #freq #power #weight infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.ButterworthHP(Freq, Power, Weight);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void butterworth_bp(char Input[])
{
   char Command[STRLEN];
   float FreqL, FreqH, Power;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %f %s %s",
	      Command, &FreqL, &FreqH, &Power, Name1, Name2) != 6)
      printf("Usage: butterworth_bp #freqL #freqH #power infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.ButterworthBP(FreqL, FreqH, Power);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void butterworth_notch(char Input[])
{
   char Command[STRLEN];
   int Cu, Cv;
   float Freq, Power;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %f %f %s %s",
	      Command, &Cu, &Cv, &Freq, &Power, Name1, Name2) != 7)
      printf("Usage: butterworth_notch #cu #cv #freq #power infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.ButterworthNotch(Cu, Cv, Freq, Power);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void gauss_lp(char Input[])
{
   char Command[STRLEN];
   float Freq;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Freq, Name1, Name2) != 4)
      printf("Usage: gauss_lp #freq infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.GaussLP(Freq);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void gauss_hp(char Input[])
{
   char Command[STRLEN];
   float Freq, Weight;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Freq, &Weight, Name1, Name2) != 5)
      printf("Usage: gauss_hp #freq #weight infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.GaussHP(Freq, Weight);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void gauss_bp(char Input[])
{
   char Command[STRLEN];
   float Center, Freq;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Center, &Freq, Name1, Name2) != 5)
      printf("Usage: gauss_bp #center #freq infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.GaussBP(Center, Freq);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void gauss_notch(char Input[])
{
   char Command[STRLEN];
   int Cu, Cv;
   float Freq;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %f %s %s",
	      Command, &Cu, &Cv, &Freq, Name1, Name2) != 6)
      printf("Usage: gauss_notch #cu #cv #freq infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.GaussNotch(Cu, Cv, Freq);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void derivative(char Input[])
{
   char Command[STRLEN];
   int PartialX, PartialY;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &PartialX, &PartialY, Name1, Name2) != 5)
      printf("Usage: derivative #partialX #partialY infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Derivative(PartialX, PartialY);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void laplacian2(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: laplacian2 infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Laplacian2();

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void homomorphic(char Input[])
{
   char Command[STRLEN];
   float Freq, Weight;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %f %s %s",
	      Command, &Freq, &Weight, Name1, Name2) != 5)
      printf("Usage: homomorphic #freq #weight infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Homomorphic(Freq, Weight);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void sinc_lp(char Input[])
{
   char Command[STRLEN];
   float Width;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %f %s %s", Command, &Width, Name1, Name2) != 4)
      printf("Usage: sinc_lp #width infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.SincLP(Width);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void filter(char Input[])
{
   char Command[STRLEN];
   char Mask[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s %s", Command, Mask, Name1, Name2) != 4)
      printf("Usage: filter maskfile infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.Filter(Mask);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void inverse_filter(char Input[])
{
   char Command[STRLEN];
   char Mask[STRLEN];
   float Min = 0.001;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %f %s %s", Command, Mask, &Min, Name1, Name2) != 5)
      printf("Usage: inverse_filter maskfile #min infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.InverseFilter(Mask, Min);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void icon(char Input[])
{
   char Command[STRLEN];
   int Size = 200;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %s %s", Command, &Size, Name1, Name2) != 4)
      printf("Usage: icon #size infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Perform operation
      Image1.MakeIcon(Size);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void fade_border(char Input[])
{
   char Command[STRLEN];
   int Size = 2;
   int Border = 255;
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %d %d %s %s",
	      Command, &Size, &Border, Name1, Name2) != 5)
      printf("Usage: fade_border #size #border infile outfile\n");
   else
   {
      // Read input image
      im_color Image1;
      Image1.ReadJpg(Name1);

      // Interpolate image
      int MaxSize = 2000;
      if ((Image1.R.Xdim > MaxSize) || (Image1.R.Ydim > MaxSize))
      {
	 float xscale = (float) MaxSize / (float) Image1.R.Xdim;
	 float yscale = (float) MaxSize / (float) Image1.R.Ydim;
	 float scale = (xscale < yscale) ? xscale : yscale;
	 int xdim = (int) (Image1.R.Xdim * scale);
	 int ydim = (int) (Image1.R.Ydim * scale);
	 printf("Inperpolating from %d %d to %d %d\n",
		Image1.R.Xdim, Image1.R.Ydim, xdim, ydim);
	 Image1.Interpolate(xdim, ydim);
      }

      // Perform operation
      int xdim = Image1.R.Xdim;
      int ydim = Image1.R.Ydim;
      for (int x = 0; x < xdim; x++)
	 for (int y = 0; y < ydim; y++)
	 {
	    int dx = (x < xdim / 2) ? x : xdim - 1 - x;
	    int dy = (y < ydim / 2) ? y : ydim - 1 - y;
	    int dist = (dx < dy) ? dx : dy;
	    if (dist < Size)
	    {
	       float scale = (float) dist / (float) Size;
	       Image1.R.Data2D[y][x] = (short)
		  (Image1.R.Data2D[y][x] * scale + (1 - scale) * Border);
	       Image1.G.Data2D[y][x] = (short)
		  (Image1.G.Data2D[y][x] * scale + (1 - scale) * Border);
	       Image1.B.Data2D[y][x] = (short)
		  (Image1.B.Data2D[y][x] * scale + (1 - scale) * Border);
	    }
	 }

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void jpg2pgm(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: jpg2pgm infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadJpg(Name1);

      // Write output image
      Image1.WriteBinary(Name2);
   }
}

//============================================================
void pgm2jpg(char Input[])
{
   char Command[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];

   if (sscanf(Input, "%s %s %s", Command, Name1, Name2) != 3)
      printf("Usage: pgm2jpg infile outfile\n");
   else
   {
      // Read input image
      im_short Image1;
      Image1.ReadBinary(Name1);

      // Write output image
      Image1.WriteJpg(Name2);
   }
}

//============================================================
void motion(char Input[])
{
   char Command[STRLEN];
   char Dir[STRLEN];
   char Name1[STRLEN];
   char Name2[STRLEN];
   im_color Image1;
   im_color Image2;
   im_color Average;

   if (sscanf(Input, "%s %s", Command, Dir) != 2)
      printf("Usage: motion directory\n");
   else
   {
      // Get list of images
      sprintf(Command, "find %s | grep jpg > images.txt", Dir);
      if (system(Command));

      // Read first image
      FILE *fd = fopen("images.txt", "r");
      if (fscanf(fd, "%s", Name1));
      Image1.ReadJpg(Name1);
      Average.Copy(Image1);
   
      // Process sequence of images
      int count = 0;
      while (fscanf(fd, "%s", Name2) != EOF)
      {
         // Read second image
         Image2.ReadJpg(Name2);

         // Perform comparison
         float diff;
         Image2.Difference(Image1, diff);
         printf("%d, %f\n", count++, diff);

         // Save average image
         Average.Add(Image2);
         if (count % 10 == 0)
         {
            sprintf(Name2, "%s/ave-%d.jpg", Dir, count);
            Average.WriteJpg(Name2);
            Average.Copy(Image1);
         }

         // Swap images
         Image1.Swap(Image2);
      }
   }
}

//============================================================
void print_menu()
{
   printf("\ncommands:\n");
   printf("---------\n");
   printf("add infile1 infile2 outfile\n");
   printf("subtract infile1 infile2 outfile\n");
   printf("multiply infile1 infile2 outfile\n");
   printf("divide infile1 infile2 outfile\n");
   printf("\n");

   printf("threshold #value infile outfile\n");
   printf("threshold_automatic infile outfile\n");
   printf("window #low #high infile outfile\n");
   printf("trim #percentage infile outfile\n");
   printf("greymap #low #high infile outfile\n");
   printf("quantize #levels #iterations infile outfile\n");
   printf("invert infile outfile\n");
   printf("\n");

   printf("equalize #regions infile outfile\n");
   printf("unsharp_masking #iterations #weight infile outfile\n");
   printf("power #gamma infile outfile\n");
   printf("cubic #param infile outfile\n");
   printf("stretch #r1 #s1 #r2 #s2 infile outfile\n");
   printf("wallis #gain infile outfile\n");
   printf("whiten infile outfile\n");
   printf("\n");

   printf("average #xdim #ydim infile outfile\n");
   printf("binomial #iterations infile outfile\n");
   printf("convolve maskfile infile outfile\n");
   printf("median #nxdim #nydim infile outfile\n");
   printf("gaussian #sigma infile outfile\n");
   printf("adaptive_gaussian #sigma1 #sigma2 infile outfile\n");
   printf("outlier_removal #nxdim #nydim #threshold infile outfile\n");
   printf("knn #nxdim #nydim #k infile outfile\n");
   printf("alpha_mean #nxdim #nydim #alpha infile outfile\n");
   printf("morphology commands #radius infile outfile\n");
   printf("search method infile infile outfile\n");
   printf("\n");

   printf("translate [wrap/clamp/zero] #dx #dy infile outfile\n");
   printf("rotate [wrap/clamp/zero] #angle #cx #cy infile outfile\n");
   printf("scale [wrap/clamp/zero] #sx #sy #cx #cy infile outfile\n");
   printf("shear [wrap/clamp/zero] #sx #sy #cx #cy infile outfile\n");
   printf("interpolate #xdim #ydim infile outfile\n");
   printf("interpolateNN #xdim #ydim infile outfile\n");
   printf("extract #x1 #x2 #y1 #y2 infile outfile\n");
   printf("fit_extract #x1 #x2 #y1 #y2 #search [g|+|-] infile outfile\n");
   printf("\n");

   printf("minmax infile\n");
   printf("statistics infile\n");
   printf("histogram infile\n");
   printf("contrast infile\n");
   printf("difference infile1 infile2\n");
   printf("\n");

   printf("gradient infile outfile\n");
   printf("gradient_edges #sigma #threshold infile outfile\n");
   printf("laplacian infile outfile\n");
   printf("laplacian_edges #sigma #threshold infile outfile\n");
   printf("canny infile outfile\n");
   printf("canny_edges #sigma #threshold infile outfile\n");
   printf("curvature #sigma infile outfile\n");
   printf("extrema #sigma infile outfile\n");
   printf("corner #sigma infile outfile\n");
   printf("watershed #sigma infile outfile\n");
   printf("region_grow_all #threshold infile outfile\n");
   printf("region_grow #x #y #threshold infile outfile\n");
   printf("blob_color #size infile outfile\n");
   printf("\n");

   printf("noise_uniform #range infile outfile\n");
   printf("noise_gaussian #stddev infile outfile\n");
   printf("noise_impulse #fraction infile outfile\n");
   printf("freq_noise #count #range infile outfile\n");
   printf("\n");

   printf("fft infile outfile\n");
   printf("ideal_lp #freq infile outfile\n");
   printf("ideal_hp #freq infile outfile\n");
   printf("ideal_bp #freqL #freqH infile outfile\n");
   printf("ideal_notch #u1 #v1 #u2 #v2 infile outfile\n");
   printf("butterworth_lp #freq #power infile outfile\n");
   printf("butterworth_hp #freq #power #weight infile outfile\n");
   printf("butterworth_bp #freqL #freqH #power infile outfile\n");
   printf("butterworth_notch #cu #cv #freq #power infile outfile\n");
   printf("gauss_lp #freq infile outfile\n");
   printf("gauss_hp #freq #weight infile outfile\n");
   printf("gauss_bp #center #freq infile outfile\n");
   printf("gauss_notch #cu #cv #freq infile outfile\n");
   printf("\n");

   printf("derivative #partialX #partialY infile outfile\n");
   printf("laplacian2 infile outfile\n");
   printf("homomorphic #freq #weight infile outfile\n");
   printf("sinc_lp #width infile outfile\n");
   printf("filter maskfile infile outfile\n");
   printf("inverse_filter maskfile #min infile outfile\n");
   printf("\n");

   printf("icon #size infile outfile\n");
   printf("fade_border #size #border infile outfile\n");
   printf("jpg2pgm infile outfile\n");
   printf("pgm2jpg infile outfile\n");
   printf("\n");

   printf("quit\n");
}

//============================================================
void execute_command(char *Input)
{
   // Get command name
   char Command[STRLEN];
   sscanf(Input, "%s", Command);
   if (strcmp(Command, "quit") == 0)
      exit(0);

   // Execute command
   else if (strcmp(Command, "add") == 0)
      add(Input);
   else if (strcmp(Command, "subtract") == 0)
      subtract(Input);
   else if (strcmp(Command, "multiply") == 0)
      multiply(Input);
   else if (strcmp(Command, "divide") == 0)
      divide(Input);

   else if (strcmp(Command, "threshold") == 0)
      threshold(Input);
   else if (strcmp(Command, "threshold_automatic") == 0)
      threshold_automatic(Input);
   else if (strcmp(Command, "window") == 0)
      window(Input);
   else if (strcmp(Command, "trim") == 0)
      trim(Input);
   else if (strcmp(Command, "greymap") == 0)
      greymap(Input);
   else if (strcmp(Command, "quantize") == 0)
      quantize(Input);
   else if (strcmp(Command, "invert") == 0)
      invert(Input);

   else if (strcmp(Command, "equalize") == 0)
      equalize(Input);
   else if (strcmp(Command, "unsharp_masking") == 0)
      unsharp_masking(Input);
   else if (strcmp(Command, "power") == 0)
      power(Input);
   else if (strcmp(Command, "cubic") == 0)
      cubic(Input);
   else if (strcmp(Command, "stretch") == 0)
      stretch(Input);
   else if (strcmp(Command, "wallis") == 0)
      wallis(Input);
   else if (strcmp(Command, "whiten") == 0)
      whiten(Input);

   else if (strcmp(Command, "average") == 0)
      average(Input);
   else if (strcmp(Command, "binomial") == 0)
      binomial(Input);
   else if (strcmp(Command, "convolve") == 0)
      convolve(Input);
   else if (strcmp(Command, "median") == 0)
      median(Input);
   else if (strcmp(Command, "gaussian") == 0)
      gaussian(Input);
   else if (strcmp(Command, "adaptive_gaussian") == 0)
      adaptive_gaussian(Input);
   else if (strcmp(Command, "outlier_removal") == 0)
      outlier_removal(Input);
   else if (strcmp(Command, "knn") == 0)
      knn(Input);
   else if (strcmp(Command, "alpha_mean") == 0)
      alpha_mean(Input);
   else if (strcmp(Command, "morphology") == 0)
      morphology(Input);
   else if (strcmp(Command, "search") == 0)
      search(Input);

   else if (strcmp(Command, "translate") == 0)
      translate(Input);
   else if (strcmp(Command, "rotate") == 0)
      rotate(Input);
   else if (strcmp(Command, "scale") == 0)
      scale(Input);
   else if (strcmp(Command, "shear") == 0)
      shear(Input);
   else if (strcmp(Command, "interpolate") == 0)
      interpolate(Input);
   else if (strcmp(Command, "interpolateNN") == 0)
      interpolateNN(Input);
   else if (strcmp(Command, "extract") == 0)
      extract(Input);
   else if (strcmp(Command, "fit_extract") == 0)
      fit_extract(Input);

   else if (strcmp(Command, "minmax") == 0)
      minmax(Input);
   else if (strcmp(Command, "statistics") == 0)
      statistics(Input);
   else if (strcmp(Command, "histogram") == 0)
      histogram(Input);
   else if (strcmp(Command, "contrast") == 0)
      contrast(Input);
   else if (strcmp(Command, "difference") == 0)
      difference(Input);

   else if (strcmp(Command, "gradient") == 0)
      gradient(Input);
   else if (strcmp(Command, "gradient_edges") == 0)
      gradient_edges(Input);
   else if (strcmp(Command, "laplacian") == 0)
      laplacian(Input);
   else if (strcmp(Command, "laplacian_edges") == 0)
      laplacian_edges(Input);
   else if (strcmp(Command, "canny") == 0)
      canny(Input);
   else if (strcmp(Command, "canny_edges") == 0)
      canny_edges(Input);
   else if (strcmp(Command, "curvature") == 0)
      curvature(Input);
   else if (strcmp(Command, "extrema") == 0)
      extrema(Input);
   else if (strcmp(Command, "corner") == 0)
      corner(Input);
   else if (strcmp(Command, "watershed") == 0)
      watershed(Input);
   else if (strcmp(Command, "region_grow_all") == 0)
      region_grow_all(Input);
   else if (strcmp(Command, "region_grow") == 0)
      region_grow(Input);
   else if (strcmp(Command, "blob_color") == 0)
      blob_color(Input);

   else if (strcmp(Command, "noise_uniform") == 0)
      noise_uniform(Input);
   else if (strcmp(Command, "noise_gaussian") == 0)
      noise_gaussian(Input);
   else if (strcmp(Command, "noise_impulse") == 0)
      noise_impulse(Input);
   else if (strcmp(Command, "freq_noise") == 0)
      freq_noise(Input);

   else if (strcmp(Command, "fft") == 0)
      fft(Input);
   else if (strcmp(Command, "ideal_lp") == 0)
      ideal_lp(Input);
   else if (strcmp(Command, "ideal_hp") == 0)
      ideal_hp(Input);
   else if (strcmp(Command, "ideal_bp") == 0)
      ideal_bp(Input);
   else if (strcmp(Command, "ideal_notch") == 0)
      ideal_notch(Input);
   else if (strcmp(Command, "butterworth_lp") == 0)
      butterworth_lp(Input);
   else if (strcmp(Command, "butterworth_hp") == 0)
      butterworth_hp(Input);
   else if (strcmp(Command, "butterworth_bp") == 0)
      butterworth_bp(Input);
   else if (strcmp(Command, "butterworth_notch") == 0)
      butterworth_notch(Input);
   else if (strcmp(Command, "gauss_lp") == 0)
      gauss_lp(Input);
   else if (strcmp(Command, "gauss_hp") == 0)
      gauss_hp(Input);
   else if (strcmp(Command, "gauss_bp") == 0)
      gauss_bp(Input);
   else if (strcmp(Command, "gauss_notch") == 0)
      gauss_notch(Input);

   else if (strcmp(Command, "derivative") == 0)
      derivative(Input);
   else if (strcmp(Command, "laplacian2") == 0)
      laplacian2(Input);
   else if (strcmp(Command, "homomorphic") == 0)
      homomorphic(Input);
   else if (strcmp(Command, "sinc_lp") == 0)
      sinc_lp(Input);
   else if (strcmp(Command, "filter") == 0)
      filter(Input);
   else if (strcmp(Command, "inverse_filter") == 0)
      inverse_filter(Input);

   else if (strcmp(Command, "icon") == 0)
      icon(Input);
   else if (strcmp(Command, "fade_border") == 0)
      fade_border(Input);
   else if (strcmp(Command, "jpg2pgm") == 0)
      jpg2pgm(Input);
   else if (strcmp(Command, "pgm2jpg") == 0)
      pgm2jpg(Input);
   else if (strcmp(Command, "motion") == 0)
      motion(Input);
   else
      print_menu();
}

//============================================================
int main(int argc, char *argv[])
{
   // Process command line arguments
   char Input[STRLEN] = "";
   if (argc > 1)
   {
      // Combine arguments
      for (int i = 1; i < argc; i++)
      {
	 strcat(Input, argv[i]);
	 strcat(Input, " ");
      }

      // Execute user command
      printf("%s\n", Input);
      if (strlen(Input) > 0)
      {
         struct timeval begin, end;
         gettimeofday(&begin, NULL);
	 execute_command(Input);
         gettimeofday(&end, NULL);
         printf("cpu sec = %f\n", get_cpu_time(begin, end));
      }
   }

   // Loop executing user commands
   else
   {
      while (true)
      {
	 // Read user command
	 printf("Enter command: ");
	 char *res = fgets(Input, STRLEN, stdin);

	 // Execute user command
	 if ((res != NULL) && (strlen(Input) > 0))
	    execute_command(Input);
      }
   }
}
