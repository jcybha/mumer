#include "mumer.h"
#include "plugins/protocol.h"

#include <string.h>
#include <stdlib.h>

static int numbers[128] = {0, };

static void init_numbers() {
	numbers[5]  = 1;
	numbers[91] = 2;
	numbers[31] = 3;
	numbers[39] = 4;
	numbers[62] = 5;
	numbers[126] = 6;
	numbers[21] = 7;
	numbers[127] = 8;
	numbers[63] = 9;
	numbers[125] = 0;
	numbers[104] = 0; // L
	numbers[0] = 0; // BLANK
}

static int get_number(int upper_bits, int lower_bits) {
	return numbers[upper_bits << 4 | lower_bits];
}

static int get_conn_conf(MUMER_PROTO proto, MUMER_CONNECTION conn) {
	conn->type = MUMER_CONN_SERIAL;

	conn->conn.serial.baud_rate = 2400;
	conn->conn.serial.data_bits = 8;
	conn->conn.serial.parity = 0;
	conn->conn.serial.stop_bits = 1;
	conn->conn.serial.flow_control = 0;
}

static int sync(MUMER_PROTO proto, char *buf, int size) {
	int current_index = buf[0] & 0x80;
	if (current_index < 1 || current_index > proto->length)
		return -1;

	return (proto->length - current_index + 1) % proto->length;
}

static int get_digit(char *buf, int index) {
	return get_number(buf[1 + 2 * index] & 7, buf[2 + 2 * index] & 15);
}

static int parse(MUMER_PROTO proto, char *buf, int size, MUMER_PACKET packet) {
	int i;
	packet->current_type = (buf[0] & 8 ? CT_AC : (buf[0] & 4 ? CT_DC : CT_NONE));
	packet->status = 0;

	if (buf[0] & 1)
		packet->status |= STATUS_RS232;
	if (buf[0] & 2)
		packet->status |= STATUS_AUTO;
	if (buf[9] & 1)
		packet->status |= STATUS_DIODE;
	if (buf[10] & 1)
		packet->status |= STATUS_SPELL;
	if (buf[11] & 2)
		packet->status |= STATUS_REL;
	if (buf[11] & 1)
		packet->status |= STATUS_HOLD;

	if (buf[9] & 8)
		packet->unit_prefix = UP_MICRO;
	else if (buf[9] & 4)
		packet->unit_prefix = UP_NANO;
	else if (buf[9] & 2)
		packet->unit_prefix = UP_KILO;
	else if (buf[10] & 8)
		packet->unit_prefix = UP_MILLI;
	else if (buf[10] & 2)
		packet->unit_prefix = UP_MEGA;

	if (buf[10] & 4)
		packet->unit_prefix = UNIT_DUTYCYCLE;
	else if (buf[11] & 8)
		packet->unit_prefix = UNIT_FARAD;
	else if (buf[11] & 4)
		packet->unit_prefix = UNIT_OHM;
	else if (buf[12] & 8)
		packet->unit_prefix = UNIT_AMPERE;
	else if (buf[12] & 4)
		packet->unit_prefix = UNIT_VOLT;
	else if (buf[12] & 2)
		packet->unit_prefix = UNIT_HERTZ;
	else if (buf[13] & 4)
		packet->unit_prefix = UNIT_CELCIUS;

	packet->number = 0;
	for (i = 0; i < 4; i++) {
		packet->number *= 10;
		packet->number += get_digit(buf, i);
	}
	if (buf[3] & 8)
		packet->number /= 1000;
	else if (buf[5] & 8)
		packet->number /= 100;
	else if (buf[7] & 8)
		packet->number /= 10;
	if (buf[1] & 8)
		packet->number = - packet->number;
}

static void proto_close(MUMER_PROTO proto) {
	if (proto->name != NULL)
		free(proto->name);
	if (proto->data != NULL)
		free(proto->data);
}

int tp4000zc_proto_init(MUMER_PROTO init) {
	init->name = strdup("tp4000zc");
	init->data = NULL;

	int freq = 4;
	int length = 14;

	init->get_conn_conf = get_conn_conf;
	init->parse = parse;
	init->sync = sync;
	init->close = proto_close;

	init_numbers();

	return 0;
}
