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
/* Main code for remote server for GDB.
	 Copyright 1989, 1993, 1994, 1995, 1997, 1998, 1999, 2000, 2002, 2003, 2004
	 Free Software Foundation, Inc.

	 This file is part of GDB.

	 This program is free software; you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation; either version 2 of the License, or
	 (at your option) any later version.

	 This program is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	 GNU General Public License for more details.

	 You should have received a copy of the GNU General Public License
	 along with this program; if not, write to the Free Software
	 Foundation, Inc., 59 Temple Place - Suite 330,
	 Boston, MA 02111-1307, USA.	*/

#include <unistd.h>
#include <setjmp.h>
#include <csignal>
#include <cstdlib>
#include <mips_emul.hpp>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define PBUFSIZ 2000

using namespace emulator;

int extended_protocol;

jmp_buf toplevel;

const int remote_debug = 1;

static int remote_desc;

/* Open a connection to a remote debugger.
	 NAME is the filename used for communication.	*/

void
remote_open (char *name)
{
	if (strchr (name, ':')) {

		char *port_str;
		int port;
		struct sockaddr sockaddr;
		socklen_t slen;
		int tmp;
		int tmp_desc;

		port_str = strchr (name, ':');

		port = atoi (port_str + 1);

		tmp_desc = socket (PF_INET, SOCK_STREAM, 0);
		if (tmp_desc < 0) {
			fprintf(stderr, "Can't open socket");
			exit (1);
		}

		/* Allow rapid reuse of this port. */
		tmp = 1;
		setsockopt (tmp_desc, SOL_SOCKET, SO_REUSEADDR, (char *) &tmp,
		sizeof (tmp));

		sockaddr.sa_family = PF_INET;
		*(uint16_t *)(sockaddr.sa_data) = htons(port);
		*((uint32_t *)(sockaddr.sa_data+2)) = INADDR_ANY;

		if (bind (tmp_desc, &sockaddr, sizeof (sockaddr))
			|| listen (tmp_desc, 1)) {
			fprintf(stderr, "Can't bind address");
			exit(1);
		}

		fprintf (stderr, "Listening on port %d\n", port);

		slen = sizeof (sockaddr);
		remote_desc = accept (tmp_desc, &sockaddr, &slen);
		if (remote_desc == -1) {
			fprintf(stderr, "Accept failed");
			exit (1);
		}

		/* Enable TCP keep alive process. */
		tmp = 1;
		setsockopt (tmp_desc, SOL_SOCKET, SO_KEEPALIVE,
			(char *)&tmp, sizeof (tmp));

		/* Tell TCP not to delay small packets.	This greatly speeds up
			 interactive response. */
		tmp = 1;
		setsockopt (remote_desc, IPPROTO_TCP, TCP_NODELAY,
			(char *) &tmp, sizeof (tmp));

		close (tmp_desc);		/* No longer need this */

		signal (SIGPIPE, SIG_IGN); /* If we don't do this,
				 then gdbserver simply exits when the remote side dies.	*/

		/* Convert IP address to string.	*/
		fprintf (stderr, "Remote debugging from host %s\n", 
			 inet_ntoa (*(struct in_addr *)(sockaddr.sa_data+2)));
	}
	else {
		fprintf (stderr, "Cannot open socket at port %s.\n", name);
		exit(1);
	}
}

void
remote_close (void)
{
	close (remote_desc);
}

/* Convert hex digit A to a number.	*/

static int
fromhex (int a)
{
	if (a >= '0' && a <= '9')
		return a - '0';
	else if (a >= 'a' && a <= 'f')
		return a - 'a' + 10;
	else {
	//	assert(0);
	}
	return 0;
}

int
unhexify (char *bin, const char *hex, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		if (hex[0] == 0 || hex[1] == 0)
		{
			/* Hex string is short, or of uneven length.
			 Return the count that has been converted so far. */
			return i;
		}
		*bin++ = fromhex (hex[0]) * 16 + fromhex (hex[1]);
		hex += 2;
	}
	return i;
}

static void
decode_address (mips_addr_t *addrp, const char *start, int len)
{
	mips_addr_t addr;
	char ch;
	int i;

	addr = 0;
	for (i = 0; i < len; i++)
	{
		ch = start[i];
		addr = addr << 4;
		addr = addr | (fromhex (ch) & 0x0f);
	}
	*addrp = addr;
}

/* Convert number NIB to a hex digit.	*/

static int
tohex (int nib)
{
	if (nib < 10)
		return '0' + nib;
	else
		return 'a' + nib - 10;
}

int
hexify (char *hex, const char *bin, int count)
{
	int i;

	/* May use a length, or a nul-terminated string as input. */
	if (count == 0)
		count = strlen (bin);

	for (i = 0; i < count; i++)
	{
		*hex++ = tohex ((*bin >> 4) & 0xf);
		*hex++ = tohex (*bin++ & 0xf);
	}
	*hex = 0;
	return i;
}

/* Send a packet to the remote machine, with error checking.
	 The data of the packet is in BUF.	Returns >= 0 on success, -1 otherwise. */

int
putpkt (char *buf)
{
	int i;
	unsigned char csum = 0;
	char *buf2;
	char buf3[1];
	int cnt = strlen (buf);
	char *p;

	buf2 = (char *)malloc (PBUFSIZ);

	/* Copy the packet into buffer BUF2, encapsulating it
		 and giving it a checksum.	*/

	p = buf2;
	*p++ = '$';

	for (i = 0; i < cnt; i++)
	{
		csum += buf[i];
		*p++ = buf[i];
	}
	*p++ = '#';
	*p++ = tohex ((csum >> 4) & 0xf);
	*p++ = tohex (csum & 0xf);

	*p = '\0';

	/* Send it over and over until we get a positive ack.	*/

	do
	{
		int cc;

		if (write (remote_desc, buf2, p - buf2) != p - buf2)
		{
			perror ("putpkt(write)");
			return -1;
		}

		if (remote_debug)
		{
			fprintf (stderr, "putpkt (\"%s\"); [looking for ack]\n", buf2);
			fflush (stderr);
		}
		cc = read (remote_desc, buf3, 1);
		if (remote_debug)
		{
			fprintf (stderr, "[received '%c' (0x%x)]\n", buf3[0], buf3[0]);
			fflush (stderr);
		}

		if (cc <= 0)
		{
			if (cc == 0)
				fprintf (stderr, "putpkt(read): Got EOF\n");
			else
				perror ("putpkt(read)");

			free (buf2);
			return -1;
		}

		/* Check for an input interrupt while we're here.	*/
		if (buf3[0] == '\003'); // do nothing
	}
	while (buf3[0] != '+');

	free (buf2);
	return 1;			/* Success! */
}

/* Returns next char from remote GDB.	-1 if error.	*/

static int
readchar (void)
{
	static char buf[BUFSIZ];
	static int bufcnt = 0;
	static char *bufp;

	if (bufcnt-- > 0)
		return *bufp++ & 0x7f;

	bufcnt = read (remote_desc, buf, sizeof (buf));

	if (bufcnt <= 0)
	{
		if (bufcnt == 0)
			fprintf (stderr, "readchar: Got EOF\n");
		else
			perror ("readchar");

		return -1;
	}

	bufp = buf;
	bufcnt--;
	return *bufp++ & 0x7f;
}

/* Read a packet from the remote machine, with error checking,
	 and store it in BUF.	Returns length of packet, or negative if error. */

int
getpkt (char *buf)
{
	char *bp;
	unsigned char csum, c1, c2;
	int c;

	while (1)
	{
		csum = 0;

		while (1)
		{
			c = readchar ();
			if (c == '$')
				break;
			if (remote_debug)
			{
				fprintf (stderr, "[getpkt: discarding char '%c']\n", c);
				fflush (stderr);
			}

			if (c < 0)
				return -1;
		}

		bp = buf;
		while (1)
		{
			c = readchar ();
			if (c < 0)
				return -1;
			if (c == '#')
				break;
			*bp++ = c;
			csum += c;
		}
		*bp = 0;

		c1 = fromhex (readchar ());
		c2 = fromhex (readchar ());

		if (csum == (c1 << 4) + c2)
			break;

		fprintf (stderr, "Bad checksum, sentsum=0x%x, csum=0x%x, buf=%s\n",
			 (c1 << 4) + c2, csum, buf);
		write (remote_desc, "-", 1);
	}

	if (remote_debug)
	{
		fprintf (stderr, "getpkt (\"%s\");	[sending ack] \n", buf);
		fflush (stderr);
	}

	write (remote_desc, "+", 1);

	if (remote_debug)
	{
		fprintf (stderr, "[sent ack]\n");
		fflush (stderr);
	}

	return bp - buf;
}

void
write_ok (char *buf)
{
	buf[0] = 'O';
	buf[1] = 'K';
	buf[2] = '\0';
}

void
write_enn (char *buf)
{
	/* Some day, we should define the meanings of the error codes... */
	buf[0] = 'E';
	buf[1] = '0';
	buf[2] = '1';
	buf[3] = '\0';
}

void
convert_int_to_ascii (char *from, char *to, int n)
{
	int nib;
	char ch;
	while (n--)
	{
		ch = *from++;
		nib = ((ch & 0xf0) >> 4) & 0x0f;
		*to++ = tohex (nib);
		nib = ch & 0x0f;
		*to++ = tohex (nib);
	}
	*to++ = 0;
}


void
convert_ascii_to_int (char *from, char *to, int n)
{
	int nib1, nib2;
	while (n--)
	{
		nib1 = fromhex (*from++);
		nib2 = fromhex (*from++);
		*to++ = (((nib1 & 0x0f) << 4) & 0xf0) | (nib2 & 0x0f);
	}
}


void
mips_emulator::gdb_prepare_resume_reply (char *buf, char *stat, unsigned char *sig)
{
	int nib;


	if (is_interrupted()) {
		*buf++ = 'T';
		nib = ((SIGINT & 0xf0) >> 4);
		*buf++ = tohex(nib);
		nib = SIGINT & 0x0f;
		*buf++ = tohex(nib);
		*sig = SIGINT;
		*stat = 'T';
	}
	else if (is_done()) {
		*buf++ = 'W';
		nib = ((retcode & 0xf0) >> 4);
		*buf++ = tohex(nib);
		nib = retcode & 0x0f;
		*buf++ = tohex(nib);
		*sig = (unsigned char)retcode;
		*stat = 'W';
	}
	else if (is_fault()) {
		*buf++ = 'X';
		nib = ((SIGSEGV & 0xf0) >> 4);
		*buf++ = tohex(nib);
		nib = SIGSEGV & 0x0f;
		*buf++ = tohex(nib);
		*sig = SIGSEGV;
		*stat = 'X';
	}
	else {
		*buf++ = 'T'; //status;
		nib = ((SIGTRAP & 0xf0) >> 4);
		*buf++ = tohex(nib);
		nib = SIGTRAP & 0x0f;
		*buf++ = tohex(nib);
		*stat = 'T';
	}

	/* For W and X, we're done.	*/
	*buf++ = 0;
}

void
decode_m_packet (char *from, mips_addr_t *mem_addr_ptr, unsigned int *len_ptr)
{
	int i = 0, j = 0;
	char ch;
	*mem_addr_ptr = *len_ptr = 0;

	while ((ch = from[i++]) != ',')
	{
		*mem_addr_ptr = *mem_addr_ptr << 4;
		*mem_addr_ptr |= fromhex (ch) & 0x0f;
	}

	for (j = 0; j < 4; j++)
	{
		if ((ch = from[i++]) == 0)
			break;
		*len_ptr = *len_ptr << 4;
		*len_ptr |= fromhex (ch) & 0x0f;
	}
}

void
decode_M_packet (char *from, mips_addr_t *mem_addr_ptr, unsigned int *len_ptr,
		 char *to)
{
	int i = 0;
	char ch;
	*mem_addr_ptr = *len_ptr = 0;

	while ((ch = from[i++]) != ',')
	{
		*mem_addr_ptr = *mem_addr_ptr << 4;
		*mem_addr_ptr |= fromhex (ch) & 0x0f;
	}

	while ((ch = from[i++]) != ':')
	{
		*len_ptr = *len_ptr << 4;
		*len_ptr |= fromhex (ch) & 0x0f;
	}

	convert_ascii_to_int (&from[i++], to, *len_ptr);
}

static char *word_to_string(u_word_t val, char *buf)
{
	// assuming little endian
	*buf++ = tohex((val>>4)&0x0F);
	*buf++ = tohex((val>>0)&0x0F);
	*buf++ = tohex((val>>12)&0x0F);
	*buf++ = tohex((val>>8)&0x0F);
	*buf++ = tohex((val>>20)&0x0F);
	*buf++ = tohex((val>>16)&0x0F);
	*buf++ = tohex((val>>28)&0x0F);
	*buf++ = tohex((val>>24)&0x0F);
	return buf;
}

static u_word_t string_to_word(char *buf)
{
	// assuming little endian
	unsigned char *buf1 = reinterpret_cast<unsigned char *>(buf);
	u_word_t val = 0;
	val = val | (tohex(buf1[0])<<4);
	val = val | (tohex(buf1[1])<<0);
	val = val | (tohex(buf1[2])<<12);
	val = val | (tohex(buf1[3])<<8);
	val = val | (tohex(buf1[4])<<20);
	val = val | (tohex(buf1[5])<<16);
	val = val | (tohex(buf1[6])<<28);
	val = val | (tohex(buf1[7])<<24);
	return val;
}

bool mips_emulator::registers_from_string(char *buf)
{
	int len = strlen (buf);
	if (len != 73*8) {
		fprintf(stderr, "Error parsing register string!\n");
		return false;
	}
	
	int ii;
	for (ii=0; ii<NUM_GPR; ii++) {
		WriteGPR(string_to_word(buf),ii);
		buf += 8;
	}
	
	buf += 8;
	WriteHI(string_to_word(buf));
	buf += 8;
	WriteLO(string_to_word(buf));
	buf += 8;

	buf += 16;
	WritePC(string_to_word(buf));

	for (ii=0; ii<NUM_FPR; ii++) {
		WriteFixedW(string_to_word(buf),ii);
		buf += 8;
	}

	return true;
}

void mips_emulator::registers_to_string(char *buf)
{
	// order: 32 general-purpose; sr; lo; hi; bad; cause; pc; 32 floating-point registers; fsr; fir; fp.

	int ii;
	for (ii=0; ii<NUM_GPR; ii++) {
		buf = word_to_string(ReadGPR(ii), buf);
	}

	buf = word_to_string(0, buf); // write sr
	buf = word_to_string(ReadLO(), buf);
	buf = word_to_string(ReadHI(), buf);
	buf = word_to_string(0, buf); // bad
	buf = word_to_string(0, buf); // cause
	buf = word_to_string(ReadPC(), buf);

	for (ii=0; ii<32; ii++) {
		buf = word_to_string(ReadFixedW(ii), buf);
	}
	
	buf = word_to_string(ReadFCSR(), buf); // fsr
	buf = word_to_string(0, buf);		   // fir
	buf = word_to_string(0, buf);		   // fp
}

int
mips_emulator::gdb(char *socket_name)
{
	char ch, stat, *own_buf, mem_buf[2000];
	int i = 0;
	unsigned char sig;
	unsigned int len;
	mips_addr_t mem_addr;
	void (*sig_handler)(int);

	if (setjmp (toplevel))
	{
		fprintf (stderr, "Exiting\n");
		exit (1);
	}

	own_buf = (char *)malloc (PBUFSIZ);

	/* We are now stopped at the first instruction of the target process */

	while (1)
	{
		remote_open (socket_name);

		restart:
		setjmp (toplevel);

		while (getpkt (own_buf) > 0)
		{
			i = 0;
			stat = 0;
			ch = own_buf[i++];
			switch (ch)
			{
				case 'q':
					own_buf[0] = 0;
					//write_ok (own_buf);
					break;
				case 'D':
					write_ok (own_buf);
					putpkt (own_buf);
					remote_close ();
					return 0;

				case '!':
					extended_protocol = 1;
					write_ok (own_buf);
					break;
				case '?':
					gdb_prepare_resume_reply (own_buf, &stat, &sig);
					break;
				case 'H':
					/* Silently ignore it so that gdb can extend the protocol
					 without compatibility headaches.	*/
					own_buf[0] = '\0';
					break;
				case 'g':
					registers_to_string (own_buf);
					break;
				case 'G':
					registers_from_string (&own_buf[1]);
					write_ok (own_buf);
					break;
				case 'm':
					decode_m_packet (&own_buf[1], &mem_addr, &len);
					mem->read_block(mem_buf, mem_addr, len);
					convert_int_to_ascii (mem_buf, own_buf, len);
					break;
				case 'M':
					decode_M_packet (&own_buf[1], &mem_addr, &len, mem_buf);
					/* need to turn off SIGUSR1 here */
					sig_handler = signal(SIGINT, SIG_IGN);
					mem->write_block(mem_addr, mem_buf, len);
					signal(SIGUSR1, sig_handler);
					write_ok (own_buf);
					break;
				case 'C':
					gdb_go_to(0);
					gdb_prepare_resume_reply (own_buf, &stat, &sig);
					break;
				case 'S':
					gdb_trace(1);
					gdb_prepare_resume_reply (own_buf, &stat, &sig);
					break;
				case 'c':
					gdb_go_to(0);
					gdb_prepare_resume_reply (own_buf, &stat, &sig);
					break;
				case 's':
					gdb_trace(1);
					gdb_prepare_resume_reply (own_buf, &stat, &sig);
					break;
				case 'k':
					fprintf (stderr, "Killing target process\n");
					if (extended_protocol)
					{
						write_ok (own_buf);
						fprintf (stderr, "Debugger restarting\n");
						reload();

						/* Wait till we are at 1st instruction in prog.	*/
						// restart
						goto restart;
						break;
					}
					else
					{
						return 0;
						break;
					}
				case 'T':
					if (is_interrupted() || is_broken() ||
						is_running() || is_debugging())
						write_ok (own_buf);
					else
						write_enn (own_buf);
					break;
				case 'R':
					/* Restarting the inferior is only supported in the
						 extended protocol.	*/
					if (extended_protocol)
					{
						write_ok (own_buf);
						fprintf (stderr, "Debugger restarting\n");
						reload();

						/* Wait till we are at 1st instruction in prog.	*/
						goto restart;
						break;
					}
					else
					{
						/* It is a request we don't understand.	Respond with an
						 empty packet so that gdb knows that we don't support
						 this request.	*/
						own_buf[0] = '\0';
						break;
					}
				case 'v': // don't do anything
				case 'd': // deprecated
				default:
					/* It is a request we don't understand.	Respond with an
					 empty packet so that gdb knows that we don't support this
					 request.	*/
					own_buf[0] = '\0';
					break;
			}

			putpkt (own_buf);

			if (stat == 'W')
				fprintf (stderr,
				 "\nProgram exited with status %d\n", sig);

			if (stat == 'X')
				fprintf (stderr, "\nChild terminated with signal = 0x%x\n",
					sig);

			if (stat == 'W' || stat == 'X')
			{
				if (extended_protocol)
				{
					fprintf (stderr, "Killing target process\n");
					write_ok (own_buf);
					fprintf (stderr, "Debugger restarting\n");
					reload();

					/* Wait till we are at 1st instruction in prog.	*/
					goto restart;
					break;
				}
				else
				{
					fprintf (stderr, "Debugger exiting\n");
					return 0;
				}
			}
		}

		/* We come here when getpkt fails.

		 For the extended remote protocol we exit (and this is the only
		 way we gracefully exit!).

		 For the traditional remote protocol close the connection,
		 and re-open it at the top of the loop.	*/
		if (extended_protocol)
		{
			remote_close ();
			return 0;
		}
		else
		{
			fprintf (stderr, "Remote side has terminated connection.	"
					 "Debugger will reopen the connection.\n");
			remote_close ();
			reload();
		}
	}
}

void mips_emulator::gdb_trace(int count)
{
	mips_inst_t inst;
	
	status = ST_DEBUGGING;

	while(status==ST_DEBUGGING && count > 0)
	{
		inst = mem->read_word_fast(ReadPC());
		execute(inst);
		icount++;
		count--;
	}
}

void mips_emulator::gdb_go_to(mips_addr_t addr)
{
	mips_inst_t inst;
	
	status = ST_DEBUGGING;
	
	while(status==ST_DEBUGGING && ReadPC() != addr)
	{
		inst = mem->read_word_fast(ReadPC());
		execute(inst);
		icount++;
	}
	
}
