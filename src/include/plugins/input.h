/**
 * Multimeter Reader
 * YoungHoon Jung (jung@cs.columbia.edu)
 */

#ifndef _INPUTPLUGIN_H_
#define _INPUTPLUGIN_H_

#include "mumer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* int init(MUMER_INPUT input); */

typedef struct MUMER_INPUT_STRUCT * MUMER_INPUT;
struct MUMER_INPUT_STRUCT {
	char *name;
	void *data;

	int (*read)(MUMER_INPUT input, void *buf, int count);
	void (*close)(MUMER_INPUT input);
};

#ifdef __cplusplus
}
#endif

#endif /* _INPUTPLUGIN_H_ */
