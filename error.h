enum ERROR {
	E_NO_ERROR,
	E_EOF
};

typedef struct error_read {
	enum ERROR error_code;
	void *content;
} *Error_p, Error;

int is_EOF(Error *error);
char *get_string(Error *error);
