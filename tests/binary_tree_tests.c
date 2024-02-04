#include <criterion/criterion.h>
#include "../src/includes/data-structures/binary_tree.h"

Test(test_binary_tree, binary_tree_creation) {
    // Test case 1: Creating a binary tree with a non-empty string
    BinaryTree* root = createBinaryTree("apple");
    cr_assert(root != NULL, "Failed to create binary tree.");
    int res = generateImageFromBinaryTree(root,"./tests/images/test_binary_tree_creation","./assets/tree.gv");
    cr_assert(res == 0, "Failed to generate graph image.");

    // Test case 2: Creating a binary tree with an empty string
    BinaryTree* emptyTree = createBinaryTree("");
    cr_assert(emptyTree == NULL, "Unexpectedly created a binary tree with an empty string.");
}

Test(test_binary_tree, binary_tree_adding_word) {
    // Test case 1: Adding a word to an empty binary tree
    BinaryTree* root = NULL;
    root = addWordToBinaryTree("school", root);
    cr_assert(root != NULL, "Failed to add word to binary tree.");
    int res = generateImageFromBinaryTree(root,"./tests/images/test_binary_tree_adding_word","./assets/tree.gv");
    cr_assert(res == 0, "Failed to generate graph image.");


    // Test case 2: Adding an empty string to the binary tree
    BinaryTree* emptyTree = addWordToBinaryTree("", NULL);
    cr_assert(emptyTree == NULL, "Unexpectedly added an empty string to the binary tree.");
}

Test(test_binary_tree, binary_tree_adding_list_of_words) {
    // Test case 1: Adding a list of words to an empty binary tree
    BinaryTree* root = NULL;
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore*)*5);
    words_array[0].word = "school";
    words_array[0].difficulty = EASY;
    
    words_array[1].word = "apple";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "tree";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "education";
    words_array[3].difficulty = EASY;
    
    words_array[4].word = "evaluation";
    words_array[4].difficulty = EASY;
    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };
    root = addWords(words, root);
    cr_assert(root != NULL, "Failed to add list of words to binary tree.");
    int res = generateImageFromBinaryTree(root,"./tests/images/test_binary_tree_adding_list_of_words","./assets/tree.gv");
    cr_assert(res == 0, "Failed to generate graph image.");


    // Test case 2: Adding an empty list of words to the binary tree
    BinaryTree* emptyTree = addWords((WordList){.words_array = (WordScore*)0, .words_array_size = 0}, NULL);
    cr_assert(emptyTree == NULL, "Unexpectedly added an empty list of words to the binary tree.");
}

Test(test_binary_tree, binary_tree_word_search) {
    BinaryTree* root = NULL;
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore*)*5);
    words_array[0].word = "school";
    words_array[0].difficulty = EASY;
    
    words_array[1].word = "apple";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "tree";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "education";
    words_array[3].difficulty = EASY;
    
    words_array[4].word = "evaluation";
    words_array[4].difficulty = EASY;

    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };
    root = addWords(words, root);
    int res = generateImageFromBinaryTree(root,"./tests/images/test_binary_tree_word_search","./assets/tree.gv");
    cr_assert(res == 0, "Failed to generate graph image.");


    // Test case 1: Word "school" should be found in the binary tree
    cr_assert(search_word(root, "school") == 1, "Failed to find the word 'school' in the binary tree.");

    // Test case 2: Word "banana" should not be found in the binary tree
    cr_assert(search_word(root, "banana") == 0, "Unexpectedly found the word 'banana' in the binary tree.");

    // Additional test cases for edge scenarios:
    // Test case 3: Searching in an empty binary tree should return 0
    BinaryTree* emptyTree = NULL;
    cr_assert(search_word(emptyTree, "apple") == 0, "Unexpected result in an empty binary tree.");

    // Test case 4: Searching for an empty string should return 0
    cr_assert(search_word(root, "") == 0, "Unexpected result when searching for an empty string.");

    // Test case 5: Searching for a word not added to the tree should return 0
    cr_assert(search_word(root, "grape") == 0, "Unexpected result when searching for a non-existing word.");
}

Test(test_binary_tree, binary_tree_remove_word) {
    // Test case 1: Removing a word from a tree with one node
    BinaryTree* root1 = createBinaryTree("apple");
    root1 = removeWord(root1, root1, "apple");
    cr_assert(root1 == NULL, "Failed to remove the only word from the binary tree.");

    // Test case 2: Removing a word from a tree with multiple nodes
    BinaryTree* root2 = createBinaryTree("apple");
    root2 = addWordToBinaryTree("banana", root2);
    root2 = addWordToBinaryTree("cherry", root2);
    root2 = removeWord(root2, root2, "banana");
    cr_assert(search_word(root2, "banana") == 0, "Failed to remove word 'banana' from the binary tree.");

    // Test case 3: Removing a word that doesn't exist in the tree
    BinaryTree* root3 = createBinaryTree("apple");
    root3 = removeWord(root3, root3, "banana");
    cr_assert(root3 != NULL, "Unexpectedly removed a non-existing word from the binary tree.");

    // Test case 4: Removing a word from an empty tree
    BinaryTree* root4 = NULL;
    root4 = removeWord(root4, root4, "apple");
    cr_assert(root4 == NULL, "Unexpected result when removing a word from an empty binary tree.");

    // Test case 5: Removing a word and verifying the tree structure
    BinaryTree* root5 = createBinaryTree("apple");
    root5 = addWordToBinaryTree("banana", root5);
    root5 = addWordToBinaryTree("cherry", root5);
    root5 = addWordToBinaryTree("date", root5);
    root5 = removeWord(root5, root5, "banana");
    cr_assert(search_word(root5, "banana") == 0, "Failed to remove word 'banana' from the binary tree.");
    cr_assert(search_word(root5, "apple") == 1, "Unexpected result when searching for word 'apple' after removal.");
    cr_assert(search_word(root5, "cherry") == 1, "Unexpected result when searching for word 'cherry' after removal.");
    cr_assert(search_word(root5, "date") == 1, "Unexpected result when searching for word 'date' after removal.");
}

Test(test_binary_tree, binary_tree_get_letter_indexes) {   
    // Test case 1: attempting to get the indexes of a letter in a word while the binary tree is empty. 
    int *pos_array = initiliazePosArray(strlen("school"));
    BinaryTree* emptyTree = NULL;
    cr_assert(getletterIndex(pos_array ,0, 'c', "school",emptyTree)==NULL, "Unexpected result when attempting to get indexes of a letter in a word in a NULL binary tree.");

    // Test case 2: attempting to get indexes of a letter in an empty string.
    BinaryTree* root1 = createBinaryTree("apple");
    root1 = addWordToBinaryTree("school", root1);
    int *pos_array1 = initiliazePosArray(strlen("school"));
    cr_assert(getletterIndex(pos_array1 ,0, 'c', "",root1)==NULL, "Unexpected result when attempting to get indexes of a letter in an empty string.");

    // Test case 3: attempting to get indexes of a letter that is not present in the word.
    BinaryTree* root2 = createBinaryTree("apple");
    root2 = addWordToBinaryTree("school", root2);
    int *pos_array2 = initiliazePosArray(strlen("school"));
    pos_array2= getletterIndex(pos_array2 ,0, 'a', "school",root2);
    cr_assert(compareArrayToString(pos_array2,"000000")==1, "Unexpected result when attempting to get indexes of a letter that is not in the word.");
    
    // Test case 4: getting index of a letter that is present once in the word.
    BinaryTree* root3 = createBinaryTree("apple");
    root3 = addWordToBinaryTree("school", root3);
    int *pos_array3 = initiliazePosArray(strlen("school"));
    pos_array3= getletterIndex(pos_array3 ,0, 'h', "school",root3);
    cr_assert(compareArrayToString(pos_array3,"001000")==1, "Unexpected result when attempting to get indexes of a letter that is present once in the word.");

    // Test case 5: getting indexes of a letter with multiple occurrences in the word.
    BinaryTree* root4 = createBinaryTree("apple");
    root4 = addWordToBinaryTree("school", root4);
    int *pos_array4 = initiliazePosArray(strlen("school"));
    pos_array4= getletterIndex(pos_array4 ,0, 'o', "school",root4);
    cr_assert(compareArrayToString(pos_array4,"000110")==1, "Unexpected result when attempting to get indexes of a letter with multiple occurrences in the word.");

}