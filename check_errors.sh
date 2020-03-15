#!/bin/bash

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
RESET="\x1b[0m"

COREWAR_EXEC=$1

CHAMP_PATH=checkers/champs/
INPUT_DATA=checkers/data_error.txt

TEST_TMP=test_temp

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

run_test()
{
	local name=`echo $@ | cut -d';' -f1`
	local input=`echo $@ | cut -d';' -f2`

	printf "%-50s" "$name"
  ${COREWAR_EXEC} "${input}" > /dev/null 2> ${TEST_TMP}
  local output=`cat -e ${TEST_TMP}`
  if [ "${output:0:5}" = "Error" ]; then
    print_ok "Good!"
  else
    print_error "Booo!"
  fi
  printf "%5s%-60s" "" "`cat -e ${TEST_TMP}`"
	printf "\n"
}

run_all_tests()
{
	while read line
	do
		run_test ${line}
	done < ${INPUT_DATA}
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

run_all_tests

rm $TEST_TMP
