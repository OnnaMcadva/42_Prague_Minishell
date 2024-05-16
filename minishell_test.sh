#!/bin/bash

make
./minishell << EOF
echo abc
echo
    echo    a       b  c
e"ch"o abc''
echo "a
echo -n 'do you like my '

echo -nnnnnnnn 'do you still like my '

mecho
ls -l | grep drwx | wc -l
< Makefile cat | grep rm > xfile
cat xfile

echo "This line doesn't want to vanish but it will =(" >> xfile
cat xfile

< Makefile cat | grep rm > xfile
cat xfile
ls
rm xfile
ls
ls | |
cat <
exit 42
EOF
printf "\nminishell exit code: $? \n\n"
./minishell << EOF
exit 1 a
EOF
printf "\nminishell exit code: $? \n\n"
./minishell << EOF
exit a 1
EOF
printf "\nminishell exit code: $? \n\n"
unset PATH
./minishell << EOF
echo "someone just unsetted PATH in bash, so system commands won't work"
printf "REALLY?\n"
echo TOLD YOU! But it didn't crash =)
exit abc
EOF

printf "\nminishell exit code: $? \n"
