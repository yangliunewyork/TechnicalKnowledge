#!/bin/sh
# Define a function to check running processes by user.
check_process() {
    echo "Checking number of process running by user $1 ..."
    PROCESS_NUM=$(ps -ef | cut -d ' ' -f 1 | grep "$1" | grep -v "grep" | wc -l)
    echo "There are $PROCESS_NUM of process running by $1."
    if [ $PROCESS_NUM -ge 1 ];
    then
        return 1
    else
        return 0
    fi
}

# Run the function
check_process $1

exit 0
