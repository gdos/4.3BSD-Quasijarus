h37115
s 00001/00036/00111
d D 6.3 04/11/28 22:31:23 msokolov 4 3
c long live sgtty!
e
s 00016/00006/00131
d D 6.2 86/05/12 01:01:43 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00137
d D 6.1 86/05/08 12:27:07 mckusick 2 1
c format updates for 4.3BSD
e
s 00138/00000/00000
d D 5.1 86/05/08 00:03:51 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
.sh "Terminals and Devices
.NH 3
Terminals
.PP
D 3
Terminals support \fIread\fP and \fIwrite\fP i/o operations,
E 3
I 3
Terminals support \fIread\fP and \fIwrite\fP I/O operations,
E 3
as well as a collection of terminal specific \fIioctl\fP operations,
D 3
to control input character editing, and output delays.
E 3
I 3
to control input character interpretation and editing,
and output format and delays.
E 3
.NH 4
Terminal input
.PP
Terminals are handled according to the underlying communication
characteristics such as baud rate and required delays,
and a set of software parameters.
.NH 5
Input modes
.PP
A terminal is in one of three possible modes: \fIraw\fP, \fIcbreak\fP,
or \fIcooked\fP.
In raw mode all input is passed through to the
reading process immediately and without interpretation.
In cbreak mode, the handler interprets input only by looking
for characters that cause interrupts or output flow control;
all other characters are made available as in raw mode.
In cooked mode, input
is processed to provide standard line-oriented local editing functions,
and input is presented on a line-by-line basis.
.NH 5
Interrupt characters
.PP
Interrupt characters are interpreted by the terminal handler only in
cbreak and cooked modes, and
cause a software interrupt to be sent to all processes in the process
group associated with the terminal.  Interrupt characters exist
to send SIGINT
and SIGQUIT signals,
and to stop a process group
with the SIGTSTP signal either immediately, or when
all input up to the stop character has been read.
.NH 5
Line editing
.PP
When the terminal is in cooked mode, editing of an input line
is performed.  Editing facilities allow deletion of the previous
character or word, or deletion of the current input line. 
In addition, a special character may be used to reprint the current
input line after some number of editing operations have been applied.
.PP
Certain other characters are interpreted specially when a process is
in cooked mode.  The \fIend of line\fP character determines
the end of an input record.  The \fIend of file\fP character simulates
an end of file occurrence on terminal input.  Flow control is provided
by \fIstop output\fP and \fIstart output\fP control characters.  Output
may be flushed with the \fIflush output\fP character; and a \fIliteral
character\fP may be used to force literal input of the immediately
following character in the input line.
I 3
.PP
Input characters may be echoed to the terminal as they are received.
Non-graphic ASCII input characters may be echoed as a two-character
printable representation, ``^character.''
E 3
.NH 4
Terminal output
.PP
On output, the terminal handler provides some simple formatting services.
These include converting the carriage return character to the
D 3
two character return-linefeed sequence, displaying non-graphic
ASCII characters as ``^character'', inserting delays after certain
standard control characters, expanding tabs, and providing translations
E 3
I 3
two character return-linefeed sequence,
inserting delays after certain standard control characters,
expanding tabs, and providing translations
E 3
for upper-case only terminals.
.NH 4
Terminal control operations
.PP
When a terminal is first opened it is initialized to a standard
state and configured with a set of standard control, editing,
and interrupt characters.  A process
may alter this configuration with certain
D 3
control operations, specifying parameters in a standard structure:
E 3
I 3
D 4
control operations, specifying parameters in a standard structure:\(dg
.FS
\(dg The control interface described here is an internal interface only
in 4.3BSD.  Future releases will probably use a modified interface
based on currently-proposed standards.
.FE
E 3
.DS
._f
struct ttymode {
	short	tt_ispeed;	/* input speed */
	int	tt_iflags;	/* input flags */
	short	tt_ospeed;	/* output speed */
	int	tt_oflags;	/* output flags */
};
.DE
and ``special characters'' are specified with the 
\fIttychars\fP structure,
.DS
._f
struct ttychars {
	char	tc_erasec;	/* erase char */
	char	tc_killc;	/* erase line */
	char	tc_intrc;	/* interrupt */
	char	tc_quitc;	/* quit */
	char	tc_startc;	/* start output */
	char	tc_stopc;	/* stop output */
	char	tc_eofc;	/* end-of-file */
	char	tc_brkc;	/* input delimiter (like nl) */
	char	tc_suspc;	/* stop process signal */
	char	tc_dsuspc;	/* delayed stop process signal */
	char	tc_rprntc;	/* reprint line */
	char	tc_flushc;	/* flush output (toggles) */
	char	tc_werasc;	/* word erase */
	char	tc_lnextc;	/* literal next character */
};
.DE
E 4
I 4
control operations described in \fItty\fR(4).
E 4
.NH 4
Terminal hardware support
.PP
The terminal handler allows a user to access basic
hardware related functions; e.g. line speed,
modem control, parity, and stop bits.  A special signal,
SIGHUP, is automatically
sent to processes in a terminal's process
group when a carrier transition is detected.  This is
normally associated with a user hanging up on a modem
controlled terminal line.
.NH 3
Structured devices
.PP
Structures devices are typified by disks and magnetic
tapes, but may represent any random-access device.
The system performs read-modify-write type buffering actions on block
devices to allow them to be read and written in a totally random
access fashion like ordinary files.
File systems are normally created in block devices.
.NH 3
Unstructured devices
.PP
Unstructured devices are those devices which
do not support block structure.  Familiar unstructured devices
are raw communications lines (with
no terminal handler), raster plotters, magnetic tape and disks unfettered
by buffering and permitting large block input/output and positioning
and formatting commands.
E 1