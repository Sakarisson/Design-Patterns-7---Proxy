CCX 		= g++ -std=c++11
CCINCLUDE	=
CCFLAGS		=  
LDFLAGS		=  
LIBS		= -pthread
PROGS		= ChatClient
OBJS		= ChatClient.o Client.o Message.o ServerConnection.o \
		  ServerProxy.o 
		 
HDRS		=


.cpp.o:
	@echo "Compiling " $<
	$(CCX) -c $(CCFLAGS) $(CCINCLUDE) $<
	@echo $@ "done"

all:	$(PROGS)

ChatClient: $(OBJS)
	$(CCX) -o $@ $(OBJS)  $(LDFLAGS) $(LIBS) 

clean:
	rm -f a.out core $(PROGS) $(OBJS) 
	




