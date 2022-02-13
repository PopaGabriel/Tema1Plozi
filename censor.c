#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "censor_group.h"


int min_int(int a, int b) {
	return (a > b)? b : a;
}


void free_system(Group *words_no_star, Group *words_prefix, Group *words_suffix) {
	free_groups(words_no_star, words_prefix, words_suffix); 
}


int check_suffix(char *suffix, char *target) {
	if (!target || !suffix)  return 0;
	if (strlen(suffix) > strlen(target)) return 0;

	for (int k = 0; k < strlen(suffix); k++) {
		if (suffix[k] != target[strlen(target) - strlen(suffix) + k]) return 0;
	}
	return 1;
}


int check_preffix(char *preffix, char *target) {
	if (!target || !preffix) return 0;
	if (strlen(preffix) > strlen(target)) return 0;
	
	int min = min_int(strlen(preffix), strlen(target));

	for (int i = 0; i < min; i++) {
		if (preffix[i] != target[i]) return 0;
	}
	return 1;
}


int is_word(char *target, Group *group) {
	if (!group || !target) return 0;
	
	for (int i = 0; i < group->size_group; i++) {
		if (strcmp(group->group_words[i], target) == 0) return 0;
	}

	return 1;
}


int is_prefix(char *target, Group *group) {
	if (!group || !target) return 0;

	for (int i = 0; i < group->size_group; i++) {
		if (check_preffix(group->group_words[i], target)) return 1;
	}

	return 0;
}


int is_suffix(char *target, Group *group) {
	if (!group || !target) return 0;

	for (int i = 0; i < group->size_group; i++) {
		if(check_suffix(group->group_words[i], target)) return 1;
	}
	return 0;
}


int can_censor(char *target, Group *words_no_star, Group *words_prefix, Group *words_suffix) {
	return is_prefix(target, words_prefix)
		|| is_suffix(target, words_suffix)
		|| !is_word(target, words_no_star);
}


void write(int length, FILE *target) {
	long double pos = ftell(target);
	rewind(target);
	fseek(target, pos - length - 1, SEEK_SET);

	for (int i = 0; i < length; i++)
		fputc('*', target);
}


void censor(char *name_file_censor, Group *words_no_star, Group *words_prefix, 
		Group *words_suffix) {
	FILE *target = fopen(name_file_censor, "r+");
	Error *aux;

	while (!is_EOF(aux = get_a_word(target))) {
		if (aux->content
			&& !((char *)aux->content)[0] == '\0'
			&& can_censor((char *)aux->content, words_no_star, words_prefix, words_suffix))
				write(strlen((char *)aux->content), target);
		free_error(aux);
	}
	free_error(aux);
	fclose(target);
}


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Not enough arguments");
        return 1;
    }

    Group *words_no_star = NULL, *words_prefix = NULL, *words_suffix = NULL;
    init_words_to_censor(&words_no_star, &words_prefix, &words_suffix, argv[1]);

    print_groups(words_no_star, words_prefix, words_suffix);
	censor(argv[2], words_no_star, words_prefix, words_suffix);
	free_system(words_no_star, words_prefix, words_suffix);
}

