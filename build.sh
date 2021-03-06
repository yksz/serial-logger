#!/bin/sh

DIRNAME="build"

cd `dirname "$0"`
if [ ! -e ${DIRNAME} ] ; then
    mkdir ${DIRNAME}
fi
cd ${DIRNAME}

cmake -DCMAKE_BUILD_TYPE=Release $@ ..
make
