

EXECUTE=./bin/so_long
FILES=./maps/*
RESET="\x1B[0m"
RED="\x1B[31m"
GREEN="\x1B[32m"
YELLOW="\x1B[33m"
INVALID=0

echo "${YELLOW}-----------------\nSoLong map tester\n-----------------\n${RESET}"

for f in $FILES
do
	if [[ "$f" == *"invalid"* ]]; then
		${EXECUTE} $f 
		if [ $? -eq 0 ] 
		then 
			echo "${RED}Error: $f should not be valid\n"
			INVALID=1
		else 
			echo "${GREEN}OK: $f is invalid\n"
		fi
	else
		${EXECUTE} $f > /dev/null 2> /dev/null
		if [ $? -eq 0 ] 
		then 
			echo "${GREEN}OK: $f is valid\n"
		else 
			echo "${RED}Error: $f should not be invalid\n"
			INVALID=1
		fi
	fi
done

if (test $INVALID -eq 1)
then
	echo "${RED}Some maps are invalid\n"
	echo "${RESET}"
	exit 1
else
	echo "${GREEN}All maps are valid\n"
	echo "${RESET}"
	exit 0
fi
