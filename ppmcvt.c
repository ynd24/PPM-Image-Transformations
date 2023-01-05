// THIS CODE IS MY OWN WORK< IT WAS WRITTEN WITHOUT CONSULTING
//
// A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Yuvraj Duggal

#include "pbm.h"
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void sepia(PPMImage * ppm_img) {
    float o_r; float o_g; float o_b;
    int R, G, B;

    for (int i = 0; i < ppm_img ->height; i++) {

        for (int j = 0; j < ppm_img -> width; j++) {
            o_r = ppm_img -> pixmap[0][i][j];
            o_g = ppm_img -> pixmap[1][i][j];
            o_b = ppm_img -> pixmap[2][i][j];

            R = (int)(o_r * 0.393 + o_g * 0.769 + o_b * 0.189);
            G = (int)(o_r * 0.349 + o_g * 0.686 + o_b * 0.168);
            B = (int)(o_r * 0.272 + o_g * 0.534 + o_b * 0.131);

            if (R > ppm_img -> max) {
                R = ppm_img -> max;
            }
            if (G > ppm_img -> max) {
                G = ppm_img -> max;
            }
            if (B > ppm_img -> max) {
                B = ppm_img -> max;
            }

            ppm_img -> pixmap[0][i][j] = R;
            ppm_img -> pixmap[1][i][j] = G;
            ppm_img -> pixmap[2][i][j] = B;
        }
    }
}

PPMImage * thumbnail(PPMImage * ppmi, unsigned int scale, const char* file) {
    unsigned int width_tn = ppmi -> width/scale;
    unsigned int height_tn = ppmi -> height/scale;

    if (ppmi -> width % scale) width_tn++;
    if (ppmi -> height % scale) height_tn++;

    PPMImage * ppmi_2 = new_ppmimage(width_tn, height_tn, ppmi -> max);

    for (int rgb=0; rgb < 3; rgb++) {
        for (int h = 0; h < ppmi_2->height; h++) {
            for(int w = 0; w < ppmi_2->width; w++) {
                ppmi_2->pixmap[rgb][h][w] = ppmi->pixmap[rgb][h*scale][w*scale];
            }
        }
    }
    write_ppmfile(ppmi_2, file);
    del_ppmimage(ppmi_2);
    del_ppmimage(ppmi);
}

void ppm_to_pbm(PPMImage *ppmi, PBMImage *pbmi, const char * file) {
    int ave = 0;
    for (int h = 0; h < ppmi -> height; h++) {

        for (int w = 0; w < ppmi -> width; w++) {
            ave = ppmi->pixmap[0][h][w]+ppmi->pixmap[1][h][w]+ppmi->pixmap[2][h][w];
            ave = ave / 3;

            if (ave < (ppmi->max)/2) {
                pbmi->pixmap[h][w] = 1;
            } else {
                pbmi->pixmap[h][w] = 0;
        }

    }
}
    write_pbmfile(pbmi, file);
    del_ppmimage(ppmi);
    del_pbmimage(pbmi);
}

void ppm_to_pgm(PPMImage* ppmi, PGMImage* pgmi, const char* file) {

    double ave = 0;

    for (int h = 0; h < ppmi->height; h++) {
        for (int w = 0; w < ppmi->width; w++) {
            ave = (ppmi->pixmap[0][h][w] + ppmi->pixmap[1][h][w] + ppmi->pixmap[2][h][w]) / 3;
            ave = ave * (pgmi->max / ppmi->max);
            pgmi->pixmap[h][w] = ave;
        }
    }

    write_pgmfile(pgmi, file);
    del_ppmimage(ppmi);
    del_pgmimage(pgmi);

}

void iso(PPMImage* ppmi, int channel) {

    for (int h = 0; h < ppmi->height; h++) {
        for (int w = 0; w < ppmi->width; w++) {

            if (channel == 0) {
                ppmi->pixmap[1][h][w] = 0;
                ppmi->pixmap[2][h][w] = 0;
            }
            else if (channel == 1) {
                ppmi->pixmap[0][h][w] = 0;
                ppmi->pixmap[2][h][w] = 0;
            }
            else if (channel == 2)
            {
                ppmi->pixmap[0][h][w] = 0;
                ppmi->pixmap[1][h][w] = 0;
            }
            
        }
    }
}


void remove_func(PPMImage* ppmi, int channel) {

    for (int h = 0; h < ppmi->height; h++) {
        for (int w = 0; w < ppmi->width; w++) {

            if (channel == 0) {
                ppmi->pixmap[0][h][w] = 0;
            }
            else if (channel == 1) {
                ppmi->pixmap[1][h][w] = 0;
            }
            else if (channel == 2)
            {
                ppmi->pixmap[2][h][w] = 0;
            }
            
        }
    }
}


void mirror(PPMImage*ppmi) {
    for (int rgb=0; rgb < 3; rgb++) {
        for (int h = 0; h < ppmi->height; h++) {
            for(int w = 0; w < ppmi->width; w++) {
                ppmi->pixmap[rgb][h][ppmi->width-w-1] = ppmi->pixmap[rgb][h][w];
            }
        }
    }
}


void n_tile(PPMImage* ppmi, int scale, const char* file) {
    unsigned int width_tn = ppmi -> width/scale;
    unsigned int height_tn = ppmi -> height/scale;

    if (ppmi -> width % scale) width_tn++;
    if (ppmi -> height % scale) height_tn++;

    for (int h = 0; h < height_tn; h++) {
            for(int w = 0; w < width_tn; w++) {
                ppmi->pixmap[0][h][w] = ppmi->pixmap[0][h*scale][w*scale];
                ppmi->pixmap[1][h][w] = ppmi->pixmap[1][h*scale][w*scale];
                ppmi->pixmap[2][h][w] = ppmi->pixmap[2][h*scale][w*scale];
            }
    }

    for (int h = 0; h < ppmi->height; h++) {
            for(int w = 0; w < ppmi->width; w++) {
                ppmi->pixmap[0][h][w] = ppmi->pixmap[0][h%height_tn][w%width_tn];
                ppmi->pixmap[1][h][w] = ppmi->pixmap[1][h%height_tn][w%width_tn];
                ppmi->pixmap[2][h][w] = ppmi->pixmap[2][h%height_tn][w%width_tn];

            }
        }
    
    write_ppmfile(ppmi, file);
    del_ppmimage(ppmi);
}



int main( int argc, char *argv[] )
{
    extern char* optarg;
    char* command_input;
    char* input_file;
    char* output_file;
    int arg_val = 0;
    bool flag = false;
    int o; 
    
    while ((o = getopt(argc, argv, "bg:i:r:smt:n:o:")) != -1) {
        switch (o)
        {
        case 'b':
            if (flag == true) {
                printf("Error: Multiple transformations specified\n");
			    exit(1);
            }
            command_input = "b";
            input_file = argv[argc-1];
            flag == true;
            break;

        case 'g':
             if (flag == true) {
                printf("Error: Multiple transformations specified\n");
			    exit(1);
            }
            char* pt_g;
            arg_val = strtol(optarg, &pt_g, 10);
            if (arg_val > 65535) {
                printf("Error: Invalid max grayscale pixel value: %s; must be less than 65,536\n", optarg);
                exit(1);
            }
            command_input = "g";
            input_file = argv[argc-1];
            flag == true;
            break;

        case 'i':
            if (flag == true) {
                printf("Error: Multiple transformations specified\n");
			    exit(1);
            }
            if (strcmp(optarg, "red") == 0 || strcmp(optarg, "green") == 0 || strcmp(optarg, "blue") == 0) {
                command_input = "i";
                input_file = argv[argc-1];
                arg_val = 0; // for red

                if (strcmp(optarg, "green") == 0) {
                    arg_val = 1; 
                }
                else if (strcmp(optarg, "blue") == 0) {
                    arg_val = 2;
                }

                flag = true;
                break;
            } else {
                printf("Error: Invalid channel specification: (%s); should be 'red', 'green' or 'blue'\n", optarg);
			    exit(1);
            }

        case 'r': 

            if (flag == true) {
                printf("Error: Multiple transformations specified\n");
			    exit(1);
            }
             if (strcmp(optarg, "red") == 0 || strcmp(optarg, "green") == 0 || strcmp(optarg, "blue") == 0) {
                command_input = "r";
                input_file = argv[argc-1];
                arg_val = 0; // for red

                if (strcmp(optarg, "green") == 0) {
                    arg_val = 1; 
                }
                else if (strcmp(optarg, "blue") == 0) {
                    arg_val = 2;
                }

                flag = true;
                break;
            } else {
                printf("Error: Invalid channel specification: (%s); should be 'red', 'green' or 'blue'\n", optarg);
			    exit(1);
            }

        case 's':
            if (flag == true) {
                printf("Error: Multiple transformations specified\n");
			    exit(1);
            }
            command_input = "s";
            input_file = argv[argc-1];
            flag = true;
            break;

        case 'm':
            if (flag == true) {
                    printf("Error: Multiple transformations specified\n");
                    exit(1);
                }
            command_input = "m";
            input_file = argv[argc-1];
            flag = true;
            break;

        case 't':
            if (flag == true) {
                printf("Error: Multiple transformations specified\n");
                exit(1);
            }
            command_input = "t";
            input_file = argv[argc-1];
            char* ptr;
            arg_val = strtol(optarg, &ptr, 10);

            if (arg_val > 8 || arg_val < 1) {
                printf("Error: Invalid scale factor: %s; must be 1-8\n", optarg);
                exit(1);
            }

            flag = true;
            break;

        case 'n':
         if (flag == true) {
                printf("Error: Multiple transformations specified\n");
                exit(1);
            }
            command_input = "n";
            input_file = argv[argc-1];
            char* ptr_n;
            arg_val = strtol(optarg, &ptr_n, 10);

            if (arg_val > 8 || arg_val < 1) {
                printf("Error: Invalid scale factor: %s; must be 1-8\n", optarg);
                exit(1);
            }

            flag = true;
            break;

        case 'o':
            output_file = optarg;
            if (output_file == NULL) {
                printf("Error: No output file specified\n");
                exit(1);
            }
            if (argc == 4) command_input = "b";
            input_file = argv[argc-1];
            break;

        case '?':
            printf("Usage: ppmcvt [-bgirsmtno] [FILE]\n");
            exit(1);
            break;
        }
    }

    if (strcmp(command_input, "b") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        PBMImage* pbmi = new_pbmimage(ppmi->width, ppmi->height);
        ppm_to_pbm(ppmi, pbmi, output_file);
        return 0; 
    }

    if (strcmp(command_input, "g") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        PGMImage* pgmi = new_pgmimage(ppmi->width, ppmi->height, ppmi->max);
        ppm_to_pgm(ppmi, pgmi, output_file); 
        return 0;
    }
    
    if (strcmp(command_input, "i") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        iso(ppmi, arg_val);
        write_ppmfile(ppmi, output_file);   
        del_ppmimage(ppmi);
        return 0;
        
    }

    if (strcmp(command_input, "r") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        remove_func(ppmi, arg_val);
        write_ppmfile(ppmi, output_file);
        del_ppmimage(ppmi);
        return 0;
    }

    if (strcmp(command_input, "s") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        sepia(ppmi);
        write_ppmfile(ppmi, output_file);
        del_ppmimage(ppmi);
        return 0;
    }

    if (strcmp(command_input, "m") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        mirror(ppmi);
        write_ppmfile(ppmi, output_file);
        del_ppmimage(ppmi);
        return 0;
    }

    if (strcmp(command_input, "t") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        thumbnail(ppmi, arg_val, output_file);
        return 0; 
    }

    if (strcmp(command_input, "n") == 0) {
        PPMImage* ppmi = read_ppmfile(input_file);
        n_tile(ppmi, arg_val, output_file);
        return 0;

    }

    return 0;


}
