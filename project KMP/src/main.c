#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "../include/kmp.h"
#include "../include/pdf_reader.h"

#define ANSI_BOLD_RED "\033[1;31m"
#define ANSI_YELLOW_BG "\033[1;33;40m"  
#define ANSI_RESET "\033[0m"
#define ANSI_CYAN "\033[1;36m"
#define ANSI_GREEN "\033[1;32m"
#define ANSI_DIM "\033[2m"

#define MAX_WORD_LEN  256

void print_line(const char *symbol, int count, const char *color) {
    if (color) printf("%s", color);
    for (int i = 0; i < count; i++) printf("%s", symbol);
    printf(ANSI_RESET "\n");
}
static void print_highlighted(const char *text, const int *positions, int count, int pattern_len) {
    int text_len = (int)strlen(text);
    int pos_idx = 0;
    int i = 0;
    while (i < text_len) {
        if (pos_idx < count && i == positions[pos_idx]) {
            printf(ANSI_BOLD_RED);
            for (int k = 0; k < pattern_len && i < text_len; k++, i++) putchar(text[i]);
            printf(ANSI_RESET);
            pos_idx++;
        } else {
            putchar(text[i]);
            i++;
        }
    }
}
static void trim(char *s) {
    char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != s) memmove(s, start, strlen(start) + 1);
    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) s[--len] = '\0';
}
int main(void) {
    char input[2048];
    char pattern[MAX_WORD_LEN];

    while (1) {
        system("clear"); 
        printf(ANSI_CYAN "      PDF SEARCH - KMP ALGORITHM\n" ANSI_RESET);
        print_line("_", 40, ANSI_CYAN);

        printf("\n" ANSI_GREEN "Enter PDF filename: " ANSI_RESET);
        if (!fgets(input, sizeof(input), stdin)) break;
        trim(input);

        if (strcasecmp(input, "exit") == 0) break;

        printf(ANSI_GREEN "Enter search pattern: " ANSI_RESET);
        if (!fgets(pattern, sizeof(pattern), stdin)) break;
        trim(pattern);
        PdfDocument *pdf = pdf_open_by_name(input);

        if (!pdf) {
            printf(ANSI_BOLD_RED "\n[ERROR] File not found. Check the name and try again.\n" ANSI_RESET);
            printf("\nPress Enter to continue...");
            getchar();
            continue; 
        }

        int total_matches = 0;
        printf("\n" ANSI_CYAN "         SEARCH RESULTS   \n" ANSI_RESET);
        print_line("_", 40, ANSI_CYAN);

        for (int p = 0; p < pdf->page_count; p++) {
            int match_count = 0;
            int *positions = kmp_search(pdf->pages[p], pattern, &match_count);
            if (match_count > 0) {
                total_matches += match_count;
                printf(ANSI_GREEN "\n[ PAGE %d ] " ANSI_RESET "Matches found: %d\n", p + 1, match_count);
                print_line(".", 30, ANSI_DIM);
                print_highlighted(pdf->pages[p], positions, match_count, (int)strlen(pattern));
                printf("\n");
                print_line("-", 50, ANSI_DIM);
                free(positions);
            }
        }

        printf(ANSI_GREEN "\nSEARCH FINISHED. Total occurrences: " ANSI_RESET ANSI_BOLD_RED "%d\n" ANSI_RESET, total_matches);
        pdf_free_document(pdf);
        printf("\n" ANSI_CYAN "Press Enter' to search again or B' to exit: " ANSI_RESET);
        
        char choice_str[10];
        if (!fgets(choice_str, sizeof(choice_str), stdin)) break;
        if (choice_str[0] == 'b' || choice_str[0] == 'B') {
            printf("\n" ANSI_CYAN "Bye Bye\n" ANSI_RESET);
            break;
        }
    }
    return 0;
}