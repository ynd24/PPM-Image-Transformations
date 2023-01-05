#include "pbm.h"
#include <stdlib.h>


PPMImage * new_ppmimage( unsigned int w, unsigned int h, unsigned int m )
{   
    PPMImage *new_ppmimg;
    new_ppmimg = (PPMImage *)malloc(sizeof(PPMImage));

    new_ppmimg->height = h;
    new_ppmimg->width = w;
    new_ppmimg->max = m;

    for (int i = 0; i <= 2; i++) {
        new_ppmimg->pixmap[i] = (unsigned int**)malloc(h * sizeof(unsigned int*)); // creat list with 3 empty spaces
    }

    for (int i = 0; i < h; i++) {
        new_ppmimg->pixmap[0][i] = malloc(w * sizeof(unsigned int)); 
        new_ppmimg->pixmap[1][i] = malloc(w * sizeof(unsigned int)); 
        new_ppmimg->pixmap[2][i] = malloc(w * sizeof(unsigned int)); 
    }
    return new_ppmimg;
}

PBMImage * new_pbmimage( unsigned int w, unsigned int h )
{
    PBMImage *pbm_img;
    pbm_img = (PBMImage*)malloc(sizeof(PBMImage));

    pbm_img->height = h;
    pbm_img->width = w;

    pbm_img->pixmap = malloc(h * sizeof(unsigned int*));

    for (int i = 0; i < h; i++) {
        pbm_img->pixmap[i] = malloc(w * sizeof(unsigned int));
    }

    return pbm_img;
}

PGMImage * new_pgmimage( unsigned int w, unsigned int h, unsigned int m )
{
    PGMImage *pgm_img = (PGMImage*)malloc(sizeof(PGMImage));

    pgm_img->height = h;
    pgm_img->width = w;
    pgm_img->max = m;

    pgm_img->pixmap = malloc(h * sizeof(unsigned int*));

    for (int i = 0; i < h; i++) {
        pgm_img->pixmap[i] = malloc(w * sizeof(unsigned int)); 
    }

    return pgm_img;
}

void del_ppmimage( PPMImage * p )
{
    for (int i = 0; i < p->height; i++){ // free arrays inside array
        free(p->pixmap[0][i]);
        free(p->pixmap[1][i]);
        free(p->pixmap[2][i]);

    }
    for (int i = 0; i < 3; i++) {
        free(p->pixmap[i]); // free outer array
    }

    free(p);

}

void del_pgmimage( PGMImage * p )
{
    for (int i = 0; i < p->height; i++) {
        free(p->pixmap[i]);
    }
    free(p->pixmap);
    free(p);
}

void del_pbmimage( PBMImage * p )
{
    for (int i = 0; i < p->height; i++) {
        free(p->pixmap[i]);
    }
    free(p->pixmap);
    free(p);
}

