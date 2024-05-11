##
## EPITECH PROJECT, 2024
## RTX
## File description:
## This is the Makefile for the RTX project
## Its goal is to compile the project
##

# All the source files
CXX_SOURCES		= 	src/main.cpp										\
					src/GlmParser.cpp									\
					src/Transform.cpp									\
					src/objects/Material.cpp							\
					src/objects/Texture.cpp								\
					src/Camera.cpp										\
					src/objects/Object.cpp								\
					src/Scene.cpp										\
					src/SceneParser.cpp									\
					src/primitives/Rectangle.cpp						\
					src/primitives/Cube.cpp								\
					src/primitives/Sphere.cpp							\
					src/primitives/ObjectsFactory.cpp					\
					src/primitives/Plane.cpp							\
					src/primitives/Cylinder.cpp							\
					src/primitives/Cone.cpp								\
					src/primitives/Properties/AbstractProperties.cpp	\
					src/primitives/Properties/PropertiesFactory.cpp		\
					src/primitives/Properties/CubeProperties.cpp		\
					src/primitives/Properties/PlaneProperties.cpp		\
					src/primitives/Properties/CylinderProperties.cpp	\
					src/primitives/Properties/ConeProperties.cpp		\
					src/Application.cpp									\

SHADERS 		= 	shaders/screen.vert									\
					shaders/texture_screen.frag							\
					shaders/raytracing.comp								\

CXX_TESTS		=	tests/testsMaterial.cpp								\
					tests/testsTexture.cpp								\
					tests/testsSceneParser.cpp							\

LIBS			=   libs/json/libjson.so								\
					parser/obj/libobj.so								\

# Compiler and linker settings
NAME 			= 	raytracer
CXX				= 	g++
GLSLC			=	$(shell which glslc)
GLSL_FLAGS		=   -O
CXXFLAGS		= 	-W -Wall -Wextra -std=c++20 -I./include  \
				 	-L. -ljson -lobj -lglfw -lvulkan -ldl -lpthread -lX11 -O3
MACOS_FLAGS		= 	-rpath /usr/local/lib/
LINUX_FLAGS		=
CXXFLAGS		+=	$(shell [ `uname -s` = "Darwin" ] && echo $(MACOS_FLAGS))
CXXFLAGS		+=	$(shell [ `uname -s` = "Linux" ] && echo $(LINUX_FLAGS))
CXX_OBJS		= 	$(CXX_SOURCES:.cpp=.o)
TEMP_SHADED 	=	$(SHADERS:.frag=.spv) $(SHADERS:.vert=.spv) \
					$(SHADERS:.comp=.spv)
# Remove all the non .spv files
SHADERS_OBJS	=	$(filter %.spv, $(TEMP_SHADED))
CXX_TESTS_OBJS	= 	$(CXX_TESTS:.cpp=.o)

LOG				=	./build.log

.PHONY: all clean fclean re tests_run \
	clean_test $(LIBS) clean_libs fclean_libs clion _tests_run

# Colors and formatting
GREEN =		\033[1;32m
YELLOW =	\033[1;33m
RED =		\033[1;31m
BLUE =		\033[1;36m
GOLD =		\033[1;33m
MAGENTA =	\033[1;35m
RESET =		\033[0m

RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]
SKIPPED = [$(MAGENTA)@$(RESET)]

ifeq ($(ENABLE_COVERAGE), 1)
	CXXFLAGS += --coverage
else
	CXXFLAGS += -O2
endif

all: $(LIBS)
# Check if $(NAME) is up to date
	@HAS_NEWER_SOURCE=0; \
	for file in $(CXX_SOURCES); do \
		if [ "$$file" -nt "$(NAME)" ]; then \
			HAS_NEWER_SOURCE=1; \
			break; \
		fi; \
	done; \
	for file in $(SHADERS); do \
		if [ "$$file" -nt "$(NAME)" ]; then \
			HAS_NEWER_SOURCE=1; \
			break; \
		fi; \
	done; \
	if [ ! -f $(NAME) ] || [ $$HAS_NEWER_SOURCE -eq 1 ]; then \
		make $(NAME) --no-print-directory; \
	else \
		printf "$(SKIPPED)$(MAGENTA)  🚀  \
 $(NAME) already up to date$(RESET)\n"; \
	fi

$(NAME):	$(SHADERS_OBJS) $(CXX_OBJS)
# Link the object files
		@printf "$(RUNNING) $(BLUE) 🔗   Linking$(RESET)"
		@$(CXX) -o $(NAME) $(CXX_OBJS) $(CXXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)
# Check if the binary was created
		@if [ -f $(NAME) ]; then \
			printf \
			"$(SUCCESS)$(GREEN)  🎉   $(NAME) built successfully$(RESET)\n";\
		else \
			printf "$(FAILURE)$(RED)  🚨   $(NAME) build failed$(RESET)\n"; \
			cat $(LOG); \
			exit 1; \
		fi

clion: $(LIBS) $(CXX_OBJS) $(CXX_TESTS_OBJS) $(SHADERS_OBJS)

$(LIBS): 	%.so:
# If lib is already shipped (.so present in the directory)
# We check if it older than any source present in the directory > src of the
# library
	@LIBRARY_SOURCE_DIR=$$(dirname $@)/src; \
	LIBRARY_SOURCES=$$(find $$LIBRARY_SOURCE_DIR -type f -name "*.cpp"); \
	SHIPPED_PATH=./$$(basename $@); \
	if [ ! -f $$SHIPPED_PATH ] || [ "$$LIBRARY_SOURCES" -nt $$SHIPPED_PATH ];\
	then \
		make -C $$(dirname $@) --no-print-directory; \
		if [ -f $@ ]; then \
			printf "$(RUNNING)$(BLUE)  🚚   Shipping $@$(RESET)"; \
			cp $@ . >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			FOLDER_NAME=$$(echo $$(dirname $@) | sed 's:.*/::' \
			| tr '[:upper:]' '[:lower:]'); \
			printf "$(RUNNING) $(BLUE) 🖇️    Linking include/\
$$FOLDER_NAME$(RESET)"; \
			cp -fr $$(dirname $@)/include/* include/ >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "$(FAILURE)$(RED)  🚨  $@ build failed$(RESET)\n"; \
			cat $$(dirname $@)/build.log; \
			exit 1; \
		fi; \
	else \
		printf "$(SKIPPED)$(MAGENTA)  🚀  \
 $@ already up to date and shipped$(RESET)\n"; \
	fi

$(CXX_OBJS):	%.o: %.cpp
# Compile the source file
		@printf "$(RUNNING) $(BLUE) 🔨   $$(basename $<)$(RESET)"
		@$(CXX) -o $@ -c $< $(CXXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)

clean: clean_libs
# Delete all the object files
		@for file in $(CXX_OBJS); do \
			printf "$(RUNNING) $(YELLOW) 🧹️   Deleting $$file$(RESET)"; \
			if [ -f $$file ]; then \
				rm -f $$file >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
		done
		@for file in $(SHADERS_OBJS); do \
			printf "$(RUNNING) $(YELLOW) 🧹️   Deleting $$file$(RESET)"; \
			if [ -f $$file ]; then \
				rm -f $$file >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
		done
# Delete all the tests' object files
		@for file in $(CXX_TESTS_OBJS); do \
			printf "$(RUNNING) $(YELLOW) 🧹   Deleting $$file$(RESET)"; \
			if [ -f $$file ]; then \
				rm -f $$file >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
		done

%.spv: 	%.frag
		@printf "$(RUNNING) $(BLUE) 🖼️    Compiling $<$(RESET)"
		@$(GLSLC) $< -o $@ $(GLSL_FLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)

%.spv: 	%.vert
		@printf "$(RUNNING) $(BLUE) 📐   Compiling $<$(RESET)"
		@$(GLSLC) $< -o $@ $(GLSL_FLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)

%.spv: 	%.comp
		@printf "$(RUNNING) $(BLUE) 🧮   Compiling $<$(RESET)"
		@$(GLSLC) $< -o $@ $(GLSL_FLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)

clean_libs:
	@for lib in $(LIBS); do \
  		LIBRARY_SOURCE_DIR=$$(dirname $$lib)/src; \
		LIBRARY_OBJECTS=$$(find $$LIBRARY_SOURCE_DIR -type f -name "*.o"); \
		if [ -n "$$LIBRARY_OBJECTS" ]; then \
			printf "$(RUNNING) $(YELLOW) 🧹   Cleaning $$(basename $$lib)\
$(RESET)"; \
			make -C $$(dirname $$lib) clean --no-print-directory \
			>> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "$(SKIPPED)$(MAGENTA)  ✨  \
 $$(basename $$lib) already cleaned$(RESET)\n"; \
		fi; \
	done

fclean: clean clean_test fclean_libs
# Delete the binary
		@printf "$(RUNNING) $(RED) 🗑️    Deleting $(NAME)$(RESET)"
		@if [ -f $(NAME) ]; then \
			rm -f $(NAME) >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "\r$(SKIPPED)\n"; \
		fi
# Delete the log file
		@printf "$(RUNNING) $(RED) 🗑️    Deleting $(LOG)$(RESET)"
		@rm -f $(LOG) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

fclean_libs:
		@for lib in $(LIBS); do \
			printf "$(RUNNING) $(RED) 🔥   Deleting $$(basename $$lib)\
$(RESET)"; \
			SHIPPED_PATH=./$$(basename $$lib); \
			if [ -f $$SHIPPED_PATH ]; then \
				rm -f $$SHIPPED_PATH >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
			LOWERCASE_DIR=$$(echo $$(dirname $$lib) | sed 's:.*/::' \
            	| tr '[:upper:]' '[:lower:]') ; \
			printf "$(RUNNING) $(RED) 💥   Deleting include/\
$${LOWERCASE_DIR}$(RESET)"; \
			if [ -e include/$${LOWERCASE_DIR} ]; then \
				rm -rf include/$${LOWERCASE_DIR} >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
			make -C $$(dirname $$lib) fclean --no-print-directory \
			>> $(LOG) 2>&1; \
		done

re:			fclean all

$(CXX_TESTS_OBJS):	%.o: %.cpp
		@printf "$(RUNNING) $(BLUE) 🧪   $$(basename $<)$(RESET)"
		@$(CXX) -o $@ -c $< $(CXXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

tests_libs:
	@for lib in $(LIBS); do \
		make -C $$(dirname $$lib) tests_run --no-print-directory \
		&& printf "$(SUCCESS)$(GREEN)  🎉   Tests for $$(basename $$lib) \
passed successfully$(RESET)\n" \
		|| (printf "$(FAILURE)$(RED)  🚨   Tests for $$(basename $$lib) \
failed$(RESET)\n" && exit 1); \
	done

tests_run:
	@ENABLE_COVERAGE='1' make _tests_run --no-print-directory

_tests_run: fclean tests_libs $(LIBS) $(CXX_OBJS) $(CXX_TESTS_OBJS)
	@printf "$(RUNNING) $(BLUE) 🔗   Linking for $(shell uname -m)\
 architecture$(RESET)";
	@$(CXX) -o tests.out $(filter-out src/main.o, $(CXX_OBJS)) \
	$(CXX_TESTS_OBJS) $(CXXFLAGS) \
	$(shell [ `uname -m` != "arm64" ]	\
	&& echo "-lcriterion" \
	|| echo "-lcriterion") >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && \
	cat $(LOG) && cat tests.log && exit 1);
	@export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:./libs/json/; \
	printf "$(RUNNING)$(MAGENTA)  ⚗️    Running tests$(RESET)" \
	&& ./tests.out --xml=criterion.xml --ignore-warnings >> tests.log 2>&1 \
	&& printf "\r$(SUCCESS)\n" \
	|| (printf "\r$(FAILURE)\n" && cat tests.log && exit 1);
	@cat tests.log;
	@printf "$(RUNNING)$(YELLOW)  📊  Generating coverage$(RESET)" \
	&& gcovr --exclude tests/ --exclude libs/ >> coverage.log 2>&1 \
	&& printf "\r$(SUCCESS)\n" \
	|| printf "\r$(FAILURE)\n";
	@cat coverage.log;

clean_test:
	@printf "$(RUNNING) $(RED) 🗑️    Deleting tests.out$(RESET)"
	@if [ -f tests.out ]; then \
		rm -f tests.out >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting coverage$(RESET)"
	@if [ -f coverage* ]; then \
		rm -f coverage* >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting *.gcda$(RESET)"
	@if [ -n "$$(find ./ -name "*.gcda")" ]; then \
		find ./ -name "*.gcda" -delete >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting *.gcno$(RESET)"
	@if [ -n "$$(find ./ -name "*.gcno")" ]; then \
		find ./ -name "*.gcno" -delete >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting criterion.xml$(RESET)"
	@if [ -f criterion.xml ]; then \
		rm -f criterion.xml >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting tests.log$(RESET)"
	@if [ -f tests.log ]; then \
		rm -f tests.log >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting coverage.log$(RESET)"
	@if [ -f coverage.log ]; then \
		rm -f coverage.log >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting .cache/$(RESET)"
	@if [ -d .cache/ ]; then \
		rm -rf .cache >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️    Deleting .local/$(RESET)"
	@if [ -d .local/ ]; then \
		rm -rf .local >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
