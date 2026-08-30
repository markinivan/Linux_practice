#!/bin/bash

echo "12345782
ffffffffff
fqafqfqfqf
asfsfsfsfsf" > test1.txt

echo "" > test2.txt

echo "fgh" > test3.txt

echo "ckjkd djjdkkc dkkdkdk dlkdkdk 
dk
dld ldld d d d dddddd
" > test4.txt

echo "ghj ff ff  wsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss" > test5.txt

echo "" > result.txt
echo "" > example.txt

c_tests_counter=0
f_tests_counter=0

FLAGS=("-l" "-w" "-c" "-m" "-lw" "-wc" "-cm" "-ml" "-lc" "-wm" "-lwc" "-lwm" "-lcm" "-wcm" "-lwcm")
FILES=("test1.txt" "test2.txt" "test3.txt" "test4.txt" "test5.txt" "test1.txt test2.txt" "test2.txt test3.txt" "test3.txt test4.txt" "test4.txt test5.txt" "test1.txt test3.txt" "test1.txt test4.txt" "test1.txt test5.txt" "test2.txt test4.txt" "test2.txt test5.txt" "test3.txt test5.txt" "test1.txt test2.txt test3.txt" "test1.txt test2.txt test3.txt test4.txt" "test3.txt test2.txt test3.txt test5.txt" "test3.txt test5.txt test4.txt test1.txt test1.txt" "test1.txt test1.txt")

for flag in "${FLAGS[@]}"; do
	for file in "${FILES[@]}"; do
		wc $flag $file > example.txt
		./build/release/wc $flag $file > result.txt
		if diff -q example.txt result.txt > /dev/null 2>&1; then
       			echo "Тест пройден"
       			c_tests_counter=$((c_tests_counter+1))
    		else
        		echo "Тест провален"
        		echo $flag 
        		echo $file
        		echo "Различия:"
        		diff example.txt result.txt
        		f_tests_counter=$((f_tests_counter+1))
    		fi
    		> example.txt
    		> result.txt
	done
done

echo "Тестов всего: $((c_tests_counter+f_tests_counter))"
echo "Тестов пройдено: ${c_tests_counter}"
echo "Тестов провалено: ${f_tests_counter}"

rm test1.txt test2.txt test3.txt test4.txt test5.txt example.txt result.txt
