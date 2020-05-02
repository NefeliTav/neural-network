#include <stdio.h>
#include <stdlib.h>
#include "brain.h"
//https://github.com/takafumihoriuchi/MNIST_for_C/
#include "MNIST_for_C/mnist.h"

double zero[10] =  {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double one[10] =   {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double two[10] =   {0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double three[10] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double four[10] =  {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double five[10] =  {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
double six[10] =   {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0};
double seven[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0};
double eight[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
double nine[10] =  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};

int main(int argc, char **argv) {
    int i;
    const int size_of_input = 784;
    const int size_of_output = 10;
    const int train_number = 100;
    int number_of_iteration = 100000;
    if (argc == 2) {
        number_of_iteration = atoi(argv[1]);
    }

    load_mnist();
    double *dtraining_input = malloc(sizeof(double) * size_of_input * train_number);
    double *dtraining_output = malloc(sizeof(double) * size_of_output * train_number);
    
    for (i = 0; i < train_number; i++) {
        //populate dtraining_input
        memcpy(dtraining_input + i*size_of_input, &train_image[i][0], sizeof(double) * size_of_input);

        //populate dtraining_output
        switch(train_label[i]) {
            case 0:
                memcpy(dtraining_output + i*size_of_output, zero, sizeof(double) * size_of_output);
                break;
            case 1:
                memcpy(dtraining_output + i*size_of_output, one, sizeof(double) * size_of_output);
                break;
            case 2:
                memcpy(dtraining_output + i*size_of_output, two, sizeof(double) * size_of_output);
                break;
            case 3:
                memcpy(dtraining_output + i*size_of_output, three, sizeof(double) * size_of_output);
                break;
            case 4:
                memcpy(dtraining_output + i*size_of_output, four, sizeof(double) * size_of_output);
                break;
            case 5:
                memcpy(dtraining_output + i*size_of_output, five, sizeof(double) * size_of_output);
                break;
            case 6:
                memcpy(dtraining_output + i*size_of_output, six, sizeof(double) * size_of_output);
                break;
            case 7:
                memcpy(dtraining_output + i*size_of_output, seven, sizeof(double) * size_of_output);
                break;
            case 8:
                memcpy(dtraining_output + i*size_of_output, eight, sizeof(double) * size_of_output);
                break;
            case 9:
                memcpy(dtraining_output + i*size_of_output, nine, sizeof(double) * size_of_output);
                break;
        }
        
    }

    matrix_t training_input = { train_number, size_of_input, dtraining_input};
    matrix_t training_output = { train_number, size_of_output, dtraining_output};
    double dsynaptic_weights[training_input.w * training_output.w];
    for (i = 0; i < training_input.w  * training_output.w; i++) {
        dsynaptic_weights[i] = get_random(-1.0, 1.0);
    }
    matrix_t synaptic_weights = { training_input.w, training_output.w, dsynaptic_weights};
    
    /*int j;
    for (j = 0; j < train_number; j++) {
        for (i=0; i<size_of_input; i++) {
            printf("%1.1f ", dtraining_input[i + j*size_of_input]);
            if ((i+1) % 28 == 0) {
                putchar('\n');
            }
        }
        putchar('\n');
        for (i=0; i<size_of_output; i++) {
            printf("%1.1f ", dtraining_output[i + j*size_of_output]);
        }
        putchar('\n');
    }*/
    
    train(&training_input, &training_output, &synaptic_weights, number_of_iteration);

    double *dtest_input = malloc(sizeof(double) * size_of_input);
    memcpy(dtest_input, &test_image[0][0], sizeof(double) * size_of_input);
    matrix_t test_input = { 1, size_of_input, dtest_input};
    matrix output = run(&synaptic_weights, &test_input);
    mat_show(output);
    free(output);
    printf("label: %d\n", test_label[3]);
    free(dtraining_input);
    free(dtraining_output);
    free(dtest_input);
}