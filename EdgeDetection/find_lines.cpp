//============================================================
//  File:       find_lines.cpp
//  Purpose:    Find line equations for edge points in an image. 
//  Author:     Yirong Chen
//  Date:       Fall 2017
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <cmath>
using namespace std;

//============================================================
void process(char *Name1, char *Name2)
{
   // Read input image
   im_float Input;
   im_color Output;
   Output.ReadJpg(Name1);
   Input.ReadJpg(Name1);
    
   int Xdim = Input.Xdim;
   int Ydim = Input.Ydim;


   // Perform Gaussian smoothing
   float Sigma = 1;
   cout << "Enter size of Gaussian blur filter: ";
   cin >> Sigma;
   Input.Gaussian(Sigma);
    
    ////Set Gradient TH
    int gradient_TH = 50;
    cout << "Enter Gradient Threshold: ";
    cin >> gradient_TH;

   // Create gradient image
   im_float Gradient(Xdim, Ydim);

   // Loop over interior pixels
   float min_value = 255;
   float max_value = 0;
   for (int y = 1; y < Ydim - 1; y++)
   for (int x = 1; x < Xdim - 1; x++)
   { 
      // Partial derivatives using Sobel weights
      float dx = Input.Data2D[y + 1][x + 1] 
               + Input.Data2D[y][x + 1] * 2 
               + Input.Data2D[y - 1][x + 1]
               - Input.Data2D[y + 1][x - 1] 
               - Input.Data2D[y][x - 1] * 2 
               - Input.Data2D[y - 1][x - 1]; 
      float dy = Input.Data2D[y + 1][x + 1] 
               + Input.Data2D[y + 1][x] * 2 
               + Input.Data2D[y + 1][x - 1]
               - Input.Data2D[y - 1][x + 1] 
               - Input.Data2D[y - 1][x] * 2 
               - Input.Data2D[y - 1][x - 1]; 

      // Calculate gradient magnitude
      Gradient.Data2D[y][x] = sqrt(dx*dx + dy*dy) / 8.0; 

      // Update min and max gradient value
      if (min_value > Gradient.Data2D[y][x])
         min_value = Gradient.Data2D[y][x];
      if (max_value < Gradient.Data2D[y][x])
         max_value = Gradient.Data2D[y][x];
   }

   // Write min and max gradient values
   cout << "Minimum gradient value: " << min_value << endl;
   cout << "Maximum gradient value: " << max_value << endl;


    //// Create modified gradient image
    vector<int> edg_x;
    vector<int> edg_y;
    int edge_number = 0;

    //// loop over the gradient values
    for (int y = 1; y < Ydim - 1; y++)
    for (int x = 1; x < Xdim - 1; x++)
    {
        if (Gradient.Data2D[y][x] >= gradient_TH)
        {
            edg_x.push_back(x);
            edg_y.push_back(y);
        }
    }
   
    //// find line equation for edge points
    int point1, point2;
    float A, B;
    float x1, x2, y1, y2;
    float dx, dy;
    
    vector<int> kset_x, kset_y, kset_index;
    
    float d_TH = 2.50;
    int kset_TH = 200;
    
    
    //==================================================== begin to find lines
    for (int i = 0; i < 10000; i++)
    {
    
        //// randomly select 2 points
        point1 = rand() % edg_x.size();
        point2 = rand() % edg_x.size();
       
        ////calculate the line equation
        if (point1 != point2 && point1 != 0 && point2 != 0)
        {
            
            x1 = edg_x[point1]; y1 = edg_y[point1];
            x2 = edg_x[point2]; y2 = edg_y[point2];
            dx = x2 - x1; dy = y2 - y1;
            
            if (dx != 0)
            {
                B = dy/dx;
                A = y1 - B * x1;
            }

        }else
            continue;

        //// Save points in distance d_TH  into kset
        for (int j = 0; j < edg_x.size(); j++)
        {
            if (edg_x[j] != 0 && edg_y[j] != 0)
            {
                float distance = fabs(A + B * edg_x[j] - edg_y[j]) / sqrt(1 + B * B);
                
                if (distance < d_TH)
                {
                    kset_x.push_back(edg_x[j]);
                    kset_y.push_back(edg_y[j]);
                    kset_index.push_back(j);
                }
            }
        }
  
        
        //// See if there's enough points nearby
        if (kset_x.size() > kset_TH)
        {
            edge_number++;
            
            ////fit high quality equation by using Least Square Line Equation
            float Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
            
            for (int k = 0; k < kset_x.size(); k++)
            {
                Sx += kset_x[k];
                Sy += kset_y[k];
                Sxx += kset_x[k] * kset_x[k];
                Sxy += kset_x[k] * kset_y[k];
            }

            float denominator = kset_x.size() * Sxx - Sx * Sx;
            
            if (denominator != 0)
            {
                A = (Sxx * Sy - Sx * Sxy) / denominator;
                B = (-Sx * Sy + kset_x.size() * Sxy) / denominator;
            }
            
            ////-------- Draw the fitting line ---------
            for (int y = 1; y < Ydim - 1; y++)
            for (int x = 1; x < Xdim - 1; x++)
            {
                float dis = fabs(A + B * x - y) / sqrt(1 + B * B);
                if (dis < 1.5)
                    Output.DrawPoint(x, y, 2, 204, 0, 204);
            }
            
            //// Remove the k points by setting their index in the set edg as zero
            for (int h = 0; h < kset_index.size(); h++)
            {
                edg_x[kset_index[h]] = 0;
                edg_y[kset_index[h]] = 0;
            }
    

        }////end if kset_TH
        
        
        kset_x.clear();
        kset_y.clear();
        kset_index.clear();
        
        

    }////end the FOR LOOP
    
    
    
    cout << "Found " << edge_number << " edges!" << endl;
    
    //// Write image with edges
    Output.WriteJpg(Name2);
    
   // Write output image
   //Gradient.WriteJpg(Name2);

}////end process


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
   process(Name1, Name2);
}
