# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 11:41:17 by yer-retb          #+#    #+#              #
#    Updated: 2022/08/22 13:09:55 by yer-retb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = philo

cc = gcc

cflag = -Wall -Wextra -Werror

srcs = philo.c

obj = $(srcs:.c=.o)

all : $(name)

$(name) : $(obj)
	$(cc) $(srcs) -o $(name)

clean :
	rm -rf $(obj)

fclean : clean
	rm -rf $(name)

re : clean all

push : 
	git add .
	git status
	git commit -m "update"
	git push github master