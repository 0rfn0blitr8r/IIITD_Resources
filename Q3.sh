 #!/usr/bin/bash

# Check if input file exists
input_file="input.txt"
if [ ! -f "$input_file" ]; then
    echo "Input file '$input_file' not found."
    exit 1
fi


rm -rf Result
mkdir Result
echo "Output is in file: Result/output.txt" > Result/output.txt

#cat input.txt
while IFS=" " read -r x y string; do
	# echo $line >> Result/output.txt
	# SUM=$((x + y))
	# echo "$SUM" >> Result/output.txt
	if [ $string == "product" ]; then
		PRODUCT=$((x * y))
		echo "Result of product: $PRODUCT" >> Result/output.txt
	elif [ $string == "compare" ]; then
		if [ $x -gt $y ]; then
			echo "Result of compare: $x" >> Result/output.txt
		else
			echo "Result of compare: $y" >> Result/output.txt
		fi
	else
		RESULT=$((x ^ y))
		echo "Result of bit-wise XOR: $RESULT" >> Result/output.txt
	fi

done < input.txt

# cat Result/output.txt