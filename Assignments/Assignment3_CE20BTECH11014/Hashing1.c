/*****************************************
 * Assignment 3
 * Name:    Ishan Srivastava
 * E-mail:  ce20btech11014@iith.ac.in
 * Course:  ID2230
 * Submitted:    3/9/2023
 * 
 * Part 1 code of the 3rd assignment which was used to form a hash table from the input generated in Inputs.c
***********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define TABLE_SIZE 100

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

    if(B){
        B->parent = root;
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

    if(B){
        B->parent = root;
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
    }
    else if(val > root->val){
        root->right = insert(root->right, root, val);
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
    }
    else if (val > root->val){
        root->right = delete(root->right,root,val);
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
    }
    root->height = update_height(root);
    return rebalance(root);
    
}

void inorder_print(AVL* root){
    if(root!=NULL){
        inorder_print(root->left);
        printf("%d - ", root->val);
        // printf("(%d) ", root->height);
        inorder_print(root->right);
    }
}

int binary_search(AVL* root, int key){
    int ans = -1;
    while (root!=NULL)
    {
        if(key == root->val){
            return 1;
        }
        if(key<root->val){
            root=root->left;
        }
        else{
            root = root->right;
        }
    }
    return 0;
}


/**
 * CODE FOR HASH TABLE IMPLEMENTATION
 */
struct HashTable
{
    AVL** table;  
    int size;
};

typedef struct HashTable HashTable;

int hashFunc2(int key){
    return key%TABLE_SIZE;
}

int hashFunc(int key){
    double x = (sqrt(5)-1)/2;
    int y = 3;

    double val = x*key - (int)(x*key);
    unsigned int hash = (unsigned int)(TABLE_SIZE*val + y);
    return hash%TABLE_SIZE;
}

HashTable* CreateHashTable(){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = TABLE_SIZE;
    table->table = (AVL**)malloc(sizeof(AVL*)*table->size);
    for(int i =0 ; i<TABLE_SIZE; i++){
        table->table[i]=NULL;
    }
    return table;
}

int HashSearch(HashTable* table, int key){
    int hash = hashFunc(key);
    AVL* root = table->table[hash];
    int val = binary_search(root,key);
    return val;
}

void HashInsert(HashTable* table, int key){
    int hash = hashFunc(key);
    table->table[hash] = insert(table->table[hash],NULL,key);
}

void HashDelete(HashTable* table, int key){
    int hash = hashFunc(key);
    table->table[hash] = delete(table->table[hash],NULL,key);
}

void HashTablePrint(HashTable* table){
    for(int i=0; i< table->size; i++){
        AVL* root = table->table[i];
        printf("TABLE INDEX %d --> ",i);
        inorder_print(root);
        printf("\n");
        printf("\n");
    }
}

int main(){
    HashTable* table = CreateHashTable();
    int array[1000];
    int key;
    for (int i = 0; i < 1000; i++)
    {
        key = rand()%10000000;
        HashInsert(table,key);
        array[i] = key;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    HashTablePrint(table);
    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    int del[100];
    int search[100];
    int i=rand()%10 ,j=rand()%10, k=0;
    while(j<1000 || i<1000){
        del[k]=array[j];
        if(k<50){
            search[k] = array[i];
        }
        else{
            search[k] = rand()%10000000;
        }
        i+=rand()%10+1;
        k++;
        j+= rand()%10+1;
    }
    for(int x=0; x<100; x++){
        printf("%d, %d\n", search[x], HashSearch(table,search[x]));
        HashDelete(table, del[x]);
    }
    HashTablePrint(table);
    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    
    return 0;
}