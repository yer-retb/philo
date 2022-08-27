# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 11:41:17 by yer-retb          #+#    #+#              #
#    Updated: 2022/08/27 04:55:03 by yer-retb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = philo

cc = gcc

cflag = -Wall -Wextra -Werror #-g -fsanitize=thread

srcs = philo.c philo_utils.c

all : $(name)

$(name) :
	$(cc) $(cflag) $(srcs) -o $(name)

clean :
	rm -rf $(name)

fclean : clean
	rm -rf $(name)

re : clean all

push : 
	git add .
	git status
	git commit -m "update"
	git push github master
