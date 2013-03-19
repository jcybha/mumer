/**
 * Multimeter Reader
 * YoungHoon Jung (jung@cs.columbia.edu)
 */

#ifndef _PROTOPLUGIN_H_
#define _PROTOPLUGIN_H_

#include "mumer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* int init(MUMER_PROTO proto); */

typedef struct MUMER_PROTO_STRUCT * MUMER_PROTO;
struct MUMER_PROTO_STRUCT {
	char *name;
	void *data;
	int freq; // Hz
	int length; // bytes

	int (*get_conn_conf)(MUMER_PROTO proto, MUMER_CONNECTION conn);
	
	int (*sync)(MUMER_PROTO proto, char *buf, int size);

	int (*parse)(MUMER_PROTO proto, char *buf, int size, MUMER_PACKET packet);
	void (*close)(MUMER_PROTO proto);
};

#ifdef __cplusplus
}
#endif

#endif /* _PROTOPLUGIN_H_ */
