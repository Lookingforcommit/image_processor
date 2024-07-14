## User Manual

This project is a minimalistic CLI app which can apply different filters to BMP images. It is able to work with 24-bit
BMPs with BITMAPINFOHEADER DIB header.

### Building the project

You can build the project from source using cmake. Here is an example build using Ninja build system: 

	cmake -S . -B build -G Ninja
	cmake build -B build -G Ninja
	ninja -C build

### Running the program

The program usage format is

	image_processor {input_filename} {output_filename} [-{filter_1} [filter_param_1] [filter_param_2] ...[-{filter_2} [filter_param_1] [filter_param_2] ...]

Running the program without arguments will show you the help message containing the list of available filters

	This is a CLI app for applying various filters to BMP images. Usage format:
	image_processor {input_filename} {output_filename} [-{filter_1} [filter_param_1][filter_param_2] ...] [-{filter_2} [filter_param_1] [filter_param_2] ...]
	List of supported filters:
	-crop {width} {height}    Crop the image leaving the top-left part of it
	-edge {threshold}         Highlight the borders of the image. Pixels with values higher than the {threshold} will be colored white, others - black
	-gs                       Convert the image into shades of gray
	-neg                      Convert the image into its negative
	-nostalg                  Apply a nostalgic, yellowish filter to the image
	-sharp                    Increase sharpness of the image


