//-----------------------------------------------------------
//  Purpose:    Header file for the Set class
//  Author:     John Gauch
//-----------------------------------------------------------

#include <iostream>
using namespace std;

//-----------------------------------------------------------
// Define the Set class interface 
//-----------------------------------------------------------
class Set
{
 public:
   // Constructors
   Set(int size);
   Set(const Set & set);
   ~Set();

   // Methods
   void Union(int set1, int set2);
   int Find(int set);
   void Print();

 private:
   int Size;
   int *Data;
};
