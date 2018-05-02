#ifndef BIOX_UTILS_H
#define BIOX_UTILS_H

#include <sys/sysinfo.h>
inline int cpus()
{
  return get_nprocs();
}

#endif