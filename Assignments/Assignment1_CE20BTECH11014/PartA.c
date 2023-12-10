/*****************************************
 * Assignment 1
 * Name:    Ishan Srivastava
 * E-mail:  ce20btech11014@iith.ac.in
 * Course:  ID2230
 * Submitted:    3/9/2023
 * 
 * The main driver program for Part A in Assignment 1.
 * This program implements a Deque using a circular array
 * This program takes the size of deque as user input
 * It has 5 modes of operation them being
 * 1. Add to the Front of Deque
 * 2. Add to the Back of Deque
 * 3. Remove from the Front of Deque
 * 4. Remove from the Back of Deque
 * 5. Print the current Deque
 * The User can quit the executable by inputing -1 while selecting what action does the user want to do
***********************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
    printf("Current Deque:\nhead = %d\ntail = %d\nnumelements = %d/%d\n\n\n", deq->head,deq->tail,deq->numelements,deq->cap);
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
    // else if (deq->tail == deq->cap-1)
    // {
    //     deq->tail = 0;
    // }else{
    //     deq->tail +=1;
    // }
    // The above two elifs and else is taken care by the below statement
    deq->arr[deq->tail] = val;
    deq->tail = (deq->tail+1)%deq->cap;
    deq->numelements+=1;
    printf("Current Deque:\nhead = %d\ntail = %d\nnumelements = %d/%d\n\n\n", deq->head,deq->tail,deq->numelements,deq->cap);

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

void PrintDeq(struct Deque *deq){
    int i;
    for( i = deq->head; i!=deq->tail; i = (i+1)%deq->cap){
        printf("%d : %d \n", i, deq->arr[i]);
    }
    // To print the i = tail value
    printf("%d : %d \n\n", i, deq->arr[i]);
}

int main( int argc, char* argv[] ){
    // Initializing the Deque
    struct Deque myDeque;
    //Taking in the size of deque required
    int capacity;
    printf("Enter the Size of the deque:\n");
    scanf("%d", &capacity);
    CreateNewDeque(&myDeque,capacity);

    // User input on what action does he want the deque to perform 
    int option = 0;

    while(option != -1)
    {
        int temp;
        printf("Choose the operation to be performed\n1. Add to front \n2. Add to Back \n3. Remove from Front \n4. Remove from Back\n5. Get front element\n6. Get back element\n7. To print current Deque \n-1. To Quit\n\n");
        scanf("%d", &option);
        if(option == 1){
            scanf("%d", &temp);
            AddFront(&myDeque,temp);
        }
        else if(option == 2){
            scanf("%d", &temp);
            AddBack(&myDeque,temp);

        }
        else if(option == 3){
            int removed_element = RemoveFront(&myDeque);
            printf("The element removed is %d \n", removed_element);
        }
        else if(option == 4){
            int removed_element = RemoveBack(&myDeque);
            printf("The element removed is %d \n", removed_element);
        }
        else if(option == 5){
            int elem = GetFront(&myDeque);
            printf("The element at front is %d \n", elem);
        }
        else if(option == 6){
            int elem = GetBack(&myDeque);
            printf("The element at Back is %d \n", elem);
        }
        else if(option == 7){
            PrintDeq(&myDeque);
        }
    }
    
    free(myDeque.arr);
    return 0;
}