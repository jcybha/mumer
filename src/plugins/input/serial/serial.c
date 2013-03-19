#include "mumer.h"
#include "plugins/input.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int input_read(MUMER_INPUT input, void *buf, int count) {
	return 0;
}

static void input_close(MUMER_INPUT input) {
	if (input->name != NULL)
		free(input->name);
	if (input->data != NULL)
		free(input->data);
}

int serial_input_init(MUMER_INPUT init) {
	init->name = strdup("serial");
	init->data = NULL;

	init->read = input_read;
	init->close = input_close;

	return 0;
}
