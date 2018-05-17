
#############################################################
#                                                           #
#              You should set all variables                 #
#                                                           #
#                                                           #
#                                                           #
		#Set name of compiled file	
NAME=main						

		#Set libraries you want linker to add to the project
#LFLAGS= -lm
LFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

		#Set compiler
CXX=g++
		
		#Set flags for compilation
CXXFLAGS+= -pedantic -O0 $(GXX_FLAGS) -g
#							    #
#							    #
#                                                           #
#############################################################


#############################################################
#			things you would not like to change				#

# Setting up compiler flags, so it will be able to generate dependencies
# ustawiamy flagi dla kompilatora, żeby automatycznie wygenerował zależności
DEP_FLAGS=-MMD -MP

# Fetching all files with extencions .cpp and .C from directory, where the makefile is
# pobieramy wszystkie pliki z rozszerzeniem .cpp i .C z folderu w którym jest makefile
SRC=$(wildcard *.cpp)
SRCC=$(wildcard *.C)

# Seting variable holding names of object files
# do tej zmiennej zapisujemy nazwy plików obiektowych jakie mają być zrobione
OBJ=$(SRC:.cpp=.o)
OBJ+=$(SRCC:.C=.o)

# Setting up variable for dependencies files
# nazwy plików z zależnościami
DEP=$(OBJ:.o=.d)

# Name of the directory, where all the object files will be stored
# nazwa folderu dla plików obiektowych i zależności
OBJDIR := obj

# list of object files with correct addres
# tworzymy listę plików obiektowych z odpowiednim adresem
OBJS := $(addprefix $(OBJDIR)/,$(OBJ))
DEPS := $(addprefix $(OBJDIR)/,$(DEP))

# check if a directory for object files exist
# najpierw upewniamu się czy mamy folder na pliki obiektowe, potem kompilujemy
.PHONY: all
all: $(OBJDIR) $(NAME)

# Linking to main program
# kompilacja z flagami do linkowania ( domyślnie ustawione) wszystkie pliki obiektowe i generuj plik wynikowy do pliku o nazwie takiej jak nazwa etykiety( w tym przypadku main)	
$(NAME): $(OBJS) 
	$(CXX) $^ $(LFLAGS) -o $@

# Compilation to object files
# tu tworzymy pliki obiektowe i pliki zależności 
$(OBJDIR)/%.o: %.C
	$(CXX) $(CXXFLAGS) $(DEP_FLAGS) -c $*.C -o $@
$(OBJDIR)/%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(DEP_FLAGS) -c $*.cpp -o $@

# directory for object files
# tworzymy katalog dla plików obiektowych
$(OBJDIR):
	mkdir $(OBJDIR)

# Very important for automatic dependencies to work
# ważne żeby zadziały automatyczne zależności
-include $(DEPS)

.PHONY: clean
clean:
	@rm -rf $(NAME) obj/ vgcore.*
.PHONY: run
run:
	./$(NAME)
.PHONY: gdb
gdb:
	gdb ./$(NAME)
.PHONY: valgrind
valgrind:
	valgrind ./$(NAME)
.PHONY: git
git: 
	make clean && git add . && git commit && git push origin master	
.PHONY: update
update:
	git clone git@bitbucket.org:robgal519/makefile_agh_wfiis.git && cp makefile_agh_wfiis/makefile . && rm -rf makefile_agh_wfiis

.PHONY: help
help:
	@clear
	@echo '-----------------------------------------------------------'
	@echo '#   make             - kompilacja i linkowanie projektu   #'
	@echo '#   make help        - wyświetla ten komunikat            #'
	@echo '#   make clean       - czyszczenie projektu               #'
	@echo '#   make run         - uruchamia program                  #'
	@echo '#   make gdb         - uruchamia gdb                      #'
	@echo '#   make valgrind    - uruchamia valgrind                 #'
	@echo '#   make git         - wysyła zmiany na git               #'
	@echo '#   make update      - pobiera najnowszą wersję makefile  #'
	@echo '-----------------------------------------------------------'	
	@echo '###########################################################'
	@echo 'OPIS:'
	@echo 'ten makefile został stworzony na zajęcia z cpp na WFiIS'
	@echo 'obsługuje pliki .C .cpp oraz wszystkie które zostaną umieszczone w derektywie #include '
	@echo ''
	@echo ''
	@echo 'UWAGA: przed użyciem make git należy wykonać następujące polecina:'
	@echo ''
	@echo '	w głównym folderze progektu wykonać:'
	@echo '		git init'
	@echo ''
	@echo '	utworzyć repozytorium na wybranym serwisie i wysłać na ten serwis klucz ssh'
	@echo '	ustawić origin '
	@echo '		git remote add origin git@birbucket.org:UserName/repoName.git'
	@echo '	ustawić domyślny edytor do commitów'
	@echo '		git config --global core.editor vim'
	@echo ''
	@echo '	polecenie make git wykonuje clean!'
