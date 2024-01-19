#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct BinaryTree BinaryTree;
struct BinaryTree{
    char data;
    int id;
    BinaryTree* left_child;
    BinaryTree* right_child;
};
int counter=0;
// ------------------------------functions signitures------------------------
BinaryTree* addWord(BinaryTree* root,const char* word);
void printBinaryTree(BinaryTree* root,int* cc);

// -------------------------------end functions signitures---------------------

// =-------------------------------------------maha--------------------------


// --------------------------------------------hajji--------------------------

BinaryTree* addWordTest(BinaryTree* root,const char* word){
    if(root==NULL){
        if(word[0]!='\0'){
            root=(BinaryTree*)malloc(sizeof(BinaryTree));
            root->data=word[0];
            root->id=counter++;
            root->right_child=NULL;
            root->left_child=addWord(root->left_child,word+1);
            return root;
        }else{
            root=(BinaryTree*)malloc(sizeof(BinaryTree));
            root->data=word[0];
            root->id=counter++;
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
void printBinaryTreeToFile(FILE* file, BinaryTree* root,int* cc){
    if(root->left_child!=NULL){
        if(root->data=='\0'){
            fprintf(file, "Node%d [label=\"\\\\0\"]\n",root->id);
        }else{
            fprintf(file, "Node%d [label=\"%c\"]\n",root->id,root->data);
        }
        if(root->left_child->data=='\0'){
            fprintf(file, "Node%d [label=\"\\\\0\"]\n",root->left_child->id);
        }else{
            fprintf(file, "Node%d [label=\"%c\"]\n",root->left_child->id,root->left_child->data);
        }
        fprintf(file, "\"Node%d\" -> \"Node%d\"\n",root->id,root->left_child->id);
    }
    else{
        fprintf(file, "null%d [shape=point]\n",*cc);
        if(root->data=='\0'){
            fprintf(file, "Node%d [label=\"\\\\0\"]\n",root->id);
        }else{
            fprintf(file, "Node%d [label=\"%c\"]\n",root->id,root->data);
        }
        fprintf(file, "\"Node%d\" -> \"null%d\"\n",root->id,(*cc)++);
    }
    if(root->right_child!=NULL){
        if(root->data=='\0'){
            fprintf(file, "Node%d [label=\"\\\\0\"]\n",root->id);
        }else{
            fprintf(file, "Node%d [label=\"%c\"]\n",root->id,root->data);
        }
        if(root->right_child->data == '\0'){
            fprintf(file, "Node%d [label=\"\\\\0\"]\n",root->right_child->id);
        }else{
            fprintf(file, "Node%d [label=\"%c\"]\n",root->right_child->id,root->right_child->data);
        }
        fprintf(file, "\"Node%d\" -> \"Node%d\"\n",root->id,root->right_child->id);
    }
    else{
        fprintf(file, "null%d [shape=point]\n",*cc);
        if(root->data=='\0'){
            fprintf(file, "Node%d [label=\"\\\\0\"]\n",root->id);
        }else{
            fprintf(file, "Node%d [label=\"%c\"]\n",root->id,root->data);
        }

        fprintf(file, "\"Node%d\" -> \"null%d\"\n",root->id,(*cc)++);
    }
    if(root->left_child!=NULL)printBinaryTreeToFile(file,root->left_child,cc);
    if(root->right_child!=NULL)printBinaryTreeToFile(file,root->right_child,cc);
}
void generateImageFromBinaryTree(BinaryTree* root){
    FILE *file = fopen("tree.dot", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }
    int cc=0;
    fprintf(file,"digraph G {\n");
    printBinaryTreeToFile(file, root, &cc);
    fprintf(file,"}");
    fclose(file);
    int result = system("dot tree.dot | gvpr -c -ftree.gv | neato -n -Tsvg -o trie.svg");
    if (result == -1) {
        perror("Error executing command");
    }
}
// #include<stdio.h>
// #include "./includes/data-structures/binary_tree.h"
// int main(void){
//     BinaryTree* root=NULL;
//     root=addWord(root,"cas");
//     root=addWord(root,"ce");
//     root=addWord(root,"ces");
//     root=addWord(root,"ci");
//     root=addWord(root,"de");
//     root=addWord(root,"des");
//     root=addWord(root,"do");
//     generateImageFromBinaryTree(root);
//     return 0;
// }