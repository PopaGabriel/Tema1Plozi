#include <stdlib.h>


enum ERROR {
	E_NO_ERROR,
	E_EOF
};

typedef struct error_read {
	enum ERROR error_code;
	void *content;
} *Error_p,  Error;

int is_EOF(Error *error);
Error *init_error_empty();
Error *init_error(int error_code, void *data);
char *get_string(Error *error);
void free_error(Error *error);

