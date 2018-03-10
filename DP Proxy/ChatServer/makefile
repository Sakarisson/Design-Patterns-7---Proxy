CCX 		= g++ -std=c++11
CCINCLUDE	=
CCFLAGS		=  
LDFLAGS		=  
LIBS		= -pthread
PROGS		= ChatServer
OBJS		= ChatLogger.o ChatServer.o ClientConnection.o ClientListener.o \
		  ClientProxy.o Message.o Server.o \
		 
HDRS		=


.cpp.o:
	@echo "Compiling " $<
	$(CCX) -c $(CCFLAGS) $(CCINCLUDE) $<
	@echo $@ "done"

all:	$(PROGS)

ChatServer: $(OBJS)
	$(CCX) -o $@ $(OBJS)  $(LDFLAGS) $(LIBS) 

clean:
	rm -f a.out core $(PROGS) $(OBJS) 
	




