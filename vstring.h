#ifndef VSTRING
#define VSTRING

typedef struct vstring String;

// string structure
struct vstring
{
    char *str;
    int size;
};

String string(char *initial);
String string_hash(char *raw_input);
String copy_string(String s);
void append_string(String *s, char *str);
void insert_string(String s, char *str, int index);
void update_string(String s, char *str);
void println_string(String s);
void print_string(String s);
void string_to_lower(String *s);
void string_to_upper(String *s);
int compare_strings(String s1, String s2);
int compare_string_str(String s, char *str);
void free_string(String *s);

#endif