#############################################################
# friso chinese word segmentation makefile.		    #
#		do not use it for commercial use.	    #
# @author	chenxin 				    #
# @email	chenxin619315@gmail.com   		    #
#############################################################

#complie
CC = gcc
#include directory
INCLUDE = .
#complie flags for devolep
CFLAGS = -g -Wall
#complile flags for products
FFLAGS = -O2 -Wall -fPIC
#extension libs for friso
ELIB = m
LIB_FILE = libfriso.so
STA_FILE = libfriso.a
LIBRARY_DIR = /usr/lib
INCLUDE_DIR = /usr/include/friso
INSTALL_DIR = /usr/local/bin


SOURCE = friso.o friso_array.o friso_hash.o friso_lexicon.o friso_link.o friso_string.o friso_ctype.o friso_UTF8.o friso_GBK.o


word_divide: 
	$(CC) tst_readfile.c -L. -lfriso -o word_divide



#clean all the object files.
.PHONY: clean
clean:
	find . -name \*.so | xargs rm -f
	find . -name \*.o  | xargs rm -f
	@if [ -f friso ];\
	    then\
	    rm -f friso;\
	fi

