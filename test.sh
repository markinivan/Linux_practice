#!/bin/bash

echo "12345782
ffffffffff
fqafqfqfqf
asfsfsfsfsf" > test1.txt

echo "" > test2.txt

echo "😊😂🤣❤️🥰😍🤩😎🥳😏
😅🤗😇🤔🧐 🤓😜😝
🤪🥺" > test3.txt

echo "ckjkd djjdkkc dkkdkdk dlkdkdk 
dk
dld ldld d d d dddddd
" > test4.txt

echo "ghj ff ff  wsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss" > test5.txt

echo "" > result.txt
echo "" > example.txt

FLAGS=("-l" "-w" "-c" "-m" "-lw" "-wc" "-cm" "-ml" "-lc" "-wm" "-lwc" "-lwm" "-lcm" "-wcm" "-lwcm")
FILES=("test1.txt" "test2.txt" "test3.txt" "test4.txt" "test5.txt" "test1.txt test2.txt" "test2.txt test3.txt" "test3.txt test4.txt" "test4.txt test5.txt" "test1.txt test3.txt" "test1.txt test4.txt" "test1.txt test5.txt" "test2.txt test4.txt" "test2.txt test5.txt" "test3.txt test5.txt" "test1.txt test2.txt test3.txt" "test1.txt test2.txt test3.txt test4.txt" "test3.txt test2.txt test3.txt test5.txt" "test3.txt test5.txt test4.txt test1.txt test1.txt" "test1.txt test1.txt")

for flag in "${FLAGS[@]}"; do
	for file in "${FILES[@]}"; do
		wc $flag $file > example.txt
		./wc $flag $file > result.txt
		if diff -q example.txt result.txt > /dev/null 2>&1; then
       			echo "Тест пройден"
    		else
        		echo "Тест провален"
        		echo $flag 
        		echo $file
        		echo "Различия:"
        		diff example.txt result.txt
    		fi
    		> example.txt
    		> result.txt
	done
done

rm test1.txt test2.txt test3.txt test4.txt test5.txt example.txt result.txt
