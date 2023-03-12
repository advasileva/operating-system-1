points = 4
tests = 1

chmod:
	chmod -R +x .

compile:
	./scripts/compile.sh ${points}

run:
	./scripts/run.sh ${points} ${tests}