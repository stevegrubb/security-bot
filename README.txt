SECURITY-BOT

BUILDING
========
To build the project run:

/usr/bin/qmake-qt4 -o Makefile security-bot.pro

Then make
./security-bot

You can then ask questions and it will answer. When you are done, type quit.


BACKGROUND
==========
The goal is to allow natural language querying of a system's security status.
It will encompass the following topics:

Security Updates (yum --security)
SE Linux enforcing (sestatus)
System is well configured (oscap)
System integrity checked (aide)
Open ports with risky programs (netcap)
Firewall status
Audit status
Users with privileges logged in (w kind of)
Anomalous events in recent activity (aureport, realtime events)
Suspicious user behavior (realtime audit events)

The ultimate question would be, "Is this system secure?" To answer this
question, it will have to consider each category. This can be modeled after
an attack tree.

THOUGHTS
========
Can external sensors set state in the aiml instance? Maybe a private
conversation?

Make a state diagram of the work it can do. These can map to predicates.

Use tree diagrams to study sentence construction

Might also be able to have a key word such as "thinking" or "working.." where the output program makes note and sets a timer to provoke another chance to talk.

NEEDS
=====
* killall needs session awareness
* need something like w except with roles and privs
* Audit rules that classify use of programs for:
Reconnaissance - ls, ps, lsof, w, who, ?cp /etc/passwd, 
Pre-exploit - wget, curl, links, elinks, rsync, scp, chmod +x
Exploitation - setarch, crashed app, using ld.so
Privilege escalation - su, sudo, shadow, passwd
Gaining IP - shadow, home dirs, shared dirs, keys 
Become permanent - write into boot, write module, load module, edit module list
Covering tracks - history files, logs, utmp, btmp, 
Spreading - ssh, tcpdump,

GOALS
=====
SElinux
-------
Is it enabled
is it causing problems
if problems, what is causing it

users
-----
Are people logged in
Do any have privs
Are they doing risky behavior?

programs
--------
Do we need to apply security updates
Do we have risky programs listening

aide
----
Have any system binaries changed config?
Is system config files still the same?

scap
----
Have we scanned lately
do a scan
Do we pass
Can we fix it

audit
----
is audit enabled
do we have rules loaded
run basic search
run basic report
run search + report
analyze events - classifier output

flow or state diagram
=====================
issue -> problem -> action

FUTURE IDEAS
============
1) Topic restricts the set of questions severly. Create a variable, subject, to serve a more flexible purpose. It is something the user may ask a check for.

2) Also create a variable, problem, specifically for the purpose of allowing the user to request a fix. When a check runs, it may set a problem or clear problem. Calling the fix clears the problem.

3) tell me about security? Then say what is known, set subject, then pause, then ask if you it checked. If yes, then use subject to direct to the correct check.

