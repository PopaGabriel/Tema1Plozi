#include "error.h"

int is_EOF(Error *error) {
	return error->error_code == 0;
}
