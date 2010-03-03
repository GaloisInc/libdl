/*
 * Libdl
 *  (C) Dario Faggioli <raistlin@linux.it>, 2009, 2010
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License (COPYING file) for more details.
 *
 */

#ifndef __DL_SYSCALLS__
#define __DL_SYSCALLS__

#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <time.h>

#define SCHED_DEADLINE	6

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setscheduler_ex	303
#define __NR_sched_setparam_ex		304
#define __NR_sched_getparam_ex		305
#define __NR_sched_wait_interval	306
#endif

#ifdef __i386__
#define __NR_sched_setscheduler_ex	341
#define __NR_sched_setparam_ex		342
#define __NR_sched_getparam_ex		343
#define __NR_sched_wait_interval	344
#endif

#ifdef __arm__
#define __NR_sched_setscheduler_ex	370
#define __NR_sched_setparam_ex		371
#define __NR_sched_getparam_ex		372
#define __NR_sched_wait_interval	373
#endif

#define SF_SIG_RORUN		2
#define SF_SIG_DMISS		4
#define SF_BWRECL_DL		8
#define SF_BWRECL_RT		16
#define SF_BWRECL_OTH		32

#define RLIMIT_DLDLINE		16
#define RLIMIT_DLRTIME		17

struct sched_param_ex {
	int sched_priority;
	struct timespec sched_runtime;
	struct timespec sched_deadline;
	struct timespec sched_period;
	unsigned int sched_flags;
	struct timespec curr_runtime;
	struct timespec used_runtime;
	struct timespec curr_deadline;
};

int sched_setscheduler_ex(pid_t pid, int policy, unsigned int len,
			  const struct sched_param_ex *param);

int sched_setparam_ex(pid_t pid, unsigned len,
		      const struct sched_param_ex *param);

int sched_getparam_ex(pid_t pid, unsigned len, struct sched_param_ex *param);

int sched_wait_interval(const struct timespec *rqtp, struct timespec *rmtp);

#endif /* __DL_SYSCALLS__ */

