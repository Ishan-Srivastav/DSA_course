Assignment 2
Name: Ishan Srivastava
Roll: CE20BTECH11014

This folder conatains the following Files
1. Inputs.c       - Code used to generate 100 inputs of length 1000
2. input.txt      - Ouput file of Inputs.c 
3. BST.c          - Code used to implement binary search trees
4. AVL.c          - Code used to implement AVL trees
5. bst_output.txt - Output of BST.c which conatains Number of comarisons and Height of BST in 1st and 2nd coloum respectively
6. avl_output.txt - Output of AVL.c which conatains Number of comarisons, Number of Pointer Operations and Height of AVL in 1st and 2nd coloum respectively
7. plots.ipynb    - Python Code used to make the plots used in the report
8. Report.pdf     - Report on the data of file bst_output.txt and avl_output.txt, used graphs generated from plots.ipynb

To compile and run the code do the following
1. gcc Inputs.c -o Inputs
   ./Inputs
2. gcc BST.c -o BST
   ./BST
3. gcc AVL.c -o AVL
   ./AVL

Ouputs generated
1. Upon running Inputs.c we get inputs.txt file with random Inputs, 
   depending on these inputs the graphs obtained may change, 
   the graphs in the report are for one of these random inputs

2. Upon running BST.c we get bst_output.txt for inputs of inputs.txt,
   It also prints the inorder traversal and height of the tree along with number of comarisons done

3. Upon running AVL.c we get avl_output.txt for inputs of inputs.txt,
   It also prints the inorder traversal and height of the tree along with number of comarisons and pointer operations done

