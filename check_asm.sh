#!/bin/bash

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
RESET="\x1b[0m"

ASM_EXEC=$1
DEMO_ASM_EXEC=./checkers/asm

CHAMPS_DIR=checkers/asm_test/champs
DIFF_DIR=checkers/asm_test/out_diff

ASM_OUTPUT=test_temp_asm
DEMO_OUTPUT=test_temp_demo

ASM_OUT_FILE=checkers/asm_test/out
DEMO_OUT_FILE=checkers/asm_test/out_demo

ERRORS_REPORT=checkers/check_inputs_report.txt

print_ok()
{
	printf "${GREEN}%s${RESET}" "$1"
}

print_error()
{
	printf "${RED}%s${RESET}" "$1"
}

print_warning()
{
	printf "${YELLOW}%s${RESET}" "$1"
}

run_all_tests()
{
  for file in `find ${CHAMPS_DIR} -type f -name "*.s"`
  do
    local name=`echo ${file%%.s} | cut -d'/' -f4`
    ${ASM_EXEC} ${file} > ${ASM_OUTPUT}
    local asm_out=`sed '1s/^..........//' ${ASM_OUTPUT}`
    echo ${asm_out} > ${ASM_OUTPUT}
    mkdir -p ${ASM_OUT_FILE}
    mv -f ${CHAMPS_DIR}/${name}.cor ${ASM_OUT_FILE}/${name}.cor
    ${DEMO_ASM_EXEC} ${file} > ${DEMO_OUTPUT}
    mkdir -p ${DEMO_OUT_FILE}
    mv -f ${CHAMPS_DIR}/${name}.cor ${DEMO_OUT_FILE}/${name}.cor
    local output=`diff -ibB ${ASM_OUTPUT} ${DEMO_OUTPUT}`
    local diff_files=`diff -ibB ${ASM_OUT_FILE}/${name}.cor ${DEMO_OUT_FILE}/${name}.cor`
    printf "%-65s" "$file"
    printf "diff for output files "
    if [ "$diff_files" = "" ]; then
      print_ok "OK "
    else
      print_error "KO "
    fi
    printf ": diff for output "
    if [ "$output" = "" ]; then
      print_ok "OK"
    else
      print_error "KO"
      echo  "$file" >>  ${ERRORS_REPORT}
      echo  "\n" >>  ${ERRORS_REPORT}
      echo  "$output" >>  ${ERRORS_REPORT}
      echo  "\n" >>  ${ERRORS_REPORT}
      echo "----------------------\n" >>  ${ERRORS_REPORT}
    fi
    printf "\n"
  done
}

print_usage_and_exit()
{
	printf "%s\n" "Usage: ./check_errors.sh exec"
	printf "%s\n" "  -exec   Path to executable"
	exit
}

if [ $# -ne 1 ];then
	print_usage_and_exit
	exit
fi

if [ ! -f $1 ];then
	printf "%s\n" "Executable ($1) not found"
	exit
fi

echo "" > ${ERRORS_REPORT}

run_all_tests

rm $ASM_OUTPUT
rm $DEMO_OUTPUT
