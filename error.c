#include "error.h"

int is_EOF(Error *error) {
	return error->error_code == 1;
}

Error *init_error(int error_code, void *data) {
	Error *aux = (Error *) malloc (sizeof(struct error_read));
	aux->error_code = error_code;
	aux->content = data;

	return aux;
}

void free_error(Error *error) {
	if (!error) return;

	if (error->content)
		free(error->content);
	free(error);
}

