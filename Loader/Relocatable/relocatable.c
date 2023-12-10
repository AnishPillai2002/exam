#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char bit[30];
char bitmask[20];

// Function to convert a bitmask into its binary representation
void bitmask_convert(char mask[]) {
    int len = strlen(mask); //length of mask bit
    strcpy(bit, "");//initilizing bit sting to empty string

    for (int i = 0; i < len; ++i) {

        // Mapping each hex digit to its binary representation
        switch (mask[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
            default : break;
        }
    }
}


void main() {
    FILE *objptr;
    int start;
    char rec[20]; // Temporary storage for record
    char name[20];// Program name
    int modif_obj_code;
    char first[3]; // First part of object code
    char second[5];// Second part of object code
    int bitmask_index = 0;
    int i, add, len;

    printf("ENTER THE STARTING ADDRESS OF THE PROGRAM\n");
    scanf("%X", &start); // Read starting address in hexadecimal
 
    
    // Open the object file for reading
    objptr = fopen("input.txt", "r");

    // Read the first record (Header Record - H)
    fscanf(objptr, "%s", rec);

    if(strcmp(rec, "H") == 0) {  // Check if it's a valid header record
        fscanf(objptr, "%s", name); // Read program name
        fscanf(objptr, "%X", &add); // Read starting address of the program
        fscanf(objptr, "%X", &len); // Read length of the program
        printf("\nPROGRAM NAME = %s\n\n", name);
        printf(" ADDRESS   OBJECT CODE \n");
        printf("____________________________\n");
    } else {
        printf("INVALID OBJECT CODE FORMAT\n");
        fclose(objptr);
        exit(1);
    }

    strcpy(rec, "");// Clear the record string

    // Read the next record
    fscanf(objptr, "%s", rec);

    // Process each record until End Record (E) is encountered
    while(strcmp(rec, "E") != 0) {

        // Check if Text Record (T)
        if(strcmp(rec, "T") == 0) {
            fscanf(objptr, "%X", &add); // Read address
            fscanf(objptr, "%X", &len); // Read length
            fscanf(objptr, "%s", bitmask); // Read bitmask
            add += start; // Adjust address by adding the starting address
            bitmask_index = 0;
            bitmask_convert(bitmask); // Convert bitmask to binary
            fscanf(objptr, "%s", rec); // Read the next record
        }

        // Check the bitmask and modify the object code accordingly
        if(bit[bitmask_index] == '1') {
            
            //splits the contents of the  rec array into two separate arrays named first and second
            for(i = 0; i < 6; ++i) {
                if(i < 2) {
                    first[i] = rec[i]; //2 characters long
                } else {
                    second[i - 2] = rec[i]; //4 characters long
                }
            }
            
            first[2] = '\0';
            second[4] = '\0';


            modif_obj_code = strtol(second, NULL, 16);// Convert second part to integer
            modif_obj_code += start; // Adjust modified object code by adding the starting address
            printf("%X\t%s%X\n", add, first, modif_obj_code); // Print the modified object code
        } else {
            printf("%X\t%s\n", add, rec);// Print the original object code
        }

        add += 3;// Increment address by 3 (assuming each record is 3 bytes)
        bitmask_index++;// Move to the next bit in the bitmask
        fscanf(objptr, "%s", rec);  // Read the next record
    }

    fclose(objptr);
}