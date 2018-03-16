
# Feautre Detection

The objective of this project is to implement a simple version of feature detection and matching for a pair of images.

## Design

**Assumption**: no feature or image rotation.

- Feature detection:

The image features are detected in blobs and the blobs are found by using the local maxima of Laplacian of Gaussian operator from the provided library.

For each feature point (x, y) in the blob, a feature vector can be calculated by using a 32x32 neighborhood centered on this point. The “feature.cpp” uses four 16x16 “sub-blocks” to calculate four gradient histograms that is quantized to eight directions. The calculation for each histogram is as follows:

For each pixel in the image, calculate its gradient magnitude and direction. The degree rage for the direction is from 0 to360. Quantized the directions into the 8 intervals: 0~45, 45~90, 90~135, 135~180, 180~225, 225~270, 270~315, and 315~360. For each degree interval, sum up the magnitude values of all pixels whose direction falls in.

All feature points and their 32 feature values in the image are stored in a hash table. After calculating the 32 feature values for each point, insert a key value pair {(x, y), 32 feature values} in to the hash table.

After looping over all feature points and finishing calculating their feature values of the image, write all key value pairs into a file named “features_im#__σ#.txt”._

- Feature matching:

Use brute force comparisons: loop over every feature points in the two images and calculate the mean absolute error of their 32 feature values. Set a threshold and write out all matched pair of points (one from image1 and one from image2) into a text file named “feature_match__ σ#.txt”

Repeat the feature detection and matching process for sigma values from 1 to 5. For each sigma value, there are three output files. Given a pair image, the program “feature.cpp” will totally generated 15 files.

