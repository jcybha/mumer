/**
 * Multimeter Reader
 * YoungHoon Jung (jung@cs.columbia.edu)
 */

#ifndef _MUMER_H_
#define _MUMER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MUMER_HANDLE * MUMER_HANDLE;

typedef struct MUMER_SERIAL_STRUCT {
	int baud_rate;
	int data_bits;
	int parity;
	int stop_bits;
	int flow_control;
} *MUMER_SERIAL;

typedef struct MUMER_CONNECTION_STRUCT {
	enum { MUMER_CONN_SERIAL, } type;
	union {
		struct MUMER_SERIAL_STRUCT serial;
	} conn;
} *MUMER_CONNECTION;

typedef struct MUMER_PACKET_STRUCT {
	enum { CT_NONE, CT_AC, CT_DC } current_type;
	enum { UP_NANO, UP_MICRO, UP_MILLI, UP_NONE, UP_KILO, UP_MEGA } unit_prefix;
	enum { UNIT_VOLT, UNIT_AMPERE, UNIT_FARAD, UNIT_HERTZ,
		UNIT_DUTYCYCLE, UNIT_CELCIUS, UNIT_OHM } unit;
	enum { STATUS_DIODE, STATUS_REL, STATUS_AUTO, STATUS_RS232,
		STATUS_HOLD, STATUS_SPELL, } status;

	double number;

	int reserve[32];

} *MUMER_PACKET;

#ifdef __cplusplus
}
#endif

#endif /* _MUMER_H_ */
