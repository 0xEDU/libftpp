compile() {
	if [ -z "$1" ]; then
		echo "No file provided to compile."
		return 1
	fi
	# Remove path from first param
	PROGRAM_NAME=$(basename "$1")
	PROGRAM_NAME="${PROGRAM_NAME%.*}"
	c++ -Wall -Wextra -Werror --std=c++20 -o ./$PROGRAM_NAME.out $1
}

clean() {
	rm -f *.out
}
