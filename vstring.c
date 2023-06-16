#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"
#include "vstring.h"

void trim_new_line(char *str_raw) {
    while (*str_raw++ != '\0')
        if (*str_raw == '\n')
            *str_raw = '\0';
}

void append_string(String *s, char *str) {
    u_int16_t new_size = s->size + strlen(str) + 1;
    s->str = realloc(s->str, (new_size) * sizeof(str));
    strcat(s->str, str);
}

void update_string(String s, char *str) {
    trim_new_line(str);
    s.size = strlen(str);
    s.str = realloc(s.str, (s.size + 1) * sizeof(char));
    strcpy(s.str, str);
}

void println_string(String s) { printf("%s\n", s.str); }

void print_string(String s) { printf("%s", s.str); }

void string_to_upper(String *s) {
    for (int i = 0; i < s->size; i++) {
        if (s->str[i] < 'z' && s->str[i] > 'a') {
            s->str[i] = toupper(s->str[i]);
        }
    }
}

void string_to_lower(String *s) {
    for (int i = 0; i < s->size; i++) {
        if (s->str[i] < 'Z' && s->str[i] > 'A') {
            s->str[i] = tolower(s->str[i]);
        }
    }
}

void free_string(String *s) {
    free(s->str);
    s->str = NULL;
}

int compare_strings(String s1, String s2) { return strcmp(s1.str, s2.str); }
int compare_string_str(String s, char *str) { return strcmp(s.str, str); }

String copy_string(String s) {
    String str;
    str.size = s.size;
    str.str = malloc((str.size + 1) * sizeof(char));
    strcpy(str.str, s.str);
    return str;
}

String string(char *initial) {
    String str;
    trim_new_line(initial);
    str.size = strlen(initial);
    str.str = malloc((str.size + 1) * sizeof(char));
    if (str.str == NULL) {
        puts("Failed to allocate character!");
        exit(3);
    }
    strcpy(str.str, initial);
    return str;
}

String string_hash(char *raw_input) {
    String str;
    trim_new_line(raw_input);
    str.str = md5(raw_input, strlen(raw_input));
    str.size = 32;
    if (str.str == NULL) {
        puts("Failed to allocate character!");
        exit(3);
    }
    return str;
}
