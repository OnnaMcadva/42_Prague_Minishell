#!/bin/bash

clang ./test10_env.c -L../libft_plus -lft_plus -g -fsanitize=address

./a.out

rm ./a.out
