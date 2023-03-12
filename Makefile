points = 4
tests = 5

chmod:
	chmod -R +xr .

compile:
	./scripts/compile.sh ${points}

run:
	./scripts/run.sh ${points} ${tests}
	make chmod

clear:
	./scripts/clear.sh ${points} ${tests}
