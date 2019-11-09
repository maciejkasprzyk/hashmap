#!/bin/bash
echo $0
DIR=$(dirname "$0")
make -C "$DIR" && "$DIR"/bin/main