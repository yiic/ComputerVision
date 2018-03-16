//============================================================
//  File:       motion.cpp
//  Purpose:    Process a sequence of jpg images and track motions.
//              Write dx and dy of each pair of images to 2 images.
//  Author:     Yirong Chen
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <map>
using namespace std;

// Global variables
const int SIZE = 1000;

char x_name[SIZE];
char y_name[SIZE];

//============================================================
void read_float(char input_dir[], im_float image[], int & image_count)
{
    // Create files.txt file
    char command[SIZE];
    sprintf(command, "ls %s/*.jpg > files.txt", input_dir);
    system(command);
    
    // Read input files
    ifstream din;
    din.open("files.txt");
    image_count = 0;
    char filename[SIZE];
    while ((image_count < SIZE) && (din >> filename))
    {
        cout << "Reading " << filename << endl;
        image[image_count].ReadJpg(filename);
        image_count++;
    }
    din.close();
}

////==========Motion tracking: find (dx, dy) for each point in a pair of images==========
void motion_float(char output_dir[], int index, im_float M1, im_float M2, int block_size)
{
    im_float MX(M1);
    im_float MY(M1);

    int Max_motion = 15;
    
    map<int, pair<int, int> > ssd_err;
    
    // loop over image M1
    for (int y = (block_size + Max_motion)/2; y < (M1.Ydim - (block_size + Max_motion)/2); y++)
    for (int x = (block_size + Max_motion)/2; x < (M1.Xdim - (block_size + Max_motion)/2); x++)
    {
        // loop over image M2 within Max_motion
        for (int dy = -Max_motion/2; dy <= Max_motion/2; dy+=1)
        for (int dx = -Max_motion/2; dx <= Max_motion/2; dx+=1)
        {
            int ssd = 0;
            
            // loop over a matching block
            for (int by = -block_size/2; by <= block_size/2; by++)
            for (int bx = -block_size/2; bx <= block_size/2; bx++)
                ssd += (M1.Data2D[y + by][x + bx] - M2.Data2D[y + dy + by][x + dx + bx]) * (M1.Data2D[y + by][x + bx] - M2.Data2D[y + dy + by][x + dx + bx]);
                    
            ssd_err.insert(make_pair(ssd, make_pair(dx,dy)));
        }
            
        //// print all map elments
        //map<int, pair<int, int> > MapIterator;
        //cout << "-------------------------------------------------" <<endl;
        //for (map<int, pair<int,int> >::const_iterator iter = ssd_err.begin(); iter != ssd_err.end(); ++iter){
        //        cout << "Key(ssd): " << iter->first << " " << "Values: " << iter->second.first << "," << iter->second.second << endl;
        //}
        
        
        //find the minimum ssd, map is already sorted by key in ascending order
        MX.Data2D[y][x] = ssd_err.begin()->second.first * 10;
        MY.Data2D[y][x] = ssd_err.begin()->second.second * 10;
            
        //cout << "dx,dy: " << ssd_err.begin()->second.first << "," << ssd_err.begin()->second.second <<endl;
            
        ssd_err.clear();
        
    }//end looping M1
   
    
    //write output image
    sprintf(x_name, "%s/motion_f_dx%03d.jpg", output_dir, index);
    cout << "Creating " << x_name << endl;
    MX.WriteJpg(x_name);
    
    sprintf(y_name, "%s/motion_f_dy%03d.jpg", output_dir, index);
    cout << "Creating " << y_name << endl;
    MY.WriteJpg(y_name);
    
}

////========================= 3 Level Searching ===========================
void motion_3L_float(char output_dir[], int index, im_float M1, im_float M2, int block_size)
{
    im_float MX(M1);
    im_float MY(M1);

    map<int, pair<int, int> > ssd_err;

    // loop over image M1
    for (int y = (block_size/2 + 7); y < M1.Ydim - (block_size/2 + 7); y++)
    for (int x = (block_size/2 + 7); x < M1.Xdim - (block_size/2 + 7); x++)
    {
        // ------------------------------------------level 1: (x, y)
        for (int dy = -4; dy <= 4; dy+=4)
        for (int dx = -4; dx <= 4; dx+=4)
        {
            int ssd = 0;

            // loop over a matching block
            for (int by = -block_size/2; by <= block_size/2; by++)
            for (int bx = -block_size/2; bx <= block_size/2; bx++)
                ssd += (M1.Data2D[y + by][x + bx] - M2.Data2D[y + dy + by][x + dx + bx]) * (M1.Data2D[y + by][x + bx] - M2.Data2D[y + dy + by][x + dx + bx]);

            ssd_err.insert(make_pair(ssd, make_pair(dx,dy)));
        }
        //cout << "level 1 end" << endl;

        // ------------------------------------------level 2: (x2, y2)
        int best_dx2 = ssd_err.begin()->second.first;
        int best_dy2 = ssd_err.begin()->second.second;

        int x2 = x + best_dx2;
        int y2 = y + best_dy2;
        ssd_err.clear();

        for (int dy2 = -2; dy2 <= 2; dy2+=2)
        for (int dx2 = -2; dx2 <= 2; dx2+=2)
        {
            int ssd = 0;

            // loop over a matching block
            for (int by2 = -block_size/2; by2 <= block_size/2; by2++)
            for (int bx2 = -block_size/2; bx2 <= block_size/2; bx2++)
                ssd += (M1.Data2D[y2 + by2][x2 + bx2] - M2.Data2D[y2 + dy2 + by2][x2 + dx2 + bx2]) * (M1.Data2D[y2 + by2][x2 + bx2] - M2.Data2D[y2 + dy2 + by2][x2 + dx2 + bx2]);

            ssd_err.insert(make_pair(ssd, make_pair(dx2,dy2)));
        }
        //cout << "level 2 end" << endl;

        // ------------------------------------------level 3: (x3, y3)
        int best_dx3 = ssd_err.begin()->second.first;
        int best_dy3 = ssd_err.begin()->second.second;

        int x3 = x2 + best_dx3;
        int y3 = y2 + best_dy3;
        ssd_err.clear();

        for (int dy3 = 1; dy3 <= 1; dy3+=1)
        for (int dx3 = -1; dx3 <= 1; dx3+=1)
        {
            int ssd = 0;

            // loop over a matching block
            for (int by3 = -block_size/2; by3 <= block_size/2; by3++)
            for (int bx3 = -block_size/2; bx3 <= block_size/2; bx3++)
                ssd += (M1.Data2D[y3 + by3][x3 + bx3] - M2.Data2D[y3 + dy3 + by3][x3 + dx3 + bx3]) * (M1.Data2D[y3 + by3][x3 + bx3] - M2.Data2D[y3 + dy3 + by3][x3 + dx3 + bx3]);

            ssd_err.insert(make_pair(ssd, make_pair(dx3,dy3)));
        }

        //cout << "level 3 end" << endl;

        int best_dx = best_dx2 + best_dx3 + ssd_err.begin()->second.first;
        int best_dy = best_dy2 + best_dy3 + ssd_err.begin()->second.second;

        MX.Data2D[y][x] = best_dx * 10;
        MY.Data2D[y][x] = best_dy * 10;

        //cout << "dx,dy: " << best_dx << "," << best_dy <<endl;

        ssd_err.clear();

        }//end looping M1


    //write output image
    sprintf(x_name, "%s/motion_f_3L_dx%03d.jpg", output_dir, index);
    cout << "Creating " << x_name << endl;
    MX.WriteJpg(x_name);

    sprintf(y_name, "%s/motion_f_3L_dy%03d.jpg", output_dir, index);
    cout << "Creating " << y_name << endl;
    MY.WriteJpg(y_name);

}

////============================================================
void process_float(char output_dir[], im_float image[], int image_count, int method, int block_size)
{
    // Create output directory
    char command[SIZE];
    sprintf(command, "mkdir -p %s", output_dir);
    system(command);
    
    for (int index = 0; index < image_count - 1; index++)
        if (method == 0)
            motion_float(output_dir, index, image[index], image[index + 1], block_size);
        else
            motion_3L_float(output_dir, index, image[index], image[index + 1], block_size);
}

//============================================================
int main(int argc, char *argv[])
{
    // Local variables
    char input_dir[SIZE];
    char output_dir[SIZE];
    int method;
    int block_size;
    im_float image_float[SIZE];
    im_color image_color[SIZE];
    int image_count = 0;

   // Get user inputs
   if (argc == 5)
   {
       method = atoi(argv[1]);
       block_size = atoi(argv[2]);
       strcpy(input_dir, argv[3]);
       strcpy(output_dir, argv[4]);
   }
   else
   {
       cout << "Enter blcok matching method: (0)basic method; (1)3-Level searching ";
       cin >> method;
       cout << "Enter matching block size: ";
       cin >> block_size;
       cout << "Enter input directory: ";
       cin >> input_dir;
       cout << "Enter output directory: ";
       cin >> output_dir;
   }

    //Read float images
    read_float(input_dir, image_float, image_count);
    process_float(output_dir, image_float, image_count, method, block_size);

}
