#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define TABLE_SIZE1 1024
#define TABLE_SIZE2 2048

int probes = 0;

struct HashTable
{
    int* table;
    int capacity;
};

typedef struct HashTable HashTable;

int hashFunc1(int key, HashTable* table){
    int w = 16;
    unsigned int ans = (unsigned int)((key>>w) + (key<<w))%table->capacity;
    return ans;
}

int hashFunc2(int key, HashTable* table){
    return (2*key + 1)%table->capacity;
}


void createHashTable(HashTable* table, int capacity){
    table->table = (int*)malloc(capacity*sizeof(int));
    table->capacity = capacity;
    for(int i=0; i<capacity; i++){
        table->table[i] = -1;
    }
}

void insert(HashTable* table, int key, FILE* file){
    int h1 = hashFunc1(key,table);
    int h2 = hashFunc2(key,table);
    int index = (h1)%table->capacity;
    while (table->table[index]!=-1)
    {  
        index = (index + h2)%table->capacity;
        probes+=1;
    }
    if(table->table[index]==-1){
        fprintf(file,"Inserting key: %d at Index: %d\n", key, index);
        table->table[index] = key;
    }else{
        printf("Failed to insert key\n");
    }
    probes=0;
}

int search(HashTable* table, int key, FILE* file){
    int h1 = hashFunc1(key,table);
    int h2 = hashFunc2(key,table);
    int index = (h1)%table->capacity;
    int count = 0;
    while (table->table[index]!=-1)
    { 
        probes+=1;
        if(table->table[index]==key){
            fprintf(file,"Found key: %d at index: %d| number of probes: %d\n", key, index, probes);
            probes=0;
            return index;  
        } 
        index = (index + h2)%table->capacity;
    }
    fprintf(file,"key: %d not found| number of probes: %d\n", key, probes);
    probes=0;
    return -1;
}

void delete(HashTable* table, int key, FILE* file){
    int h1 = hashFunc1(key,table);
    int h2 = hashFunc2(key,table);
    int index = (h1)%table->capacity;
    while (table->table[index]!=key && table->table[index]!=-1)
    {  
        index = (index + h2)%table->capacity;

    }
    if(table->table[index]!=-1 && table->table[index]==key){
        table->table[index] = -2;
        fprintf(file,"Deleted key: %d at Index: %d\n", key,index);
    }else{
        fprintf(file,"Failed to delete key: %d at index: %d, table[index] = %d\n", key, index, table->table[index]);
    }
}

void indicies_count(HashTable* table){
    int count = 0, size =0;
    for(int i=0; i<table->capacity; i++){
        
        if(table->table[i]==-1 || table->table[i]==-2){
            count+=1;
        }else{
            size+=1;
        }
    }
    printf("Table Size:- %d Table Empty Spaces: %d\n", size, count);
}

void print_hash_table(HashTable* table){
    for(int i=0; i<table->capacity; i++){
        printf("%d - %d \n", i, table->table[i]);
    }
}

int main(){
    // HashTable* table = createHashTable(TABLE_SIZE1);
    // HashTable* table2 = createHashTable(TABLE_SIZE2);
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    HashTable* table2= (HashTable*)malloc(sizeof(HashTable)) ;
    createHashTable(table,TABLE_SIZE1);
    createHashTable(table2,TABLE_SIZE2);
    int array[1000];
    int in_table[1000];
    int key;
    FILE* file1 = fopen("table1.txt", "w");
    FILE* file2 = fopen("table2.txt", "w");
    // srand(time(0));
    for(int i = 0; i < 1000; i++)
    {
        key = rand()%10000000 + 1;
        array[i] = key;
        in_table[i] = 1;
        for(int j=0; j<i; j++){
            if(array[j] == key){
                array[i] = -1;
                i--;
                break;
            }
        }
        if(array[i]!=-1){
            insert(table,key, file1);
            insert(table2,key, file2);
        }
        // insert(table2,key);
        array[i] = key;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Table 1\n");
    indicies_count(table);

    printf("Table 2\n");
    indicies_count(table2);
    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    int del[100];
    int find[100];
    int i=rand()%10 ,j=rand()%10, k=0;
    while(k<100){
        del[k]=array[j];
        in_table[j] = 0;
        find[k] = array[i];
        i+=rand()%5+1;
        k++;
        j+= rand()%5+1;
    }
    // 100 successfull searches
    for(int x=0; x<100; x++){
        search(table, find[x], file1);
        search(table2, find[x], file2);
    }
    // 100 deletes
    for(int x=0; x<100; x++){
        delete(table, del[x], file1);
        delete(table2, del[x], file2);
    }
    k=0;
    i = 0;
    while(k<100){
        i+=rand()%5+1;
        if(in_table[i]==0){
            continue;
        }
        find[k] = array[i];
        k++;
    }
    // another 100 successfull searches
    for(int x=0; x<100; x++){
        search(table, find[x], file1);
        search(table2, find[x], file2);
    }
    // 100 unsuccessfull searches
    for(int x=0; x<100; x++){
        search(table, del[x], file1);
        search(table2, del[x], file2);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Table 1\n");
    indicies_count(table);

    printf("Table 2\n");
    indicies_count(table2);
    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    fclose(file1);
    fclose(file2);
    return 0;
}