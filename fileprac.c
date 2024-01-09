#include <stdio.h>

#define LINE_LENGTH 80

int main() {
    FILE *random_file;
    char line[LINE_LENGTH + 1];
    random_file = fopen("random.txt", "r");
    if (random_file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    printf("File opened");
    // also reads the \n
    while (fgets(line, 3, random_file) != NULL) {
        printf("%s|", line);
    }
//     |he|he|he|
//      |ha|ha|ha|
//      |66|6|%

    if (fclose(random_file) != 0) {
        fprintf(stderr, "fclose failed\n");
        return 1;
    }
    return 0;
}