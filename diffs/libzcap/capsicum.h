/*
 * We're using Capsicum!
 */
#ifndef CAPSICUM_H
#define CAPSICUM_H

#include <sys/queue.h>

#include <nv.h>

void startSandbox(void *data);
void stopSandbox(void *ptr);
void startNullSandbox(void);
struct sandbox * findSandbox(void *ptr);
struct sandbox *startChild(void *data);
void killChild(void);
void suicide(int signal);
nvlist_t * sendCommand(nvlist_t *nvl, void *ptr);
#endif	/* !CAPSICUM_H */