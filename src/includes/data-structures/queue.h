#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "./binary_tree.h"

typedef struct QueueNode QueueNode;
struct QueueNode{
    char node_data;
    char left_child_data;
    char right_child_data;
    QueueNode* next;
}; 
typedef struct Queue {
    QueueNode* front; 
    QueueNode* rear;  
}Queue; 

void enqueue(Queue *queue, BinaryTree *tree_node) {
    
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    
    if (newNode == NULL) {
        printf("ERROR: Memory allocation failed for the new node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->node_data = tree_node->data;
    newNode->left_child_data= tree_node->left_child!=NULL?  tree_node->left_child->data : '-' ;
    newNode->right_child_data= tree_node->right_child!=NULL?  tree_node->right_child->data : '-' ;
    newNode->next = NULL;

    if (queue->front == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}
