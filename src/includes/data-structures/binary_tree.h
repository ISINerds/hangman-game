#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "../utils/file_parsing.h"
#include "./queue.h"

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
BinaryTree* createNode(char data, BinaryTree* left_child, BinaryTree* right_child){
  BinaryTree* node;
  node = (BinaryTree*) malloc(sizeof(BinaryTree));
  node->data = data;
  node->id=counter++;
  node->left_child = left_child;
  node->right_child = right_child;
  return node;
}

BinaryTree* createBinaryTree(char *word){
  if(word[0] == '\0'){
    return createNode('\0',NULL,NULL);
  } 
  return createNode(word[0],createBinaryTree(word+1),NULL);
}

BinaryTree* addWordToBinaryTree(char *word, BinaryTree* binary_tree){
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

int search_word(char *word, BinaryTree *binary_tree, Queue* q){
  if((binary_tree == NULL)||(word[0] < binary_tree->data)) return 0;
  printf("%c \t",binary_tree->data);
  enqueue(q, binary_tree);
  if(word[0] == binary_tree->data){
    if(word[0] == '\0') return 1;
    return search_word(word+1, binary_tree->left_child, q);
  }
  return search_word(word, binary_tree->right_child,q);
}


void letter_index(Queue *q, char c){
    int i=-1;
    int exist=-1;
    QueueNode *p = q->front;
    while(p->next!=NULL){
        if(p->next->node_data==p->left_child_data){
            i++;
            if(p->node_data==c) {
                printf("letter %c exists at index %d\n",c,i);
                exist=1;
            }
        }
        p=p->next;
    }
    if(exist==-1){
        printf("letter %c does not exist\n",c);
    }
}


// void test (){
//     BinaryTree* bt=NULL; 
//     const char *words[] = {"do", "desert", "ce","ces","ci","casse"};
//     for(int i=0; i < sizeof(words) / sizeof(words[0]);i++){
//         bt=addWordToBinaryTree(words[i],bt);
//     }  
//     char letters[] = {'c', 'd', 'e', 'i', 'o', 's','a'}; 
//     for(int i=0; i < sizeof(words) / sizeof(words[0]);i++){
//         printf("-------------------------\n");
//         printf("Word = %s \n",words[i]);
//         Queue* q = (Queue*)malloc(sizeof(Queue));
//         q->front = q->rear = NULL;
//         printf("path: ");
//         int word_exist = search_word(words[i],bt,q);
//         printf("\n");
//         if(word_exist!=0){
//             for(int i=0; i < sizeof(letters) / sizeof(letters[0]);i++){
//                 letter_index(q,letters[i]);
//             }
//         }
//     }
// }

// --------------------------------------------hajji--------------------------


BinaryTree* addWords(Words words,BinaryTree* root){
    for(int i=0;i<words.words_array_size;i++){
        root = addWordToBinaryTree(words.words_array[i],root);
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