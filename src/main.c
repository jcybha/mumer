#include "mumer.h"
#include "plugins/input.h"
#include "plugins/output.h"
#include "plugins/protocol.h"

#include <stdio.h>

int main() {
	struct MUMER_INPUT_STRUCT input;
	struct MUMER_PROTO_STRUCT proto;
	struct MUMER_OUTPUT_STRUCT output;	

	serial_input_init(&input);
	tp4000zc_proto_init(&proto);
	print_output_init(&output);
}
