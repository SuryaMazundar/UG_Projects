#!/bin/bash
# 1. Randomizes ./Numbers args.
# 2. Various flag combinations
# 3. Runs:
#      ./Numbers seed1 seed2 | ./sprog3 [flags] > ans.txt
#      ./Numbers seed1 seed2 | ./Prog3 [flags] > b.txt
#      diff ans.txt b.txt

# Make sure to remake the file!

test_case_number=0

# Flags
only_show_fails=false

for arg in "$@"; do
  if [ "$arg" = "-fail" ]; then
    only_show_fails=true
  fi
done

test_cases=(
    ""                                         
    "-verbose"
    "-unique"
    "-sorted"
    "-verbose -unique"
    "-verbose -sorted"
    "-unique -verbose"
    "-sorted -verbose"
    "-verbose -unique"
    "-verbose -sorted"
    "-gibberish"                     
    "-verbose -gibberish"       
    "-gibberish -unique"
    "-gibberish -sorted"
    "-verbose -unique -Don't -you -just -love -this -lab"   
    "-ad2uiee23"
    "e e e e e e e"                                    
)

# Loop over each flag test case.
for flags in "${test_cases[@]}"; do
    # range = {0, 1000}
    seed1=$(( RANDOM % 1001 ))
    seed2=$(( RANDOM % 1001 ))

    ((++test_case_number))

    # Pass each flag as separate args.
    read -r -a flag_args <<< "$flags"

    # Build the commands (for display purposes).
    cmd_sprog3="./Numbers $seed1 $seed2 | ./sprog3 ${flag_args[*]} > ans.txt"
    cmd_prog3="./Numbers $seed1 $seed2 | ./Prog3 ${flag_args[*]} > b.txt"

    # Execute commands capturing stdout and stderr separately.
    ./Numbers "$seed1" "$seed2" | ./sprog3 "${flag_args[@]}" > ans.txt 2> ans_err.txt
    ./Numbers "$seed1" "$seed2" | ./Prog3 "${flag_args[@]}" > b.txt 2> prog_err.txt

    # First, check if stdout outputs differ.
    if ! diff ans.txt b.txt > /dev/null; then
        echo -e "Test case ($test_case_number / ${#test_cases[@]})"
        echo "--------------------------------------------------"
        echo -e "Seeds: $seed1, $seed2 and flags: '$flags'\n"
        echo "Executing command for sprog3:"
        echo "$cmd_sprog3"
        echo "Executing command for Prog3:"
        echo -e "$cmd_prog3\n"
        echo -e "Result: Test \e[1m\e[1;31mFAILED\e[0m\e[0m for flags: '$flags', seeds: $seed1, $seed2"
        echo ""
        diff ans.txt b.txt
        echo ""
        echo "--------------------------------------------------"
        continue
    fi

    # If sprog3 outputs anything to stderr, then Prog3 must output the usage message.
    if [ -s ans_err.txt ]; then
        expected_usage="usage: ./Prog3 [-sorted|unique] [-verbose] < file.txt"
        actual_usage=$(cat prog_err.txt)
        if [ "$actual_usage" != "$expected_usage" ]; then
            echo -e "Test case ($test_case_number / ${#test_cases[@]})"
            echo "--------------------------------------------------"
            echo -e "Seeds: $seed1, $seed2 and flags: '$flags'\n"
            echo "Expected stderr from Prog3:"
            echo "$expected_usage"
            echo "Actual stderr from Prog3:"
            echo "$actual_usage"
            echo -e "\nResult: Test \e[1m\e[1;31mFAILED\e[0m\e[0m for flags: '$flags', seeds: $seed1, $seed2"
            echo "--------------------------------------------------"
            continue
        fi
    fi

    # If we get here, the test case passed.
    if [ "$only_show_fails" != "true" ]; then
        echo -e "\n"
        echo -e "Test case ($test_case_number / ${#test_cases[@]})"
        echo "--------------------------------------------------"
        echo -e "Result: Test \e[1m\e[1;32mPASSED\e[0m\e[0m for flags: '$flags', seeds: $seed1, $seed2"
        echo "--------------------------------------------------"
        echo -e "\n"
    fi
done
