#! /bin/bash

PROG=$0

program=dining-p
seats=$1
guests=$2
rm pid.txt
touch pid.txt

if [ $# -ne 2 ] ; then 
   echo 
   echo "Usage: ${PROG} seats guests "
   echo "where seats is the setting capacity of the table"
   echo "      guests is the number of philosphers eating"
   echo ""
   exit 1
fi


count=1
while [ ${count} -le ${guests} ] ; do
      ./${program} ${seats} ${count} &
      echo $! >> pid.txt
#      echo "PID of '${program} ${seats} ${count}' is " $!
      count=$(( $count + 1 ))
done


