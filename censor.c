#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "censor_group.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments");
        return 1;
    }

    Group *words_no_star = NULL, *words_prefix = NULL, *words_suffix = NULL;
    init_words_to_censor(&words_no_star, &words_prefix, &words_suffix, argv[1]);

    print_groups(words_no_star, words_prefix, words_suffix);
    free_groups(words_no_star, words_prefix, words_suffix);
}
