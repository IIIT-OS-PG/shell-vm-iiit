all:
	g++ vmsh.cpp change_direc.cpp child_handler.cpp eval_pipe.cpp header.h input.cpp prompt.cpp -o exec.out
