/*************************************************************************
    Copyright (C) 2005 Joseph D'Errico, Wei Qin
    See file COPYING for more information.

    This program is free software; you can redistribute it and/or modify    
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*************************************************************************/
/***************************************************************************
                          syscall.c  -  description
                             -------------------
    begin                : Wed Sep 26 2001
    copyright            : (C) 2001 CEA and Université Paris XI Orsay
    author               : Gilles Mouchard
    email                : gilles.mouchard@lri.fr, gilles.mouchard@cea.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/* The file is modified by Wei Qin for arm target.
 * Added mmap syscall interpretation.
 */

#ifdef linux
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

#define EINVAL 22
#include "config.h"
#include "misc.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/times.h>

#include "arch.hpp"

#define __SYSCALL_exit		  1
#define __SYSCALL_fork		  2
#define __SYSCALL_read		  3
#define __SYSCALL_write		  4
#define __SYSCALL_open		  5
#define __SYSCALL_close		  6
#define __SYSCALL_waitpid		  7
#define __SYSCALL_creat		  8
#define __SYSCALL_link		  9
#define __SYSCALL_unlink		 10
#define __SYSCALL_execve		 11
#define __SYSCALL_chdir		 12
#define __SYSCALL_time		 13
#define __SYSCALL_mknod		 14
#define __SYSCALL_chmod		 15
#define __SYSCALL_lchown		 16
#define __SYSCALL_break		 17
#define __SYSCALL_oldstat		 18
#define __SYSCALL_lseek		 19
#define __SYSCALL_getpid		 20
#define __SYSCALL_mount		 21
#define __SYSCALL_umount		 22
#define __SYSCALL_setuid		 23
#define __SYSCALL_getuid		 24
#define __SYSCALL_stime		 25
#define __SYSCALL_ptrace		 26
#define __SYSCALL_alarm		 27
#define __SYSCALL_oldfstat		 28
#define __SYSCALL_pause		 29
#define __SYSCALL_utime		 30
#define __SYSCALL_stty		 31
#define __SYSCALL_gtty		 32
#define __SYSCALL_access		 33
#define __SYSCALL_nice		 34
#define __SYSCALL_ftime		 35
#define __SYSCALL_sync		 36
#define __SYSCALL_kill		 37
#define __SYSCALL_rename		 38
#define __SYSCALL_mkdir		 39
#define __SYSCALL_rmdir		 40
#define __SYSCALL_dup		 41
#define __SYSCALL_pipe		 42
#define __SYSCALL_times		 43
#define __SYSCALL_prof		 44
#define __SYSCALL_brk		 45
#define __SYSCALL_setgid		 46
#define __SYSCALL_getgid		 47
#define __SYSCALL_signal		 48
#define __SYSCALL_geteuid		 49
#define __SYSCALL_getegid		 50
#define __SYSCALL_acct		 51
#define __SYSCALL_umount2		 52
#define __SYSCALL_lock		 53
#define __SYSCALL_ioctl		 54
#define __SYSCALL_fcntl		 55
#define __SYSCALL_mpx		 56
#define __SYSCALL_setpgid		 57
#define __SYSCALL_ulimit		 58
#define __SYSCALL_oldolduname	 59
#define __SYSCALL_umask		 60
#define __SYSCALL_chroot		 61
#define __SYSCALL_ustat		 62
#define __SYSCALL_dup2		 63
#define __SYSCALL_getppid		 64
#define __SYSCALL_getpgrp		 65
#define __SYSCALL_setsid		 66
#define __SYSCALL_sigaction		 67
#define __SYSCALL_sgetmask		 68
#define __SYSCALL_ssetmask		 69
#define __SYSCALL_setreuid		 70
#define __SYSCALL_setregid		 71
#define __SYSCALL_sigsuspend		 72
#define __SYSCALL_sigpending		 73
#define __SYSCALL_sethostname	 74
#define __SYSCALL_setrlimit		 75
#define __SYSCALL_getrlimit		 76
#define __SYSCALL_getrusage		 77
#define __SYSCALL_gettimeofday	 78
#define __SYSCALL_settimeofday	 79
#define __SYSCALL_getgroups		 80
#define __SYSCALL_setgroups		 81
#define __SYSCALL_select		 82
#define __SYSCALL_symlink		 83
#define __SYSCALL_oldlstat		 84
#define __SYSCALL_readlink		 85
#define __SYSCALL_uselib		 86
#define __SYSCALL_swapon		 87
#define __SYSCALL_reboot		 88
#define __SYSCALL_readdir		 89
#define __SYSCALL_mmap		 90
#define __SYSCALL_munmap		 91
#define __SYSCALL_truncate		 92
#define __SYSCALL_ftruncate		 93
#define __SYSCALL_fchmod		 94
#define __SYSCALL_fchown		 95
#define __SYSCALL_getpriority	 96
#define __SYSCALL_setpriority	 97
#define __SYSCALL_profil		 98
#define __SYSCALL_statfs		 99
#define __SYSCALL_fstatfs		100
#define __SYSCALL_ioperm		101
#define __SYSCALL_socketcall		102
#define __SYSCALL_syslog		103
#define __SYSCALL_setitimer		104
#define __SYSCALL_getitimer		105
#define __SYSCALL_stat		106
#define __SYSCALL_lstat		107
#define __SYSCALL_fstat		108
#define __SYSCALL_olduname		109
#define __SYSCALL_iopl		110
#define __SYSCALL_vhangup		111
#define __SYSCALL_idle		112
#define __SYSCALL_vm86old		113
#define __SYSCALL_wait4		114
#define __SYSCALL_swapoff		115
#define __SYSCALL_sysinfo		116
#define __SYSCALL_ipc		117
#define __SYSCALL_fsync		118
#define __SYSCALL_sigreturn		119
#define __SYSCALL_clone		120
#define __SYSCALL_setdomainname	121
#define __SYSCALL_uname		122
#define __SYSCALL_modify_ldt		123
#define __SYSCALL_adjtimex		124
#define __SYSCALL_mprotect		125
#define __SYSCALL_sigprocmask	126
#define __SYSCALL_create_module	127
#define __SYSCALL_init_module	128
#define __SYSCALL_delete_module	129
#define __SYSCALL_get_kernel_syms	130
#define __SYSCALL_quotactl		131
#define __SYSCALL_getpgid		132
#define __SYSCALL_fchdir		133
#define __SYSCALL_bdflush		134
#define __SYSCALL_sysfs		135
#define __SYSCALL_personality	136
#define __SYSCALL_afs_syscall	137
#define __SYSCALL_setfsuid		138
#define __SYSCALL_setfsgid		139
#define __SYSCALL__llseek		140
#define __SYSCALL_getdents		141
#define __SYSCALL__newselect		142
#define __SYSCALL_flock		143
#define __SYSCALL_msync		144
#define __SYSCALL_readv		145
#define __SYSCALL_writev		146
#define __SYSCALL_getsid		147
#define __SYSCALL_fdatasync		148
#define __SYSCALL__sysctl		149
#define __SYSCALL_mlock		150
#define __SYSCALL_munlock		151
#define __SYSCALL_mlockall		152
#define __SYSCALL_munlockall		153
#define __SYSCALL_sched_setparam		154
#define __SYSCALL_sched_getparam		155
#define __SYSCALL_sched_setscheduler		156
#define __SYSCALL_sched_getscheduler		157
#define __SYSCALL_sched_yield		158
#define __SYSCALL_sched_get_priority_max	159
#define __SYSCALL_sched_get_priority_min	160
#define __SYSCALL_sched_rr_get_interval	161
#define __SYSCALL_nanosleep		162
#define __SYSCALL_mremap		163
#define __SYSCALL_setresuid		164
#define __SYSCALL_getresuid		165
#define __SYSCALL_vm86		166
#define __SYSCALL_query_module	167
#define __SYSCALL_poll		168
#define __SYSCALL_nfsservctl		169
#define __SYSCALL_setresgid		170
#define __SYSCALL_getresgid		171
#define __SYSCALL_prctl              172
#define __SYSCALL_rt_sigreturn	173
#define __SYSCALL_rt_sigaction	174
#define __SYSCALL_rt_sigprocmask	175
#define __SYSCALL_rt_sigpending	176
#define __SYSCALL_rt_sigtimedwait	177
#define __SYSCALL_rt_sigqueueinfo	178
#define __SYSCALL_rt_sigsuspend	179
#define __SYSCALL_pread		180
#define __SYSCALL_pwrite		181
#define __SYSCALL_chown		182
#define __SYSCALL_getcwd		183
#define __SYSCALL_capget		184
#define __SYSCALL_capset		185
#define __SYSCALL_sigaltstack	186
#define __SYSCALL_sendfile		187
#define __SYSCALL_getpmsg		188
#define __SYSCALL_putpmsg		189
#define __SYSCALL_vfork		190
#define __SYSCALL_ugetrlimit		191
#define __SYSCALL_mmap2		192
#define __SYSCALL_truncate64		193
#define __SYSCALL_ftruncate64	194
#define __SYSCALL_stat64		195
#define __SYSCALL_lstat64		196
#define __SYSCALL_fstat64		197
#define __SYSCALL_lchown32		198
#define __SYSCALL_getuid32		199
#define __SYSCALL_getgid32		200
#define __SYSCALL_geteuid32		201
#define __SYSCALL_getegid32		202
#define __SYSCALL_setreuid32		203
#define __SYSCALL_setregid32		204
#define __SYSCALL_getgroups32	205
#define __SYSCALL_setgroups32	206
#define __SYSCALL_fchown32		207
#define __SYSCALL_setresuid32	208
#define __SYSCALL_getresuid32	209
#define __SYSCALL_setresgid32	210
#define __SYSCALL_getresgid32	211
#define __SYSCALL_chown32		212
#define __SYSCALL_setuid32		213
#define __SYSCALL_setgid32		214
#define __SYSCALL_setfsuid32		215
#define __SYSCALL_setfsgid32		216
#define __SYSCALL_pivot_root		217
#define __SYSCALL_mincore		218
#define __SYSCALL_madvise		219
#define __SYSCALL_getdents64		220
#define __SYSCALL_fcntl64		221

#define swap (1-WORDS_BIGENDIAN)

using namespace emulator;
//void do_syscall(emulator_t *emu, mips_addr_t pc);

//void impl_syscall(emulator_t *emu, mips_inst_t inst)
//{

	//if(emu->emulate_syscall)
//		do_syscall(emu,inst);
//}

//#define SYSCALL_NUM emu->regs.ReadGPR(2);

/* //does not fit syscall definition in MIPS
char *sc_disasm(mips_inst_t inst, mips_addr_t pc, char *buf)
{
	buf += sprintf(buf, "swi %x;\n", SYSCALL_NUM);
	return buf;
}
#endif
*/

#define STRLEN(addr) my_strlen(emu, addr)

#define PARM(i) (i<4)?emu->ReadGPR(4+i):\
		emu->mem->read_word(emu->ReadGPR(29)+16)

// $a3 contains an error flag when returning, 
// see http://www.cs.hmc.edu/courses/2005/spring/cs182-02/sys161/mips.html
#define RETURN(x) emu->WriteGPR((u_word_t)(x), 2), \
				emu->WriteGPR((u_word_t)x==(u_word_t)-EINVAL, 7)

static void mips_swap(void *buf, int count)
{
	if(count > 0)
	{
		char temp[8];
		char *src = (char *) buf + count - 1;
		char *dst = temp;
		
		do
		{
			*dst = *src;
		} while(src--, dst++, --count);
	}
}

static int my_strlen(emulator_t *emu, mips_addr_t addr)
{
	int len = 0;
	char buffer[32];
	
	while(1)
	{
		int size = sizeof(buffer);
		char *p = buffer;
		MEM_READ(buffer, addr, size);
		while(size > 0)
		{
			if(*p == 0) return len;
			len++;
			size--;
			p++;
		}
		addr += sizeof(buffer);
	}
}

bool mips_syscall_exit(emulator_t *emu)
{
	int ret = PARM(0);
	if (emu->is_verbose())
		fprintf(stderr, "exit(%d)\n", ret);

	emu->prog_exit(ret);

	return true;
}

bool mips_syscall_fork(emulator_t *emu) { RETURN(-EINVAL); return false; }

bool mips_syscall_read(emulator_t *emu)
{
	int fd;
	size_t count;
	mips_addr_t buf_addr;
	void *buf;
	ssize_t ret;
	
	fd = PARM(0);
	buf_addr = PARM(1);
	count = (size_t) PARM(2);
	buf = malloc(count);
	if (emu->is_verbose())
		fprintf(stderr, "read(fd=%d, buf=0x%08x, count=%d)\n", fd, buf_addr, (int)count);
		
	if(buf)
	{
		ret = read(fd, buf, count);
		if(ret > 0) MEM_WRITE(buf_addr, buf, ret);
		free(buf);
	}
	else
	{
		ret = -1;
	}
	RETURN(ret);
	return ret != -1;
}

bool mips_syscall_write(emulator_t *emu)
{
	int fd;
	size_t count;
	void *buf;
	mips_addr_t buf_addr;
	ssize_t ret;
	
	fd = PARM(0);
	buf_addr = PARM(1);
	count = (size_t) PARM(2);
	if (emu->is_verbose())
		fprintf(stderr, "write(fd=%d, buf=0x%08x, count=%d)\n", fd, buf_addr, (int)count);
	buf = malloc(count);
	if(buf)
	{
		MEM_READ(buf, buf_addr, count);
		ret = write(fd, buf, count);
		free(buf);
	}
	else
	{
		ret = -1;
	}
	RETURN(ret);
	return ret != -1;
}

bool mips_syscall_open(emulator_t *emu)
{
	mips_addr_t addr;
	int pathnamelen;
	char *pathname;
	int flags, new_flags;
	mode_t mode;
	int ret;
	
	addr = PARM(0);
	pathnamelen = STRLEN(addr);
	pathname = (char *) malloc(pathnamelen + 1);
	MEM_READ(pathname, addr, pathnamelen + 1);
	flags = PARM(1);
	mode = PARM(2);
	if (emu->is_verbose())
		fprintf(stderr, "open(pathname=\"%s\", flags=%d, mode=%d)\n", pathname, flags, (int)mode);

#if 0 // flags for mips-linux is different from i386-linux
#define O_ACCMODE   0x0003
#define O_RDONLY    0x0000
#define O_WRONLY    0x0001
#define O_RDWR      0x0002
#define O_APPEND    0x0008					// 02000 for i386
#define O_SYNC      0x0010					// 010000 for i386
#define O_NONBLOCK  0x0080					// 04000 for i386
#define O_CREAT     0x0100  /* not fcntl */ // 0100 for i386
#define O_TRUNC     0x0200  /* not fcntl */
#define O_EXCL      0x0400  /* not fcntl */	// 0200 for i386
#define O_NOCTTY    0x0800  /* not fcntl */	// 0400 for i386
#define O_FSYNC     O_SYNC
#define O_ASYNC     0x1000

#ifdef __USE_LARGEFILE64
# define O_LARGEFILE    0x2000  /* Allow large file opens.*/ // 0100000 for i386
#endif

#ifdef __USE_GNU
# define O_NOFOLLOW 0x20000 /* Do not follow links.  */ 
# define O_DIRECT   0x8000  /* Direct disk access hint.  */ //040000 for i386
# define O_DIRECTORY    0x10000 /* Must be a directory.  */
#endif

#define O_NDELAY    O_NONBLOCK
#endif

	// need to tranalate flags
	new_flags = flags & 0x31203;	// common bits
	if (flags & 0x8)  new_flags |= 02000;
	if (flags & 0x10) new_flags |= 010000;
	if (flags & 0x80) new_flags |= 04000;
	if (flags & 0x100) new_flags |= 0100;
	if (flags & 0x400) new_flags |= 0200;
	if (flags & 0x800) new_flags |= 0400;
	if (flags & 0x2000) new_flags |= 0100000;
	if (flags & 0x8000) new_flags |= 040000;

	ret = open(pathname, new_flags, mode);
	free(pathname);
	RETURN(ret);
	return ret != -1;
}
bool mips_syscall_close(emulator_t *emu)
{
	int fd;
	int ret;
	
	fd = PARM(0);
	if (emu->is_verbose())
		fprintf(stderr, "close(fd=%d)\n", fd);
	ret = close(fd);
	RETURN(ret);
	return ret != -1;
}

bool mips_syscall_waitpid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_creat(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_link(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_unlink(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_execve(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_chdir(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_time(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mknod(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_chmod(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_lchown(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_break(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_oldstat(emulator_t *emu) { RETURN(-EINVAL); return false; }

bool mips_syscall_lseek(emulator_t *emu)
{
	int fildes;
	off_t offset;
	int whence;
	off_t ret;
	
	fildes = PARM(0);
	offset = PARM(1);
	whence = PARM(2);
	if (emu->is_verbose())
		fprintf(stderr, "lseek(fd=%d, offset=%lu, whence=%d)\n", fildes, offset, whence);
	ret = lseek(fildes, offset, whence);
	RETURN(ret);
	return ret != -1;
}

bool mips_syscall_getpid(emulator_t *emu)
{
	pid_t pid;
	
	if (emu->is_verbose())
		fprintf(stderr, "getpid()\n");
	pid = getpid();
	RETURN(pid);
	return true;
}

bool mips_syscall_mount(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_umount(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setuid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getuid(emulator_t *emu)
{
	uid_t uid;
	
	if (emu->is_verbose())
		fprintf(stderr, "getuid()\n");
	uid = getuid();
	RETURN(uid);
	return true;
}

bool mips_syscall_stime(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ptrace(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_alarm(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_oldfstat(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_pause(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_utime(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_stty(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_gtty(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_access(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_nice(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ftime(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sync(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_kill(emulator_t *emu) { RETURN(0); return false; }
bool mips_syscall_rename(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mkdir(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rmdir(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_dup(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_pipe(emulator_t *emu) { RETURN(-EINVAL); return false; }

static void mips_swap_tms(struct tms *buf)
{
	mips_swap(&buf->tms_utime, sizeof(&buf->tms_utime));
	mips_swap(&buf->tms_stime, sizeof(&buf->tms_stime));
	mips_swap(&buf->tms_cutime, sizeof(&buf->tms_cutime));
	mips_swap(&buf->tms_cstime, sizeof(&buf->tms_cstime));
}

bool mips_syscall_times(emulator_t *emu)
{
	mips_addr_t buf_addr;
	struct tms buf;
	clock_t ret;
	
	ret = times(&buf);	
	if(swap) mips_swap_tms(&buf);
	buf_addr = PARM(0);
	MEM_WRITE(buf_addr, &buf, sizeof(struct tms));
	RETURN(ret);
	return ret != (clock_t) -1;
}

bool mips_syscall_prof(emulator_t *emu) { RETURN(-EINVAL); return false; }

bool mips_syscall_brk(emulator_t *emu)
{
	mips_addr_t new_brk_point;
	bool success;
	
	new_brk_point = PARM(0);
	success = true;/*false*/;
	if (emu->is_verbose())
		fprintf(stderr, "brk(end=0x%08x)\n", new_brk_point);
	if(new_brk_point > emu->get_brk())
	{
		emu->set_brk(new_brk_point);
		success = true;
	}
	
	RETURN(emu->get_brk());
	return success;
}

bool mips_syscall_setgid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getgid(emulator_t *emu)
{
	gid_t gid;
	if (emu->is_verbose())
		fprintf(stderr, "getgid()\n");
	gid = getgid();
	RETURN(gid);
	return true;
}

bool mips_syscall_signal(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_geteuid(emulator_t *emu)
{
	uid_t uid;
	
	if (emu->is_verbose())
		fprintf(stderr, "geteuid()\n");
	uid = geteuid();
	RETURN(uid);
	return true;
}

bool mips_syscall_getegid(emulator_t *emu)
{
	gid_t gid;
	
	if (emu->is_verbose())
		fprintf(stderr, "getegid()\n");
	gid = getegid();
	RETURN(gid);
	return true;
}

bool mips_syscall_acct(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_umount2(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_lock(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ioctl(emulator_t *emu) { 	RETURN(-EINVAL); return false; }
bool mips_syscall_fcntl(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mpx(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setpgid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ulimit(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_oldolduname(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_umask(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_chroot(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ustat(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_dup2(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getppid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getpgrp(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setsid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sigaction(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sgetmask(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ssetmask(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setreuid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setregid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sigsuspend(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sigpending(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sethostname(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setrlimit(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getrlimit(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getrusage(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_gettimeofday(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_settimeofday(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getgroups(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setgroups(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_select(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_symlink(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_oldlstat(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_readlink(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_uselib(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_swapon(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_reboot(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_readdir(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_munmap(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_truncate(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ftruncate(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fchmod(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fchown(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getpriority(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setpriority(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_profil(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_statfs(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fstatfs(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ioperm(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_socketcall(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_syslog(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setitimer(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getitimer(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_stat(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_lstat(emulator_t *emu) { RETURN(-EINVAL); return false; }

bool mips_syscall_mmap(emulator_t *emu)
{
    if (PARM(3) != 0x802 /* MAP_PRIVATE|MAP_ANONYMOUS */) {
	  RETURN(-EINVAL);
	  return false;
    }
	/* check if overflow */
	if (emu->get_mmap_brk() + PARM(1) > emu->get_mmap_brk()) {
 	  RETURN(emu->get_mmap_brk());
      emu->set_mmap_brk(emu->get_mmap_brk() + PARM(1));
      return true;
	}
	else {
	  RETURN(-EINVAL);
	  return false;
	}
}


static void mips_swap_stat(struct stat *buf)
{
	mips_swap(&buf->st_dev, sizeof(&buf->st_dev));
	mips_swap(&buf->st_ino, sizeof(&buf->st_ino));
	mips_swap(&buf->st_mode, sizeof(&buf->st_mode));
	mips_swap(&buf->st_nlink, sizeof(&buf->st_nlink));
	mips_swap(&buf->st_uid, sizeof(&buf->st_uid));
	mips_swap(&buf->st_gid, sizeof(&buf->st_gid));
	mips_swap(&buf->st_rdev, sizeof(&buf->st_rdev));
	mips_swap(&buf->st_size, sizeof(&buf->st_size));
	mips_swap(&buf->st_blksize, sizeof(&buf->st_blksize));
	mips_swap(&buf->st_blocks, sizeof(&buf->st_blocks));
	mips_swap(&buf->st_atime, sizeof(&buf->st_atime));
	mips_swap(&buf->st_mtime, sizeof(&buf->st_mtime));
	mips_swap(&buf->st_ctime, sizeof(&buf->st_ctime));
	/*mips_swap(&buf->st_ino, sizeof(&buf->st_ino));*/
}

bool mips_syscall_fstat(emulator_t *emu)
{
	int fd;
	struct stat *buf;
	mips_addr_t buf_addr;
	int ret;
	
	fd = PARM(0);
	buf_addr = PARM(1);
	if (emu->is_verbose())
		fprintf(stderr, "fstat(fd=%d, buf=0x%08x)\n", fd, buf_addr);
	buf = (struct stat *) malloc(sizeof(struct stat));
	if(buf)
	{
		ret = fstat(fd, buf);
		if(ret >= 0)
		{
			if(swap) mips_swap_stat(buf);
			MEM_WRITE(buf_addr, buf, sizeof(struct stat));
		}
		free(buf);
	}
	else
	{
		ret = -1;
	}
	RETURN(ret);
	return ret != -1;
}

bool mips_syscall_olduname(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_iopl(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_vhangup(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_idle(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_vm86old(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_wait4(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_swapoff(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sysinfo(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ipc(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fsync(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sigreturn(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_clone(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setdomainname(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_uname(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_modify_ldt(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_adjtimex(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mprotect(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sigprocmask(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_create_module(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_init_module(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_delete_module(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_get_kernel_syms(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_quotactl(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getpgid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fchdir(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_bdflush(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sysfs(emulator_t *emu) { RETURN(-EINVAL); return false; }

bool mips_syscall_personality(emulator_t *emu) { return true; }

bool mips_syscall_afs_syscall(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setfsuid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setfsgid(emulator_t *emu) { RETURN(-EINVAL); return false; }

bool mips_syscall__llseek(emulator_t *emu)
{
	int fd;
	uint32_t offset_high;
	uint32_t offset_low;
	mips_addr_t result_addr;
	int whence;
	int ret;
	
	fd = PARM(0);
	offset_high = PARM(1);
	offset_low = PARM(2);
	result_addr = PARM(3);
	whence = PARM(4);
	if (emu->is_verbose())
		fprintf(stderr, "_lseek(fd=%d, offset_high=%u, offset_low=%u, result=0x%08x, whence=%d)\n", fd, offset_high, offset_low, result_addr, whence);
	if(offset_high == 0)
	{
		off_t lseek_ret = lseek(fd, offset_low, whence);
		if(lseek_ret >= 0)
		{
#define emm emu
			WRITE_DWORD(lseek_ret, result_addr);
#undef emm
			ret = 0;
		}
		else
		{
			ret = -1;
		}
	}
	else
	{
		ret = -1;
	}
	RETURN(ret);
	return ret != -1;
}

bool mips_syscall_getdents(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_newselect(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_flock(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_msync(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_readv(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_writev(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getsid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fdatasync(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sysctl(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mlock(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_munlock(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mlockall(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_munlockall(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_setparam(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_getparam(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_setscheduler(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getsheduler(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_yield(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_get_priority_max(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_get_priority_min(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sched_rr_get_interval(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_nanosleep(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mremap(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setresuid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getresuid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_vm86(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_query_module(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_poll(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_nfsservctl(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setresgid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getresgid(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_prctl(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigreturn(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigaction(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigprocmask(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigpending(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigtimedwait(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigqueueinfo(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_rt_sigsuspend(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_pread(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_pwrite(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_chown(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getcwd(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_capget(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_capset(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sigaltstack(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_sendfile(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getpmsg(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_putpmsg(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_vfork(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ugetrlimit(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mmap2(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_truncate64(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_ftruncate64(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_stat64(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_lstat64(emulator_t *emu) { RETURN(-EINVAL); return false; }

#ifdef linux
static void mips_swap_stat64(struct stat64 *buf)
{
	mips_swap(&buf->st_dev, sizeof(&buf->st_dev));
	/*mips_swap(&buf->__pad1, sizeof(&buf->__pad1));*/
	mips_swap(&buf->st_ino, sizeof(&buf->st_ino));
	mips_swap(&buf->st_mode, sizeof(&buf->st_mode));
	mips_swap(&buf->st_nlink, sizeof(&buf->st_nlink));
	mips_swap(&buf->st_uid, sizeof(&buf->st_uid));
	mips_swap(&buf->st_gid, sizeof(&buf->st_gid));
	mips_swap(&buf->st_rdev, sizeof(&buf->st_rdev));
	/*mips_swap(&buf->__pad2, sizeof(&buf->__pad2));*/
	mips_swap(&buf->st_size, sizeof(&buf->st_size));
	mips_swap(&buf->st_blksize, sizeof(&buf->st_blksize));
	mips_swap(&buf->st_blocks, sizeof(&buf->st_blocks));
	mips_swap(&buf->st_atime, sizeof(&buf->st_atime));
	/*mips_swap(&buf->__unused1, sizeof(&buf->__unused1));*/
	mips_swap(&buf->st_mtime, sizeof(&buf->st_mtime));
	/*mips_swap(&buf->__unused2, sizeof(&buf->__unused2));*/
	mips_swap(&buf->st_ctime, sizeof(&buf->st_ctime));
	/*mips_swap(&buf->__unused3, sizeof(&buf->__unused3));*/
	/*mips_swap(&buf->st_ino, sizeof(&buf->st_ino));*/
}
#endif

bool mips_syscall_fstat64(emulator_t *emu)
{
#ifdef linux
	int fd;
	mips_addr_t buf_addr;
	struct stat64 *buf;
	int ret;
	
	fd = PARM(0);
	buf_addr = PARM(1);
	if (emu->is_verbose())
		fprintf(stderr, "fstat64(fd=%d, buf=0x%08x)\n", fd, buf_addr);
	buf = (struct stat64 *) malloc(sizeof(struct stat64));
	if(buf)
	{
		ret = fstat64(fd, buf);
		if(ret >= 0)
		{
			if(swap) mips_swap_stat64(buf);
			MEM_WRITE(buf_addr, buf, sizeof(struct stat64));
		}
		free(buf);
	}
	else
	{
		ret = -1;
	}
	RETURN(ret);
	return ret != -1;
#else
	int ret = -1;
	RETURN(ret);
	return false;
#endif
}

bool mips_syscall_lchown32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getgid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_geteuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getegid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setreuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setregid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getgroups32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setgroups32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fchown32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setresuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getresuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setresgid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getresgid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_chown32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setgid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setfsuid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_setfsgid32(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_pivot_root(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_mincore(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_madvise(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_getdents64(emulator_t *emu) { RETURN(-EINVAL); return false; }
bool mips_syscall_fnctl64(emulator_t *emu) { RETURN(-EINVAL); return false; }

static char *get_syscall_name(int num)
{
	switch(num)
	{
		case __SYSCALL_exit: return "exit";
		case __SYSCALL_fork: return "fork";
		case __SYSCALL_read: return "read";
		case __SYSCALL_write: return "write";
		case __SYSCALL_open: return "open";
		case __SYSCALL_close: return "close";
		case __SYSCALL_waitpid: return "waitpid";
		case __SYSCALL_creat: return "creat";
		case __SYSCALL_link: return "link";
		case __SYSCALL_unlink: return "unlink";
		case __SYSCALL_execve: return "execve";
		case __SYSCALL_chdir: return "chdir";
		case __SYSCALL_time: return "time";
		case __SYSCALL_mknod: return "mknod";
		case __SYSCALL_chmod: return "chmod";
		case __SYSCALL_lchown: return "lchown";
		case __SYSCALL_break: return "break";
		case __SYSCALL_oldstat: return "oldstat";
		case __SYSCALL_lseek: return "lseek";
		case __SYSCALL_getpid: return "getpid";
		case __SYSCALL_mount: return "mount";
		case __SYSCALL_umount: return "umount";
		case __SYSCALL_setuid: return "setuid";
		case __SYSCALL_getuid: return "getuid";
		case __SYSCALL_stime: return "stime";
		case __SYSCALL_ptrace: return "ptrace";
		case __SYSCALL_alarm: return "alarm";
		case __SYSCALL_oldfstat: return "oldfstat";
		case __SYSCALL_pause: return "pause";
		case __SYSCALL_utime: return "utime";
		case __SYSCALL_stty: return "stty";
		case __SYSCALL_gtty: return "gtty";
		case __SYSCALL_access: return "access";
		case __SYSCALL_nice: return "nice";
		case __SYSCALL_ftime: return "ftime";
		case __SYSCALL_sync: return "sync";
		case __SYSCALL_kill: return "kill";
		case __SYSCALL_rename: return "rename";
		case __SYSCALL_mkdir: return "mkdir";
		case __SYSCALL_rmdir: return "rmdir";
		case __SYSCALL_dup: return "dup";
		case __SYSCALL_pipe: return "pipe";
		case __SYSCALL_times: return "times";
		case __SYSCALL_prof: return "prof";
		case __SYSCALL_brk: return "brk";
		case __SYSCALL_setgid: return "setgid";
		case __SYSCALL_getgid: return "getgid";
		case __SYSCALL_signal: return "signal";
		case __SYSCALL_geteuid: return "geteuid";
		case __SYSCALL_getegid: return "getegid";
		case __SYSCALL_acct: return "acct";
		case __SYSCALL_umount2: return "umount2";
		case __SYSCALL_lock: return "lock";
		case __SYSCALL_ioctl: return "ioctl";
		case __SYSCALL_fcntl: return "fcntl";
		case __SYSCALL_mpx: return "mpx";
		case __SYSCALL_setpgid: return "setpgid";
		case __SYSCALL_ulimit: return "ulimit";
		case __SYSCALL_oldolduname: return "oldolduname";
		case __SYSCALL_umask: return "umask";
		case __SYSCALL_chroot: return "chroot";
		case __SYSCALL_ustat	: return "ustat";
		case __SYSCALL_dup2: return "dup2";
		case __SYSCALL_getppid: return "getppid";
		case __SYSCALL_getpgrp: return "getpgrp";
		case __SYSCALL_setsid: return "setsid";
		case __SYSCALL_sigaction: return "sigaction";
		case __SYSCALL_sgetmask: return "sgetmask";
		case __SYSCALL_ssetmask: return "ssetmask";
		case __SYSCALL_setreuid: return "setreuid";
		case __SYSCALL_setregid: return "setregid";
		case __SYSCALL_sigsuspend: return "sigsuspend";
		case __SYSCALL_sigpending: return "sigpending";
		case __SYSCALL_sethostname: return "sethostname";
		case __SYSCALL_setrlimit: return "setrlimit";
		case __SYSCALL_getrlimit: return "getrlimit";
		case __SYSCALL_getrusage: return "getrusage";
		case __SYSCALL_gettimeofday: return "gettimeofday";
		case __SYSCALL_settimeofday: return "settimeofday";
		case __SYSCALL_getgroups: return "getgroups";
		case __SYSCALL_setgroups: return "setgroups";
		case __SYSCALL_select: return "select";
		case __SYSCALL_symlink: return "symlink";
		case __SYSCALL_oldlstat: return "oldlstat";
		case __SYSCALL_readlink: return "readlink";
		case __SYSCALL_uselib: return "uselib";
		case __SYSCALL_swapon: return "swapon";
		case __SYSCALL_reboot: return "reboot";
		case __SYSCALL_readdir: return "readdir";
		case __SYSCALL_mmap: return "mmap";
		case __SYSCALL_munmap: return "munmap";
		case __SYSCALL_truncate: return "truncate";
		case __SYSCALL_ftruncate: return "ftruncate";
		case __SYSCALL_fchmod: return "fchmod";
		case __SYSCALL_fchown: return "fchown";
		case __SYSCALL_getpriority: return "getpriority";
		case __SYSCALL_setpriority: return "setpriority";
		case __SYSCALL_profil: return "profil";
		case __SYSCALL_statfs: return "statfs";
		case __SYSCALL_fstatfs: return "fstatfs";
		case __SYSCALL_ioperm: return "ioperm";
		case __SYSCALL_socketcall: return "socketcall";
		case __SYSCALL_syslog: return "syslog";
		case __SYSCALL_setitimer: return "setitimer";
		case __SYSCALL_getitimer: return "getitimer";
		case __SYSCALL_stat: return "stat";
		case __SYSCALL_lstat: return "lstat";
		case __SYSCALL_fstat: return "fstat";
		case __SYSCALL_olduname: return "olduname";
		case __SYSCALL_iopl: return "iopl";
		case __SYSCALL_vhangup: return "vhangup";
		case __SYSCALL_idle: return "idle";
		case __SYSCALL_vm86old: return "vm86old";
		case __SYSCALL_wait4: return "wait4";
		case __SYSCALL_swapoff: return "swapoff";
		case __SYSCALL_sysinfo: return "sysinfo";
		case __SYSCALL_ipc: return "ipc";
		case __SYSCALL_fsync: return "fsync";
		case __SYSCALL_sigreturn: return "sigreturn";
		case __SYSCALL_clone: return "clone";
		case __SYSCALL_setdomainname: return "setdomainname";
		case __SYSCALL_uname: return "uname";
		case __SYSCALL_modify_ldt: return "modify_ldt";
		case __SYSCALL_adjtimex: return "adjtimex";
		case __SYSCALL_mprotect: return "mprotect";
		case __SYSCALL_sigprocmask: return "sigprocmask";
		case __SYSCALL_create_module: return "create_module";
		case __SYSCALL_init_module: return "init_module";
		case __SYSCALL_delete_module: return "delete_module";
		case __SYSCALL_get_kernel_syms: return "get_kernel_syms";
		case __SYSCALL_quotactl: return "quotactl";
		case __SYSCALL_getpgid: return "getpgid";
		case __SYSCALL_fchdir: return "fchdir";
		case __SYSCALL_bdflush: return "bdflush";
		case __SYSCALL_sysfs: return "sysfs";
		case __SYSCALL_personality: return "personality";
		case __SYSCALL_afs_syscall: return "afs_syscall";
		case __SYSCALL_setfsuid: return "setfsuid";
		case __SYSCALL_setfsgid: return "setfsgid";
		case __SYSCALL__llseek: return "_llseek";
		case __SYSCALL_getdents: return "getdents";
		case __SYSCALL__newselect: return "newselect";
		case __SYSCALL_flock: return "flock";
		case __SYSCALL_msync: return "msync";
		case __SYSCALL_readv: return "readv";
		case __SYSCALL_writev: return "writev";
		case __SYSCALL_getsid: return "getsid";
		case __SYSCALL_fdatasync: return "fdatasync";
		case __SYSCALL__sysctl: return "sysctl";
		case __SYSCALL_mlock: return "mlock";
		case __SYSCALL_munlock: return "munlock";
		case __SYSCALL_mlockall: return "mlockall";
		case __SYSCALL_munlockall: return "munlockall";
		case __SYSCALL_sched_setparam: return "sched_setparam";
		case __SYSCALL_sched_getparam: return "sched_getparam";
		case __SYSCALL_sched_setscheduler: return "sched_setscheduler";
		case __SYSCALL_sched_getscheduler: return "getsheduler";
		case __SYSCALL_sched_yield: return "sched_yield";
		case __SYSCALL_sched_get_priority_max: return "sched_get_priority_max";
		case __SYSCALL_sched_get_priority_min: return "sched_get_priority_min";
		case __SYSCALL_sched_rr_get_interval: return "sched_rr_get_interval";
		case __SYSCALL_nanosleep: return "nanosleep";
		case __SYSCALL_mremap: return "mremap";
		case __SYSCALL_setresuid	: return "setresuid";
		case __SYSCALL_getresuid: return "getresuid";
		case __SYSCALL_vm86: return "vm86";
		case __SYSCALL_query_module: return "query_module";
		case __SYSCALL_poll: return "poll";
		case __SYSCALL_nfsservctl: return "nfsservctl";
		case __SYSCALL_setresgid	: return "setresgid";
		case __SYSCALL_getresgid: return "getresgid";
		case __SYSCALL_prctl: return "prctl";
		case __SYSCALL_rt_sigreturn: return "rt_sigreturn";
		case __SYSCALL_rt_sigaction: return "rt_sigaction";
		case __SYSCALL_rt_sigprocmask: return "rt_sigprocmask";
		case __SYSCALL_rt_sigpending: return "rt_sigpending";
		case __SYSCALL_rt_sigtimedwait: return "rt_sigtimedwait";
		case __SYSCALL_rt_sigqueueinfo: return "rt_sigqueueinfo";
		case __SYSCALL_rt_sigsuspend: return "rt_sigsuspend";
		case __SYSCALL_pread: return "pread";
		case __SYSCALL_pwrite: return "pwrite";
		case __SYSCALL_chown: return "chown";
		case __SYSCALL_getcwd: return "getcwd";
		case __SYSCALL_capget: return "capget";
		case __SYSCALL_capset: return "capset";
		case __SYSCALL_sigaltstack: return "sigaltstack";
		case __SYSCALL_sendfile: return "sendfile";
		case __SYSCALL_getpmsg: return "getpmsg";
		case __SYSCALL_putpmsg: return "putpmsg";
		case __SYSCALL_vfork: return "vfork";
		case __SYSCALL_ugetrlimit: return "ugetrlimit";
		case __SYSCALL_mmap2: return "mmap2";
		case __SYSCALL_truncate64: return "truncate64";
		case __SYSCALL_ftruncate64: return "ftruncate64";
		case __SYSCALL_stat64: return "stat64";
		case __SYSCALL_lstat64: return "lstat64";
		case __SYSCALL_fstat64: return "fstat64";
		case __SYSCALL_lchown32: return "lchown32";
		case __SYSCALL_getuid32: return "getuid32";
		case __SYSCALL_getgid32: return "getgid32";
		case __SYSCALL_geteuid32: return "geteuid32";
		case __SYSCALL_getegid32: return "getegid32";
		case __SYSCALL_setreuid32: return "setreuid32";
		case __SYSCALL_setregid32: return "setregid32";
		case __SYSCALL_getgroups32: return "getgroups32";
		case __SYSCALL_setgroups32: return "setgroups32";
		case __SYSCALL_fchown32: return "fchown32";
		case __SYSCALL_setresuid32: return "setresuid32";
		case __SYSCALL_getresuid32: return "getresuid32";
		case __SYSCALL_setresgid32: return "setresgid32";
		case __SYSCALL_getresgid32: return "getresgid32";
		case __SYSCALL_chown32: return "chown32";
		case __SYSCALL_setuid32: return "setuid32";
		case __SYSCALL_setgid32: return "setgid32";
		case __SYSCALL_setfsuid32: return "setfsuid32";
		case __SYSCALL_setfsgid32: return "setfsgid32";
		case __SYSCALL_pivot_root: return "pivot_root";
		case __SYSCALL_mincore: return "mincore";
		case __SYSCALL_madvise: return "madvise";
		case __SYSCALL_getdents64: return "getdents64";
		case __SYSCALL_fcntl64: return "fnctl64";
	}
	return "?";
}

void do_syscall(emulator_t *emu, mips_address_t pc)
{
	int syscall_num = (emu->ReadGPR(2))-4000;  //read syscall code from v0($2) - 4000
	bool ret = false;
	
	if (emu->is_verbose())
		fprintf(stderr, "got a system call (number : %u, name : %s)\n", syscall_num, get_syscall_name(syscall_num));
		
	fflush(stderr);
	switch(syscall_num)
	{
		case __SYSCALL_exit: ret = mips_syscall_exit(emu); break;
		case __SYSCALL_fork: ret = mips_syscall_fork(emu); break;
		case __SYSCALL_read: ret = mips_syscall_read(emu); break;
		case __SYSCALL_write: ret = mips_syscall_write(emu); break;
		case __SYSCALL_open: ret = mips_syscall_open(emu); break;
		case __SYSCALL_close: ret = mips_syscall_close(emu); break;
		case __SYSCALL_waitpid: ret = mips_syscall_waitpid(emu); break;
		case __SYSCALL_creat: ret = mips_syscall_creat(emu); break;
		case __SYSCALL_link: ret = mips_syscall_link(emu); break;
		case __SYSCALL_unlink: ret = mips_syscall_unlink(emu); break;
		case __SYSCALL_execve: ret = mips_syscall_execve(emu); break;
		case __SYSCALL_chdir: ret = mips_syscall_chdir(emu); break;
		case __SYSCALL_time: ret = mips_syscall_time(emu); break;
		case __SYSCALL_mknod: ret = mips_syscall_mknod(emu); break;
		case __SYSCALL_chmod: ret = mips_syscall_chmod(emu); break;
		case __SYSCALL_lchown: ret = mips_syscall_lchown(emu); break;
		case __SYSCALL_break: ret = mips_syscall_break(emu); break;
		case __SYSCALL_oldstat: ret = mips_syscall_oldstat(emu); break;
		case __SYSCALL_lseek: ret = mips_syscall_lseek(emu); break;
		case __SYSCALL_getpid: ret = mips_syscall_getpid(emu); break;
		case __SYSCALL_mount: ret = mips_syscall_mount(emu); break;
		case __SYSCALL_umount: ret = mips_syscall_umount(emu); break;
		case __SYSCALL_setuid: ret = mips_syscall_setuid(emu); break;
		case __SYSCALL_getuid: ret = mips_syscall_getuid(emu); break;
		case __SYSCALL_stime: ret = mips_syscall_stime(emu); break;
		case __SYSCALL_ptrace: ret = mips_syscall_ptrace(emu); break;
		case __SYSCALL_alarm: ret = mips_syscall_alarm(emu); break;
		case __SYSCALL_oldfstat: ret = mips_syscall_oldfstat(emu); break;
		case __SYSCALL_pause: ret = mips_syscall_pause(emu); break;
		case __SYSCALL_utime: ret = mips_syscall_utime(emu); break;
		case __SYSCALL_stty: ret = mips_syscall_stty(emu); break;
		case __SYSCALL_gtty: ret = mips_syscall_gtty(emu); break;
		case __SYSCALL_access: ret = mips_syscall_access(emu); break;
		case __SYSCALL_nice: ret = mips_syscall_nice(emu); break;
		case __SYSCALL_ftime: ret = mips_syscall_ftime(emu); break;
		case __SYSCALL_sync: ret = mips_syscall_sync(emu); break;
		case __SYSCALL_kill: ret = mips_syscall_kill(emu); break;
		case __SYSCALL_rename: ret = mips_syscall_rename(emu); break;
		case __SYSCALL_mkdir: ret = mips_syscall_mkdir(emu); break;
		case __SYSCALL_rmdir: ret = mips_syscall_rmdir(emu); break;
		case __SYSCALL_dup: ret = mips_syscall_dup(emu); break;
		case __SYSCALL_pipe: ret = mips_syscall_pipe(emu); break;
		case __SYSCALL_times: ret = mips_syscall_times(emu); break;
		case __SYSCALL_prof: ret = mips_syscall_prof(emu); break;
		case __SYSCALL_brk: ret = mips_syscall_brk(emu); break;
		case __SYSCALL_setgid: ret = mips_syscall_setgid(emu); break;
		case __SYSCALL_getgid: ret = mips_syscall_getgid(emu); break;
		case __SYSCALL_signal: ret = mips_syscall_signal(emu); break;
		case __SYSCALL_geteuid: ret = mips_syscall_geteuid(emu); break;
		case __SYSCALL_getegid: ret = mips_syscall_getegid(emu); break;
		case __SYSCALL_acct: ret = mips_syscall_acct(emu); break;
		case __SYSCALL_umount2: ret = mips_syscall_umount2(emu); break;
		case __SYSCALL_lock: ret = mips_syscall_lock(emu); break;
		case __SYSCALL_ioctl: ret = mips_syscall_ioctl(emu); break;
		case __SYSCALL_fcntl: ret = mips_syscall_fcntl(emu); break;
		case __SYSCALL_mpx: ret = mips_syscall_mpx(emu); break;
		case __SYSCALL_setpgid: ret = mips_syscall_setpgid(emu); break;
		case __SYSCALL_ulimit: ret = mips_syscall_ulimit(emu); break;
		case __SYSCALL_oldolduname: ret = mips_syscall_oldolduname(emu); break;
		case __SYSCALL_umask: ret = mips_syscall_umask(emu); break;
		case __SYSCALL_chroot: ret = mips_syscall_chroot(emu); break;
		case __SYSCALL_ustat	: ret = mips_syscall_ustat(emu); break;
		case __SYSCALL_dup2: ret = mips_syscall_dup2(emu); break;
		case __SYSCALL_getppid: ret = mips_syscall_getppid(emu); break;
		case __SYSCALL_getpgrp: ret = mips_syscall_getpgrp(emu); break;
		case __SYSCALL_setsid: ret = mips_syscall_setsid(emu); break;
		case __SYSCALL_sigaction: ret = mips_syscall_sigaction(emu); break;
		case __SYSCALL_sgetmask: ret = mips_syscall_sgetmask(emu); break;
		case __SYSCALL_ssetmask: ret = mips_syscall_ssetmask(emu); break;
		case __SYSCALL_setreuid: ret = mips_syscall_setreuid(emu); break;
		case __SYSCALL_setregid: ret = mips_syscall_setregid(emu); break;
		case __SYSCALL_sigsuspend: ret = mips_syscall_sigsuspend(emu); break;
		case __SYSCALL_sigpending: ret = mips_syscall_sigpending(emu); break;
		case __SYSCALL_sethostname: ret = mips_syscall_sethostname(emu); break;
		case __SYSCALL_setrlimit: ret = mips_syscall_setrlimit(emu); break;
		case __SYSCALL_getrlimit: ret = mips_syscall_getrlimit(emu); break;
		case __SYSCALL_getrusage: ret = mips_syscall_getrusage(emu); break;
		case __SYSCALL_gettimeofday: ret = mips_syscall_gettimeofday(emu); break;
		case __SYSCALL_settimeofday: ret = mips_syscall_settimeofday(emu); break;
		case __SYSCALL_getgroups: ret = mips_syscall_getgroups(emu); break;
		case __SYSCALL_setgroups: ret = mips_syscall_setgroups(emu); break;
		case __SYSCALL_select: ret = mips_syscall_select(emu); break;
		case __SYSCALL_symlink: ret = mips_syscall_symlink(emu); break;
		case __SYSCALL_oldlstat: ret = mips_syscall_oldlstat(emu); break;
		case __SYSCALL_readlink: ret = mips_syscall_readlink(emu); break;
		case __SYSCALL_uselib: ret = mips_syscall_uselib(emu); break;
		case __SYSCALL_swapon: ret = mips_syscall_swapon(emu); break;
		case __SYSCALL_reboot: ret = mips_syscall_reboot(emu); break;
		case __SYSCALL_readdir: ret = mips_syscall_readdir(emu); break;
		case __SYSCALL_mmap: ret = mips_syscall_mmap(emu); break;
		case __SYSCALL_munmap: ret = mips_syscall_munmap(emu); break;
		case __SYSCALL_truncate: ret = mips_syscall_truncate(emu); break;
		case __SYSCALL_ftruncate: ret = mips_syscall_ftruncate(emu); break;
		case __SYSCALL_fchmod: ret = mips_syscall_fchmod(emu); break;
		case __SYSCALL_fchown: ret = mips_syscall_fchown(emu); break;
		case __SYSCALL_getpriority: ret = mips_syscall_getpriority(emu); break;
		case __SYSCALL_setpriority: ret = mips_syscall_setpriority(emu); break;
		case __SYSCALL_profil: ret = mips_syscall_profil(emu); break;
		case __SYSCALL_statfs: ret = mips_syscall_statfs(emu); break;
		case __SYSCALL_fstatfs: ret = mips_syscall_fstatfs(emu); break;
		case __SYSCALL_ioperm: ret = mips_syscall_ioperm(emu); break;
		case __SYSCALL_socketcall: ret = mips_syscall_socketcall(emu); break;
		case __SYSCALL_syslog: ret = mips_syscall_syslog(emu); break;
		case __SYSCALL_setitimer: ret = mips_syscall_setitimer(emu); break;
		case __SYSCALL_getitimer: ret = mips_syscall_getitimer(emu); break;
		case __SYSCALL_stat: ret = mips_syscall_stat(emu); break;
		case __SYSCALL_lstat: ret = mips_syscall_lstat(emu); break;
		case __SYSCALL_fstat: ret = mips_syscall_fstat(emu); break;
		case __SYSCALL_olduname: ret = mips_syscall_olduname(emu); break;
		case __SYSCALL_iopl: ret = mips_syscall_iopl(emu); break;
		case __SYSCALL_vhangup: ret = mips_syscall_vhangup(emu); break;
		case __SYSCALL_idle: ret = mips_syscall_idle(emu); break;
		case __SYSCALL_vm86old: ret = mips_syscall_vm86old(emu); break;
		case __SYSCALL_wait4: ret = mips_syscall_wait4(emu); break;
		case __SYSCALL_swapoff: ret = mips_syscall_swapoff(emu); break;
		case __SYSCALL_sysinfo: ret = mips_syscall_sysinfo(emu); break;
		case __SYSCALL_ipc: ret = mips_syscall_ipc(emu); break;
		case __SYSCALL_fsync: ret = mips_syscall_fsync(emu); break;
		case __SYSCALL_sigreturn: ret = mips_syscall_sigreturn(emu); break;
		case __SYSCALL_clone: ret = mips_syscall_clone(emu); break;
		case __SYSCALL_setdomainname: ret = mips_syscall_setdomainname(emu); break;
		case __SYSCALL_uname: ret = mips_syscall_uname(emu); break;
		case __SYSCALL_modify_ldt: ret = mips_syscall_modify_ldt(emu); break;
		case __SYSCALL_adjtimex: ret = mips_syscall_adjtimex(emu); break;
		case __SYSCALL_mprotect: ret = mips_syscall_mprotect(emu); break;
		case __SYSCALL_sigprocmask: ret = mips_syscall_sigprocmask(emu); break;
		case __SYSCALL_create_module: ret = mips_syscall_create_module(emu); break;
		case __SYSCALL_init_module: ret = mips_syscall_init_module(emu); break;
		case __SYSCALL_delete_module: ret = mips_syscall_delete_module(emu); break;
		case __SYSCALL_get_kernel_syms: ret = mips_syscall_get_kernel_syms(emu); break;
		case __SYSCALL_quotactl: ret = mips_syscall_quotactl(emu); break;
		case __SYSCALL_getpgid: ret = mips_syscall_getpgid(emu); break;
		case __SYSCALL_fchdir: ret = mips_syscall_fchdir(emu); break;
		case __SYSCALL_bdflush: ret = mips_syscall_bdflush(emu); break;
		case __SYSCALL_sysfs: ret = mips_syscall_sysfs(emu); break;
		case __SYSCALL_personality: ret = mips_syscall_personality(emu); break;
		case __SYSCALL_afs_syscall: ret = mips_syscall_afs_syscall(emu); break;
		case __SYSCALL_setfsuid: ret = mips_syscall_setfsuid(emu); break;
		case __SYSCALL_setfsgid: ret = mips_syscall_setfsgid(emu); break;
		case __SYSCALL__llseek: ret = mips_syscall__llseek(emu); break;
		case __SYSCALL_getdents: ret = mips_syscall_getdents(emu); break;
		case __SYSCALL__newselect: ret = mips_syscall_newselect(emu); break;
		case __SYSCALL_flock: ret = mips_syscall_flock(emu); break;
		case __SYSCALL_msync: ret = mips_syscall_msync(emu); break;
		case __SYSCALL_readv: ret = mips_syscall_readv(emu); break;
		case __SYSCALL_writev: ret = mips_syscall_writev(emu); break;
		case __SYSCALL_getsid: ret = mips_syscall_getsid(emu); break;
		case __SYSCALL_fdatasync: ret = mips_syscall_fdatasync(emu); break;
		case __SYSCALL__sysctl: ret = mips_syscall_sysctl(emu); break;
		case __SYSCALL_mlock: ret = mips_syscall_mlock(emu); break;
		case __SYSCALL_munlock: ret = mips_syscall_munlock(emu); break;
		case __SYSCALL_mlockall: ret = mips_syscall_mlockall(emu); break;
		case __SYSCALL_munlockall: ret = mips_syscall_munlockall(emu); break;
		case __SYSCALL_sched_setparam: ret = mips_syscall_sched_setparam(emu); break;
		case __SYSCALL_sched_getparam: ret = mips_syscall_sched_getparam(emu); break;
		case __SYSCALL_sched_setscheduler: ret = mips_syscall_sched_setscheduler(emu); break;
		case __SYSCALL_sched_getscheduler: ret = mips_syscall_getsheduler(emu); break;
		case __SYSCALL_sched_yield: ret = mips_syscall_sched_yield(emu); break;
		case __SYSCALL_sched_get_priority_max: ret = mips_syscall_sched_get_priority_max(emu); break;
		case __SYSCALL_sched_get_priority_min: ret = mips_syscall_sched_get_priority_min(emu); break;
		case __SYSCALL_sched_rr_get_interval: ret = mips_syscall_sched_rr_get_interval(emu); break;
		case __SYSCALL_nanosleep: ret = mips_syscall_nanosleep(emu); break;
		case __SYSCALL_mremap: ret = mips_syscall_mremap(emu); break;
		case __SYSCALL_setresuid	: ret = mips_syscall_setresuid(emu); break;
		case __SYSCALL_getresuid: ret = mips_syscall_getresuid(emu); break;
		case __SYSCALL_vm86: ret = mips_syscall_vm86(emu); break;
		case __SYSCALL_query_module: ret = mips_syscall_query_module(emu); break;
		case __SYSCALL_poll: ret = mips_syscall_poll(emu); break;
		case __SYSCALL_nfsservctl: ret = mips_syscall_nfsservctl(emu); break;
		case __SYSCALL_setresgid	: ret = mips_syscall_setresgid(emu); break;
		case __SYSCALL_getresgid: ret = mips_syscall_getresgid(emu); break;
		case __SYSCALL_prctl: ret = mips_syscall_prctl(emu); break;
		case __SYSCALL_rt_sigreturn: ret = mips_syscall_rt_sigreturn(emu); break;
		case __SYSCALL_rt_sigaction: ret = mips_syscall_rt_sigaction(emu); break;
		case __SYSCALL_rt_sigprocmask: ret = mips_syscall_rt_sigprocmask(emu); break;
		case __SYSCALL_rt_sigpending: ret = mips_syscall_rt_sigpending(emu); break;
		case __SYSCALL_rt_sigtimedwait: ret = mips_syscall_rt_sigtimedwait(emu); break;
		case __SYSCALL_rt_sigqueueinfo: ret = mips_syscall_rt_sigqueueinfo(emu); break;
		case __SYSCALL_rt_sigsuspend: ret = mips_syscall_rt_sigsuspend(emu); break;
		case __SYSCALL_pread: ret = mips_syscall_pread(emu); break;
		case __SYSCALL_pwrite: ret = mips_syscall_pwrite(emu); break;
		case __SYSCALL_chown: ret = mips_syscall_chown(emu); break;
		case __SYSCALL_getcwd: ret = mips_syscall_getcwd(emu); break;
		case __SYSCALL_capget: ret = mips_syscall_capget(emu); break;
		case __SYSCALL_capset: ret = mips_syscall_capset(emu); break;
		case __SYSCALL_sigaltstack: ret = mips_syscall_sigaltstack(emu); break;
		case __SYSCALL_sendfile: ret = mips_syscall_sendfile(emu); break;
		case __SYSCALL_getpmsg: ret = mips_syscall_getpmsg(emu); break;
		case __SYSCALL_putpmsg: ret = mips_syscall_putpmsg(emu); break;
		case __SYSCALL_vfork: ret = mips_syscall_vfork(emu); break;
		case __SYSCALL_ugetrlimit: ret = mips_syscall_ugetrlimit(emu); break;
		case __SYSCALL_mmap2: ret = mips_syscall_mmap2(emu); break;
		case __SYSCALL_truncate64: ret = mips_syscall_truncate64(emu); break;
		case __SYSCALL_ftruncate64: ret = mips_syscall_ftruncate64(emu); break;
		case __SYSCALL_stat64: ret = mips_syscall_stat64(emu); break;
		case __SYSCALL_lstat64: ret = mips_syscall_lstat64(emu); break;
		case __SYSCALL_fstat64: ret = mips_syscall_fstat64(emu); break;
		case __SYSCALL_lchown32: ret = mips_syscall_lchown32(emu); break;
		case __SYSCALL_getuid32: ret = mips_syscall_getuid32(emu); break;
		case __SYSCALL_getgid32: ret = mips_syscall_getgid32(emu); break;
		case __SYSCALL_geteuid32: ret = mips_syscall_geteuid32(emu); break;
		case __SYSCALL_getegid32: ret = mips_syscall_getegid32(emu); break;
		case __SYSCALL_setreuid32: ret = mips_syscall_setreuid32(emu); break;
		case __SYSCALL_setregid32: ret = mips_syscall_setregid32(emu); break;
		case __SYSCALL_getgroups32: ret = mips_syscall_getgroups32(emu); break;
		case __SYSCALL_setgroups32: ret = mips_syscall_setgroups32(emu); break;
		case __SYSCALL_fchown32: ret = mips_syscall_fchown32(emu); break;
		case __SYSCALL_setresuid32: ret = mips_syscall_setresuid32(emu); break;
		case __SYSCALL_getresuid32: ret = mips_syscall_getresuid32(emu); break;
		case __SYSCALL_setresgid32: ret = mips_syscall_setresgid32(emu); break;
		case __SYSCALL_getresgid32: ret = mips_syscall_getresgid32(emu); break;
		case __SYSCALL_chown32: ret = mips_syscall_chown32(emu); break;
		case __SYSCALL_setuid32: ret = mips_syscall_setuid32(emu); break;
		case __SYSCALL_setgid32: ret = mips_syscall_setgid32(emu); break;
		case __SYSCALL_setfsuid32: ret = mips_syscall_setfsuid32(emu); break;
		case __SYSCALL_setfsgid32: ret = mips_syscall_setfsgid32(emu); break;
		case __SYSCALL_pivot_root: ret = mips_syscall_pivot_root(emu); break;
		case __SYSCALL_mincore: ret = mips_syscall_mincore(emu); break;
		case __SYSCALL_madvise: ret = mips_syscall_madvise(emu); break;
		case __SYSCALL_getdents64: ret = mips_syscall_getdents64(emu); break;
		case __SYSCALL_fcntl64: ret = mips_syscall_fnctl64(emu); break;
	}
	
	if(!ret)
	{
		if (emu->is_verbose())
			fprintf(stderr, "Warning : system call returns an error (number : %u, name : %s)\n", syscall_num, get_syscall_name(syscall_num));
	}
	else
	{
	}
}

