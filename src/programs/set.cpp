//----------------------------------------------
// Purpose: Implement simple Set class
// Author:  John Gauch
//----------------------------------------------

#include "set.h"

//----------------------------------------------
// Constructor function
//----------------------------------------------
Set::Set(int size)
{
   // Allocate array
   Size = size;
   Data = new int[Size];

   // Initialize set data
   for (int i=0; i<Size; i++)
      Data[i] = -1;
}

//----------------------------------------------
// Copy constructor function
//----------------------------------------------
Set::Set(const Set & set)
{
   // Allocate array
   Size = set.Size;
   Data = new int[Size];

   // Copy set data
   for (int i=0; i<Size; i++)
      Data[i] = set.Data[i];
}

//----------------------------------------------
// Destructor function
//----------------------------------------------
Set::~Set()
{
   // Deallocate array
   if (Data != NULL)
      delete(Data);
}

//----------------------------------------------
// Union operation
//----------------------------------------------
void Set::Union(int set1, int set2)
{
   // Error checking
   if (set1 < 0 || set1 >= Size ||
       set2 < 0 || set2 >= Size)
       return;

   // Find both parents
   int parent1 = Find(set1);
   int parent2 = Find(set2);
   
   // Update set array
   if (parent1 != parent2)
      Data[parent1] = parent2;
}

//----------------------------------------------
// Find operation
//----------------------------------------------
int Set::Find(int set)
{
   // Error checking
   if (set < 0 || set >= Size)
       return -1;

   // Find parent of this set
   int parent = set;
   while (Data[parent] >= 0)
      parent = Data[parent]; 

   // Update set array
   if (set != parent)
      Data[set] = parent;
   return parent;
}

//----------------------------------------------
// Print operation
//----------------------------------------------
void Set::Print()
{
   // Print set data
   for (int i=0; i<Size; i++)
      cout << i << " " << Data[i] << endl;
}

#ifdef SET_MAIN
//-----------------------------------------------------------
// Testing function
//-----------------------------------------------------------
int main()
{
   // Test constructor
   const int SIZE = 100;
   Set test(SIZE);

   // Test Union
   for (int i=0; i<SIZE/2; i++)
   {
      int set1 = random() % SIZE;
      int set2 = random() % SIZE;
      cout << "union " << set1 << " " << set2 << endl;
      test.Union(set1,set2);
   }

   // Test Find
   for (int i=0; i<SIZE/2; i++)
   {
      int set = random() % SIZE;
      cout << "find " << set << " " << test.Find(set) << endl;
   }

   // Test Print
   test.Print();

   return 0;
}
#endif
