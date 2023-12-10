/*****************************************
 * Assignment 2
 * Name:    Ishan Srivastava
 * E-mail:  ce20btech11014@iith.ac.in
 * Course:  ID2230
 * Submitted:    3/9/2023
 * 
 * Part 2 code of the 2nd assignment which was used to form AVL from the input generated in Inputs.c
 * Each of the 
 * Number of Input = 100 arrays
 * Length of Input = 1000 numbers
***********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numComparisions = 0;

struct AVL{
    int  val;
    struct AVL* left;
    struct AVL* right;
    struct AVL* parent;
    int  height;
};

typedef struct AVL AVL;

int max(int x, int y){
    if(x>y){
        return x;
    }
    return y;
}

void createAVL(AVL* root, int val){
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    root->height = 0;
}

AVL* createNode(int val, AVL* parent){
    AVL* node = (AVL*)malloc(sizeof(AVL));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->height = 0;
    return node;
}

int update_height(AVL* root){
    if(root!=NULL){
        int lh = update_height(root->left);
        int rh = update_height(root->right);
        return max(lh , rh)+1;
    }
    return -1;
}

AVL* insert(AVL* root, AVL* parent,int val){
    if(root==NULL){
        return createNode(val,parent);
    }
    if(val < root->val){
        root->left = insert(root->left, root, val);
        numComparisions++;
    }
    else if(val > root->val){
        root->right = insert(root->right, root, val);
        numComparisions++;
    }
    root->height = update_height(root);
    return root;
}

AVL* delete(AVL* root, AVL* parent, int val){
    if(root==NULL){
        return root;
    }
    // recursively go to the element to be deleted
    if(val < root->val){
        root->left = delete(root->left,root,val);
        numComparisions++;
    }
    else if (val > root->val){
        root->right = delete(root->right,root,val);
        numComparisions++;
    }
    // when element is found do the following
    else{
        // if the left child is empty return the right child free up the allocated memory of the node
        if(root->left == NULL){
            AVL* tempNode = root->right;
            free(root);
            return tempNode;
        }
        // similarly if the right child is empty
        else if (root->right == NULL)
        {
            AVL* tempNode = root->left;
            free(root);
            return tempNode;
        }

        // If the node is not a leaf node or the node has 2 children
        // The succesor of the deleted node will be the node's right subtree's child which doesnt have a left child
        // Find the minimum element in the right subtree that will be the replacement for the deleted node
        AVL* temp = root->right;
        //loop to get the element in the right subtree with no left child
        while(temp->left!=NULL){
            temp = temp->left;
        }
        
        // replace the nodes val with the found temp node val rest pointers remain the same.
        root->val = temp->val;
        // delete the swapped succesor node
        root->right = delete(root->right, root,temp->val);
        numComparisions+=2;
    }
    root->height = update_height(root);
    return root;
    
}

void inorder_print(AVL* root){
    if(root!=NULL){
        inorder_print(root->left);
        printf("%d ", root->val);
        // printf("(%d) ", root->height);
        inorder_print(root->right);
    }
}

int main(){
    
    // open file
    FILE* file = fopen("input.txt", "r");
    FILE* outputFile = fopen("bst_output.txt", "w");
    if(file == NULL){
        printf("No Input File found please run Inputs.c first \n");
        return 1;
    }
    // approximately 4000 charecters (3 digit numbers*1000 + 999 spaces = 3999 char max in each line)
    char line[4000];
    while(fgets(line, sizeof(line), file)!=NULL){
        AVL* root = (AVL*)malloc(sizeof(AVL));
        int len = strlen(line);
        // removing new line char from the line end
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        char* token = strtok(line, " ");
       int array[1000];
        int i=0;
        while (token != NULL)
        {
            int data = atoi(token);
            array[i]=data;
            i++;
            root = insert(root,NULL,data);
            token = strtok(NULL, " ");
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("BEFORE DELETION:\n");
        printf("(%d) ", root->height);
        inorder_print(root);
        printf("\n");
        int del[100];
        int j=rand()%10, k=0;
        while(j<1000){
            del[k]=array[j];
            k++;
            j+= rand()%10+1;
        }
        for(int x=0; x<100; x++){
            delete(root,NULL,del[x]);
        }
        printf("AFTER DELETION:\n");
        printf("(%d) ", root->height);
        printf("\n");
        inorder_print(root);
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("NUM OF COMPARISIONS = %d\n", numComparisions);
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(outputFile, "%d %d\n", numComparisions, root->height);


        numComparisions=0;

        root = NULL;
    }

    // close file
    fclose(file);
    fclose(outputFile);
    return 0;
}