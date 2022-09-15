CC=gcc
CFLAGS= -g
FSMLIB=libfsm.a
APP=app.exe
APP_BIT_COUNTER=app_bit_counter.exe
TARGET:${APP} ${FSMLIB} ${APP_BIT_COUNTER} reg_test.exe
${APP}:app.o ${FSMLIB}
	@echo "Building "${APP}
	${CC} ${CFLAGS} app.o -o ${APP} -L . -lfsm
${APP_BIT_COUNTER}:app_bit_counter.o ${FSMLIB}
	@echo "Building "${APP_BIT_COUNTER}
	${CC} ${CFLAGS} app_bit_counter.o -o ${APP_BIT_COUNTER} -L . -lfsm
app_bit_counter.o:app_bit_counter.c
	@echo "Building app_bit_counter.o"
	${CC} ${CFLAGS} -c app_bit_counter.c -o app_bit_counter.o
${FSMLIB}:fsm.o std_fsm.o Stack/stack.o fsm_utils.o
	@echo "Building "${FSMLIB}
	ar rs ${FSMLIB} fsm.o std_fsm.o Stack/stack.o fsm_utils.o
fsm.o:fsm.c
	@echo "Building fsm.o"
	${CC} ${CFLAGS} -c fsm.c -o fsm.o
std_fsm.o:std_fsm.c
	@echo "Building std_fsm.o"
	${CC} ${CFLAGS} -c std_fsm.c -o std_fsm.o
fsm_utils.o:fsm_utils.c
	@echo "Building fsm_utils.o"
	${CC} ${CFLAGS} -c fsm_utils.c -o fsm_utils.o
Stack/stack.o:Stack/stack.c
	@echo "Building Stack/stack.o"
	${CC} ${CFLAGS} -c Stack/stack.c -o Stack/stack.o
reg_test.exe:reg_test.o
	@echo "Building reg_test.exe"
	${CC} ${CFLAGS} reg_test.o -o reg_test.exe -L . -lfsm
reg_test.o:reg_test.c
	@echo "Building reg_test.o"
	${CC} ${CFLAGS} -c reg_test.c -o reg_test.o
clean:
	@echo "Cleaning built objects"
	rm *.o
	rm *exe	
	rm *.a
	rm Stack/*.o
