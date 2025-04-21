compile() {
	if [ -z "$1" ]; then
		echo "No file provided to compile."
		return 1
	fi

	if [ "$1" = 'debug' ]; then
		DEBUG="-ggdb"
		shift
	else
		DEBUG=""
	fi

	# Remove path from first param
	PROGRAM_NAME=$(basename "$1")
	PROGRAM_NAME="${PROGRAM_NAME%.*}"
	echo $@
	c++ -Wall -Wextra -Werror --std=c++20 -I./includes $DEBUG -pthreads -o ./$PROGRAM_NAME.out $@
}

clean() {
	rm -f *.out
}
