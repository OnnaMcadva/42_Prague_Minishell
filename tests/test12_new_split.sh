#!/bin/bash

clang ./test12_new_split.c -L/usr/local/opt/readline/lib -lreadline -L../libft_plus -lft_plus -g -fsanitize=address

./a.out

rm -rf a.out*
