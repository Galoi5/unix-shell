#include "argparse.h"

// This entire function was made using getopt
// I have spent 4 hours trying to figure out how to do this on my own.
// Dont reinvent the wheel, use the wheel.


int count_words(const char* str) {
    int count = 0;
    int in_word = 0;
    
    while (*str) {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}


char** split_string(const char* input, int* word_count) {
    *word_count = count_words(input);
    char** words = malloc((*word_count + 1) * sizeof(char*));
    if (!words) return NULL;
    
    char* input_copy = strdup(input);
    if (!input_copy) {
        free(words);
        return NULL;
    }
    
    int i = 0;
    char* word = strtok(input_copy, " \t\n");
    while (word && i < *word_count) {
        words[i] = strdup(word);
        if (!words[i]) {
            // Cleanup on error
            for (int j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            free(input_copy);
            return NULL;
        }
        i++;
        word = strtok(NULL, " \t\n");
    }
    words[i] = NULL;  // NULL terminate the array
    
    free(input_copy);
    return words;
}

char** argparse(char* input) {
    if (!input) return NULL;
    
    int word_count;
    char** words = split_string(input, &word_count);
    if (!words) return NULL;

    char** result = malloc((word_count + 1) * sizeof(char*));
    if (!result) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        return NULL;
    }
    
    int result_count = 0;

    if (word_count > 0) {
        result[result_count] = strdup(words[0]);
        if (!result[result_count]) {
            // Cleanup on error
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(result);
            free(words);
            return NULL;
        }
        result_count++;
    }
    
    int opt;
    
    // Reset getopt
    optind = 1;
    
    // Parse options
    while ((opt = getopt(word_count, words, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-")) != -1) {
        if (opt == '?') {
            // Invalid option, skip it
            continue;
        }
        
        // Store the option
        char opt_str[3] = "-";
        opt_str[1] = (char)opt;
        opt_str[2] = '\0';
        
        result[result_count] = strdup(opt_str);
        if (!result[result_count]) {
            // Cleanup on error
            for (int i = 0; i < result_count; i++) {
                free(result[i]);
            }
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(result);
            free(words);
            return NULL;
        }
        result_count++;
        
        // If the option requires an argument, store it
        if (optarg) {
            result[result_count] = strdup(optarg);
            if (!result[result_count]) {
                // Cleanup on error
                for (int i = 0; i < result_count; i++) {
                    free(result[i]);
                }
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(result);
                free(words);
                return NULL;
            }
            result_count++;
        }
    }
    
    // Add any remaining non-option arguments
    while (optind < word_count) {
        result[result_count] = strdup(words[optind]);
        if (!result[result_count]) {
            // Cleanup on error
            for (int i = 0; i < result_count; i++) {
                free(result[i]);
            }
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(result);
            free(words);
            return NULL;
        }
        result_count++;
        optind++;
    }
    
    // NULL terminate the result array
    result[result_count] = NULL;
    
    // Cleanup
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    
    return result;
}

void free_args(char** args) {
    if (!args) return;
    
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
