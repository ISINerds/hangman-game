#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "../utils/file_parsing.h"
#include<stdbool.h>
typedef struct BinaryTree BinaryTree;
struct BinaryTree{
    char data;
    int id;
    BinaryTree* left_child;
    BinaryTree* right_child;
};
int counter=0;

BinaryTree* addWordToBinaryTree(const char* word,BinaryTree* root);
void printBinaryTree(BinaryTree* root,int* cc);


BinaryTree* createNode(char data, BinaryTree* left_child, BinaryTree* right_child){
  BinaryTree* node;
  node = (BinaryTree*) malloc(sizeof(BinaryTree));
  node->data = data;
  node->id=counter++;
  node->left_child = left_child;
  node->right_child = right_child;
  return node;
}

BinaryTree* createBinaryTreeFromWord(const char *word){
  if(word[0] == '\0'){
    return createNode('\0',NULL,NULL);
  } 
  return createNode(word[0],createBinaryTreeFromWord(word+1),NULL);
}

BinaryTree* createBinaryTree(const char *word){
    if(*word == '\0')return createNode('\0',NULL,NULL);
    else return createBinaryTreeFromWord(word);
}

BinaryTree* addWordToBinaryTree(const char *word, BinaryTree* binary_tree){
  if(binary_tree == NULL){
    return createBinaryTree(word);
  } 
  if(word[0] == '\0'){
    return (binary_tree->data == '\0') ? binary_tree : createNode('\0',NULL,binary_tree);
  } 
  if(word[0] < binary_tree->data){
    return createNode(word[0], createBinaryTree(word+1), binary_tree);
  } 
  if(word[0] == binary_tree->data){
    binary_tree->left_child = addWordToBinaryTree(word+1, binary_tree->left_child);
    return binary_tree;
  }
  binary_tree->right_child = addWordToBinaryTree(word, binary_tree->right_child);
  return binary_tree;
}

//initialize an array to store the letter indexes of a letter
int * initiliazePosArray(int size) {
    int* array = (int*) malloc (size * sizeof(int));
    for(int i=0; i<size ; i++) {
        array[i]=0;
    }
    return array;
}

//function to get the letter different indexes of a letter in a word 
//result is an array of 0 and 1  where 0 means that the letter isn't present at this index  
//and 1 means that it is.
int* getletterIndex(int * array_pos ,int index, char letter, char* word, BinaryTree* BT) {
    if(BT == NULL) return array_pos;
    if ( (index==0) && (word[0] < BT->data) ) return array_pos;
    if(BT->data == '\0') {
        if(BT->left_child==NULL && BT->right_child==NULL){
            return array_pos;
        }else{
            return getletterIndex(array_pos, index, letter, word, BT->right_child);
        }
    }
    if(word[0] == BT->data) {
        if(letter==BT->data) {
            array_pos[index]=1;
        }
        return getletterIndex(array_pos, index+1, letter, word+1, BT->left_child);
    }
    else{
        return getletterIndex(array_pos, index, letter, word, BT->right_child);
    }

}

int search_word(BinaryTree* root,char *word){
  if((root == NULL)||(root->data > word[0])) return 0; //does not exist 
  if(word[0] == root->data){
    if(word[0] == '\0') return 1; // exists
    return search_word(root->left_child,word+1);
  }
  return search_word(root->right_child,word);
}

int compareArrayToString(int* array, const char* str) {
        int length = strlen(str);
        for (int i = 0; i < length; ++i) {
            // Convert each digit to a character and compare with the corresponding character in the string
            if (array[i] != (str[i] - '0')) {
                return 0;  //false
            }
        }
        return 1; //true
    }

BinaryTree* addWords(WordList words,BinaryTree* root){
    for(int i=0;i<words.words_array_size;i++){
        root = addWordToBinaryTree(words.words_array[i].word,root);
    }
    return root;
}

BinaryTree* removeWord(BinaryTree* root,BinaryTree* parent,const char* word){
    if((root == NULL)||(root->data > word[0])) return root;
    if(word[0] == root->data){
        root->left_child=removeWord(root->left_child,root,word+1);
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
        return root;
    }
    root->right_child=removeWord(root->right_child,root,word);
    return root;
}

//binary tree graph generation
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

int generateImageFromBinaryTree(BinaryTree *root, const char* output_file_name_without_extension, const char* tree_parser_path) {
    char output_file_name[256];
    snprintf(output_file_name, sizeof(output_file_name), "%s.dot", output_file_name_without_extension);

    FILE *file = fopen(output_file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return EXIT_FAILURE;
    }

    int cc = 0;
    fprintf(file, "digraph G {\n");
    printBinaryTreeToFile(file, root, &cc);
    fprintf(file, "}");
    fclose(file);

    // Construct the command with the provided output_file_name
    char command[500];
    // snprintf(command, sizeof(command), "dot %s | gvpr -c -f %s | neato -n -Tpng -o %s.png", output_file_name,tree_parser_path ,output_file_name_without_extension);
    snprintf(command, sizeof(command), "dot %s -Tpng -o %s.png", output_file_name ,output_file_name_without_extension);

    int result = system(command);
    if (result == -1) {
        perror("Error executing command");
        return EXIT_FAILURE;
    }
    char command2[500];
    snprintf(command2, sizeof(command2), "rm %s", output_file_name);

    int result2 = system(command2);
    if (result2 == -1) {
        perror("Error executing command");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
