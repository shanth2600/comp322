#!/bin/bash
while read in; 
 do  kill -15 $in > /dev/null;
done < pid.txt
