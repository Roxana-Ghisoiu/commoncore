#!/bin/bash
echo Hello
/bin/echo Salut
echo $USER
echo "$USER"
/bin/echo "User is: $USER"
echo '$USER'
echo "This * should not expand"
echo *
/bin/echo Hello\ World
ls
pwd
./script.sh
echo "Unclosed
echo 'Unclosed
echo Hello ; echo Fail
