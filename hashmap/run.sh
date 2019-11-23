#!/bin/bash
DIR=$(dirname "$0")
make -C "$DIR" && "$DIR"/bin/main "$DIR"/../data/words.txt 1000 100
