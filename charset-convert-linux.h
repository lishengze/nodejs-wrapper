#ifndef CHARSET_CONVERT_LINUX_H
#define CHARSET_CONVERT_LINUX_H

#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <malloc.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;

iconv_t CodeConverter(const char*from_charset, const char* to_charset) ;
			
int _Gb2312ToUtf8(char* inbuf, size_t inlen, char* outbuf, size_t outlen);	

int Gb2312ToUtf8(char* inputData, string& outputData) ;

int Gb2312ToUtf8(char* inputData, int inputLength, char* outputData, int outputLength) ;

int _Utf8ToGb2312(char* inbuf, int inlen, char* outbuf, int outlen);

int Utf8ToGb2312(char* inputData, string& outputData);

int convert(iconv_t cd, char* inbuf, int inlen, char* outbuf, int outlen) ;

#endif
