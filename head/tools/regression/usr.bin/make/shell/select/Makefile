#
# We just select the builtin shells and check whether it is really
# executed. This should print just the shell paths. Because we
# normally don't have a ksh, we make this test conditional. This means
# one has to recreate the test results once ksh is installed.
#
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/make/shell/select/Makefile 146865 2005-05-31 14:13:07Z harti $
#

.ifmake sh_test

.SHELL: name=sh
sh_test: print_path

.elifmake csh_test

.SHELL: name=csh
csh_test: print_path

.elifmake ksh_test

.SHELL: name=ksh
ksh_test: print_path

.endif

print_path:
	@ps -opid,command | awk '$$1=='$$$$' { print $$2; }'
