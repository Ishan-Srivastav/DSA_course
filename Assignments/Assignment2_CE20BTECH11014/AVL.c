/*****************************************
 * Assignment 2
 * Name:    Ishan Srivastava
 * E-mail:  ce20btech11014@iith.ac.in
 * Course:  ID2230
 * Submitted:    3/9/2023
 * 
 * Part 3 code of the 2nd assignment which was used to form AVL-Tree from the input generated in Inputs.c
 * Number of Input = 100 arrays
 * Length of Input = 1000 numbers
***********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numComparision = 0;
int numPointerOperation = 0;

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
    root->height = 1;
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
        // get left height
        int lh = update_height(root->left);
        // get right height
        int rh = update_height(root->right);
        return max(lh , rh)+1;
    }
    return -1;
}

AVL* rightRotate(AVL* root){
    AVL* x = root->left;
    AVL* B = x->right;

    x->right = root;
    root->left = B;

    x->parent = root->parent;
    root->parent = x;

    numPointerOperation+=4;

    if(B){
        B->parent = root;
        numPointerOperation++;
    }

    root->height = update_height(root);
    x->height = update_height(x);
    // root->height = max(root->left->height,root->right->height)+1;
    // x->height = max(x->left->height,x->right->height)+1;

    return x;

        /**
         * // y == root
         *            /                   /
         *           y                   x
         *         /  \        RR(y)    / \   
         *        x    C    ------->   A   y
         *       / \                      / \   
         *      A   B                    B   C
         */

} 

AVL* leftRotate(AVL* root){
    AVL* y = root->right;
    AVL* B = y->left;

    // swapping positions as per diagram
    y->left = root;
    root->right = B;
    // resetting parent pointers
    y->parent = root->parent;
    root->parent = y;
    numPointerOperation+=4;

    if(B){
        B->parent = root;
        numPointerOperation++;
    }
    // updating height
    root->height = update_height(root);
    y->height = update_height(y);

    return y;
        /*
         *    x == root
         *            /                        /
         *           x                        y
         *          / \          LR(x)       / \ 
         *         A   y      ------->      x   C
         *            / \                  / \ 
         *           B   C                A   B
         */

}

int Balance(AVL* root){
    int lh = (root->left!=NULL)? root->left->height:-1;
    int rh = (root->right!=NULL)? root->right->height:-1;

    return lh - rh;
}

AVL* rebalance(AVL* root){
    if(root->left){
        root->left = rebalance(root->left);
    }
    if(root->right){
        root->right = rebalance(root->right);
    }
    root->height = update_height(root);
    
    int balance = Balance(root);

    // left subtree is of more height
    if(balance > 1){
        // if left subtree is right heavy
        if(Balance(root->left)<0){
            root->left = leftRotate(root->left);
        }
        return rightRotate(root);
    }
    // right subtree is of more height
    else if(balance<-1){
        // right subtree is left
        if(Balance(root->right)>0){
            root->right = rightRotate(root->right);
        }
        return leftRotate(root);
    }
    return root;
}

AVL* insert(AVL* root, AVL* parent, int val){
    if(root==NULL){
        return createNode(val,parent);
    }
    if(val < root->val){
        root->left = insert(root->left, root, val);
        numComparision++;
    }
    else if(val > root->val){
        root->right = insert(root->right, root, val);
        numComparision++;
    }
    root->height = update_height(root);
    return rebalance(root);
}

AVL* delete(AVL* root, AVL* parent, int val){
    if(root==NULL){
        return root;
    }
    // recursively go to the element to be deleted
    if(val < root->val){
        root->left = delete(root->left,root,val);
        numComparision++;
    }
    else if (val > root->val){
        root->right = delete(root->right,root,val);
        numComparision++;
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
        numComparision+=2;
    }
    root->height = update_height(root);
    return rebalance(root);
    
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
    FILE* outputFile = fopen("avl_output.txt", "w");
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
        printf("NUM OF COMPARISIONS = %d\n", numComparision);
        printf("NUM OF * OPERATIONS = %d\n", numPointerOperation);
        printf("------------------------------------------------------------------------------------------------------------------------\n");

        fprintf(outputFile, "%d %d %d\n", numComparision, numPointerOperation, root->height);

        numComparision=0;
        numPointerOperation=0;

        root = NULL;
    }

    // close file
    fclose(file);
    fclose(outputFile);
    return 0;
}