#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
  char** words_array;
  int words_array_size;
}Words;

Words parseFile(const char *file_path) {
    Words words;
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
            
        
        words.words_array = (char **)malloc(words.words_array_size * sizeof(char *));
        if (words.words_array== NULL) {
            printf("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < words.words_array_size; i++) {
            size_t buffer_size = 0;
            getline(&words.words_array[i], &buffer_size, file);

            // remove the newline character if exist
            size_t length = strlen(words.words_array[i]);
            if (words.words_array[i][length - 1] == '\n') {
                words.words_array[i][length - 1] = '\0';
            }
            printf("%s\n",words.words_array[i]);
        }

        fclose(file);

        return words;

    }   
   
}

void freeWordsArray(Words words){
    for (int i=0; i<words.words_array_size; i++){
        free(words.words_array[i]);
    }
    free(words.words_array);
}

//to test that include that file and copy these lines to the main 
    // Words words = parseFile("./assets/words.txt");
    // printf("%d",words.words_array_size);
    // freeWordsArray(words);