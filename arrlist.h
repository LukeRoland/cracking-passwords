#ifndef ARRLIST
#define ARRLIST

#include "vstring.h"
#include "stdbool.h"

typedef struct list List;

// fucntion pointers for list structure
typedef String (*get_element)(List l, int index);
typedef void (*add_element)(List *l, String s);
typedef void (*free_elements)(List l);
typedef void (*remove_element)(List *l, int index);
typedef void (*set_element)(List *l, String s, int index);

// dictionary structures
struct list
{
    String *entries;
    int size;
    int length;

    get_element get;
    add_element add;
    remove_element pop;
    free_elements free;
    set_element set;
};

List array_list();
void read_line(List *l, FILE *f);
double sort_list(List *l);
String *search_list(List *l, String s);

#endif
