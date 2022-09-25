# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 12:03:12 by nmathieu          #+#    #+#              #
#    Updated: 2022/09/25 05:44:17 by nmathieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      := webserv
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++98 -MMD -I src -g3 -D DEBUG
LINKFLAGS :=

SRC_DIR   := src
OBJ_DIR   := obj

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

all:
	@$(MAKE) --no-print-directory $(NAME)
.PHONY: all

clean:
	@echo "cleaning objects..."
	@rm -f $(OBJ_FILES) $(DEP_FILES)
.PHONY: clean

fclean:
	@$(MAKE) --no-print-directory clean
	@echo "cleaning binary..."
	@rm -f $(NAME)
.PHONY: fclean

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
.PHONY: re

$(NAME): $(OBJ_FILES)
	@echo "linking..."
	@$(CXX) $(LINKFLAGS) $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "compiling '$<'..."
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP_FILES)
