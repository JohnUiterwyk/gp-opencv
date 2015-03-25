/*
 * popen2.h
 *
 *  Created on: 26/08/2013
 *      Author: james
 */

#ifndef POPEN2_H_
#define POPEN2_H_

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t popen2(const char *command, int *infp, int *outfp);

#endif /* POPEN2_H_ */
