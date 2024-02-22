#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pt1, *pt2;
    char nom1[50], nom2[50];
    int *X, *Y;

    // Part 1: Writing data to the binary file
    printf("Part 1: Writing data to the binary file\n");

    // Allocate memory for X
    int nombre_elements;
    printf("Enter the number of elements: ");
    scanf("%d", &nombre_elements);

    if (nombre_elements <= 0) {
        printf("Invalid number of elements.\n");
        exit(1);
    }

    X = (int *)calloc(nombre_elements, sizeof(int));

    // Input data for X
    printf("Enter data for X:\n");
    for (int i = 0; i < nombre_elements; i++) {
        printf("Element %d: ", i + 1);
        // printf("----%d\n", scanf("%d", &X[i]));
        if (!scanf("%d", &X[i])){
            printf("error in type\n");
            exit(1);
        }
    }

    // Input binary file name
    printf("Enter the binary file name: ");
    scanf("%s", nom1);

    // Open binary file for writing
    pt1 = fopen(nom1, "wb");
    if (pt1 == NULL) {
        printf("Unable to open the binary file.\n");
        exit(1);
    }

    // Write data to the binary file
    fwrite(X, sizeof(int), nombre_elements, pt1);

    // Close the binary file
    fclose(pt1);

    // Check if the binary file is present
    printf("Check if the binary file is present in the working directory.\n");

    // Part 2: Transferring data to the text file
    printf("\nPart 2: Transferring data to the text file\n");

    // Allocate memory for Y
    Y = (int *)calloc(nombre_elements, sizeof(int));

    // Input text file name
    printf("Enter the text file name: ");
    scanf("%s", nom2);

    // Open binary file for reading
    pt1 = fopen(nom1, "rb");
    if (pt1 == NULL) {
        printf("Unable to open the binary file for reading.\n");
        exit(1);
    }

    // Open text file for writing
    pt2 = fopen(nom2, "w");
    if (pt2 == NULL) {
        printf("Unable to open the text file for writing.\n");
        fclose(pt1);
        exit(1);
    }

    // Read data from the binary file and write to the text file
    while (fread(Y, sizeof(int), 1, pt1) == 1) {
        fprintf(pt2, "%d\n", *Y);
    }

    // Close both files
    fclose(pt1);
    fclose(pt2);

    printf("Data transfer from binary file to text file is complete.\n");

    // Free allocated memory
    free(X);
    free(Y);

    return 0;
}
