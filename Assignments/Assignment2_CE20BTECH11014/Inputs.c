/*****************************************
 * Assignment 2
 * Name:    Ishan Srivastava
 * E-mail:  ce20btech11014@iith.ac.in
 * Course:  ID2230
 * Submitted:    3/9/2023
 * 
 * Part 1 code of the 2nd assignment which was used to generate
 * the input required 
 * Number of Input = 100 arrays
 * Length of Input = 1000 numbers
***********************************************/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>


int main(){
    int n_arr = 100, n_ele = 1000;
    srand(time(0));
    FILE* fptr = fopen("input.txt", "w");
    if(fptr == NULL){
        printf("UNABLE TO OPEN FILE");
        return 1;
    }
    for(int i=0; i<n_arr; i++){
        int arr[1000];
        for(int j=0; j<n_ele; j++){
            arr[j] = rand()%1000 + 1;
        }
        for(int k=0; k<n_ele; k++){
            fprintf(fptr, "%d ", arr[k]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return 0;
}