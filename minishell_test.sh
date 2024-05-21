#!/bin/bash
make

echo "bash: SHLVL is $SHLVL"
./minishell << EOF
echo \$SHLVL
echo \$SHELL
echo abc
echo
    echo    a       b  c
e"ch"o abc''
echo "a
echo -n 'do you like my '

echo -nnnnnnnn 'do you still like my '

echo "\$USER"
echo '\$USER'
echo \$SABARABADA
echo \$
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
cat << END
abc
def
END
ls | |
cat <
ls -z
echo "\$?"

export > export.txt
export ABC=def
export lalala
export GHI=
export AB?C=doesnt_work
unset AB
unset ABCD
env > env_with_ABC.txt

cd blabla
cd tests/
pwd
cd ..
pwd
cd ~
pwd
cd -
pwd
unset HOME
cd
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
printf "REALLY?\n"
echo TOLD YOU!
env > env_without_PATH2.txt
EOF

printf "\nbash: minishell exit code: $? \n\n"
echo "********************************************************************************"
