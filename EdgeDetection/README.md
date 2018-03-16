# Edge Detection

The objective of this project is to implement and test a program to find edges for JEPG images. The program works well for images in which only have rectangular objects.

## Design

File created: find_line.cpp

1. Set a gradient threshold, and save the x and y coordinates for the points in the range of the threshold.

2. Randomly select 2 points in the saved points set and calculate the fitting line function for them.

3. Loop all saved points and put the points that within a distance from the fitting line into “kset”.

4. If the number of the points in the “kset” is large enough, fit high quality line equation to these points. I used the Least Square Line Equation for the high quality line fitting. Then, remove those points from the set of all points.

5. Repeat enough times so that good edge lines can be found out.

6. Loop over interior pixels and draw the fitting lines.
