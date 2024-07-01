#!/bin/bash
dd if=/proc/231528/mem of=./linux.vdso bs=1 skip=140737354125312 count=8192
objdump -T linux.vdso

