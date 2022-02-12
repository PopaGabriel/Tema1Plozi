#include "censor_group.h"

Group *create_group()
{
    Group *aux = (Group *)malloc(sizeof(struct group_words));
    aux->size_group = 0;
    aux->group_words = NULL;
    return aux;
}

void add_to_group(char *word, Group *group)
{
    if (group == NULL)
        return;
    if (group->group_words == NULL)
    {
        // Alloc the size
        group->group_words = (char **)malloc(sizeof(char *));
        group->size_group += 1;
        group->group_words[0] = strdup(word);
        return;
    }

    group->size_group += 1;
    group->group_words = (char **)realloc(group->group_words, sizeof(char *) * group->size_group);
    group->group_words[group->size_group - 1] = strdup(word);
}

char *get_a_word(FILE *bad_words_file)
{
    char aux;
    char *return_string = malloc(1);
    return_string[0] = '\0';

    while ((aux = fgetc(bad_words_file)) != EOF && aux != ' ' && aux != '\n')
    {
        return_string = (char *)realloc(return_string, strlen(return_string) + 2);
        strncat(return_string, &aux, 1);
    }
    return return_string;
}

void print(Group *group, char *message)
{
    printf("%s size: %d\n", message, group->size_group);
    for (int i = 0; i < group->size_group; i++)
    {
        printf("%s\n", group->group_words[i]);
    }
}

int index_of(char *haystack, char needle)
{
    if (haystack[0] == '*')
        return 0;

    else if (haystack[strlen(haystack) - 1] == '*')
        return 2;

    return -1;
}

void filter_words(char *word, Group *prefix_group, Group *suffix_group, Group *normal_group)
{
    switch (index_of(word, '*'))
    {
    case -1:
        add_to_group(word, normal_group);
        break;
    case 0:
        add_to_group(word, prefix_group);
        break;
    default:
        add_to_group(word, suffix_group);
        break;
    }
}

void free_group(Group *aux)
{
    if (!aux)
        return;

    for (int i = 0; i < aux->size_group; i++)
        free(aux->group_words[i]);
    free(aux->group_words);
    free(aux);
}

void fill_dicts(Group *words_no_star, Group *words_prefix, Group *words_suffix, char *name)
{
    char *aux;
    FILE *bad_words_file = fopen(name, "r");

    while (strlen((aux = get_a_word(bad_words_file))) != 0)
    {
        filter_words(aux, words_prefix, words_suffix, words_no_star);
        free(aux);
    }
    free(aux);
    fclose(bad_words_file);
}

void build_dict(Group **words_no_star, Group **words_prefix, Group **words_suffix)
{
    *words_no_star = create_group();
    *words_prefix = create_group();
    *words_suffix = create_group();
}

void print_groups(Group *words_no_star, Group *words_prefix, Group *words_suffix)
{
    print(words_no_star, "No star dic");
    print(words_prefix, "prefix start node");
    print(words_suffix, "suffix dict");
}

void free_groups(Group *words_no_star, Group *words_prefix, Group *words_suffix)
{
    free_group(words_no_star);
    free_group(words_prefix);
    free_group(words_suffix);
}

void init_words_to_censor(Group **words_no_star, Group **words_prefix, Group **words_suffix, char *name) {
    build_dict(words_no_star, words_prefix, words_suffix);
    fill_dicts(*words_no_star, *words_prefix, *words_suffix, name);
}
