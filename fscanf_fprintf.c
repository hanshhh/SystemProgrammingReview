#include <stdio.h>

#define LINE_LENGTH 80

int main() {
    FILE *input_file, *output_file;
    char line[LINE_LENGTH + 1];
    int num;
    input_file = fopen("random2.txt", "r");
    output_file = fopen("out2.txt", "w");

    if (input_file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    printf("File opened");

    // fscanf returns EOF if end of file (or an input error) occurs before any values are stored. If values are stored, it returns the number of items stored; that is, the number of times a value is assigned with one of the fscanf argument pointers. EOF is returned if an error occurs before any items are matched.

    
    while (fscanf(input_file, "%s %d",line, &num) == 2) {
        printf("%s %d\n", line, num);
        fprintf(output_file, "%s %d\n", line, num);
    }
//     |he|he|he|
//      |ha|ha|ha|
//      |66|6|%

    if (fclose(input_file) != 0) {
        fprintf(stderr, "fclose failed\n");
        return 1;
    }
    if (fclose(output_file) != 0) {
        fprintf(stderr, "fclose failed\n");
        return 1;
    }
    return 0;
}