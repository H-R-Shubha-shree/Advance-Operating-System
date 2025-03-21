# this makefile uses your sources:
 # $(APPN).x - RPCgen input, XDR protocol definition
 # $(APPN)_svc_proc.c - define server process called by server stub
 # $(APPN).c - tell the client what to do (talk to servers etc)
 # $(APPN)_shared.h - shared include stuff (added since last month)
# to make the following:
 # $(APPN)_xdr.c - client/server XDR library agccess
 # $(APPN)_svc.c - server stub, a main() wrapper
 # $(APPN)_clnt.c - client stub w/ function name defined in protocol
 # $(APPN).h - miscellaneous includes generated from protocol def.
 # $(APPN) - the executable for the client
 # $(APPN)_svc - the executable for the server

# these for different machines and stages of development
CC=nvcc
APPN= idshr
#LFLAGS=
RSRC=$(APPN).x $(APPN)_svc_proc.c $(APPN).c $(APPN)_shared.h
CFLAGS= -DDEBUG
RPCGEN = rpcgen

CLIENT_AND_SERVER: $(APPN) $(APPN)_svc # client and server executables

all: $(CLIENT_AND_SERVER)

# compile the protocol
$(APPN)_xdr.c $(APPN)_svc.c $(APPN)_clnt.c $(APPN).h:: $(APPN).x
        $(RPCGEN) $(APPN).x

# build the client application
$(APPN): $(APPN).h $(APPN)_shared.h $(APPN).o $(APPN)_clnt.o $(APPN)_xdr.o
        $(CC) $(CFLAGS) -o $(APPN) $(APPN).o $(APPN)_clnt.o $(APPN)_xdr.o \
        $(LFLAGS)

# explicitly watch for new .h files
$(APPN).o: $(APPN).c $(APPN).h $(APPN)_shared.h
        $(CC) -c -o $@ $(CFLAGS) $(APPN).c
$(APPN)_svc_proc.o: $(APPN)_svc_proc.c $(APPN).h $(APPN)_shared.h
        $(CC) -c -o $@ $(CFLAGS) $(APPN)_svc_proc.c
$(APPN)_shared.h:
        echo > $(APPN)_shared.h

# build the server application
$(APPN)_svc: $(APPN).h $(APPN)_shared.h $(APPN)_svc_proc.o $(APPN)_svc.o \
$(APPN)_xdr.o reduction.o
        $(CC) $(CFLAGS) -o $(APPN)_svc $(APPN)_svc_proc.o $(APPN)_svc.o \
        $(APPN)_xdr.o reduction.o $(LFLAGS)

reduction.o: reduction.cu
	nvcc -c -arch=sm_60 reduction.cu

# blast away
clean:
        $(RM) $(APPN) $(APPN)_svc $(APPN)_svc.c $(APPN)_xdr.c $(APPN)_clnt.c $(APPN).h *.o *.*%

$(APPN).ar: $(RSRC)
        bundle $(RSRC) > $(APPN).ar
