points = 7
tests = 5

chmod:
	chmod -R +xr .

compile:
	./scripts/compile.sh ${points}

run:
	make clear
	./scripts/run.sh ${points} ${tests}

clear:
	./scripts/clear.sh ${points} ${tests}
