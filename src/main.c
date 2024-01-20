#include<stdio.h>
#include "./includes/utils/file_parsing.h"
#include "./includes/data-structures/binary_tree.h"
int main(void){
    BinaryTree* root=NULL;
    root=addWordTest(root,"cas");
    root=addWordTest(root,"ce");
    root=addWordTest(root,"ces");
    root=addWordTest(root,"ci");
    root=addWordTest(root,"de");
    root=addWordTest(root,"des");
    root=addWordTest(root,"do");
    generateImageFromBinaryTree(root);
    return 0;
}