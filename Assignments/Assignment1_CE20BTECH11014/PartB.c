/*****************************************
 * Assignment 1
 * Name:    Ishan Srivastava
 * E-mail:  ce20btech11014@iith.ac.in
 * Course:  ID2230
 * Submitted:    3/9/2023
 * 
 * The main driver program for Part B in Assignment 1.
 * This program uses the deque implemented in PartA to solve a 2D maze
 * This program takes as an input a maze file which has 'S', 'E', '#', ' ' being start, end, wall, space respectively
 * it then returns wheter the maze can be solved or not and a solved maze
***********************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE_LENGTH 100

/*******
 * @brief - This is the structure of our deque object
 * @param arr - The main array in which the elements are stored
 * @param numelements - Stores the number of elements present in the deque at a given point 
 * @param head - position of the current head of the deque
 * @param tail - position of the current tail of the deque
 * @param cap  - The max capacity of the deque
 *******/

struct Deque
{
    int* arr;
    int numelements;
    int head;
    int tail;
    int cap;
};
// All the fuunctions of the Deque which are defined below main.
void CreateNewDeque(struct Deque *deq, int capacity);
int isFull(struct Deque *deq);
int isEmpty(struct Deque *deq);
void AddFront(struct Deque *deq, int val);
void AddBack(struct Deque *deq, int val);
int RemoveFront(struct Deque *deq);
int RemoveBack(struct Deque *deq);
int GetFront(struct Deque *deq);
int GetBack(struct Deque *deq);

/**
 * @brief Main Solver code for the maze
 * 
 * @param h tells the height of the maze
 * @param l tells the length of the maze
 * @param maze the inputted maze board
 * @return int return 1 if solution is found 0 if no solution
 * 
 * NOTE: Psuedocode used is the one given in assignment.
 */
int solver(int h, int l, char maze[h][l]){
    int visited[h][l];
    int isSolved = 0;
    int start_i,start_j;
    int end_i,end_j;
    // initiallizing the visited matrix
    for(int i=0; i<h;i+=1){
        for(int j=0; j<l; j+=1){
            // initiallizing all the walls as visited
            if(maze[i][j]=='#')visited[i][j]=1;
            else visited[i][j]=0;
            // noting the starting index of the maze
            if(maze[i][j]=='S'){
                start_i=i;
                start_j=j;
            }
            if(maze[i][j]=='E'){
                end_i=i;
                end_j=j;
            }
        }
    }
    
    // Making two deques to save 2 positional values of the maze[i][j]
    struct Deque mydeque_height; // saves the i index
    struct Deque mydeque_length; // saves the j index
    CreateNewDeque(&mydeque_height,5*h);
    CreateNewDeque(&mydeque_length,5*l);
    
    // Adding the start index to the deque
    AddBack(&mydeque_height, start_i);
    AddBack(&mydeque_length, start_j);
    while (isEmpty(&mydeque_height)!=1)
    {
        int curr_i = RemoveFront(&mydeque_height), curr_j = RemoveFront(&mydeque_length);
        
        if(maze[curr_i][curr_j]=='E') {
            isSolved = 1;
            break;
        }
        if(visited[curr_i][curr_j]==1 || maze[curr_i][curr_j]=='#')continue;
        else{
            visited[curr_i][curr_j]=1;
            // add up neighbour
            if(curr_i!=0){
                // if point (curr_i-1,curr_j) is further from (end_i,end_j) than (curr_i,curr_j) add to back
                if(abs(curr_i-end_i)<abs(curr_i-1-end_i)){
                    AddBack(&mydeque_height, curr_i-1);
                    AddBack(&mydeque_length, curr_j);
                }
                // if point (curr_i-1,curr_j) is closer to (end_i,end_j) than (curr_i,curr_j) add to Front
                else{
                    AddFront(&mydeque_height, curr_i-1);
                    AddFront(&mydeque_length, curr_j);
                }
                // maze[curr_i-1][curr_j] = '.';
                if(maze[curr_i-1][curr_j]==' '){
                    maze[curr_i-1][curr_j]='.';
                }
            }
            //add down neighbour
            if(curr_i!=h-1){
                // if point (curr_i+1,curr_j) is further from (end_i,end_j) than (curr_i,curr_j) add to back
                if(abs(curr_i - end_i)<abs(curr_i+1 - end_i)){
                    AddBack(&mydeque_height, curr_i+1);
                    AddBack(&mydeque_length, curr_j);
                }
                else{
                    AddFront(&mydeque_height, curr_i+1);
                    AddFront(&mydeque_length, curr_j);
                }
                // maze[curr_i+1][curr_j] = '.';
                if(maze[curr_i+1][curr_j]==' '){
                    maze[curr_i+1][curr_j]='.';
                }
            }
            //add right neighbour
            if(curr_j!=l-1){
                // if point (curr_i,curr_j+1) is further from (end_i,end_j) than (curr_i,curr_j) add to back
                if(abs(curr_j-end_j)<abs(curr_j+1 - end_j)){
                    AddBack(&mydeque_height, curr_i);
                    AddBack(&mydeque_length, curr_j+1);
                }
                else{
                    AddFront(&mydeque_height, curr_i);
                    AddFront(&mydeque_length, curr_j+1);
                }
                // maze[curr_i][curr_j+1] = '.';
                if(maze[curr_i][curr_j+1]==' '){
                    maze[curr_i][curr_j+1]='.';
                }
                
            }
            //add left neighbour
            if(curr_j!=0){
                if(abs(curr_j-end_j)<abs(curr_j-1 - end_j)){
                    AddBack(&mydeque_height, curr_i);
                    AddBack(&mydeque_length, curr_j-1);
                }
                else{
                    AddFront(&mydeque_height, curr_i);
                    AddFront(&mydeque_length, curr_j-1);
                }
                // maze[curr_i][curr_j-1] = '.';
                if(maze[curr_i][curr_j-1]==' '){
                    maze[curr_i][curr_j-1]='.';
                }
            }
        }
        
    }
    for(int x=0; x<h; x+=1){
        for(int y=0; y<l; y+=1){
            if(maze[x][y]!='.' || maze[x][y]!=' ')printf("(%c)",maze[x][y]);
            else printf(" %c ",maze[x][y]);
        }
        printf("\n");
    }
    //Frees up the memory allocated dynamically in the deque
    free(mydeque_height.arr);
    free(mydeque_length.arr);

    return isSolved;
}


int main(int argc, char *argv[]){
    char file_name[50];
    printf("Enter the file Name:\n");
    scanf("%s", file_name);
    FILE* ptr = fopen(file_name,"r");
    if(ptr == NULL){
        printf("ERROR NO FILE INPUT");
        exit(1);
    }
    char line[MAX_LINE_LENGTH];
    
    //finding the breadth of the row
    int len = 0;
    fgets(line,100,ptr);
    while(line[len]!='\n'){
        len++;
    }
    //finding the height of the maze
    int height = 1;
    // printf("%d\n",len);
    while (fgets(line,100,ptr)!=NULL){
        height+=1;
    }
    // printf("%d\n",height);
    // resetting the file pointer to the start of the file
    fseek(ptr,0L,SEEK_SET);
    char maze[height][len];
    int i=0;
    int j=0;
    char row;
    // taking input of the file in maze
    while (!feof(ptr)){   
        row = fgetc(ptr);
        if(j<len){
            maze[i][j]=row;
            j+=1;
        }else{
            i+=1;
            j=0;
        }
    }

    int ans = solver(height,len,maze);
    if(ans == 1){
        printf("\nTHIS MAZE CAN BE SOLVED!!!");
    }
    else{
        printf("\nTHIS MAZE CAN'T BE SOLVED!!!");
    }
    
    fclose(ptr);
    return 0;
}


/*CONTAINS THE CODE IMPLEMENTATION OF DEQUE FROM QUESTION 1 WITHOUT THE PRINT STATEMENTS*/

/****
 * @brief This Function intitializes the Deque by assigning the Deque a user defined size/capacity. The allocated memory using malloc is freed in the main function
 * @param deq -> the deque object that is to be initialized
 * @param capacity -> the maximum number of elements the deque can store
 ****/

void CreateNewDeque(struct Deque *deq, int capacity){
    if(deq == NULL) return;

    deq->arr = (int*)malloc(capacity*sizeof(int));
    deq->numelements=1;
    deq->head=-1;
    deq->tail=-1;
    deq->cap = capacity;
}

/**
 * @brief Check for if the deque is currently full or not
 * @paragraph if the head pointer is equal to the tail pointer+1 ie tail behind the head or if head at 0 and tail at end
 * the array is considered full
 * @param deq 
 * @return int 1 if full 0 if not full
 */
int isFull(struct Deque *deq){
    if((deq->head == deq->tail+1) || (deq->head ==0 && deq->tail == deq->cap-1)) return 1;
    return 0;
}

/**
 * @brief Check for if the deque is currently empty or not
 * @paragraph if the head is -1 ie there are no elements in the array it is considered to be empty
 * @param deq 
 * @return int 1 if empty 0 if not empty
 */
int isEmpty(struct Deque *deq){
    if(deq->head == -1)return 1;
    return 0;
}

/*********************************************
 * @brief This fucntions adds the element to the front of the Deque
 * 
 * @param deq - is the user defined Deque object of a given size
 * @param val - is the user defined integer value to add in front of the deque
 *********************************************/
void AddFront(struct Deque *deq, int val){
    if(isFull(deq)){
        printf("ERROR: OVERFLOW\n\n");
        return;
    }
    // if the deq is empty initialize it
    if(deq->head == -1){    
        deq->head = 0; 
        deq->tail = 1;
    } 
    // if deq head is at 0 we need to send it to the last position
    else if (deq->head==0){
        deq->head=deq->cap-1;
    }
    // in all other cases the deq head is shifted one step back
    else{
        deq->head -=1;
    }
    deq->arr[deq->head] = val;
    deq->numelements+=1;
   
}

/*********************************************
 * @brief This fucntions adds the element to the back of the Deque
 * 
 * @param deq - is the user defined Deque object of a given size
 * @param val - is the user defined integer value to add at the back of the deque
 *********************************************/
void AddBack(struct Deque *deq, int val){
    if(isFull(deq)){
        printf("ERROR: OVERFLOW\n\n");
        return;
    }
    if(deq->head == -1){  
        deq->head = 0;
        deq->tail = 1;
    }
    deq->arr[deq->tail] = val;
    deq->tail = (deq->tail+1)%deq->cap;
    deq->numelements+=1;
    

}

/**
 * @brief Removes the element at the head of the deque, then shifts the head pointer towards the right/next element
 * 
 * @param deq takes deq as an input
 * @return int that has been removed
 */

int RemoveFront(struct Deque *deq){
    if(isEmpty(deq)){
        printf("\nERROR: UNDERFLOW\n");
        return -1;
    }
    int element = deq->arr[deq->head];
    if(deq->head == deq->tail-1){
        deq->head=-1;
        deq->tail=-1;
    }
    else{
        // deq->head+=1;
        // if(deq->head==deq->cap){
        //     deq->head=0;
        // }
        deq->head = (deq->head+1)%deq->cap;
    }
    deq->numelements-=1;
    return element;
}
/**
 * @brief Removes the element on the tail of the deq, shifts the pointer to the left/prev element.
 * 
 * @param deq 
 * @return int that has been removed 
 */
int RemoveBack(struct Deque *deq){
    if(isEmpty(deq)){
        printf("ERROR: UNDERFLOW");
        return -1;
    }
    if(deq->head == deq->tail-1){
        deq->head=-1;
        deq->tail=-1;
    }
    else if(deq->tail == 0){
        deq->tail = deq->cap-1;
    }
    else{
        deq->tail -=1;
    }
    deq->numelements-=1;
    int element = deq->arr[deq->tail];
    return element;
}

int GetFront(struct Deque *deq){
    if(isEmpty(deq)){
        printf("ERROR : UNDERFLOW");
        return -1;
    }
    return deq->arr[deq->head];
}

int GetBack(struct Deque *deq){
    if(isEmpty(deq)){
        printf("ERROR : UNDERFLOW");
        return -1;
    }
    if (deq->tail==0){
        return deq->arr[deq->cap - 1];
    }
    return deq->arr[deq->tail-1];
}