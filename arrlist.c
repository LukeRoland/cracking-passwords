#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arrlist.h"

String get_string(List l, int index) {
    if (index < l.length) {
        return l.entries[index];
    }
    puts("List index out of bounds exception!");
    exit(2);
}

void add_string(List *l, String s) {
    if (l != NULL && s.str != NULL) {
        if (l->length >= l->size) {
            l->size = (l->size * 3) / 2;
            l->entries = realloc(l->entries, l->size * sizeof(String));
        }
        *(l->entries + l->length) = s;
        (l->length)++;
    }
}

void remove_string(List *l, int index) {
    printf("%d\n", l->length);
    if (index <= l->length) {
        free_string(&l->entries[index]);
        for (int i = index; i < l->length - 1; i++) {
            l->entries[i] = l->entries[i + 1];
        }
        l->length -= 1;
        return;
    }
    puts("List index out of bounds exception!");
    exit(2);
}

void set_string(List *l, String s, int index) {
    if (index < l->length) {
        l->entries[index] = s;
        return;
    }
    puts("List index out of bounds exception!");
    exit(2);
}

void free_list(List l) {
    for (int i = 0; i < l.length; i++) {
        free_string(&(l.entries)[i]);
    }
    free(l.entries);
}

List array_list() {
    List l;
    l.size = 5;
    l.length = 0;
    l.entries = malloc(l.size * sizeof(String));
    l.get = get_string;
    l.add = add_string;
    l.free = free_list;
    l.pop = remove_string;
    l.set = set_string;
    return l;
}

void read_line(List *l, FILE *f) {
    char new_line[1000];
    fgets(new_line, 1000, f);
    for (int i = 0; new_line[i] != '\0'; i++) {
        if (new_line[i] == '\n')
            new_line[i] = '\0';
    }
    String s = string(new_line);
    l->add(l, s);
}

int compare_elements(const void *s1, const void *s2) {
    String *str1 = (String *)s1;
    String *str2 = (String *)s2;
    return compare_strings(*str1, *str2);
}

double sort_list(List *l) {
    double start = clock();
    qsort(l->entries, l->length, sizeof(String), compare_elements);
    return (clock() - start) / CLOCKS_PER_SEC;
}

String *binary_search_list(List *l, int left, int right, String target) {
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (compare_strings(l->get(*l, middle), target) == 0) {
            String *s = malloc(sizeof(String));
            *s = l->get(*l, middle);
            return s;
        }
        if (compare_strings(l->get(*l, middle), target) < 0)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return NULL;
}

// searches the list using binary search and returns a copy of the string if it
// was found
String *search_list(List *l, String s) {
    return binary_search_list(l, 0, l->length - 1, s);
}
