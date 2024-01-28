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


Test(test_binary_tree, binary_tree_null_search) {
    // Test case: Searching for a word in a NULL binary tree should return 0
    cr_assert(search_word(NULL, "school") == 0, "Unexpected result when searching for a word in a NULL binary tree.");
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