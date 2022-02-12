#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

typedef struct group_words
{
    int size_group;
    char **group_words;
} * Group_p, Group;

Group *create_group();
void add_to_group(char *word, Group *group);
char *get_a_word(FILE *bad_words_file);
void print(Group *group, char *message);
int index_of(char *haystack, char needle);
void filter_words(char *word, Group *prefix_group, Group *suffix_group, Group *normal_group);
void free_group(Group *aux);
void fill_dicts(Group *words_no_star, Group *words_prefix, Group *words_suffix, char *name);
void build_dict(Group **words_no_star, Group **words_prefix, Group **words_suffix);
void print_groups(Group *words_no_star, Group *words_prefix, Group *words_suffix);
void free_groups(Group *words_no_star, Group *words_prefix, Group *words_suffix);
void init_words_to_censor(Group **words_no_star, Group **words_prefix, Group **words_suffix, char *name);
