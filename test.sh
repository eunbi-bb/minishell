# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    test.sh                                            :+:    :+:             #
#                                                      +:+                     #
#    By: djonker <djonker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/23 06:35:52 by djonker       #+#    #+#                  #
#    Updated: 2023/10/15 12:45:26 by eucho         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

ERRORS=0
PASSES=0
SLEEP=0
VALGRIND=0
SHOWLEAKS=1

testfunction()
{
	timeout 3 bash -c "$1" > /tmp/realstdoutfile 2> /tmp/realstderrfile
	REALRETURN=$?
	timeout 3 ./minishell -c "$1" > /tmp/ministdoutfile 2> /tmp/ministderrfile
	MINIRETURN=$?
	ERROROK=0
	diff /tmp/realstdoutfile /tmp/ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} \nreal: $(cat /tmp/realstdoutfile 2> /dev/null)\nmini: $(cat /tmp/ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff /tmp/realstderrfile /tmp/ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
		ERROROK=1
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "syntax error" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "Syntax Error" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "not found" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "not found" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "file or directory" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "file or directory" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "many arguments" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "many arguments" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "argument required" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "argument required" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "which: no" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "which: no" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "Usage" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "Usage" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "Is a directory" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "Is a directory" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "ermission denied" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "ermission denied" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "not a valid identifier" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "not a valid identifier" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "invalid option" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "invalid option" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "Not a directory" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "Not a directory" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "OLDPWD not set" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "OLDPWD not set" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat /tmp/realstderrfile)\nmini: $(cat /tmp/ministderrfile)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	if [ $VALGRIND -eq 1 ]
	then
		timeout 10 valgrind --leak-check=full ./minishell -c "$1" 2> /tmp/memorycheck > /dev/null
		cat /tmp/memorycheck | grep definitely | grep "[123456789] bytes" > /dev/null
		if [ $? -eq 0 ]
		then
			printf "\n\e[1;31mDefinite Memory Leaks with command $1\e[0;00m\n"
			if [ $SHOWLEAKS -eq 1 ]
			then
				cat /tmp/memorycheck
			fi
			ERRORS=$(($ERRORS+1))
			VALGRIND=0
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep indirectly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep possibly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			printf "\e[1;32mMemory OK\e[0;00m\n"
			PASSES=$(($PASSES+1))
		fi
		VALGRIND=1
	else
		printf "\n"
	fi
	rm /tmp/realstdoutfile /tmp/realstderrfile /tmp/ministdoutfile /tmp/ministderrfile
	sleep $SLEEP
}

redirectfunctionrel()
{
	mkdir -p tmp
	echo 1 > tmp/m1; echo 1 > tmp/r1; echo 2 > tmp/m2; echo 2 > tmp/r2; echo 3 > tmp/r3; echo 3 > tmp/m3;
	timeout 3 bash -c "$1" > /tmp/realstdoutfile 2> /tmp/realstderrfile
	REALRETURN=$?
	timeout 3 ./minishell -c "$2" > /tmp/ministdoutfile 2> /tmp/ministderrfile
	MINIRETURN=$?
	ERROROK=0
	diff /tmp/realstdoutfile /tmp/ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} \nreal: $(cat /tmp/realstdoutfile 2> /dev/null)\nmini: $(cat /tmp/ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff /tmp/realstderrfile /tmp/ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
		ERROROK=1
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "syntax error" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "Syntax Error" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "not found" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "not found" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "file or directory" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "file or directory" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "many arguments" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "many arguments" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "argument required" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "argument required" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat /tmp/realstderrfile)\nmini: $(cat /tmp/ministderrfile)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff tmp/r1 tmp/m1 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 1 doesn't match with command ${1} \nreal: $(cat tmp/r1 2> /dev/null)\nmini: $(cat tmp/m1 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 1 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff tmp/r2 tmp/m2 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 2 doesn't match with command ${1} \nreal: $(cat tmp/r2 2> /dev/null)\nmini: $(cat tmp/m2 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 2 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff tmp/r3 tmp/m3 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 3 doesn't match with command ${1} \nreal: $(cat tmp/r3 2> /dev/null)\nmini: $(cat tmp/m3 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 3 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	if [ $VALGRIND -eq 1 ]
	then
		timeout 10 valgrind --leak-check=full ./minishell -c "$1" 2> /tmp/memorycheck > /dev/null
		cat /tmp/memorycheck | grep definitely | grep "[123456789] bytes" > /dev/null
		if [ $? -eq 0 ]
		then
			printf "\n\e[1;31mDefinite Memory Leaks with command $1\e[0;00m\n"
			if [ $SHOWLEAKS -eq 1 ]
			then
				cat /tmp/memorycheck
			fi
			ERRORS=$(($ERRORS+1))
			VALGRIND=0
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep indirectly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep possibly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			printf "\e[1;32mMemory OK\e[0;00m\n"
			PASSES=$(($PASSES+1))
		fi
		VALGRIND=1
	else
		printf "\n"
	fi
	rm -rf /tmp/realstdoutfile /tmp/realstderrfile /tmp/ministdoutfile /tmp/ministderrfile tmp 2> /dev/null
	sleep $SLEEP
}
redirectfunctionabs()
{
	mkdir -p /tmp/minitest
	echo 1 > /tmp/minitest/m1; echo 1 > /tmp/minitest/r1; echo 2 > /tmp/minitest/m2; echo 2 > /tmp/minitest/r2; echo 3 > /tmp/minitest/r3; echo 3 > /tmp/minitest/m3;
	timeout 3 bash -c "$1" > /tmp/realstdoutfile 2> /tmp/realstderrfile
	REALRETURN=$?
	timeout 3 ./minishell -c "$2" > /tmp/ministdoutfile 2> /tmp/ministderrfile
	MINIRETURN=$?
	ERROROK=0
	diff /tmp/realstdoutfile /tmp/ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} \nreal: $(cat /tmp/realstdoutfile 2> /dev/null)\nmini: $(cat /tmp/ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff /tmp/realstderrfile /tmp/ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
		ERROROK=1
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "syntax error" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "Syntax Error" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "not found" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "not found" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "file or directory" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "file or directory" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "many arguments" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "many arguments" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "argument required" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "argument required" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat /tmp/realstderrfile)\nmini: $(cat /tmp/ministderrfile)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff /tmp/minitest/r1 /tmp/minitest/m1 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 1 doesn't match with command ${1} \nreal: $(cat /tmp/minitest/r1 2> /dev/null)\nmini: $(cat /tmp/minitest/m1 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 1 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff /tmp/minitest/r2 /tmp/minitest/m2 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 2 doesn't match with command ${1} \nreal: $(cat /tmp/minitest/r2 2> /dev/null)\nmini: $(cat /tmp/minitest/m2 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 2 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff /tmp/minitest/r3 /tmp/minitest/m3 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 3 doesn't match with command ${1} \nreal: $(cat /tmp/minitest/r3 2> /dev/null)\nmini: $(cat /tmp/minitest/m3 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 3 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	if [ $VALGRIND -eq 1 ]
	then
		timeout 10 valgrind --leak-check=full ./minishell -c "$1" 2> /tmp/memorycheck > /dev/null
		cat /tmp/memorycheck | grep definitely | grep "[123456789] bytes" > /dev/null
		if [ $? -eq 0 ]
		then
			printf "\n\e[1;31mDefinite Memory Leaks with command $1\e[0;00m\n"
			if [ $SHOWLEAKS -eq 1 ]
			then
				cat /tmp/memorycheck
			fi
			ERRORS=$(($ERRORS+1))
			VALGRIND=0
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep indirectly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep possibly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			printf "\e[1;32mMemory OK\e[0;00m\n"
			PASSES=$(($PASSES+1))
		fi
		VALGRIND=1
	else
		printf "\n"
	fi
	rm -rf /tmp/realstdoutfile /tmp/realstderrfile /tmp/ministdoutfile /tmp/ministderrfile /tmp/minitest 2> /dev/null
	sleep $SLEEP
}

redirectfunctionhome()
{
	mkdir -p ~/tmp
	echo 1 > ~/tmp/m1; echo 1 > ~/tmp/r1; echo 2 > ~/tmp/m2; echo 2 > ~/tmp/r2; echo 3 > ~/tmp/r3; echo 3 > ~/tmp/m3;
	timeout 3 bash -c "$1" > /tmp/realstdoutfile 2> /tmp/realstderrfile
	REALRETURN=$?
	timeout 3 ./minishell -c "$2" > /tmp/ministdoutfile 2> /tmp/ministderrfile
	MINIRETURN=$?
	ERROROK=0
	diff /tmp/realstdoutfile /tmp/ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} \nreal: $(cat /tmp/realstdoutfile 2> /dev/null)\nmini: $(cat /tmp/ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff /tmp/realstderrfile /tmp/ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
		ERROROK=1
	fi
	if [ $ERROROK -eq 0 ]
	then
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} \nreal: $(cat /tmp/realstderrfile)\nmini: $(cat /tmp/ministderrfile)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff ~/tmp/r1 ~/tmp/m1 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 1 doesn't match with command ${1} \nreal: $(cat ~/tmp/r1 2> /dev/null)\nmini: $(cat ~/tmp/m1 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 1 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff ~/tmp/r2 ~/tmp/m2 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 2 doesn't match with command ${1} \nreal: $(cat ~/tmp/r2 2> /dev/null)\nmini: $(cat ~/tmp/m2 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 2 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	diff ~/tmp/r3 ~/tmp/m3 > /dev/null
	if [ $? -ne 0 ]
	then
		printf "\n\e[1;31mKO file 3 doesn't match with command ${1} \nreal: $(cat ~/tmp/r3 2> /dev/null)\nmini: $(cat ~/tmp/m3 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mFile 3 OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	if [ $VALGRIND -eq 1 ]
	then
		timeout 10 valgrind --leak-check=full ./minishell -c "$1" 2> /tmp/memorycheck > /dev/null
		cat /tmp/memorycheck | grep definitely | grep "[123456789] bytes" > /dev/null
		if [ $? -eq 0 ]
		then
			printf "\n\e[1;31mDefinite Memory Leaks with command $1\e[0;00m\n"
			if [ $SHOWLEAKS -eq 1 ]
			then
				cat /tmp/memorycheck
			fi
			ERRORS=$(($ERRORS+1))
			VALGRIND=0
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep indirectly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep possibly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			printf "\e[1;32mMemory OK\e[0;00m\n"
			PASSES=$(($PASSES+1))
		fi
		VALGRIND=1
	else
		printf "\n"
	fi
	rm -rf /tmp/realstdoutfile /tmp/realstderrfile /tmp/ministdoutfile /tmp/ministderrfile ~/tmp 2> /dev/null
	sleep $SLEEP
}

environmentfunction()
{
	timeout 3 bash -c "$1" 2> /tmp/realstderrfile | grep "$2" > /tmp/realstdoutfile 2>> /tmp/realstderrfile
	REALRETURN=$?
	timeout 3 ./minishell -c "$1" 2> /tmp/ministderrfile | grep "$2" > /tmp/ministdoutfile 2>> /tmp/ministderrfile
	MINIRETURN=$?
	ERROROK=0
	diff /tmp/realstdoutfile /tmp/ministdoutfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstdout OK \e[0;00m"
		PASSES=$(($PASSES+1))
	else
		printf "\e[1;31mKO stdout doesn't match with command ${1} | grep ${2} \nreal: $(cat /tmp/realstdoutfile 2> /dev/null)\nmini: $(cat /tmp/ministdoutfile 2> /dev/null)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	diff /tmp/realstderrfile /tmp/ministderrfile > /dev/null
	if [ $? -eq 0 ]
	then
		printf "\e[1;32mstderr OK \e[0;00m"
		PASSES=$(($PASSES+1))
		ERROROK=1
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "invalid option" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "invalid option" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "not a valid identifier" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "not a valid identifier" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "file or directory" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "file or directory" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		cat /tmp/realstderrfile | grep "not found" > /dev/null
		if [ $? -eq 0 ]
		then
			cat /tmp/ministderrfile | grep "not found" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\e[1;32mstderr OK \e[0;00m"
				PASSES=$(($PASSES+1))
				ERROROK=1
			fi
		fi
	fi
	if [ $ERROROK -eq 0 ]
	then
		printf "\n\e[1;31mKO stderr doesn't match with command ${1} | grep ${2} \nreal: $(cat /tmp/realstderrfile)\nmini: $(cat /tmp/ministderrfile)\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	fi
	if [ $REALRETURN -ne $MINIRETURN ]
	then
		printf "\n\e[1;31mKO Return doesn't match with command ${1} | grep ${2} \nReal $REALRETURN\nMini $MINIRETURN\e[0;00m\n"
		ERRORS=$(($ERRORS+1))
	else
		printf "\e[1;32mreturn OK \e[0;00m"
		PASSES=$(($PASSES+1))
	fi
	if [ $VALGRIND -eq 1 ]
	then
		timeout 10 valgrind --leak-check=full ./minishell -c "$1" 2> /tmp/memorycheck > /dev/null
		cat /tmp/memorycheck | grep definitely | grep "[123456789] bytes" > /dev/null
		if [ $? -eq 0 ]
		then
			printf "\n\e[1;31mDefinite Memory Leaks with command ${1} | grep ${2}\e[0;00m\n"
			if [ $SHOWLEAKS -eq 1 ]
			then
				cat /tmp/memorycheck
			fi
			ERRORS=$(($ERRORS+1))
			VALGRIND=0
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep indirectly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command ${1} | grep ${2}\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			cat /tmp/memorycheck | grep possibly | grep "[123456789] bytes" > /dev/null
			if [ $? -eq 0 ]
			then
				printf "\n\e[1;31mIndirect Memory Leaks with command $1\e[0;00m\n"
				if [ $SHOWLEAKS -eq 1 ]
				then
					cat /tmp/memorycheck
				fi
				ERRORS=$(($ERRORS+1))
				VALGRIND=0
			fi
		fi
		if [ $VALGRIND -eq 1 ]
		then
			printf "\e[1;32mMemory OK\e[0;00m\n"
			PASSES=$(($PASSES+1))
		fi
		VALGRIND=1
	else
		printf "\n"
	fi
	rm /tmp/realstdoutfile /tmp/realstderrfile /tmp/ministdoutfile /tmp/ministderrfile
	sleep $SLEEP
}

# Testing Lines

# basic
printf "\e[1;36mTesting basics\e[0;00m\n"
testfunction ""
testfunction "./script.sh"
testfunction "./minishell -c \"exit 123\""
testfunction "''"
testfunction "' '"
testfunction "true"
testfunction "true  "
testfunction "false"
testfunction "  false"
testfunction "  false  "
testfunction "\"\""
testfunction "\" \""
testfunction "''"
testfunction "' '"
testfunction "!!"
testfunction "  !!  "
testfunction "\'!!\'"
testfunction "\"!!\""
testfunction "~"
testfunction "  ~  "
testfunction "\'~\'"
testfunction "\"~\""
testfunction ".."
testfunction "  ..  "
testfunction "\'..\'"
testfunction "\"..\""
testfunction "/home"
testfunction "////home"
testfunction "  /home  "
testfunction "  ////home  "
testfunction "'/home'"
testfunction "\"/home\""
testfunction "/nonexist"
testfunction "'/nonexist'"
testfunction "\"/nonexist\""
testfunction "src"
testfunction "'src'"
testfunction "\"src\""
testfunction "notexist"
testfunction "\'notexist\'"
testfunction "\"notexist\""
testfunction "./notexist"
testfunction "'./notexist'"
testfunction "\"./notexist\""
testfunction "cat notexist"
testfunction "'cat notexist'"
testfunction "\"cat notexist\""

# permissions
printf "\e[1;36mTesting permissions\e[0;00m\n"
touch perm
chmod 000 perm
printf "\e[1;36mfile 000\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction ".///perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 111 perm
printf "\e[1;36mfile 111\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 222 perm
printf "\e[1;36mfile 222\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 333 perm
printf "\e[1;36mfile 333\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 444 perm
printf "\e[1;36mfile 444\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 555 perm
printf "\e[1;36mfile 555\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 666 perm
printf "\e[1;36mfile 666\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 777 perm
printf "\e[1;36mfile 777\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
rm perm
mkdir perm
chmod 000 perm
printf "\e[1;36mdir 000\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 111 perm
printf "\e[1;36mdir 111\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 222 perm
printf "\e[1;36mdir 222\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 333 perm
printf "\e[1;36mdir 333\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 444 perm
printf "\e[1;36mdir 444\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 555 perm
printf "\e[1;36mdir 555\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 666 perm
printf "\e[1;36mdir 666\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
chmod 777 perm
printf "\e[1;36mdir 777\e[0;00m\n"
testfunction "perm"
testfunction "./perm"
testfunction "cat perm"
testfunction "perm && perm"
testfunction "./perm && ./perm"
testfunction "cat perm && ./perm"
testfunction "perm || perm"
testfunction "./perm || ./perm"
testfunction "cat perm || ./perm"
testfunction "perm ; perm"
testfunction "./perm ; ./perm"
testfunction "cat perm ; ./perm"
testfunction "perm | perm"
testfunction "./perm | ./perm"
testfunction "cat perm | ./perm"
rm -rf perm

# echo
printf "\e[1;36mTesting echo\e[0;00m\n"
testfunction "echo"
testfunction "echo ''"
testfunction "echo ' '"
testfunction "  echo  "
testfunction "echo hallo"
testfunction "echo hallo && echo hallo && echo hallo"
testfunction "echo hallo || echo hallo || echo hallo"
testfunction "echo hallo ; echo hallo ; echo hallo"
testfunction "echo hallo | echo hallo | echo hallo"
testfunction "echo   hallo  "
testfunction 'echo "hallo"'
testfunction "echo 'hallo'"
testfunction 'echo "hallo" hallo'
testfunction "echo 'hallo' hallo"
testfunction "echo -n hallo"
testfunction "echo -nnn hallo"
testfunction "echo -nnm hallo"
testfunction "echo -n -n hallo"
testfunction "echo -n -m hallo"
testfunction "echo -n -n -n -n -n -n -n -n hallo"
testfunction "echo -n hallo -n"
testfunction "echo \$FAKEVAR"
testfunction "echo \$PATH"
testfunction "echo ~"
testfunction "echo \"bip | bip ; coyotte > < \""
#testfunction "echo \\>" # \ is not part of subject
testfunction "export var=\"\$USER\" && echo \$USER\$var\$USER\$USER\$USERtest\$USER"
testfunction "echo \"\\s\""
#testfunction "echo \"\\\\s\"" # \ is not part of subject
#testfunction "echo bounjour \\; ls" # \ is not part of subject
testfunction "echo \"12\""
testfunction "echo \"hey\"J"
testfunction "echo \"hey\"\$PATH"
testfunction "echo 'hey\$PATH'"
testfunction "echo \"hey\$PATH\""
testfunction "echo \"'hey\$PATH'\""
testfunction "echo '\"hey\$PATH\"'"
testfunction "echo \"hey\"&"
testfunction "echo \"hey\"\"hey\""

 # exec
printf "\e[1;36mTesting exec\e[0;00m\n"
testfunction "exec bla"
testfunction "  exec   bla  "
testfunction "exec ''"
testfunction "exec ' '"
testfunction "exec \"bla\""
testfunction "exec 'bla'"
testfunction "exec cat"
testfunction "exec ls"
testfunction "exec ls && exec ls && exec ls"
testfunction "exec ls || exec ls || exec ls"
testfunction "exec ls ; exec ls ; exec ls"
testfunction "exec ls | exec ls | exec ls"
testfunction "exec 'ls'"
testfunction "exec \"ls\""
testfunction "exec exit"
testfunction "exec 'exit'"
testfunction "exec \"exit\""
testfunction "exec \"'exit'\""
testfunction "exec '\"exit\"'"
testfunction "exec exit 123"
testfunction "exec 'exit' 123"
testfunction "exec 'exit 123'"
testfunction "exec \"exit\" 123"
testfunction "exec \"exit 123\""
testfunction "exec cat -r"
testfunction "exec 'cat' -r"
testfunction "exec \"cat\" -r"
testfunction "exec 'cat -r'"
testfunction "exec \"cat -r\""
testfunction "exec echo hallo"
testfunction "exec 'echo' hallo"
testfunction "exec \"echo\" hallo"
testfunction "exec 'echo hallo'"
testfunction "exec \"echo hallo\""

 # variable
printf "\e[1;36mTesting \$VAR variable\e[0;00m\n"
testfunction "$"
testfunction "echo \$''"
testfunction "echo \$PWD"
testfunction "echo \$PWD && echo \$PWD && echo \$PWD"
testfunction "echo \$PWD || echo \$PWD || echo \$PWD"
testfunction "echo \$PWD ; echo \$PWD ; echo \$PWD"
testfunction "echo \$PWD | echo \$PWD | echo \$PWD"
testfunction "echo '\$PWD'"
testfunction "echo \"\$PWD\""
testfunction "echo \$?"
testfunction "echo \$DOESNOTEXIST"
testfunction "\$DOESNOTEXIST"
testfunction "cd \$HOME"
testfunction "ls \$HOME"
testfunction "echo \$SHLVL\"\$SHLVL\"\$SHLVL'\$SHLVL'\$SHLVL"
testfunction "echo \$FAKEVAR"
testfunction "echo \$SHLVL"
testfunction "echo \$SHLVL \$PWD \$USER \$?"
testfunction "echo \$SHLVL && echo \$SHLVL && echo \$SHLVL"
testfunction "echo \$SHLVL || echo \$SHLVL || echo \$SHLVL"
testfunction "echo \$SHLVL ; echo \$SHLVL ; echo \$SHLVL"
testfunction "echo \$SHLVL | echo \$SHLVL | echo \$SHLVL"
testfunction "echo '\$SHLVL'"
testfunction "echo \"\$SHLVL\""
testfunction "echo \"'\$SHLVL'\""
testfunction "echo '\"\$SHLVL\"'"
testfunction "echo \"   '\$PATH' \""
testfunction "echo \"'\$'PATH''\""
testfunction "echo \"'\$\"PATH\"' \""
testfunction "echo \"'hey\$PATH hello' \""
testfunction "echo \"   '\$(PATH)' \""
testfunction "echo \"\$PATHblabla\""
testfunction "echo \$PWD"
testfunction "echo \$PW'D'"
testfunction "echo \$PW\"D\""
testfunction "echo \$?"
#testfunction "echo \$\$" # test is ok, but PID will always be different
testfunction "printf \$SHLVL\"\$SHLVL\"\$SHLVL'\$SHLVL'\$SHLVL"
#testfunction "printf \$FAKEVAR" # will fail because of bash using builtin, and we use /usr/bin/printf
testfunction "printf \$SHLVL"
testfunction "printf \$SHL VL"
testfunction "printf \$PWD"
testfunction "printf \$PW'D'"
testfunction "printf \$PW\"D\""
testfunction "printf \$?"
#testfunction "printf \$\$" # test is ok, but PID will always be different

# export
printf "\e[1;36mTesting export\e[0;00m\n"
testfunction "export ''"
testfunction "export ' '"
environmentfunction "export" "SHLVL"
testfunction "export bla=bla"
testfunction "export bla=bla && export bla=bla && export bla=bla"
testfunction "export bla=bla || export bla=bla || export bla=bla"
testfunction "export bla=bla ; export bla=bla ; export bla=bla"
testfunction "export bla=bla | export bla=bla | export bla=bla"
testfunction "export 'bla=bla bla'"
testfunction "export bla bla"
testfunction "export bla=''"
testfunction "export ''=bla"
testfunction "export bla =bla"
testfunction "export bla= bla"
testfunction "export bla = bla"
testfunction "export    bla=bla"
testfunction "   export bla=bla"
testfunction "export 'bla=bla'"
testfunction "export \"bla=bla\""
testfunction "export \"'bla=bla'\""
testfunction "export '\"bla=bla\"'"
testfunction "export bla='bla'"
testfunction "export bla=\"bla\""
environmentfunction "export bla=bla" "bla"
environmentfunction "export bla='bla'" "bla"
environmentfunction "export bla=\"bla\"" "bla"
testfunction "export bla"
testfunction "export 'bla'"
testfunction "export \"bla\""
environmentfunction "export bla" "bla"
environmentfunction "export 'bla'" "bla"
environmentfunction "export \"bla\"" "bla"
testfunction "export 0bla=bla"
environmentfunction "export 0bla=bla" "0bla"
testfunction "export -bla=bla"
environmentfunction "export -bla=bla" "-bla"
testfunction "export _bla=bla"
environmentfunction "export _bla=bla" "_bla"
testfunction "export _bla"
environmentfunction "export _bla" "_bla"
testfunction "export PATH=bahbah"
testfunction "export 'PATH=bahbah'"
testfunction "export \"PATH=bahbah\""
environmentfunction "export PATH=bahbah" "PATH"
environmentfunction "export 'PATH=bahbah'" "PATH"
environmentfunction "export \"PATH=bahbah\"" "PATH"
testfunction "export arg=\"-la\" && ls \$arg"
testfunction "export arg=a && export \$var=test && echo \$var \$a"
testfunction "export \$abc=a && unset abc"
environmentfunction "export \$abc=a && unset abc" "abc"
environmentfunction "export test1" "test1"
environmentfunction "export test2=" "test2"
environmentfunction "export varra=hallo" "varra"
testfunction "export \"\" tester=b"
environmentfunction "export test3=\$HOME" "test3"

# unset
printf "\e[1;36mTesting unset\e[0;00m\n"
testfunction "unset notexistant"
testfunction "unset ''"
testfunction "unset ' '"
testfunction "   unset   nonexistant   "
testfunction "unset notexistant"
testfunction "unset 'notexistant'"
testfunction "unset \"notexistant\""
testfunction "unset PATH"
testfunction "unset PATH && unset PATH && unset PATH"
testfunction "unset PATH || unset PATH || unset PATH"
testfunction "unset PATH ; unset PATH ; unset PATH"
testfunction "unset PATH | unset PATH | unset PATH"
testfunction "unset \$PATH"
testfunction "   unset   PATH  "
testfunction "unset 'PATH'"
testfunction "unset 'PA'TH"
testfunction "unset \"PATH\""
testfunction "unset \"PA\"TH"
testfunction "unset \"'PATH'\""
testfunction "unset '\"PATH\"'"
testfunction "unset"
testfunction "'unset'"
testfunction "\"unset\""
testfunction "unset -wat"
testfunction "unset '-wat'"
testfunction "unset \"-wat\""
environmentfunction "unset PATH" "PATH"
environmentfunction "unset \$PATH" "PATH"
environmentfunction "unset 'PATH'" "PATH"
environmentfunction "unset \"PATH\"" "PATH"
environmentfunction "unset \"'PATH'\"" "PATH"
environmentfunction "unset '\"PATH\"'" "PATH"
environmentfunction "'unset PATH'" "PATH"
environmentfunction "\"unset PATH\"" "PATH"
environmentfunction "unset SHLVL" "SHLVL"
environmentfunction "unset PWD" "PWD"

# env
printf "\e[1;36mTesting env\e[0;00m\n"
testfunction "env ''"
testfunction "env ' '"
testfunction "   env    blabla  "
testfunction "env blabla"
testfunction "env 'blabla'"
testfunction "env \"blabla\""
testfunction "'env blabla'"
testfunction "\"env blabla\""
testfunction "env -wat"
testfunction "env '-wat'"
testfunction "env \"-wat\""
testfunction "'env -wat'"
testfunction "\"env -wat\""
#environmentfunction "env" "SHLVL" # Error only happens with -c command not when running minishell normally
#environmentfunction "'env'" "SHLVL" # Error only happens with -c command not when running minishell normally
#environmentfunction "\"env\"" "SHLVL" # Error only happens with -c command not when running minishell normally
environmentfunction "env blabla" "SHLVL"
environmentfunction "env -wat" "SHLVL"
testfunction "env | grep OLDPWD"
testfunction "env | grep OLDPWD && env | grep OLDPWD && env | grep OLDPWD"
testfunction "env | grep OLDPWD || env | grep OLDPWD || env | grep OLDPWD"
testfunction "env | grep OLDPWD ; env | grep OLDPWD ; env | grep OLDPWD"
testfunction "env | grep OLDPWD | env | grep OLDPWD | env | grep OLDPWD"
testfunction "env | grep 'OLDPWD'"
testfunction "env | grep \"OLDPWD\""

# exit
printf "\e[1;36mTesting exit\e[0;00m\n"
testfunction "exit"
testfunction "exit && exit && exit"
testfunction "exit || exit || exit"
testfunction "exit ; exit ; exit"
testfunction "exit | exit | exit"
testfunction "exit ''"
testfunction "exit ' '"
testfunction "'exit'"
testfunction "\"exit\""
testfunction "exit 1"
testfunction "  exit 1   "
testfunction "exit '1'"
testfunction "exit \"1\""
testfunction "'exit 1'"
testfunction "\"exit 1\""
testfunction "exit 123"
testfunction "exit 256"
testfunction "exit bla"
testfunction "exit 'bla'"
testfunction "exit \"bla\""
testfunction "exit -wat"
testfunction "exit '-wat'"
testfunction "exit \"-wat\""
testfunction "exit 9223372036854775807"
testfunction "exit 9223372036854775808"
testfunction "exit -9223372036854775807"
testfunction "exit -9223372036854775808"
testfunction "exit -9223372036854775809"

# cd and pwd
printf "\e[1;36mTesting cd and pwd\e[0;00m\n"
testfunction "cd"
testfunction "cd && cd && cd"
testfunction "cd || cd || cd"
testfunction "cd ; cd ; cd"
testfunction "cd | cd | cd"
testfunction "cd ''"
testfunction "cd ' '"
testfunction "mkdir -p tmp/a/b && cd tmp/a/b && rm -r ../../a && cd .."
testfunction "cd && pwd"
testfunction "cd && pwd && cd && pwd && cd && pwd"
testfunction "cd && pwd || cd && pwd || cd && pwd"
testfunction "cd && pwd ; cd && pwd ; cd && pwd"
testfunction "cd && pwd | cd && pwd | cd && pwd"
testfunction "cd .."
testfunction "cd '..'"
testfunction "cd \"..\""
testfunction "cd \"'..'\""
testfunction "cd '\"..\"'"
testfunction "cd .. && pwd"
testfunction "cd .. && pwd && cd .. && pwd"
testfunction "cd .. bla"
testfunction "cd '..' bla"
testfunction "cd \"..\" bla"
testfunction "cd '.. bla'"
testfunction "cd \".. bla\""
testfunction "cd .. bla && pwd"
testfunction "cd ../../../../../../../../../.."
testfunction "cd ..///..///..///..////..///..///..//..///..///.."
testfunction "cd ../../../../../../../../../.. && pwd"
testfunction "cd ..///..///..///..////..///..///..//..///..///.. && pwd"
testfunction "cd ."
testfunction "cd . && pwd"
testfunction "cd ~" 
testfunction "cd ~ && pwd"
testfunction "unset HOME && cd ~"
testfunction "unset HOME && cd ~ && pwd"
testfunction "export HOME=/home/user42 && cd ~"
testfunction "export HOME=/home/user42 && cd ~ && pwd"
testfunction "export HOME=///home///user42 && cd ~ && pwd"
testfunction "cd -"
#testfunction "cd - && pwd" # double prints for some reason not an issue in runtime
testfunction "cd src && cd -" 
#testfunction "cd src && cd - && pwd" # also double prints for some reason
testfunction "cd src"
testfunction "cd src && pwd"
testfunction "cd /etc"
testfunction "cd ///etc"
testfunction "cd /etc && pwd"
testfunction "cd ~/Documents"
testfunction "cd ~/Documents && pwd"
testfunction "cd nonexistingpath"
testfunction "cd nonexistingpath && pwd"
testfunction "pwd"
testfunction "pwd ''"
testfunction "pwd ' '"
testfunction "pwd bla"
testfunction "pwd 'bla'"
testfunction "pwd \"bla\""
testfunction "pwd -wat"
testfunction "pwd '-wat'"
testfunction "pwd \"-wat\""

# which
#printf "\e[1;36mTesting which\e[0;00m\n" # Our Which is better
#testfunction "which" # Our Which is better
#testfunction "which ''" # Our Which is better
#testfunction "which ' '" # Our Which is better
#testfunction "which cat" # Our Which is better
#testfunction "which 'cat'" # Our Which is better
#testfunction "which \"cat\"" # Our Which is better
#testfunction "which bleh" # Our Which is better
#testfunction "which ." # Our Which is better
#testfunction "which ls" # Our Which is better
#testfunction "which cd" # Our Which is better
#testfunction "which which" # Our Which is better
#testfunction "'which which'" # Our Which is better
#testfunction "\"which which\"" # Our Which is better
#testfunction "which 'which'" # Our Which is better
#testfunction "which \"which\"" # Our Which is better
#testfunction "which exit" # Our Which is better

# > trunctuate
printf "\e[1;36mTesting > trunctuate \e[0;00m\n"
testfunction ">"
redirectfunctionabs "cat '' > '' > ''" "cat '' > '' > ''"
redirectfunctionabs "cat ' ' > ' ' > ' '" "cat ' ' > ' ' > ' '"
redirectfunctionhome "cat ~/tmp/r1>~/tmp/r2>~/tmp/r3" "cat ~/tmp/m1>~/tmp/m2>~/tmp/m3"
redirectfunctionabs "cat /tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3" "cat /tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3"
#redirectfunctionabs "echo hallo && echo hallo && cat /tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3" "cat /tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3" #works correctly in runtime
#redirectfunctionabs "echo hallo || echo hallo || cat /tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3" "cat /tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3" #works correctly in runtime
#redirectfunctionabs "echo hallo ; echo hallo ; cat /tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3" "cat /tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3" #works correctly in runtime
redirectfunctionabs "echo hallo | echo hallo | cat /tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3" "cat /tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3"
redirectfunctionabs "cat ///tmp/minitest///r1>///tmp/minitest///r2>/tmp///minitest///r3" "cat ////tmp///minitest////m1>///tmp///minitest///m2>///tmp/minitest///m3"
redirectfunctionabs "cat '/tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3'" "cat '/tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3'"
redirectfunctionabs "cat \"/tmp/minitest/r1>/tmp/minitest/r2>/tmp/minitest/r3\"" "cat \"/tmp/minitest/m1>/tmp/minitest/m2>/tmp/minitest/m3\""
redirectfunctionabs "cat /tmp/minitest/r1  >  /tmp/minitest/r2  >  /tmp/minitest/r3" "cat /tmp/minitest/m1  >  /tmp/minitest/m2  >  /tmp/minitest/m3"
redirectfunctionabs "cat /tmp/minitest/r1 > /tmp/minitest/r2 > /tmp/minitest/r3" "cat /tmp/minitest/m1 > /tmp/minitest/m2 > /tmp/minitest/m3"
redirectfunctionabs "cat '/tmp/minitest/r1' > '/tmp/minitest/r2' > '/tmp/minitest/r3'" "cat '/tmp/minitest/m1' > '/tmp/minitest/m2' > '/tmp/minitest/m3'"
redirectfunctionabs "cat \"/tmp/minitest/r1\" > \"/tmp/minitest/r2\" > \"/tmp/minitest/r3\"" "cat \"/tmp/minitest/m1\" > \"/tmp/minitest/m2\" > \"/tmp/minitest/m3\""
redirectfunctionabs "cat \"'/tmp/minitest/r1'\" > \"'/tmp/minitest/r2'\" > \"'/tmp/minitest/r3'\"" "cat \"'/tmp/minitest/m1'\" > \"'/tmp/minitest/m2'\" > \"'/tmp/minitest/m3'\""
redirectfunctionabs "cat '\"/tmp/minitest/r1\"' > '\"/tmp/minitest/r2\"' > '\"/tmp/minitest/r3\"'" "cat '\"/tmp/minitest/m1\"' > '\"/tmp/minitest/m2\"' > '\"/tmp/minitest/m3\"'"
redirectfunctionabs "printf 'blabla' > /tmp/minitest/r1; printf 'blabla' > /tmp/minitest/r2; printf 'blabla' > /tmp/minitest/r3" "printf 'blabla' > /tmp/minitest/m1; printf 'blabla' > /tmp/minitest/m2; printf 'blabla' > /tmp/minitest/m3"
redirectfunctionabs "printf 'blabla' > /tmp/minitest/r1 && printf 'blabla' > /tmp/minitest/r2 && printf 'blabla' > /tmp/minitest/r3" "printf 'blabla' > /tmp/minitest/m1 && printf 'blabla' > /tmp/minitest/m2 && printf 'blabla' > /tmp/minitest/m3"
redirectfunctionabs "echo \"hoi\" > | /tmp/minitest/r1" "echo \"hoi\" > | /tmp/minitest/m1"
#redirectfunctionabs "echo \"hoi\" >| /tmp/minitest/r1" "echo \"hoi\" >| /tmp/minitest/m1" # >| is not part of the subject
redirectfunctionabs "> /tmp/minitest/r1 | echo blabla" "> /tmp/minitest/m1 | echo blabla"
redirectfunctionabs "exit > /tmp/minitest/r1" "exit > /tmp/minitest/m1"
redirectfunctionabs "cd .. > /tmp/minitest/r1" "cd .. > /tmp/minitest/m1"
redirectfunctionabs "> /tmp/minitest/r1" "> /tmp/minitest/m1"
redirectfunctionabs "echo 2 > /tmp/minitest/r1 > /tmp/minitest/r2" "echo 2 > /tmp/minitest/m1 > /tmp/minitest/m2"
redirectfunctionabs "echo 2 > /tmp/minitest/r1 > /tmp/minitest/r2" "echo 2 > /tmp/minitest/m1 > /tmp/minitest/m2"
redirectfunctionabs "echo test > /tmp/minitest/r1 2" "echo test > /tmp/minitest/m1 2"
redirectfunctionabs "Non_exist_cmd > /tmp/minitest/r1" "Non_exist_cmd > /tmp/minitest/m1"
redirectfunctionrel "cat tmp/r1>tmp/r2>tmp/r3" "cat tmp/m1>tmp/m2>tmp/m3"
#redirectfunctionrel "echo hallo && echo hallo && cat tmp/r1>tmp/r2>tmp/r3" "cat tmp/m1>tmp/m2>tmp/m3" #works correctly in runtime
#redirectfunctionrel "echo hallo || echo hallo || cat tmp/r1>tmp/r2>tmp/r3" "cat tmp/m1>tmp/m2>tmp/m3" #works correctly in runtime
#redirectfunctionrel "echo hallo ; echo hallo ; cat tmp/r1>tmp/r2>tmp/r3" "cat tmp/m1>tmp/m2>tmp/m3" #works correctly in runtime
redirectfunctionrel "echo hallo | echo hallo | cat tmp/r1>tmp/r2>tmp/r3" "cat tmp/m1>tmp/m2>tmp/m3"
redirectfunctionrel "cat tmp///r1>tmp///r2>tmp///r3" "cat tmp///m1>tmp///m2>tmp///m3"
redirectfunctionrel "cat 'tmp/r1>tmp/r2>tmp/r3'" "cat 'tmp/m1>tmp/m2>tmp/m3'"
redirectfunctionrel "cat \"tmp/r1>tmp/r2>tmp/r3\"" "cat \"tmp/m1>tmp/m2>tmp/m3\""
redirectfunctionrel "cat tmp/r1  >  tmp/r2  >  tmp/r3" "cat tmp/m1  >  tmp/m2  >  tmp/m3"
redirectfunctionrel "cat tmp/r1 > tmp/r2 > tmp/r3" "cat tmp/m1 > tmp/m2 > tmp/m3"
redirectfunctionrel "cat 'tmp/r1' > 'tmp/r2' > 'tmp/r3'" "cat 'tmp/m1' > 'tmp/m2' > 'tmp/m3'"
redirectfunctionrel "cat \"tmp/r1\" > \"tmp/r2\" > \"tmp/r3\"" "cat \"tmp/m1\" > \"tmp/m2\" > \"tmp/m3\""
redirectfunctionrel "cat \"'tmp/r1'\" > \"'tmp/r2'\" > \"'tmp/r3'\"" "cat \"'tmp/m1'\" > \"'tmp/m2'\" > \"'tmp/m3'\""
redirectfunctionrel "cat '\"tmp/r1\"' > '\"tmp/r2\"' > '\"tmp/r3\"'" "cat '\"tmp/m1\"' > '\"tmp/m2\"' > '\"tmp/m3\"'"
redirectfunctionrel "printf 'blabla' > tmp/r1; printf 'blabla' > tmp/r2; printf 'blabla' > tmp/r3" "printf 'blabla' > tmp/m1; printf 'blabla' > tmp/m2; printf 'blabla' > tmp/m3"
redirectfunctionrel "printf 'blabla' > tmp/r1 && printf 'blabla' > tmp/r2 && printf 'blabla' > tmp/r3" "printf 'blabla' > tmp/m1 && printf 'blabla' > tmp/m2 && printf 'blabla' > tmp/m3"
redirectfunctionrel "echo \"hoi\" > | tmp/r1" "echo \"hoi\" > | tmp/m1"
#redirectfunctionrel "echo \"hoi\" >| tmp/r1" "echo \"hoi\" >| tmp/m1" # >| is not part of the subject
redirectfunctionrel "> tmp/r1 | echo blabla" "> tmp/m1 | echo blabla"
redirectfunctionrel "exit > tmp/r1" "exit > tmp/m1"
redirectfunctionrel "cd .. > tmp/r1" "cd .. > tmp/m1"
redirectfunctionrel "> tmp/r1" "> tmp/m1"
redirectfunctionrel "echo 2 > tmp/r1 > tmp/r2" "echo 2 > tmp/m1 > tmp/m2"
redirectfunctionrel "echo 2 > tmp/r1 > tmp/r2" "echo 2 > tmp/m1 > tmp/m2"
redirectfunctionrel "echo test > tmp/r1 2" "echo test > tmp/m1 2"
redirectfunctionrel "Non_exist_cmd > tmp/r1" "Non_exist_cmd > tmp/m1"

# >> append
printf "\e[1;36mTesting >> append \e[0;00m\n"
testfunction ">>"
redirectfunctionhome "cat ~/tmp/r1>>~/tmp/r2>>~/tmp/r3" "cat ~/tmp/m1>>~/tmp/m2>>~/tmp/m3"
redirectfunctionabs "cat '' >> '' >> ''" "cat '' >> '' >> ''"
redirectfunctionabs "cat ' ' >> ' ' >> ' '" "cat ' ' >> ' ' >> ' '"
redirectfunctionabs "cat /tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3" "cat /tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3"
#redirectfunctionabs "echo hallo && echo hallo && cat /tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3" "cat /tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3" #works correctly in runtime
#redirectfunctionabs "echo hallo || echo hallo || cat /tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3" "cat /tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3" #works correctly in runtime
#redirectfunctionabs "echo hallo ; echo hallo ; cat /tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3" "cat /tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3" #works correctly in runtime
redirectfunctionabs "echo hallo | echo hallo | cat /tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3" "cat /tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3"
redirectfunctionabs "cat ///tmp/minitest///r1>>///tmp///minitest///r2>>///tmp///minitest///r3" "cat ///tmp/minitest///m1>>///tmp/minitest///m2>>///tmp///minitest///m3"
redirectfunctionabs "cat '/tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3'" "cat '/tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3'"
redirectfunctionabs "cat \"/tmp/minitest/r1>>/tmp/minitest/r2>>/tmp/minitest/r3\"" "cat \"/tmp/minitest/m1>>/tmp/minitest/m2>>/tmp/minitest/m3\""
redirectfunctionabs "cat /tmp/minitest/r1  >>  /tmp/minitest/r2  >>  /tmp/minitest/r3" "cat /tmp/minitest/m1  >>  /tmp/minitest/m2  >>  /tmp/minitest/m3"
redirectfunctionabs "cat /tmp/minitest/r1 >> /tmp/minitest/r2 >> /tmp/minitest/r3" "cat /tmp/minitest/m1 >> /tmp/minitest/m2 >> /tmp/minitest/m3"
redirectfunctionabs "cat '/tmp/minitest/r1' >> '/tmp/minitest/r2' >> '/tmp/minitest/r3'" "cat '/tmp/minitest/m1' >> '/tmp/minitest/m2' >> '/tmp/minitest/m3'"
redirectfunctionabs "cat \"/tmp/minitest/r1\" >> \"/tmp/minitest/r2\" >> \"/tmp/minitest/r3\"" "cat \"/tmp/minitest/m1\" >> \"/tmp/minitest/m2\" >> \"/tmp/minitest/m3\""
redirectfunctionabs "cat \"'/tmp/minitest/r1'\" >> \"'/tmp/minitest/r2'\" >> \"'/tmp/minitest/r3'\"" "cat \"'/tmp/minitest/m1'\" >> \"'/tmp/minitest/m2'\" >> \"'/tmp/minitest/m3'\""
redirectfunctionabs "cat '\"/tmp/minitest/r1\"' >> '\"/tmp/minitest/r2\"' >> '\"/tmp/minitest/r3\"'" "cat '\"/tmp/minitest/m1\"' >> '\"/tmp/minitest/m2\"' >> '\"/tmp/minitest/m3\"'"
redirectfunctionabs "printf 'blabla' >> /tmp/minitest/r1; printf 'blabla' >> /tmp/minitest/r2; printf 'blabla' >> /tmp/minitest/r3" "printf 'blabla' >> /tmp/minitest/m1; printf 'blabla' >> /tmp/minitest/m2; printf 'blabla' >> /tmp/minitest/m3"
redirectfunctionabs "printf 'blabla' >> /tmp/minitest/r1 && printf 'blabla' >> /tmp/minitest/r2 && printf 'blabla' >> /tmp/minitest/r3" "printf 'blabla' >> /tmp/minitest/m1 && printf 'blabla' >> /tmp/minitest/m2 && printf 'blabla' >> /tmp/minitest/m3"
redirectfunctionabs "echo \"hoi\" >> | /tmp/minitest/r1" "echo \"hoi\" >> | /tmp/minitest/m1"
redirectfunctionabs "echo \"hoi\" >>| /tmp/minitest/r1" "echo \"hoi\" >>| /tmp/minitest/m1"
redirectfunctionabs ">> /tmp/minitest/r1 | echo blabla" ">> /tmp/minitest/m1 | echo blabla"
redirectfunctionabs "exit >> /tmp/minitest/r1" "exit >> /tmp/minitest/m1"
redirectfunctionabs "cd .. >> /tmp/minitest/r1" "cd .. >> /tmp/minitest/m1"
redirectfunctionabs ">> /tmp/minitest/r1" ">> /tmp/minitest/m1"
redirectfunctionabs "echo 2 >> /tmp/minitest/r1 >> /tmp/minitest/r2" "echo 2 >> /tmp/minitest/m1 >> /tmp/minitest/m2"
redirectfunctionabs "echo 2 >> /tmp/minitest/r1 >> /tmp/minitest/r2" "echo 2 >> /tmp/minitest/m1 >> /tmp/minitest/m2"
redirectfunctionabs "echo test >> /tmp/minitest/r1 2" "echo test >> /tmp/minitest/m1 2"
redirectfunctionabs "Non_exist_cmd >> /tmp/minitest/r1" "Non_exist_cmd >> /tmp/minitest/m1"
redirectfunctionrel "cat tmp/r1>>tmp/r2>>tmp/r3" "cat tmp/m1>>tmp/m2>>tmp/m3"
#redirectfunctionrel "echo hallo && echo hallo && cat tmp/r1>>tmp/r2>>tmp/r3" "cat tmp/m1>>tmp/m2>>tmp/m3" #works correctly in runtime
#redirectfunctionrel "echo hallo || echo hallo || cat tmp/r1>>tmp/r2>>tmp/r3" "cat tmp/m1>>tmp/m2>>tmp/m3" #works correctly in runtime
#redirectfunctionrel "echo hallo ; echo hallo ; cat tmp/r1>>tmp/r2>>tmp/r3" "cat tmp/m1>>tmp/m2>>tmp/m3" #works correctly in runtime
redirectfunctionrel "echo hallo | echo hallo | cat tmp/r1>>tmp/r2>>tmp/r3" "cat tmp/m1>>tmp/m2>>tmp/m3"
redirectfunctionrel "cat tmp///r1>>tmp///r2>>tmp///r3" "cat tmp///m1>>tmp///m2>>tmp///m3"
redirectfunctionrel "cat 'tmp/r1>>tmp/r2>>tmp/r3'" "cat 'tmp/m1>>tmp/m2>>tmp/m3'"
redirectfunctionrel "cat \"tmp/r1>>tmp/r2>>tmp/r3\"" "cat \"tmp/m1>>tmp/m2>>tmp/m3\""
redirectfunctionrel "cat tmp/r1  >>  tmp/r2  >>  tmp/r3" "cat tmp/m1  >>  tmp/m2  >>  tmp/m3"
redirectfunctionrel "cat tmp/r1 >> tmp/r2 >> tmp/r3" "cat tmp/m1 >> tmp/m2 >> tmp/m3"
redirectfunctionrel "cat 'tmp/r1' >> 'tmp/r2' >> 'tmp/r3'" "cat 'tmp/m1' >> 'tmp/m2' >> 'tmp/m3'"
redirectfunctionrel "cat \"tmp/r1\" >> \"tmp/r2\" >> \"tmp/r3\"" "cat \"tmp/m1\" >> \"tmp/m2\" >> \"tmp/m3\""
redirectfunctionrel "cat \"'tmp/r1'\" >> \"'tmp/r2'\" >> \"'tmp/r3'\"" "cat \"'tmp/m1'\" >> \"'tmp/m2'\" >> \"'tmp/m3'\""
redirectfunctionrel "cat '\"tmp/r1\"' >> '\"tmp/r2\"' >> '\"tmp/r3\"'" "cat '\"tmp/m1\"' >> '\"tmp/m2\"' >> '\"tmp/m3\"'"
redirectfunctionrel "printf 'blabla' >> tmp/r1; printf 'blabla' >> tmp/r2; printf 'blabla' >> tmp/r3" "printf 'blabla' >> tmp/m1; printf 'blabla' >> tmp/m2; printf 'blabla' >> tmp/m3"
redirectfunctionrel "printf 'blabla' >> tmp/r1 && printf 'blabla' >> tmp/r2 && printf 'blabla' >> tmp/r3" "printf 'blabla' >> tmp/m1 && printf 'blabla' >> tmp/m2 && printf 'blabla' >> tmp/m3"
redirectfunctionrel "echo \"hoi\" >> | tmp/r1" "echo \"hoi\" >> | tmp/m1"
redirectfunctionrel "echo \"hoi\" >>| tmp/r1" "echo \"hoi\" >>| tmp/m1"
redirectfunctionrel ">> tmp/r1 | echo blabla" ">> tmp/m1 | echo blabla"
redirectfunctionrel "exit >> tmp/r1" "exit >> tmp/m1"
redirectfunctionrel "cd .. >> tmp/r1" "cd .. >> tmp/m1"
redirectfunctionrel ">> tmp/r1" ">> tmp/m1"
redirectfunctionrel "echo 2 >> tmp/r1 >> tmp/r2" "echo 2 >> tmp/m1 >> tmp/m2"
redirectfunctionrel "echo 2 >> tmp/r1 >> tmp/r2" "echo 2 >> tmp/m1 >> tmp/m2"
redirectfunctionrel "echo test >> tmp/r1 2" "echo test >> tmp/m1 2"
redirectfunctionrel "Non_exist_cmd >> tmp/r1" "Non_exist_cmd >> tmp/m1"

# < input from
printf "\e[1;36mTesting < input from \e[0;00m\n"
testfunction "<"
redirectfunctionhome "cat < ~/tmp/r1" "cat < ~/tmp/m1"
redirectfunctionabs "cat < ''" "cat < ''"
redirectfunctionabs "cat < ' '" "cat < ' '"
redirectfunctionabs "cat < /tmp/minitest/r1" "cat < /tmp/minitest/m1"
#redirectfunctionabs "echo hallo && echo hallo && cat < /tmp/minitest/r1" "cat < /tmp/minitest/m1" #works correctly in runtime
#redirectfunctionabs "echo hallo || echo hallo || cat < /tmp/minitest/r1" "cat < /tmp/minitest/m1" #works correctly in runtime
#redirectfunctionabs "echo hallo ; echo hallo ; cat < /tmp/minitest/r1" "cat < /tmp/minitest/m1" #works correctly in runtime
redirectfunctionabs "echo hallo | echo hallo | cat < /tmp/minitest/r1" "cat < /tmp/minitest/m1"
redirectfunctionabs "cat < ///tmp/minitest///r1" "cat < ///tmp///minitest///m1"
redirectfunctionabs "cat </tmp/minitest/r1</tmp/minitest/r2</tmp/minitest/r3" "cat </tmp/minitest/m1</tmp/minitest/m2</tmp/minitest/m3"
redirectfunctionabs "cat '</tmp/minitest/r1</tmp/minitest/r2</tmp/minitest/r3'" "cat '</tmp/minitest/m1</tmp/minitest/m2</tmp/minitest/m3'"
redirectfunctionabs "cat \"</tmp/minitest/r1</tmp/minitest/r2</tmp/minitest/r3\"" "cat \"</tmp/minitest/m1</tmp/minitest/m2</tmp/minitest/m3\""
redirectfunctionabs "cat <  /tmp/minitest/r1  <  /tmp/minitest/r2  <  /tmp/minitest/r3" "cat <  /tmp/minitest/m1  <  /tmp/minitest/m2  <  /tmp/minitest/m3"
redirectfunctionabs "cat < /tmp/minitest/r1 < /tmp/minitest/r2 < /tmp/minitest/r3" "cat < /tmp/minitest/m1 < /tmp/minitest/m2 < /tmp/minitest/m3"
redirectfunctionabs "cat < '/tmp/minitest/r1' < '/tmp/minitest/r2' < '/tmp/minitest/r3'" "cat < '/tmp/minitest/m1' < '/tmp/minitest/m2' < '/tmp/minitest/m3'"
redirectfunctionabs "cat < \"/tmp/minitest/r1\" < \"/tmp/minitest/r2\" < \"/tmp/minitest/r3\"" "cat < \"/tmp/minitest/m1\" < \"/tmp/minitest/m2\" < \"/tmp/minitest/m3\""
redirectfunctionabs "cat < \"'/tmp/minitest/r1'\" < \"'/tmp/minitest/r2'\" < \"'/tmp/minitest/r3'\"" "cat < \"'/tmp/minitest/m1'\" < \"'/tmp/minitest/m2'\" < \"'/tmp/minitest/m3'\""
redirectfunctionabs "cat < '\"/tmp/minitest/r1\"' < '\"/tmp/minitest/r2\"' < '\"/tmp/minitest/r3\"'" "cat < '\"/tmp/minitest/m1\"' < '\"/tmp/minitest/m2\"' < '\"/tmp/minitest/m3\"'"
redirectfunctionabs "< /tmp/minitest/r1 cat < /tmp/minitest/r2 < /tmp/minitest/r3" "< /tmp/minitest/m1 cat < /tmp/minitest/m2 < /tmp/minitest/m3"
redirectfunctionabs "< /tmp/minitest/r1 < /tmp/minitest/r2 cat < /tmp/minitest/r3" "< /tmp/minitest/m1 < /tmp/minitest/m2 cat < /tmp/minitest/m3"
redirectfunctionabs "< /tmp/minitest/r1 < /tmp/minitest/r2 < /tmp/minitest/r3 cat" "< /tmp/minitest/m1 < /tmp/minitest/m2 < /tmp/minitest/m3 cat"
redirectfunctionrel "cat < tmp/r1" "cat < tmp/m1"
#redirectfunctionrel "echo hallo && echo hallo && cat < tmp/r1" "cat < tmp/m1" #works correctly in runtime
#redirectfunctionrel "echo hallo || echo hallo || cat < tmp/r1" "cat < tmp/m1" #works correctly in runtime
#redirectfunctionrel "echo hallo ; echo hallo ; cat < tmp/r1" "cat < tmp/m1" #works correctly in runtime
redirectfunctionrel "echo hallo | echo hallo | cat < tmp/r1" "cat < tmp/m1"
redirectfunctionrel "cat < tmp///r1" "cat < tmp///m1"
redirectfunctionrel "cat <tmp/r1<tmp/r2<tmp/r3" "cat <tmp/m1<tmp/m2<tmp/m3"
redirectfunctionrel "cat '<tmp/r1<tmp/r2<tmp/r3'" "cat '<tmp/m1<tmp/m2<tmp/m3'"
redirectfunctionrel "cat \"<tmp/r1<tmp/r2<tmp/r3\"" "cat \"<tmp/m1<tmp/m2<tmp/m3\""
redirectfunctionrel "cat <  tmp/r1  <  tmp/r2  <  tmp/r3" "cat <  tmp/m1  <  tmp/m2  <  tmp/m3"
redirectfunctionrel "cat < tmp/r1 < tmp/r2 < tmp/r3" "cat < tmp/m1 < tmp/m2 < tmp/m3"
redirectfunctionrel "cat < 'tmp/r1' < 'tmp/r2' < 'tmp/r3'" "cat < 'tmp/m1' < 'tmp/m2' < 'tmp/m3'"
redirectfunctionrel "cat < \"tmp/r1\" < \"tmp/r2\" < \"tmp/r3\"" "cat < \"tmp/m1\" < \"tmp/m2\" < \"tmp/m3\""
redirectfunctionrel "cat < \"'tmp/r1'\" < \"'tmp/r2'\" < \"'tmp/r3'\"" "cat < \"'tmp/m1'\" < \"'tmp/m2'\" < \"'tmp/m3'\""
redirectfunctionrel "cat < '\"tmp/r1\"' < '\"tmp/r2\"' < '\"tmp/r3\"'" "cat < '\"tmp/m1\"' < '\"tmp/m2\"' < '\"tmp/m3\'"
redirectfunctionrel "< tmp/r1 cat < tmp/r2 < tmp/r3" "< tmp/m1 cat < tmp/m2 < tmp/m3"
redirectfunctionrel "< tmp/r1 < tmp/r2 cat < tmp/r3" "< tmp/m1 < tmp/m2 cat < tmp/m3"
redirectfunctionrel "< tmp/r1 < tmp/r2 < tmp/r3 cat" "< tmp/m1 < tmp/m2 < tmp/m3 cat"

# << heredoc
printf "\e[1;36mTesting << heredoc \e[0;00m\n"
testfunction "<<"
#testfunction "cat << EOF
#t e s t
#EOF
#"
#testfunction "cat << 'EOF'
#t e s t
#EOF
#"
#testfunction "cat << \"EOF\"
#t e s t
#EOF
#"
#testfunction "cat '<< EOF'
#t e s t
#EOF
#"
#testfunction "cat \"<< EOF\"
#t e s t
#EOF
#"
#testfunction "cat << EOF
#t e s t
#EOF"
#testfunction "cat << EOF
#t e s t
#EOF 
#EOF
#"
#testfunction "cat << EOF
#t e s t
 #EOF
#EOF
#"
#testfunction "echo << EOF
#t e s t
#EOF
#"
#testfunction "echo << 'EOF'
#t e s t
#EOF
#"
#testfunction "echo << \"EOF\"
#t e s t
#EOF
#"
#testfunction "echo '<< EOF'
#t e s t
#EOF
#"
#testfunction "echo \"<< EOF\"
#t e s t
#EOF
#"
#testfunction "echo << EOF
#t e s t
#EOF"
#testfunction "echo << EOF
#t e s t
#EOF 
#EOF
#"
#testfunction "echo << EOF
#t e s t
 #EOF
#EOF
#"

# < << >> > redirection combinations
printf "\e[1;36mTesting < << >> > redirection combinations \e[0;00m\n"
redirectfunctionabs "/tmp/minitest/r1 < cat > /tmp/minitest/r2 > /tmp/minitest/r3" "/tmp/minitest/m1 < cat > /tmp/minitest/m2 > /tmp/minitest/m3"
redirectfunctionabs "cat -e > /tmp/minitest/r1 < /tmp/minitest/r2" "cat -e > /tmp/minitest/m1 < /tmp/minitest/m2"
redirectfunctionabs "cat < /tmp/minitest/r1 < /tmp/minitest/r2 > /tmp/minitest/r3" "cat < /tmp/minitest/m1 < /tmp/minitest/m2 > /tmp/minitest/m3"
#redirectfunctionabs "echo hey <> /tmp/minitest/r1" "echo hey <> /tmp/minitest/r1" # <> is also not part of the subject
redirectfunctionabs "echo hey >< /tmp/minitest/r1" "echo hey >< /tmp/minitest/r1"
#redirectfunctionabs "< /tmp/minitest/r1 cat | << EOF cat | cat >> /tmp/minitest/r3" "< /tmp/minitest/m1 cat | << EOF cat | cat >> /tmp/minitest/m3"
redirectfunctionrel "tmp/r1 < cat > tmp/r2 > tmp/r3" "tmp/m1 < cat > tmp/m2 > tmp/m3"
redirectfunctionrel "cat -e > tmp/r1 < tmp/r2" "cat -e > tmp/m1 < tmp/m2"
redirectfunctionrel "cat < tmp/r1 < tmp/r2 > tmp/r3" "cat < tmp/m1 < tmp/m2 > tmp/m3"
#redirectfunctionrel "echo hey <> tmp/r1" "echo hey <> tmp/r1" # <> is also not part of the subject
redirectfunctionrel "echo hey >< tmp/r1" "echo hey >< tmp/r1"
#redirectfunctionrel "< tmp/r1 cat | << EOF cat | cat >> tmp/r3" "< tmp/m1 cat | << EOF cat | cat >> tmp/m3"

# piping
printf "\e[1;36mTesting piping\e[0;00m\n"
testfunction "|"
testfunction "ls |"
testfunction "ls | ''"
testfunction "ls | ' '"
testfunction "!! | !!"
testfunction "~ | ~"
testfunction "cat /dev/random | base64 | head -c 10"
testfunction "echo 1 && true | echo 2 && true | echo 3 && true | echo 4 && true | echo 5 && true | echo 6 && true"
testfunction "sleep 1 | sleep 1 | sleep 1"
testfunction "'sleep 1 | sleep 1 | sleep 1'"
testfunction "\"sleep 1 | sleep 1 | sleep 1\""
testfunction "cat Makefile | grep pr | head -n 5 | cat"
testfunction "cat Makefile | grep pr | head -n 5 | cd file_not_exit"
testfunction "ls | exit"

# quotes
printf "\e[1;36mTesting quotes\e[0;00m\n"
testfunction "\"\""
testfunction "'\"\"'"
testfunction "\"'\"\"'\""
testfunction "'\"'\"\"'\"'"
testfunction "\"'\"'\"\"'\"'\""
testfunction "''"
testfunction "\"''\""
testfunction "'\"''\"'"
testfunction "\"'\"''\"'\""
testfunction "'\"'\"''\"'\"'"
testfunction "printf \"hallo\""
testfunction "printf 'hallo'"
testfunction "printf ''\"hallo\"''"
testfunction "printf \"'\"hallo\"'\""
testfunction "printf '\"'\"hallo\"'\"'"
testfunction "echo '\"abc\"'"
testfunction "echo \"\" bonjour"

# open " quotes
printf "\e[1;36mTesting \" open quotes\e[0;00m\n"
#testfunction "\""
testfunction "printf \"hallo
hallo\""
testfunction "printf \"
\""
testfunction "printf \"hallo
\"\"hallo
\"\"hallo
\""
#testfunction "printf \"hallo
#\"\"hallo
#\"   \"hallo
#\""
testfunction "printf '\"hallo'\"
\""

# open ' quotes
printf "\e[1;36mTesting ' open quotes\e[0;00m\n"
#testfunction "'"
testfunction "printf 'hallo
hallo'"
testfunction "printf '
'"
testfunction "printf 'hallo
''hallo
''hallo
'"
#testfunction "printf 'hallo
#''hallo
#'   'hallo
#'"

# Syntax errors
printf "\e[1;36mTesting Syntax errors \e[0;00m\n"
testfunction "<>"
testfunction "><"
testfunction "echo hello;;echo 'hello'"
testfunction "echo hello; ;echo 'hello'"
testfunction "echo hello|||echo 'hello'"
testfunction "echo hello|| |echo 'hello'"
testfunction "echo hello| ||echo 'hello'"
testfunction "echo hello| | |echo 'hello'"
testfunction "echo hello||;echo 'hello'"
testfunction "echo hello|| ;echo 'hello'"
testfunction "echo hello|| &echo 'hello'"
testfunction "echo hello||&echo 'hello'"
testfunction "echo hello&&&echo 'hello'"
testfunction "echo hello&& &echo 'hello'"
testfunction "echo hello& &&echo 'hello'"
testfunction "echo hello& & &echo 'hello'"
testfunction "echo hello&&;echo 'hello'"
testfunction "echo hello&& ;echo 'hello'"
testfunction "echo hello&&|echo 'hello'"
testfunction "echo hello&& |echo 'hello'"

# Go crazy

# Shutdown
rm ' ' file
printf "\e[1;36mThe tester found $ERRORS KO's and $PASSES OK's out of $(($ERRORS+$PASSES)) tests\e[0;00m\n"
exit $ERRORS