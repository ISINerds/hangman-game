#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../data-structures/trie.h"


BinaryTree* intiliazeBinaryTree(char data,BinaryTree* lc, BinaryTree* rc) {
    BinaryTree* node = (BinaryTree*) malloc(sizeof(BinaryTree));

    if(node == NULL ) {
        printf("Error while allocating a Binary Tree \n");
        return NULL;
    }
    node->id= counter++;
    node->data=data;
    node->left_child= lc; 
    node->right_child= rc; 
    return node;
}
BinaryTree* convertTrieToBT (Trie* trie) {
    if (trie != NULL) {

        BinaryTree* newBT = intiliazeBinaryTree(trie->data, NULL, NULL);

        if(isNodeLeaf(0,trie->array_node_sons) == 1) {
            printf("%c this is a leaf \n", trie->data);
            return newBT;
        }
        else {
            Trie* trie_first_left_child = getFirstRightLeftChild(0,0,trie->array_node_sons);
            newBT->left_child = convertTrieToBT(trie_first_left_child);
            if(trie_first_left_child!= NULL) {
                int j=getAlphabeticalOrder(trie_first_left_child->data) +1;
                newBT->left_child->right_child = convertTrieToBT(getFirstRightLeftChild(j,0,trie->array_node_sons));
                
                BinaryTree* nextBT = newBT->left_child->right_child;
                if(nextBT!=NULL) {
                    j= getAlphabeticalOrder(nextBT->data) + 1;
                    while(j<=26) {
                        if(trie->array_node_sons[j] != NULL) {
                            if(j==26) {
                                nextBT->right_child= NULL;
                                break;
                            }
                            //nextBT= convertTrieToBT(trie->array_node_sons[j]);
                            //nextBT->right_child = convertTrieToBT(getFirstRightLeftChild(j+1,0,trie->array_node_sons));
                            //nextBT->right_child = convertTrieToBT(getFirstRightLeftChild(j,0,trie->array_node_sons));
                            nextBT->right_child = convertTrieToBT(trie->array_node_sons[j]);

                            if(nextBT->right_child != NULL) {
                                j= getAlphabeticalOrder(nextBT->right_child->data)+1;
                                nextBT = nextBT->right_child;
                            }
                            else{
                                return newBT;
                            }
                        }
                        else {
                            j++;
                        }
                        
                    }
                }
                return newBT;
                
            }
            return newBT;

        }

    }
    else {
        return NULL;
    }

    
}

BinaryTree* convertTrieListToBT (Trie** array_roots) {
    BinaryTree* BT;
    Trie* trie_first_left_child = getFirstRightLeftChild(0,1,array_roots);

    if(trie_first_left_child != NULL) {
        int i= getAlphabeticalOrder(trie_first_left_child->data) -1 ;
        BT = convertTrieToBT(trie_first_left_child);
        printf("first index : %d \n", i);
        printf("data : %c \n", BT->data);
        // if(i==25) {
        //     BT->right_child = NULL;
        // }
        if(i<25) {
            BinaryTree* newBT = BT;
            while(i<=25) {
                if(array_roots[i] != NULL) {
                    if(i==25) {
                        newBT->right_child = NULL;
                        break;
                    }
                    else {
                        newBT->right_child = convertTrieToBT(getFirstRightLeftChild(i+1,1,array_roots));
                        if(newBT->right_child != NULL) {
                            i=getAlphabeticalOrder (newBT->right_child->data) - 1;
                            newBT= newBT->right_child;
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    i++;
                }
                
            }

        }
        return BT;

    }
    else {
        return NULL;
    }
}

int main() {

    char *words[] = {"cas", "ce", "ces", "ci", "de", "des", "do"};
    const int size_Words = 7;

    ListTrie dict = initiliazeListTrie(26);

    for (int j=0; j<size_Words; j++) {
        char firstSymbol = words[j][0];
        if (dict.array_roots[getAlphabeticalOrder(firstSymbol) -1 ] == NULL ) {
            Trie* trieP = initiliazeTrie(firstSymbol);
            if (trieP!=NULL) {
                dict.array_roots[getAlphabeticalOrder(firstSymbol)-1]= trieP;

            }else {
                printf("Error in allocation of TrieP pointer \n");
            }
        }
        addWordToTrie(words[j],1,strlen(words[j]), dict.array_roots[getAlphabeticalOrder(firstSymbol)-1]);
        
    }

    // for (int i=0; i< 26; i++) {
    //     if (dict.array_roots[i]!=NULL){
    //         printf("Array at : %d has value : %c \n",getAlphabeticalOrder(dict.array_roots[i]->data) - 1,dict.array_roots[i]->data);
    //         if(i<25) {
    //             printf("the node with value %c has a right sibling : %c \n",dict.array_roots[i]->data, getFirstRightLeftChild(i+1,1,dict.array_roots)->data);
    //         }
    //     }
    // }
    // char* str = "ccc";
    // printf("The word : %s, exists? : %d \n",str,wordExists(str,0,strlen(str),dict.array_roots[getAlphabeticalOrder(str[0])-1 ] ) );

    BinaryTree* BT =convertTrieListToBT(dict.array_roots);
    
    //recursiveBFS(BT);
    generateImageFromBinaryTree(BT);
    free(BT);
    free(dict.array_roots);
    return 0;
}