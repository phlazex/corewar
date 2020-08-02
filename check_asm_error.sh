#!/bin/bash

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
RESET="\x1b[0m"
BLUE="\e[0;34m"

ASM_EXEC=$1
#DEMO_ASM_EXEC=./demo/linux/asm
DEMO_ASM_EXEC=./demo/vm_champs/asm

CHAMPS_DIR=checkers/asm_test/error_champs

ASM_OUTPUT=test_temp_asm
DEMO_OUTPUT=test_temp_demo

ERRORS_REPORT=checkers/check_asm_report.txt

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
    printf "Launching ${BLUE}./asm${RESET} with flag ${BLUE}-asm${RESET} and ${BLUE}./demo_asm${RESET} for file ${BLUE}$file${RESET}\n"
    local name=`echo ${file%%.s} | cut -d'/' -f4`
    ${ASM_EXEC} ${file} > ${ASM_OUTPUT}
    printf "%-80sFile not created: "
    if test -f "${CHAMPS_DIR}/${name}.cor"; then
      print_error "KO"
    else
      print_ok "OK"
    fi
    printf "\n"
    local error=`sed '1s/^..........//' ${ASM_OUTPUT} | grep '^Error: .'`
    local logo=`sed '1s/^..........//' ${ASM_OUTPUT} | grep 'ASSEMBLER TRANSLATOR v 1.0$'`
#    ${DEMO_ASM_EXEC} ${file} 2> ${DEMO_OUTPUT}
    ${DEMO_ASM_EXEC} ${file} > ${DEMO_OUTPUT}
    local output=`diff -ibB ${ASM_OUTPUT} ${DEMO_OUTPUT}`
    printf "%-80sError found: "
    if [ "$error" != "" -o "$logo" != "" ]; then
      print_ok "OK"
    else
      print_error "KO"
    fi
    printf "\n"
    echo "------------------------------------------" >> ${ERRORS_REPORT}
    echo "$file" >> ${ERRORS_REPORT}
    echo >> ${ERRORS_REPORT}
    echo "$output" >> ${ERRORS_REPORT}
    echo >> ${ERRORS_REPORT}
    echo "__________________________________________" >> ${ERRORS_REPORT}
    printf "\n"
  done
  printf "\n"
  printf "${BLUE}./asm${RESET} = ${YELLOW}${ASM_EXEC}${RESET}, ${BLUE}./demo_asm = ${YELLOW}${DEMO_ASM_EXEC}${RESET}\n"
  printf "\t${BLUE}-asm${RESET}\tTo convert assembler file to byte code\n"
}

print_usage_and_exit()
{
	printf "%s\n" "Usage: ./check_asm_error.sh exec"
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

rm -rf $ASM_OUTPUT
rm -rf $DEMO_OUTPUT
