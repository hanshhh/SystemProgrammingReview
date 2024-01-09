#include <stdio.h>
int main() {
    FILE *data_file;
    int error;
    int number = 512;
    char character = 's';
    float fraction = 4.5;
    int numbers[] = {400, 800, 1200, 1400, 1600, 2000};
    data_file = fopen("my_data", "wb");
    if (data_file == NULL) {
        fprintf(stderr, "Error:could not open file\n");
        return 1;
    }
    error += fwrite(&number, sizeof(int), 1, data_file);
    error += fwrite(&character,sizeof(char), 1, data_file);
    error += fwrite(&fraction, sizeof(fraction), 1, data_file);
    error += fwrite(numbers, sizeof(int), 6, data_file);
    if (error != 9) {
        fprintf(stderr, "Error writing data\n");
    }
    return 0;

}