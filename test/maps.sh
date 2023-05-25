EXECUTE=./bin/so_long
FILES=./maps/*
RESET="\x1B[0m"
RED="\x1B[31m"
GREEN="\x1B[32m"
YELLOW="\x1B[33m"
INVALID=0

printf "${YELLOW}SoLong map tester\n-----------------\n${RESET}"

for f in $FILES
do
	if [[ $f == *"invalid"* ]]; then
	${EXECUTE} $f > /dev/null 2> /dev/null  && (printf "${RED}Error: $f should not be valid\n" && INVALID=1) || printf "${GREEN}OK: $f is invalid\n"
	else
	${EXECUTE} $f > /dev/null 2> /dev/null  && printf "${GREEN}OK: $f is valid\n" || (printf "${RED}Error: $f should be valid\n" && INVALID=1)
	fi
done

if (test ${INVALID})
then
	printf "${RED}Some maps are invalid\n"
	printf "${RESET}"
	exit 1
else
	printf "${GREEN}All maps are valid\n"
	printf "${RESET}"
	exit 0
fi
