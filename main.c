#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "arrlist.h"
#include "vstring.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Enter the filenames!\n");
    }

    FILE *hashes = fopen(argv[1], "r");
    FILE *dictionary = fopen(argv[2], "r");
    FILE *cracked_passwords = fopen(argv[3], "w");

    if (dictionary == NULL) {
        printf("ERROR: failed to open dictionary file!\n");
        exit(2);
    }

    if (hashes == NULL) {
        printf("ERROR: failed to open hashes dictionary file!\n");
        exit(2);
    }

    if (cracked_passwords == NULL) {
        printf("ERROR: failed to oppen output file!\n");
        exit(2);
    }

    List hash_list = array_list();

    double start_time = clock();
    int num_passwords_cracked = 0;
    int num_passwords_remaining = 0;

    while (!feof(hashes)) {
        char line[50];
        fgets(line, 50, hashes);
        num_passwords_remaining++;
        hash_list.add(&hash_list, string(line));
    }

    sort_list(&hash_list);

    while (!feof(dictionary)) {
        char line[50];
        fgets(line, 50, dictionary);
        String hash = string_hash(line);
        String *result = search_list(&hash_list, hash);
        if (result != NULL) {
            printf("Password: %-20s Hash: %s\n", line, result->str);
            free(result);
            num_passwords_cracked++;
            num_passwords_remaining--;
        }
        free_string(&hash);
        fprintf(cracked_passwords, "%s\n", line);
        if (num_passwords_remaining == 0)
            break;
    }

    hash_list.free(hash_list);
    fclose(dictionary);
    fclose(hashes);
    fclose(cracked_passwords);

    // print the entry to the terminal
    printf("%d cracked with %d reaming!\n", num_passwords_cracked,
           num_passwords_remaining);
    printf("Took %.2f seconds to crack %.2f%% of the passwords!\n",
           (clock() - start_time) / CLOCKS_PER_SEC,
           (num_passwords_cracked /
            (double)(num_passwords_cracked + num_passwords_remaining)) *
               100.0);

    puts("Done!");
}
