/**
 * Multimeter Reader
 * YoungHoon Jung (jung@cs.columbia.edu)
 */

#ifndef _OUTPUTPLUGIN_H_
#define _OUTPUTPLUGIN_H_

#include "mumer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* int mumer_output_init(MUMER_OUTPUT output); */

typedef struct MUMER_OUTPUT_STRUCT * MUMER_OUTPUT;

struct MUMER_OUTPUT_STRUCT {
	char *name;
	void *data;

	void (*handle_packet)(MUMER_OUTPUT output, MUMER_PACKET pakcet);
	void (*close)(MUMER_OUTPUT output);
};

#ifdef __cplusplus
}
#endif

#endif /* _OUTPUTPLUGIN_H_ */
