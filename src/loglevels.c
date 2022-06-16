#include "loglevels.h"

const char LLLUT[4][8] = {
	"debug", "warning","error","none"
};

const char *lltostr(enum LogLevel ll) {
	if(ll < 0 || ll > 3)
		return "none";
	return LLLUT[ll];
}
