//===========================================================================
//  File:       feature.cpp
//  Purpose:    Feature detection and matching for a pair of iamges.
//  Author:     Yirong Chen
//  Date:       Fall 2017
//===========================================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#define PI 3.14159265
using namespace std;

// Locate blobs: calcualte local maxima of LoG  =============================
void locate_blob(im_float &image, int sigma, int radius)
{
    image.Gaussian(sigma);
    image.Laplacian();
    image.Extrema(radius);
}

// Calculate image features =================================================
void image_features(im_float image, im_float image_blob, map<pair<int, int>, vector <float> > &im_features, string filename, int sigma)
{
    //// calculate image gradient mag and dir
    im_float mag(image.Xdim,image.Ydim);
    im_float dir(image.Xdim,image.Ydim);
    
    for (int y = 1; y < image.Ydim - 1; y++)
    for (int x = 1; x < image.Xdim - 1; x++)
    {
        float dX = (image.Data2D[y + 1][x + 1]
                    + image.Data2D[y][x + 1] * 2
                    + image.Data2D[y - 1][x + 1]
                    - image.Data2D[y + 1][x - 1]
                    - image.Data2D[y][x - 1] * 2
                    - image.Data2D[y - 1][x - 1])/8.0;
        
        float dY = (image.Data2D[y + 1][x + 1]
                    + image.Data2D[y + 1][x] * 2
                    + image.Data2D[y + 1][x - 1]
                    - image.Data2D[y - 1][x + 1]
                    - image.Data2D[y - 1][x] * 2
                    - image.Data2D[y - 1][x - 1])/8.0;
        
        mag.Data2D[y][x] = (PIXEL)sqrt(dX * dX + dY * dY);
        dir.Data2D[y][x] = (PIXEL)atan2(dY, dX) * 180 / PI + 180;
    }
    
    //// calcualte all features vlaues for each point of the bolbs in an image
    // create feature vector for each (x, y)
    int by, bx;
    vector <float> feature_vec;
    for (int h = 0; h < 32; h++)
        feature_vec.push_back(0.0);

    // Loop over image
    for (int y = 15; y < image.Ydim - 16; y++)
    for (int x = 15; x < image.Xdim - 16; x++)
    {
        if (image_blob.Data2D[y][x] > 0)
        {
            // 1st histogram
            for (by = y - 15; by <= y; by++)
            for (bx = x - 15; bx <= x; bx++)
            {
                if (dir.Data2D[by][bx] >= 0 and dir.Data2D[by][bx] < 45)
                    feature_vec[0] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 45 and dir.Data2D[by][bx] < 90)
                    feature_vec[1] += mag.Data2D[by][bx];
                    
                if (dir.Data2D[by][bx] >= 90 and dir.Data2D[by][bx] < 135)
                    feature_vec[2] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 135 and dir.Data2D[by][bx] < 180)
                    feature_vec[3] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 180 and dir.Data2D[by][bx] < 225)
                    feature_vec[4] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 225 and dir.Data2D[by][bx] < 270)
                    feature_vec[5] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 270 and dir.Data2D[by][bx] < 315)
                    feature_vec[6] += mag.Data2D[by][bx];
                
                if (dir.Data2D[by][bx] >= 315 and dir.Data2D[by][bx] <= 360)
                    feature_vec[7] += mag.Data2D[by][bx];
            }
            
            // 2ed histogram
            for (by = y - 15; by <= y; by++)
            for (bx = x + 1; bx <= x + 16; bx++)
            {
                if (dir.Data2D[by][bx] >= 0 and dir.Data2D[by][bx] < 45)
                    feature_vec[8] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 45 and dir.Data2D[by][bx] < 90)
                    feature_vec[9] += mag.Data2D[by][bx];
                    
                if (dir.Data2D[by][bx] >= 90 and dir.Data2D[by][bx] < 135)
                    feature_vec[10] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 135 and dir.Data2D[by][bx] < 180)
                    feature_vec[11] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 180 and dir.Data2D[by][bx] < 225)
                    feature_vec[12] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 225 and dir.Data2D[by][bx] < 270)
                    feature_vec[13] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 270 and dir.Data2D[by][bx] < 315)
                    feature_vec[14] += mag.Data2D[by][bx];
                
                if (dir.Data2D[by][bx] >= 315 and dir.Data2D[by][bx] <= 360)
                    feature_vec[15] += mag.Data2D[by][bx];
            }
            
            // 3rd histogram
            for (by = y + 1; by <= y + 16; by++)
            for (bx = x - 15; bx <= x; bx++)
            {
                if (dir.Data2D[by][bx] >= 0 and dir.Data2D[by][bx] < 45)
                    feature_vec[16] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 45 and dir.Data2D[by][bx] < 90)
                    feature_vec[17] += mag.Data2D[by][bx];
                    
                if (dir.Data2D[by][bx] >= 90 and dir.Data2D[by][bx] < 135)
                    feature_vec[18] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 135 and dir.Data2D[by][bx] < 180)
                    feature_vec[19] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 180 and dir.Data2D[by][bx] < 225)
                    feature_vec[20] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 225 and dir.Data2D[by][bx] < 270)
                    feature_vec[21] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 270 and dir.Data2D[by][bx] < 315)
                    feature_vec[22] += mag.Data2D[by][bx];
                
                if (dir.Data2D[by][bx] >= 315 and dir.Data2D[by][bx] <= 360)
                    feature_vec[23] += mag.Data2D[by][bx];
            }

            // 4th histogram
            for (by = y + 1; by <= y + 16; by++)
            for (bx = x + 1; bx <= x + 16; bx++)
            {
                if (dir.Data2D[by][bx] >= 0 and dir.Data2D[by][bx] < 45)
                    feature_vec[24] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 45 and dir.Data2D[by][bx] < 90)
                    feature_vec[25] += mag.Data2D[by][bx];
                    
                if (dir.Data2D[by][bx] >= 90 and dir.Data2D[by][bx] < 135)
                    feature_vec[26] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 135 and dir.Data2D[by][bx] < 180)
                    feature_vec[27] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 180 and dir.Data2D[by][bx] < 225)
                    feature_vec[28] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 225 and dir.Data2D[by][bx] < 270)
                    feature_vec[29] += mag.Data2D[by][bx];

                if (dir.Data2D[by][bx] >= 270 and dir.Data2D[by][bx] < 315)
                    feature_vec[30] += mag.Data2D[by][bx];
                
                if (dir.Data2D[by][bx] >= 315 and dir.Data2D[by][bx] <= 360)
                    feature_vec[31] += mag.Data2D[by][bx];
            }
            
            //// for the current blob point, save all the feature values
            im_features.insert(make_pair(make_pair(x, y), feature_vec));
      
            //clear the vector
            for (int h = 0; h < 32; h++)
                feature_vec[h] = 0.0;
            
        }//end "if in blob"
    }//end image loopping
    
    ////Write features to a text file
    ofstream file;
    file.open(filename + "_σ" + to_string(sigma) + ".txt");
    
    file << "------------" << filename << "------------" << endl << endl;
    
    // loop and write all map elements
    for (map<pair<int, int>, vector <float> >::const_iterator iter = im_features.begin(); iter != im_features.end(); ++iter)
    {
        file << "(" << iter->first.first << ", " << iter->first.second << "), "
             << "σ=" << sigma << ",  "
             << "feature values: [ ";
                for(vector<float>::const_iterator it = iter->second.begin(); it != iter->second.end(); ++it)
                    file << *it << " ";
        file << "]" << endl << endl;
    }
    file << "Total number of feature point: " << im_features.size() << endl;
    file.close();
    
    cout << "A text file " << "'" + filename + "_σ" + to_string(sigma) + ".txt' " << "is generated!   ";
    cout << "Total number of feature point: " << im_features.size() << endl;
    
}//end of function


// Feature detection and matching ===========================================
void feature(char *Name1, char *Name2, int sigma)
{
    // Read image1
    im_float image1;
    image1.ReadJpg(Name1);
    
    // Read image2
    im_float image2;
    image2.ReadJpg(Name2);
    
    // Create blob iamges
    im_float image1_blob(image1);
    im_float image2_blob(image2);
    
    // Locate blobs
    locate_blob(image1_blob, sigma, 5);
    locate_blob(image2_blob, sigma, 5);
    
    // Create hashtables to store image feature
    map<pair<int, int>, vector <float> > im1_features;
    map<pair<int, int>, vector <float> > im2_features;

    // Calculate image features
    image_features(image1, image1_blob, im1_features, "features_im1", sigma);
    image_features(image2, image2_blob, im2_features, "features_im2", sigma);
    
    //Feature matching: brute force comparisons
    ofstream file;
    file.open("feature_match_σ" + to_string(sigma) + ".txt");
    file << "matching results: " << endl << endl;
    file << "(x1,y1)      "
         << "(x2,y2)     "
         << "Mean Abs Error"
         << endl;
    file << "-----------------------------------------" << endl;
    
    vector <float> fea1;
    vector <float> fea2;
    int match_num = 0;

    for (map<pair<int, int>, vector <float> >::const_iterator iter1 = im1_features.begin(); iter1 != im1_features.end(); ++iter1)
        for (map<pair<int, int>, vector <float> >::const_iterator iter2 = im2_features.begin(); iter2 != im2_features.end(); ++iter2)
        {
            float err = 0;
            // calcualte mean abs error
            for (int i = 0; i < iter1->second.size(); i ++)
                err += fabs(iter1->second[i] - iter2->second[i]);
                
            err /= iter1->second.size();
            
            // Wirte matched points into the file.
            if (err < 5){
                file << "(" << iter1->first.first << ", " << iter1->first.second << ") "
                     << "--> "
                     << "(" << iter2->first.first << ", " << iter2->first.second << ")   err: "
                     << err
                     << endl;
            
                match_num++;
            }
            
            fea1.clear();
            fea2.clear();
            
        }//end of the two for-loops.
    
    file << endl << "Total number of matched pairs: " << match_num << endl;
    file.close();
    
    cout << "A text file " << "'feature_match_σ" + to_string(sigma) + ".txt' " << "is generated!   ";
    cout << "Total number of matched pairs: " << match_num << endl;
    
}//end of function

//===========================================================================
int main(int argc, char *argv[])
{
    // Get input file name
    char Name1[STRLEN];
    char Name2[STRLEN];
    //int sigma;

    if (argc == 3)
    {
        strcpy(Name1, argv[1]);
        strcpy(Name2, argv[2]);
        //sigma = atoi(argv[3]);
    }
    else
    {
        cout << "Enter name of first image: ";
        cin >> Name1;
        cout << "Enter name of second image: ";
        cin >> Name2;
        //cout << "Enter the sigma value: ";
        //cin >> sigma;
    }
    
    // Perform feature detection and matching for sigma = [1,2,3,4,5]
    for (int i = 1; i <= 5; i++)
        feature(Name1, Name2, i);
    
}
