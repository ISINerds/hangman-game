#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** words_array;
    int words_array_size;
} Words;

typedef struct {
    char character;
    int count;
} CharCount;

typedef enum {
    EASY,
    MEDIUM,
    HARD
} Difficulty;
typedef struct {
    char* word;
    Difficulty difficulty;
} WordScore;
typedef struct {
    WordScore* words_array;
    int words_array_size;
} WordList;

int findCharIndex(CharCount* chars_table, int table_size, char c) {
    for (int i = 0; i < table_size; ++i) {
        if (chars_table[i].character == c) {
            return i; 
        }
    }
    return -1;
}

float averageCharOccurrence(const char* word) {
    if (word == NULL || *word == '\0') {
        return 0.0;
    }

    int word_length = strlen(word);
    CharCount* chars_table = (CharCount*)malloc(word_length * sizeof(CharCount));
    
    if (chars_table == NULL) {
        printf("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int table_size= 0;

    for (const char* ptr = word; *ptr != '\0'; ++ptr) {

        int char_index = findCharIndex(chars_table, table_size, *ptr);

        if (char_index == -1) {
            // add the character when not found 
            chars_table[table_size].character = *ptr;
            chars_table[table_size].count = 1;
            table_size++;
        } else {
            chars_table[char_index].count++;
        }
    }

   
    float totalOccurrence = 0.0;
    for (int i = 0; i < table_size; i++) {
        totalOccurrence += (float)chars_table[i].count;
    }

    free(chars_table); 

    return totalOccurrence/table_size;
}

int nbVowels(const char* word) {
    if (word == NULL || *word == '\0') {
        return 0;
    }

    int nb_vowels = 0;

    while (*word != '\0') {
        char c = tolower(*word);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            nb_vowels++;
        }
        word++;
    }

    return nb_vowels;
}

void calculateDifficulty(const char* word){
    int length = strlen(word);
    int nb_vowels = nbVowels(word);
    float avg_char_occ = averageCharOccurrence(word);
    // float score = (length + 0.5*avg_char_occ)*nb_vowels/10;
    float score = (length +nb_vowels)/avg_char_occ;
    printf("%s -- %.2f\n",word,score);
}

WordList parseFile(const char *file_path) {
    WordList words;
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }else {

        words.words_array_size = 0;
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '\n') {
                words.words_array_size ++;
            }
        }
        if (ch != '\n') {
            words.words_array_size++;
        }

        // go back to the beginning of the file
        fseek(file, 0, SEEK_SET);
            
        
        words.words_array = (WordScore*)malloc(words.words_array_size * sizeof(WordScore));
        if (words.words_array== NULL) {
            printf("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < words.words_array_size; i++) {
            size_t buffer_size = 0;
            getline(&words.words_array[i].word, &buffer_size, file);

            // remove the newline character if exist
            size_t length = strlen(words.words_array[i].word);
            if (words.words_array[i].word[length - 1] == '\n') {
                words.words_array[i].word[length - 1] = '\0';
            }
            words.words_array[i].difficulty= EASY;
            //easy 0..3 // meduim 3..5 // hard 6+
            //TO_DO 
            calculateDifficulty(words.words_array[i].word);
        }

        fclose(file);

        return words;

    }   
   
}

void freeWordsArray(WordList words){
    for (int i=0; i<words.words_array_size; i++){
        free(words.words_array[i].word);
    }
    free(words.words_array);
}

//to test that include that file and copy these lines to the main 
    // Words words = parseFile("./assets/words.txt");
    // printf("%d",words.words_array_size);
    // freeWordsArray(words);

//--------------
