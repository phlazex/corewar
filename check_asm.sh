#!/bin/bash

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
RESET="\x1b[0m"

ASM_EXEC=$1
#DEMO_COREWAR_EXEC=./checkers/demo_corewar

CHAMPS_DIR=checkers/asm_test/champs
DIFF_DIR=checkers/asm_test/out

TEST_TMP=test_temp_my
#DEMO_OUTPUT=test_temp_demo

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
    local name=`echo ${file%%.*} | cut -d'/' -f4`
    ${ASM_EXEC} ${file} > ${TEST_TMP}
   # ${DEMO_COREWAR_EXEC} ${file} > /dev/null 2> ${DEMO_OUTPUT}
   # ${DEMO_COREWAR_EXEC} ${file} > checkers/diff_files/${name}.txt
    local output=`diff -ibB ${TEST_TMP} ${DIFF_DIR}/${name}.txt`
    local diff_files=`diff -ibB ${CHAMPS_DIR}/${name}.cor ${CHAMPS_DIR}/${name}.cor_new`
    printf "%-65s" "$file"
    printf ": "
    if [ "$diff_files" = "" ]; then
      print_ok "Out OK! : "
    else
      print_error "WTF man!!"
    fi
    if [ "$output" = "" ]; then
      print_ok "Good!"
    else
      print_error "Booo!"
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

rm $TEST_TMP
#rm $DEMO_OUTPUT
