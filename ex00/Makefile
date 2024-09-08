NAME = btc
CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -g
OBJ_DIR = .obj/
SRC_DIR = src/

# ---------- Sources --------- #

SRC = \
	$(SRC_DIR)main.cpp \
	$(SRC_DIR)BitcoinExchange.cpp

OBJ =	$(SRC:%.cpp=$(OBJ_DIR)%.o)
D_OBJ =	$(SRC:%.cpp=$(OBJ_DIR)%.d)

# ---------- Rules --------- #

all:
	$(MAKE) $(NAME)

$(OBJ_DIR)%.o: %.cpp | $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CPP) $(CPP_FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)$(SRC_DIR)
	mkdir -p $@


clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

-include $(D_OBJ)

.PHONY: all clean flcean re