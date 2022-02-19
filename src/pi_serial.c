#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double random_double(double min, double max){
    double random, range, number;

    random = ((double) rand())/RAND_MAX;
    range = (max - min)*random;
    number = min + range;

    return number;
}

int inside_centered_circle(double radius, double x, double y){
    double xcenter = 0.0, ycenter = 0.0, distance;

    distance = sqrt((x - xcenter)*(x - xcenter) + (y - ycenter)*(y - ycenter));

    if(distance < radius)
        return 1;
    else    
        return 0;
}

double pi_calculator(double radius){
    int i, circle_count = 0;
    long int npoints = 1000000000;
    double pi, xpoints, ypoints;

    for(i = 0; i < npoints; i++){
        xpoints = random_double(0, radius);
        ypoints = random_double(0, radius);

        if(inside_centered_circle(radius, xpoints, ypoints) == 1)
            circle_count++;
    }

    pi = 4.0*((double)circle_count)/((double)npoints);

    pi = (4.0*circle_count)/npoints;

    return pi;
}

void print_archive(double pi){
    FILE *archive;

    archive = fopen("pi_serial.txt", "a");
    fprintf(archive, "%f", pi);
    fprintf(archive, "\n");

    fclose(archive);
    free(archive);
}

int main(){
    double pi, radius = 1.0;

    pi = pi_calculator(radius);
    print_archive(pi);

    return 0;
}