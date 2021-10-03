all:
	gcc -o process_tree process_tree.c
clean:
	rm process_tree
run:
	./process_tree 4 3
