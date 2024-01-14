#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct BinaryTree BinaryTree;
struct BinaryTree{
    char data;
    BinaryTree* left_child;
    BinaryTree* right_child;
};
// ------------------------------functions signitures------------------------
BinaryTree* addWord(BinaryTree* root,const char* word);
// void printBinaryTree(BinaryTree* root,int* cc);

// -------------------------------end functions signitures---------------------

// =-------------------------------------------maha--------------------------


// --------------------------------------------hajji--------------------------

BinaryTree* addWord(BinaryTree* root,const char* word){
    if(root==NULL){
        if(word[0]!='\0'){
            root=(BinaryTree*)malloc(sizeof(BinaryTree));
            root->data=word[0];
            root->right_child=NULL;
            root->left_child=addWord(root->left_child,word+1);
            return root;
        }else{
            root=(BinaryTree*)malloc(sizeof(BinaryTree));
            root->data=word[0];
            root->right_child=NULL;
            root->left_child=NULL;
            return root;
        }
    }else{
        if(word[0]==root->data){
            root->left_child=addWord(root->left_child,word+1);
            return root;
        }else{
            root->right_child=addWord(root->right_child,word);
            return root;
        }
    }
}
/*
This function will assist us in displaying the tree.
The only challenge associated with it is the necessity to assign
a unique identifier to each node.
This is crucial because there might be nodes with identical values,
making it difficult to visualize the structure accurately.
*/
// void printBinaryTree(BinaryTree* root,int* cc){
//     if(root->left_child!=NULL)printf("\"%c-%d\" -> \"%c-%d\"\n",root->data,root->id,root->left_child->data,root->left_child->id);
//     else{
//         printf("null%d [shape=point]\n",*cc);
//         printf("\"%c-%d\" -> \"null%d\"\n",root->data,root->id,(*cc)++);
//     }
//     if(root->right_child!=NULL)printf("\"%c-%d\" -> \"%c-%d\"\n",root->data,root->id,root->right_child->data,root->right_child->id);
//     else{
//         printf("null%d [shape=point]\n",*cc);
//         printf("\"%c-%d\" -> \"null%d\"\n",root->data,root->id,(*cc)++);
//     }
//     if(root->left_child!=NULL)printBinaryTree(root->left_child,cc);
//     if(root->right_child!=NULL)printBinaryTree(root->right_child,cc);
// }
