#!/bin/bash

cc -o kmalloc-test -std=c99 -g -DSTANDALONE k-malloc.c
valgrind ./kmalloc-test
