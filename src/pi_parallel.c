#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <omp.h>

#define CHUNK 125000000
#define number_of_threads 8

double random_double(double min, double max, int *seed){
    double random, range, number;

    random = ((double) rand_r(seed))/RAND_MAX;
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
    int i, seed, circle_count = 0, chunk = CHUNK;
    long int npoints = 1000000000;
    double pi, xpoints, ypoints;

    omp_set_num_threads(number_of_threads);
    #pragma omp parallel shared(circle_count, chunk) private(i, seed, xpoints, ypoints)
    {
        seed = time(NULL);

        #pragma omp for schedule(dynamic, chunk) reduction(+:circle_count)
            for(i = 0; i < npoints; i++){
                xpoints = random_double(0, radius, &seed);
                ypoints = random_double(0, radius, &seed);

                if(inside_centered_circle(radius, xpoints, ypoints) == 1)
                    circle_count++;
            }
    }

    printf("\ncircle_count: %d\n", circle_count);

    pi = 4.0*((double)circle_count)/((double)npoints);

    return pi;
}

void print_archive(double pi){
    FILE *archive;

    archive = fopen("pi_parallel.txt", "a");
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