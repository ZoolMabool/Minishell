# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dguet <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 14:30:02 by dguet             #+#    #+#              #
#    Updated: 2022/12/21 16:04:12 by dguet            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_YELLOW="\e[38;5;226m"
_RED="\e[38;5;9m"
_GREEN="\e[38;5;10m" 

NAME		= minishell 

SRC			=	main.c\
				decoration/decoration.c\
				path/path.c\
				error/error.c\
				error/error_utils.c\
				builtin/pwd/builtin_pwd.c\
				builtin/echo/builtin_echo.c\
				builtin/cd/builtin_cd.c\
				builtin/export/extract_arg/extract_arg_after_equal.c\
				builtin/export/extract_arg/extract_arg_with_equal.c\
				builtin/export/update_envp_l/update_envp_l.c\
				builtin/export/print_export/print_export.c\
				builtin/export/check_arg/check_char_equal.c\
				builtin/export/check_arg/check_plus.c\
				builtin/export/check_arg/check_dollars.c\
				builtin/export/check_arg/check_if_new_variables.c\
				builtin/export/check_arg/compare_arg_envp_l.c\
				builtin/export/size_env_or_arg/len_arg.c\
				builtin/export/size_env_or_arg/size_arg.c\
				builtin/export/size_env_or_arg/size_arg_before_equal.c\
				builtin/export/size_env_or_arg/size_env.c\
				builtin/export/sort_export/sort_after_first_char.c\
				builtin/export/sort_export/sort_ascii.c\
				builtin/export/sort_export/sort_first_char.c\
				builtin/export/builtin_export.c\
				builtin/export/utils_export.c\
				builtin/unset/builtin_unset.c\
				builtin/unset/utils_unset.c\
				builtin/env/builtin_env.c\
				builtin/exit/builtin_exit.c\
				builtin/exit/exit_utils.c\
				free/free.c\
				utils/utils1.c\
				utils/utils2.c\
				utils/utils3.c\
				prompt.c\
				arg_parser/arg_parser.c\
				arg_parser/arg_parser_utils.c\
				arg_parser/isolate_chevrons.c\
				arg_parser/pipes_parser.c\
				arg_parser/pipes_parser_utils.c\
				arg_parser/env_var_interpreter/interpret_env_variables.c\
				arg_parser/env_var_interpreter/utils_env_var_interpreter.c\
				arg_parser/env_var_interpreter/extract_env_var_name.c\
				arg_parser/env_var_interpreter/delete_var_inside_arg.c\
				arg_parser/env_var_interpreter/replace_var_by_status_code.c\
				arg_parser/env_var_interpreter/interpret_current_env_variable.c\
				arg_parser/quotes_remover/remove_quotes.c\
				arg_parser/redirections/handle_infile_redirection.c\
				arg_parser/redirections/handle_outfile_redirection.c\
				arg_parser/redirections/redirections_utils.c\
				arg_parser/redirections/redirections_utils2.c\
				arg_parser/pipe_detection/isolate_pipe_symbols.c\
				execution/exec_without_pipes/exec_without_pipes.c\
				execution/exec_without_pipes/exec_without_pipes_utils.c\
				execution/exec_pipes/exec_pipes.c\
				execution/exec_pipes/exec_pipes_utils.c\
				execution/exec_pipes/exec_pipes_utils2.c\
				execution/execution_utils.c\
				execution/execution_utils2.c\
				heredoc/heredoc.c\
				signal/signal.c\

SRCDIR 		= ./src/

INCDIR 		= ./includes/

SRCS 		= $(addprefix $(SRCDIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

CFLAGS 		= -Wall -Werror -Wextra -g  -I$(INCDIR) -Ilibft -I/usr/local/include 

LFLAGS		= -Llibft -lft -L/usr/local/lib -lreadline

CC			= clang

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $@

all :		$(NAME)

$(NAME):	$(OBJS)
			@make -sC libft
			@$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LFLAGS)
			@echo $(_GREEN)
			@echo "*************************"
			@echo "*                       *"
			@echo "*  COMPILATION SUCCESS  *"
			@echo "*                       *"
			@echo "*************************"

clean_1 : 
			@echo $(_YELLOW)
			@echo "*************************"
			@echo "*                       *"
			@echo "*    CLEAN  COMPLETE    *"
			@echo "*                       *"
			@echo "*************************"

clean : 	clean_1
			@rm -f $(OBJS)
			@make -sC libft clean
fclean_1 :
			@echo $(_RED)
			@echo "*************************"
			@echo "*                       *"
			@echo "*    FCLEAN COMPLETE    *"
			@echo "*                       *"
			@echo "*************************"

fclean : 	clean fclean_1
			@rm -f $(NAME)
			@make -sC libft fclean
	
re : 		fclean all 

.PHONY: all clean fclean re
