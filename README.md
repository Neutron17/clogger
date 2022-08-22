# clogger

# WARNING: this repo is outdated see [nlog](https://github.com/Neutron17/nlog)

basic logger in c

## Example
```c
#include "log.h"

int main() {
  struct Logger log = loginit(LOG_WARN, "log.txt");
  debug(log,"Debug");
  err(log, "Error");
  logdump(log, true);
  logfree(&log);
  return 0;
}
```
