//============================================================
//  File:       process.cpp
//  Purpose:    To process a directory of jpg images.
//  Author:     John Gauch
//============================================================

#include "../libim/im_short.h"
#include "../libim/im_color.h"
#include "../libim/im_float.h"
#include "../libim/im_complex.h"
#include <fstream>
#include <iostream>
using namespace std;

// Global variables
const int SIZE = 1000;

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

//============================================================
void read_color(char input_dir[], im_color image[], int & image_count)
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

//============================================================
void process_float(char output_dir[], im_float image[], int image_count)
{
   // Create output directory
   char command[SIZE];
   sprintf(command, "mkdir -p %s", output_dir);
   system(command);
   
   // Calculate difference images
   char filename[SIZE];
   for (int index = 0; index < image_count; index++)
   {
      im_float difference(image[0]);
      difference.Subtract(image[index]);
      sprintf(filename, "%s/diff_float%03d.jpg", output_dir, index);
      cout << "Creating " << filename << endl;
      difference.WriteJpg(filename);
   }
}

//============================================================
void process_color(char output_dir[], im_color image[], int image_count)
{
   // Create output directory
   char command[SIZE];
   sprintf(command, "mkdir -p %s", output_dir);
   system(command);
   
   // Calculate difference images
   char filename[SIZE];
   for (int index = 0; index < image_count; index++)
   {
      im_color difference(image[0]);
      difference.Subtract(image[index]);
      sprintf(filename, "%s/diff_color%03d.jpg", output_dir, index);
      cout << "Creating " << filename << endl;
      difference.WriteJpg(filename);
   }
}

//============================================================
int main(int argc, char *argv[])
{
   // Local variables
   char input_dir[SIZE];
   char output_dir[SIZE];
   im_float image_float[SIZE];
   im_color image_color[SIZE];
   int image_count = 0;

   // Get user inputs
   if (argc == 3)
   {
      strcpy(input_dir, argv[1]);
      strcpy(output_dir, argv[2]);
   }
   else
   {
      cout << "Enter input directory: ";
      cin >> input_dir;
      cout << "Enter output directory: ";
      cin >> output_dir;
   }

   // Read float images
   read_float(input_dir, image_float, image_count);
   process_float(output_dir, image_float, image_count);

   // Process color images
   read_color(input_dir, image_color, image_count);
   process_color(output_dir, image_color, image_count);
}
