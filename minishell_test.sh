#!/bin/bash
make

echo "bash: SHLVL is $SHLVL"
./minishell << EOF
echo "\$SHLVL"
echo "\$SHELL"
echo abc
echo
    echo    a       b  c
e"ch"o abc''
echo "a
echo -n 'do you like my '

echo -nnnnnnnn 'do you still like my '

echo "\$USER"
echo '\$USER'
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
ls -z
echo "\$?"

cd tests/
pwd
cd ..
pwd
cd ~
pwd
cd -
pwd
unset OLDPWD PATH
cd -
ls
env > env_without_PATH1.txt
exit 42
EOF

printf "\nbash: minishell exit code: $? \n\n"

./minishell << EOF
exit 1 a
EOF

printf "\nbash: minishell exit code: $? \n\n"

./minishell << EOF
exit a 1
EOF

printf "\nbash: minishell exit code: $? \n\n"

unset PATH
./minishell << EOF
echo "Someone just unset the PATH in Bash, so system commands won't work"
env > env_without_PATH2.txt
printf "REALLY?\n"
echo TOLD YOU!
exit abc
EOF

printf "\nbash: minishell exit code: $? \n\n"
