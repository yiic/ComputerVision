//============================================================
//  File:       smoothing.cpp
//  Purpose:    Implements solution to CSCE 5683 Fall 2010 hw#3
//  Author:     John Gauch
//  Date:       Fall 2010
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"

bool debug = true;

//============================================================
void search_binomial(im_short &Input, im_short &Noise, char *Output)
{
   // Search for best smoothing parameters
   int BestCount = 0;
   float BestMSE = 256;
   im_short Smooth;
   Smooth.Copy(Noise);
   for (int count = 1; count <= 5; count++)
      {
	 Smooth.Binomial();
	 float MSE;
	 Smooth.Difference(Input, MSE);
	 if (debug) printf("count %d, MSE %f\n", count, MSE);
	 if (MSE < BestMSE)
	 {
	    BestCount = count;
	    BestMSE = MSE;
	 }
      }

   // Save best output image
   Smooth.Copy(Noise);
   for (int count = 1; count <= BestCount; count++)
      Smooth.Binomial();
   Smooth.WriteJpg(Output);
   printf("binomial: count %d, best MSE %f\n", BestCount, BestMSE);
}

//============================================================
void search_median(im_short &Input, im_short &Noise, char *Output)
{
   // Search for best smoothing parameters
   int BestSize = 0;
   float BestMSE = 256;
   im_short Smooth;
   for (int size = 1; size <= 5; size++)
      {
	 Smooth.Copy(Noise);
	 Smooth.Median(size, size);
	 float MSE;
	 Smooth.Difference(Input, MSE);
	 if (debug) printf("size %d, MSE %f\n", size, MSE);
	 if (MSE < BestMSE)
	 {
	    BestSize = size;
	    BestMSE = MSE;
	 }
      }

   // Save best output image
   Smooth.Copy(Noise);
   Smooth.Median(BestSize, BestSize);
   Smooth.WriteJpg(Output);
   printf("median: size %d, best MSE %f\n", BestSize, BestMSE);
}

//============================================================
void search_gaussian(im_short &Input, im_short &Noise, char *Output)
{
   // Search for best smoothing parameters
   float BestSigma = 0;
   float BestMSE = 256;
   im_short Smooth;
   for (float sigma = 0.1; sigma <= 5.0; sigma += 0.1)
      {
	 Smooth.Copy(Noise);
	 Smooth.Gaussian(sigma);
	 float MSE;
	 Smooth.Difference(Input, MSE);
	 if (debug) printf("sigma %f, MSE %f\n", sigma, MSE);
	 if (MSE < BestMSE)
	 {
	    BestSigma = sigma;
	    BestMSE = MSE;
	 }
      }

   // Save best output image
   Smooth.Copy(Noise);
   Smooth.Gaussian(BestSigma);
   Smooth.WriteJpg(Output);
   printf("gaussian: sigma %f, best MSE %f\n", BestSigma, BestMSE);
}

//============================================================
void search_outlier_removal(im_short &Input, im_short &Noise, char *Output)
{
   // Search for best smoothing parameters
   int BestSize = 0;
   float BestThreshold = 0;
   float BestMSE = 256;
   im_short Smooth;
   for (int size = 1; size <= 5; size++)
      for (float threshold = 0.1; threshold <= 5; threshold += 0.1)
	 {
	    Smooth.Copy(Noise);
	    Smooth.OutlierRemoval(size, size, threshold);
	    float MSE;
	    Smooth.Difference(Input, MSE);
	    if (debug) printf("size %d, threshold %f, MSE %f\n", size, threshold, MSE);
	    if (MSE < BestMSE)
	    {
	       BestSize = size;
	       BestThreshold = threshold;
	       BestMSE = MSE;
	    }
	 }

   // Save best output image
   Smooth.Copy(Noise);
   Smooth.OutlierRemoval(BestSize, BestSize, BestThreshold);
   Smooth.WriteJpg(Output);
   printf("outlier_removal: size %d, threshold %f, best MSE %f\n", 
      BestSize, BestThreshold, BestMSE);
}

//============================================================
void search_knn(im_short &Input, im_short &Noise, char *Output)
{
   // Search for best smoothing parameters
   int BestSize = 0;
   int BestK = 0;
   float BestMSE = 256;
   im_short Smooth;
   for (int size = 1; size <= 5; size++)
      for (int K = 1; K <= size * size; K++)
	 {
	    Smooth.Copy(Noise);
	    Smooth.kNN(size, size, K);
	    float MSE;
	    Smooth.Difference(Input, MSE);
	    if (debug) printf("size %d, K %d, MSE %f\n", size, K, MSE);
	    if (MSE < BestMSE)
	    {
	       BestSize = size;
	       BestK = K;
	       BestMSE = MSE;
	    }
	 }

   // Save best output image
   Smooth.Copy(Noise);
   Smooth.kNN(BestSize, BestSize, BestK);
   Smooth.WriteJpg(Output);
   printf("knn: size %d, K %d, best MSE %f\n", BestSize, BestK, BestMSE);
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
   
   // Read input image 
   im_short Input;
   Input.ReadJpg(Name1);

   // Perform uniform noise removal
   im_short Noise(Input);
   Noise.NoiseUniform(25);
   float MSE;
   Noise.Difference(Input, MSE);
   Noise.WriteJpg((char *)"uniform.jpg");
   printf("\nuniform noise error: %f\n", MSE);
   search_binomial(Input, Noise, (char *)"uniform_binomial.jpg");
   search_median(Input, Noise, (char *)"uniform_median.jpg");
   search_gaussian(Input, Noise, (char *)"uniform_gaussian.jpg");
   search_outlier_removal(Input, Noise, (char *)"uniform_outlier_removal.jpg");
   search_knn(Input, Noise, (char *)"uniform_knn.jpg");

   // Perform gaussian noise removal
   Noise.Copy(Input);
   Noise.NoiseGaussian(10);
   Noise.Difference(Input, MSE);
   Noise.WriteJpg((char *)"gaussian.jpg");
   printf("\ngaussian noise error: %f\n", MSE);
   search_binomial(Input, Noise, (char *)"gaussian_binomial.jpg");
   search_median(Input, Noise, (char *)"gaussian_median.jpg");
   search_gaussian(Input, Noise, (char *)"gaussian_gaussian.jpg");
   search_outlier_removal(Input, Noise, (char *)"gaussian_outlier_removal.jpg");
   search_knn(Input, Noise, (char *)"gaussian_knn.jpg");

   // Perform impulse noise removal
   Noise.Copy(Input);
   Noise.NoiseImpulse('b', 0.05);
   Noise.Difference(Input, MSE);
   Noise.WriteJpg((char *)"impulse.jpg");
   printf("\nimpulse noise error: %f\n", MSE);
   search_binomial(Input, Noise, (char *)"impulse_binomial.jpg");
   search_median(Input, Noise, (char *)"impulse_median.jpg");
   search_gaussian(Input, Noise, (char *)"impulse_gaussian.jpg");
   search_outlier_removal(Input, Noise, (char *)"impulse_outlier_removal.jpg");
   search_knn(Input, Noise, (char *)"impulse_knn.jpg");
}
