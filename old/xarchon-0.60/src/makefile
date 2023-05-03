#SRC = actors.c audio.c  board.c    canvas.c   computer.c   field.c   human.c   iface.c   list.c   network.c   sprite.c   theme.c   toolkit.c   Xarchon_Problem.cpp   Xarchon_Interface.cpp   Xarchon_Game.cpp   Xarchon_Genetic.cpp
SRC = actors.c audio.c board.c canvas.c computer.c \
      field.c human.c  iface.c  list.c  network.c  \
      sprite.c  theme.c toolkit.c sample-driver-null.c archon.c 

CC=gcc
CFLAGS=-I. -Ixaw -g -O0
LOADLIBES=-lX11 -lXt -lXaw -lXpm -lm
 
ALL: main

main: toolkit.o xaw/xaw-toolkit.o $(patsubst %.c,%.o, $(SRC))
