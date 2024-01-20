#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "../utils/file_parsing.h"
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


BinaryTree* addWords(Words words,BinaryTree* root){
    for(int i=0;i<words.words_array_size;i++){
        root = addWord(root,words.words_array[i]);   
    }
    return root;
}

BinaryTree* removeWord(BinaryTree* root,BinaryTree* parent,const char* word){
    if((root == NULL)||(root->data > word[0])) return root;
    if(word[0] == root->data){
        root->left_child=removeWord(root->left_child,root,word+1);
        printf("me = %c, parent = %c\n",root->data,parent->data);
        if(parent->left_child==root){
            if(root->left_child==NULL && root->right_child==NULL){
                parent->left_child=NULL;
                free(root);
                return NULL;
            }else if(root->left_child==NULL){
                parent->left_child=root->right_child;
                free(root);
                return parent->left_child;
            }
        }else{
            if(root->left_child==NULL && root->right_child==NULL){
                parent->right_child=NULL;
                free(root);
                return NULL;
            }else if(root->left_child==NULL){
                parent->right_child=root->right_child;
                free(root);
                return parent->right_child;
            }
        }
        // root->data='-';
        return root;
    }
    root->right_child=removeWord(root->right_child,root,word);
    return root;
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