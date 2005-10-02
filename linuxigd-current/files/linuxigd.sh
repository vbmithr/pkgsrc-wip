#!@RCD_SCRIPTS_SHELL@
#
# $NetBSD: linuxigd.sh,v 1.1.1.1 2005/10/02 13:35:54 obache Exp $
#
# PROVIDE: linuxidg
# REQUIRE: ipnat
#
# set linuxigd_flags="ext_if int_if" in rc.conf

. /etc/rc.subr

name="linuxigd"
rcvar=${name}
command="@PREFIX@/sbin/upnpd"
required_vars="ipnat"

load_rc_config ${name}
run_rc_command "$1"
