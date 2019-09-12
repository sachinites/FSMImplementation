CC=gcc
CFLAGS= -g
FSMLIB=libfsm.a
APP=app.exe
APP_BIT_COUNTER=app_bit_counter.exe
TARGET:${APP} ${FSMLIB} ${APP_BIT_COUNTER}
${APP}:app.o ${FSMLIB}
	@echo "Building "${APP}
	${CC} ${CFLAGS} app.o -o ${APP} -L . -lfsm
${APP_BIT_COUNTER}:app_bit_counter.o ${FSMLIB}
	@echo "Building "${APP_BIT_COUNTER}
	${CC} ${CFLAGS} app_bit_counter.o -o ${APP_BIT_COUNTER} -L . -lfsm
app_bit_counter.o:app_bit_counter.c
	@echo "Building app_bit_counter.o"
	${CC} ${CFLAGS} -c app_bit_counter.c -o app_bit_counter.o
${FSMLIB}:fsm.o std_fsm.o
	@echo "Building "${FSMLIB}
	ar rs ${FSMLIB} fsm.o std_fsm.o
fsm.o:fsm.c
	@echo "Building fsm.o"
	${CC} ${CFLAGS} -c fsm.c -o fsm.o
std_fsm.o:std_fsm.c
	@echo "Building std_fsm.o"
	${CC} ${CFLAGS} -c std_fsm.c -o std_fsm.o
clean:
	@echo "Cleaning built objects"
	rm *.o
	rm *exe	
	rm *.a
