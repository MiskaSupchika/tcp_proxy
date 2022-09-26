#ifndef HEADER_HPP
# define HEADER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include "header.hpp"
#include <poll.h>
#include <sstream>
#include <fstream>
#include <cstring>


# define COL_G "\e[1;38;2;55;255;0m"
# define COL_Y "\e[1;38;2;255;230;0m"
# define COL_B "\e[1;38;2;34;15;212m"
# define COL_R "\e[1;38;2;179;0;0m"
# define COL_RES "\e[m"

# define BUFF_SIZE 1024

# define PORT 1100
# define IP_ADRESS INADDR_ANY //hexadecimal


#endif