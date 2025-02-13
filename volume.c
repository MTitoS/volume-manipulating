#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <windows.h>

int manipulateVolume(FILE *input, FILE *output, float factor);

int main (int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor");
        return 1;
    }

    float factor = atof(argv[3]);

    printf("Opening the input file.\n");
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        perror("Could not open input file.");
        return 1;
    }

    printf("Opening the output file.\n");
    FILE *output = fopen(argv[2], "w");

    if (output == NULL) {
        perror("Could not open output file.\n");
        return 1;
    }

    manipulateVolume(input, output, factor);

    printf("Closing the files.");
    fclose(input);
    fclose(output);

    return 0;
}

int manipulateVolume(FILE *input, FILE *output, float factor) {
    printf("Starting the manipulation of volume, factor: %f.\n", factor);
}
