//============================================================
//  File:       segment.cpp
//  Purpose:    inplement and test an image segementation algorithm
//  Author:     Yirong Chen
//  Date:       Fall 2017
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include "../programs/set.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//============================================================ Process
void process(char *Name1, char *Name2)
{
    // Read input image
    im_float Image1;
    Image1.ReadJpg(Name1);
    
    //Get Gaussian smoothing sigma value
    float Sigma = 1;
    cout << "Enter Gaussian smoothing sigma value: ";
    cin >> Sigma;
    
    //Get Merge TH value
    float Merge_TH = 1;
    cout << "Enter Merge Threshold (intensity difference between 2 adjacent regions): ";
    cin >> Merge_TH;
    
    //Find watershed regions
    im_short region;
    Image1.Watershed(Sigma, region);
    
    int Xdim = Image1.Xdim;
    int Ydim = Image1.Ydim;

    short min, max;
    region.MinMax(min, max);
    
    //total number of regions
    int count = max + 1;
    cout << "Number of regions (watershed): " << count << endl;
    
    vector <int> size(count);
    vector <int> ave(count);
    vector <vector <int> > adjacent(count);
    
    //get each region's size and average intensity
    for (int y = 1; y < Ydim - 1; y++)
    for (int x = 1; x < Xdim - 1; x++)
    {
        int reg = region.Data2D[y][x];
        ave[reg] = Image1.Data2D[y][x];
        size[reg]++;
    }

    //// Get adjacency list for each region
    // Loop over image from left to right
    for (int y = 1; y < Ydim - 1; y++)
    for (int x = 1; x < Xdim - 1; x++)
    {
        int reg1 = region.Data2D[y][x];
        int reg2 = region.Data2D[y][x+1];
        
        if (reg1 != reg2)
            adjacent[reg1].push_back(reg2);
    }
    // Loop over image from vetical again
    for (int x = 1; x < Xdim - 1; x++)
    for (int y = 1; y < Ydim - 1; y++)
    {
        int reg1 = region.Data2D[y][x];
        int reg2 = region.Data2D[y][x];
        
        if (reg1 != reg2)
            adjacent[reg1].push_back(reg2);
    }
    //remove duplicated values
    for (int i = 0; i < count; i++){
        sort( adjacent[i].begin(), adjacent[i].end() );
        adjacent[i].erase( unique( adjacent[i].begin(), adjacent[i].end() ), adjacent[i].end() );
    }
    
    //======================================== Merge begin
    Set merge(count);
    
    for (int i = 0; i < adjacent.size(); i++)
    for (int j = 0; j < adjacent[i].size(); j++)
    {
        if (merge.Find(i) != merge.Find(j)){
            if (fabs(ave[i] - ave[j]) <= Merge_TH){
                merge.Union(i, j);
                int new_size = size[i] + size[j];
                float new_ave = (size[i] * ave[i] + size[j] * ave[j]) / new_size;
                size[i] = size[j] = new_size;
                ave[i] = ave[j] = new_ave;
            }
        }
    }
    
    //Modify merged image
    for (int y = 1; y < Ydim - 1; y++)
    for (int x = 1; x < Xdim - 1; x++)
    {
        int reg = region.Data2D[y][x];
        Image1.Data2D[y][x] = ave[reg];
    }
    //Modify new region image
    int c = count;
    for (int y = 1; y < Ydim - 1; y++)
    for (int x = 1; x < Xdim - 1; x++)
    {
        int reg = region.Data2D[y][x];
        int parent_reg = merge.Find(reg);
        
        region.Data2D[y][x] = parent_reg;
    }
    
//    //total number of regions
//    region.MinMax(min, max);
//    int new_count = max + 1;
//    //cout << "Number of regions (after merging): " << new_count << endl;
    
    
    Image1.WriteJpg(Name2);
    region.WriteJpg((char *)"new_region.jpg");
    region.RegionBoundary(255);
    region.WriteJpg((char *)"new_boundary.jpg");

}//end process


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
