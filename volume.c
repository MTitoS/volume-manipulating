#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    char chunkID[4];
    int chunkSize;
    char format[4];
    char subchunk1ID[4];
    int subchunk1Size;
    short audioFormat;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
    char subchunk2ID[4];
    int subchunk2Size;
} WAVHeader;

void manipulateVolume(FILE *input, FILE *output, float factor);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    float factor = atof(argv[3]);

    printf("Opening the input file.\n");
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        perror("Could not open input file.");
        return 1;
    }

    printf("Opening the output file.\n");
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL) {
        perror("Could not open output file.");
        fclose(input);
        return 1;
    }

    WAVHeader header;
    
    fread(&header, sizeof(WAVHeader), 1, input);
    fwrite(&header, sizeof(WAVHeader), 1, output);

    //printf("%i\n", header.numChannels);

    manipulateVolume(input, output, factor);

    printf("Closing the input file.\n");
    fclose(input);

    printf("Closing the output file.\n");
    fclose(output);

    printf("Conversion succeeded.\n");
    return 0;
}

void manipulateVolume(FILE *input, FILE *output, float factor) {
    printf("Starting the manipulation of volume, factor: %f\n", factor);

    int16_t sample;
    
    while (fread(&sample, sizeof(int16_t), 1, input) == 1) {
        int32_t newSample = (int32_t)(sample * factor);

        if (newSample > 32767) newSample = 32767;
        if (newSample < -32768) newSample = -32768;

        int16_t finalSample = (int16_t)newSample;

        fwrite(&finalSample, sizeof(int16_t), 1, output);
    }
}
