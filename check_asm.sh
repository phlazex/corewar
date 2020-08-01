#!/bin/bash

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
RESET="\x1b[0m"
BLUE="\e[0;34m"

ASM_EXEC=$1
DEMO_ASM_EXEC=./demo/linux/asm
#DEMO_ASM_EXEC=./demo/vm_champs/asm

CHAMPS_DIR=checkers/asm_test/champs
DIFF_DIR=checkers/asm_test/out_diff

ASM_OUTPUT=test_temp_asm
DEMO_OUTPUT=test_temp_demo

ASM_OUT_FILE=checkers/asm_test/out
DEMO_OUT_FILE=checkers/asm_test/out_demo

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
    hexdump -vC ${ASM_OUT_FILE}/${name}.cor > ${ASM_OUTPUT}
    hexdump -vC ${DEMO_OUT_FILE}/${name}.cor > ${DEMO_OUTPUT}
    local diff_hexdump=`diff -ibB ${ASM_OUTPUT} ${DEMO_OUTPUT}`
    printf "Launching ${BLUE}./asm${RESET} and ${BLUE}./demo_asm${RESET} with flag ${BLUE}-asm${RESET} for file ${BLUE}$file${RESET}\n"
    printf "Output files: ${BLUE}${ASM_OUT_FILE}/${name}.cor${RESET} and ${BLUE}${DEMO_OUT_FILE}/${name}.cor${RESET}\n"
    printf "%-21sDiff for output: "
    if [ "$output" = "" ]; then
      print_ok "OK"
    else
      print_error "KO"
      echo "------------------------------------------" >> ${ERRORS_REPORT}
      echo "$file" >> ${ERRORS_REPORT}
      echo >> ${ERRORS_REPORT}
      echo "$output" >> ${ERRORS_REPORT}
      echo >> ${ERRORS_REPORT}
      echo "__________________________________________" >> ${ERRORS_REPORT}
    fi
    printf " / Diff for output files: "
    if [ "$diff_files" = "" ]; then
      print_ok "OK"
    else
      print_error "KO"
    fi
    printf " / Diff for hexdump files: "
    if [ "$diff_hexdump" = "" ]; then
      print_ok "OK"
    else
      print_error "KO"
    fi
    printf "\n"
    ${ASM_EXEC} ${ASM_OUT_FILE}/${name}.cor > ${ASM_OUTPUT}
    local asm_out=`sed '1s/^..........//' ${ASM_OUTPUT}`
    echo ${asm_out} > ${ASM_OUTPUT}
    ${DEMO_ASM_EXEC} ${DEMO_OUT_FILE}/${name}.cor > ${DEMO_OUTPUT}
    local output=`diff -ibB ${ASM_OUTPUT} ${DEMO_OUTPUT}`
    local diff_files=`diff -ibB ${ASM_OUT_FILE}/${name}.s ${DEMO_OUT_FILE}/${name}.s`
    hexdump -vC ${ASM_OUT_FILE}/${name}.s > ${ASM_OUTPUT}
    hexdump -vC ${DEMO_OUT_FILE}/${name}.s > ${DEMO_OUTPUT}
    local diff_hexdump=`diff -ibB ${ASM_OUTPUT} ${DEMO_OUTPUT}`
    printf "Launching ${BLUE}./asm${RESET} and ${BLUE}./demo_asm${RESET} with flag ${BLUE}-dis${RESET} for output files\n"
    printf "New output files: ${BLUE}${ASM_OUT_FILE}/${name}.s${RESET} and ${BLUE}${DEMO_OUT_FILE}/${name}.s${RESET}\n"
    echo "------------------------------------------" >> ${ERRORS_REPORT}
    echo "${ASM_OUT_FILE}/${name}.cor, ${DEMO_OUT_FILE}/${name}.cor" >> ${ERRORS_REPORT}
    echo >> ${ERRORS_REPORT}
    echo "$output" >> ${ERRORS_REPORT}
    echo >> ${ERRORS_REPORT}
    echo "__________________________________________" >> ${ERRORS_REPORT}
    printf "%-43sDiff for output files: "
    if [ "$diff_files" = "" ]; then
      print_ok "OK"
    else
      print_error "KO"
    fi
    printf " / Diff for hexdump files: "
    if [ "$diff_hexdump" = "" ]; then
      print_ok "OK"
    else
      print_error "KO"
    fi
    printf "\n\n"
  done
  printf "${BLUE}./asm${RESET} = ${YELLOW}${ASM_EXEC}${RESET}, ${BLUE}./demo_asm = ${YELLOW}${DEMO_ASM_EXEC}${RESET}\n"
  printf "\t${BLUE}-asm${RESET}\tTo convert assembler file to byte code\n"
  printf "\t${BLUE}-dis${RESET}\tTo convert byte code to assembler file\n"
}

print_usage_and_exit()
{
	printf "%s\n" "Usage: ./check_asm.sh exec"
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
