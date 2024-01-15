#pragma once
#include<stdlib.h>
#include<stdio.h>
typedef struct BinaryTree BinaryTree;
struct BinaryTree{
    char data;
    BinaryTree* left_child;
    BinaryTree* right_child;
};
// ------------------------------functions signitures------------------------


// -------------------------------end functions signitures---------------------

// =-------------------------------------------maha--------------------------
BinaryTree* createNode(char data, BinaryTree* left_child, BinaryTree* right_child){
  BinaryTree* node;
  node = (BinaryTree*) malloc(sizeof(BinaryTree));
  node->data = data;
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

void test (){
    BinaryTree* bt;
    bt=addWordToBinaryTree("hi",bt);
    bt=addWordToBinaryTree("hello",bt);
    bt=addWordToBinaryTree("here",bt);
    bt=addWordToBinaryTree("ear",bt);
    bt=addWordToBinaryTree("near",bt);
    bt=addWordToBinaryTree("dear",bt);
    
}
// --------------------------------------------hajji--------------------------


