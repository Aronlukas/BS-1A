#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


int minInt(char *str1, char *str2) {
    int l1 = strlen(str1);
    int l2 = strlen(str2);
    if (l1 < l2) return l1;
    return l2;
}



int main(int argc, char *argv[]) {

    // --- Setup arguments ---

    printf("%d\n", argc);
    printf("Erstes Argument (Run file Path): %s\n", argv[0]);

    // File Paths from command line arguments
    char *file1_path_arg = NULL;
    char *file2_path_arg = NULL;

    char *output_file;
    int opt_i = 0;

    int c;
    while ( (c = getopt(argc, argv, "io:")) != -1) {
        switch (c) {
            case 'o': output_file = optarg; break;
            case 'i': opt_i++; break;
            case '?': break;
        }
    }

    if (strcasecmp("", output_file) != 0) { // Wenn ein OutputFile angegeben wurde
        printf("Path of output file: %s\n", output_file); // Print OutputFile
    }

    if ((argc - optind) != 2) {
        printf("Fehler: Zu wenig Argumente \n Zwei Argumente benoetigt.\n"); // Bessere Fehlermeldung
        printf("Anzahl der uebrigen Argumente: %d\n", argc - optind);
        return -1;
    }

    char *file1_path = argv[optind];
    char *file2_path = argv[optind+1];

    printf("Pfad von File1: %s\nPfad von File2: %s\n", file1_path, file2_path);


    // --- Open files into *file1 and *file2 ---

    FILE *file1, *file2;
    if ((file1 = fopen(file1_path, "r")) == NULL) {
        fprintf(stderr, "open failed at %s: %s\n", file1_path, strerror(errno));
        exit(EXIT_FAILURE);
    } if ((file2 = fopen(file2_path, "r")) == NULL) {
        fprintf(stderr, "open failed at %s: %s\n", file2_path, strerror(errno));
        exit(EXIT_FAILURE);
    }



    // --- Read and compare lines ---
    char buffer1[12];
    char buffer2[12];
    while (fgets(buffer1, sizeof(buffer1), file1) != NULL && fgets(buffer2, sizeof(buffer2), file2) != NULL ) {
        printf("%d\n", strcmp(buffer1, buffer2));
    }



    // Exit, if fgets failed at file1 or file2
    if (ferror(file1) | ferror(file2)) {
        fprintf(stderr, "fgets failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Close files (file1 and file2)
    fclose(file1);
    fclose(file2);

    return 0;
}

