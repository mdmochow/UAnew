#!/bin/sh
 
# starts in $(ProjectDir)
# example /C/documents/solution/project/
 
# first step
awk '$0 !~ /#define _PROJECT_BUILD/ { print $0 }
     $0  ~ /#define _PROJECT_BUILD/ { n = $3 + 1; print $1 " " $2 " " n }' \
     uobject.h > version_temp.h    
 
# second step
touch -r uobject.h version_temp.h
 
# third step
cp -p version_temp.h uobject.h
rm -f version_temp.h