#!/bin/sh
################################################################################
#
# lockgraphs.sh by Michele Dallachiesa -- 2008-05-07 -- v0.1
#
# $FreeBSD: soc2013/dpl/head/share/examples/witness/lockgraphs.sh 178885 2008-05-07 21:50:17Z attilio $
#
################################################################################

sysctl debug.witness.graphs | awk '
BEGIN {
  print "digraph lockgraphs {"
  }

NR > 1 && $0 ~ /"Giant"/ {
  gsub(","," -> ");
  print $0 ";"
}

END { 
  print "}"
  }'

#eof
