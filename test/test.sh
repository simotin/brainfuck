#!/bin/bash

TARGET=../brainfuck
RESULT=`./${TARGET} helloworld.bf`

if [ $? -ne 0 ]; then
	echo "helloworld.bf failed..."
fi
if [ "${RESULT}" != "Hello, world!" ]; then
	echo "helloworld.bf failed..."
fi

RESULT=`./${TARGET} hoge.bf`
if [ $? -ne 0 ]; then
	echo "hoge.bf failed..."
fi
if [ "${RESULT}" != "hoge" ]; then
	echo "hoge.bf failed..."
fi

RESULT=`./${TARGET} 3.bf`
if [ $? -ne 0 ]; then
	echo "3.bf failed..."
fi
if [ "${RESULT}" != "3" ]; then
	echo "3.bf failed..."
fi
