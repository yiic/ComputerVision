//============================================================
//  File:       stereo.cpp
//  Purpose:    Given a pair of images, calculate the disparity of each point.
//  Author:     Yirong Chen
//  Date:       Fall 2017
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//============================================================
void stereo(char *Name1, char *Name2, char *Name3)
{
    // Read left image
    im_float Left;
    Left.ReadJpg(Name1);
    
    // Read right image
    im_float Right;
    Right.ReadJpg(Name2);
    
    //Diff of two images
    //im_float Diff(Left);
    //Diff.Subtract(Right);
    
    // Disparities Left -> Right
    im_float L2R(Left);
    
    // Perform stereo matching================================
    int block_size = 5;
    vector <int> ssd_err;
    short disparity;
    
    // Loop over left image
    for (int y = 0; y < (Left.Ydim - 5); y++)
    for (int x = 0; x < (Left.Xdim - 5); x++)
    {
        //Loop over x location in right image (rx)
        for (int rx = 0; rx < (Right.Xdim - 5); rx++)
        {
            int ssd = 0;
            
            //loop within a matching block
            for (int dy = 0; dy <= block_size; dy++)
            for(int dx = 0; dx <= block_size; dx++)
            {
                ////ssd += pow(Left.Data2D[y + dy][x + dx] - Right.Data2D[y + dy][rx + dx], 2) + abs(rx - x);
                ssd += (Left.Data2D[y + dy][x + dx] - Right.Data2D[y + dy][rx + dx]) * (Left.Data2D[y + dy][x + dx] - Right.Data2D[y + dy][rx + dx]) + abs(rx - x);
            }
            
            //save the ssd of current block in the ssd_err
            ssd_err.push_back(ssd);
        }
        
        //find the minimum ssd
        int min_ssd = ssd_err[0];
        int best_rx = 0;
        
        for (int i = 0; i < ssd_err.size(); i++)
        {
            if (ssd_err[i] < min_ssd)
            {
                min_ssd = ssd_err[i];
                best_rx = i;
            }
        }
        
        //cout << "best_rx = " << best_rx << ", x = " << x << endl;
        
        //save disparity abs(rx-x) to image L2R
        disparity = abs(best_rx - x);
        L2R.Data2D[y][x] = disparity;
        
        ssd_err.clear();
        
        
        //cout << "(x,y) = " << "(" << x << "," << y << ")" <<endl;
        //mcout << "disparity: " << disparity << endl;
    }
    

    
    // Write output image
    L2R.WriteJpg(Name3);
    cout << "A disparity image is generated in the same directory." <<endl;
}

//============================================================
int main(int argc, char *argv[])
{
    // Get input file name
    char Name1[STRLEN];
    char Name2[STRLEN];
    char Name3[STRLEN];
    if (argc == 4)
    {
        strcpy(Name1, argv[1]);
        strcpy(Name2, argv[2]);
        strcpy(Name3, argv[3]);
    }
    else
    {
        printf("Enter name of left image: ");
        if (scanf("%s", Name1) != 1);
        printf("Enter name of right image: ");
        if (scanf("%s", Name2) != 1);
        printf("Enter name of output image: ");
        if (scanf("%s", Name3) != 1);
    }
    
    // Perform stereo matching
    stereo(Name1, Name2, Name3);
}
