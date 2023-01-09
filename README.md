# PPM-Image-Transformations
ppmcvt manipulates input Portable Pixel Map (PPM) files and outputs a new image based on its given options. Only one option that specifies a transformation can be used at a time. <br>

In the synopsis, options followed by a ‘:’ expect a subsequent parameter. <br>
The options are: <br>
-b <br>
convert input file to a Portable Bitmap (PBM) file. (DEFAULT) <br>
-g: <br>
convert input file to a Portable Gray Map (PGM) file using the specified
max grayscale pixel value [1-65535]. <br>
-i: <br>
isolate the specified RGB channel. Valid channels are “red”, “green”, or
“blue”. <br>
-r: <br>
remove the specified RGB channel. Valid channels are “red”, “green”,
or “blue”. <br>
-s <br>
apply a sepia transformation <br>
-m <br>
vertically mirror the first half of the image to the second half <br>
-t: <br>
reduce the input image to a thumbnail based on the given scaling
factor [1-8]. <br>
-n: <br>
tile thumbnails of the input image based on the given scaling factor [1-
8]. <br>
-o: <br>
write output image to the specified file. Existent output files will be
overwritten. <br>
EXIT STATUS <br>
ppmcvt exits 0 on success and 1 on failure.
