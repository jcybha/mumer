#include "mumer.h"
#include "plugins/output.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void handle_packet(MUMER_OUTPUT output, MUMER_PACKET packet) {
	printf("hello\n");
}

static void output_close(MUMER_OUTPUT output) {
	if (output->name != NULL)
		free(output->name);
	if (output->data != NULL)
		free(output->data);
}

int print_output_init(MUMER_OUTPUT init) {
	init->name = strdup("print");
	init->data = NULL;

	init->handle_packet = handle_packet;
	init->close = output_close;

	return 0;
}
