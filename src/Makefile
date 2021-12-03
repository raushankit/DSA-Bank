CPP = g++ 
FLAGS = -O5 -Wall -W
RM  = rm -fr
EXEC = a.out

SRCPATH = classes
OBJDIR = ../build

CLASSES = \
	 Account.o \
	 atm.o \
	 backup.o \
	 bank.o \
	 customer_atm.o \
	 customer_bank.o \
	 log.o \
	 manager.o \
	 syntax.o \
	 verification.o \

FUNCTS = \
	 main.o \
	 function.o \

OBJECTS = \
	 $(addprefix $(OBJDIR)/, $(FUNCTS)) \
	 $(addprefix $(OBJDIR)/, $(CLASSES))	\

all: $(OBJECTS) compile touch 

$(OBJDIR)/%.o: %.cpp | $(CRDIR)/$(OBJDIR)
					 $(CPP) $(FLAGS) $(INCLUDES) -c $< -o $@
$(OBJDIR)/%.o: $(SRCPATH)/%.cpp | $(CRDIR)/$(OBJDIR)
					 $(CPP) $(FLAGS) $(INCLUDES) -c $< -o $@
$(CRDIR)/%:
					 mkdir -p $*
run: | all
					 ./$(EXEC)
clean:  
					 $(RM) $(OBJDIR) $(EXEC)
compile: 
					 $(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC) 
touch:
					 @echo " "
					 @echo "Compilation done successfully..................."
					 @echo " "
