#include "wheel/wheel/def.h"

typedef struct rc rc;

rc rc_init(LIBWHEEL_TYPE value);

rc rc_copy(rc);

void rc_delete(rc);

#include "wheel/wheel/undef.h"
