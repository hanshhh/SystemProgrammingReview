#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s1[5];
    char *s2 = "1234567";
    strncpy(s1, s2, sizeof(s1));
    s1[sizeof(s1) - 1] = '\0';
   
    printf("%s\n", s1);

    char s3[30];
    char s4[14] = "university of";
    char s5[15] = " C programming";
    strcpy(s3, s4);
    // unlike strncpy, strncat copies 
    // third arg the max number of charactor not including the null terminator that should be copied from s5 to the end of s3;
    strncat(s3, s5, sizeof(s3) - strlen(s3) - 1);
    printf("%s\n", s3);



    char s6[30] = "University of C programming";
    char *p;
    p = strchr(s6, 'v');
    if (p == NULL) {
        printf("Character not found\n");
    } else {
        printf("Character found at index %ld\n", p - s6);
    }
    



    return 0;
}


