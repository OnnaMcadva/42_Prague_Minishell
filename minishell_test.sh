#!/bin/bash

./minishell << EOF
echo abc
    echo    a       b  c
e"ch"o abc''
echo "a
echo -n 'do you like my '

echo -nnnnnnnn 'do you still like my '

ls -l | grep drwx | wc -l
< Makefile cat | grep rm > tempfile
cat tempfile

echo "This line doesn't want to vanish but it will =(" >> tempfile
cat tempfile

< Makefile cat | grep rm > tempfile
cat tempfile
ls
rm tempfile
ls
ls | |
cat <
exit 42
EOF
printf "\nminishell exit code: $? \n"
./minishell << EOF
exit abc
EOF
printf "\nminishell exit code: $? \n"
