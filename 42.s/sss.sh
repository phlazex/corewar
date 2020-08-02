#!/bin/bash
for n in {1..1000};
  do ../cmake-build-debug/asm casimir.s
  ddd=`diff casimir.cor casimir_demo.cor`
  printf "%d: ", $n
  if [ "$ddd" != "" ]; then
    printf "$ddd"
    break
  fi
  done
