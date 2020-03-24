#!/bin/bash

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
RESET="\x1b[0m"

COREWAR_EXEC=$1

CHAMP_PATH=checkers/champs_errors/
INPUT_DATA=checkers/data_error.txt
ERRORS_REPORT=checkers/check_errors_report.txt

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

	printf "%-60s" "$name"
  ${COREWAR_EXEC} ${input} > /dev/null 2> ${TEST_TMP}
  local output=`cat -e ${TEST_TMP}`
  if [ "${output:0:5}" = "Error" ]; then
    print_ok "Good!"
  else
    print_error "Booo!"
  fi
  printf "%5s%-60s" "" "`cat -e ${TEST_TMP}`"
	printf "\n"
}

run_tests_files()
{
  for file in `find ${CHAMP_PATH} -type f -name "*.cor"`
  do
    ${COREWAR_EXEC} ${file} > /dev/null 2> ${TEST_TMP}
    local output=`cat -e ${TEST_TMP}`
    printf "%-60s" "$file"
    if [ "${output:0:5}" = "Error" ]; then
      print_ok "Good!"
      printf "     %s" "$output"
    else
      print_error "Booo!"
      echo "$file" >>  ${ERRORS_REPORT}
      echo "\n" >>  ${ERRORS_REPORT}
      echo "$output" >>  ${ERRORS_REPORT}
      echo "\n" >>  ${ERRORS_REPORT}
      echo "_____\n" >>  ${ERRORS_REPORT}
    fi
    printf "\n"
  done
}

run_all_tests()
{
	while read line
	do
		run_test ${line}
	done < ${INPUT_DATA}

  printf "_____________________________\n\n"

  run_tests_files
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