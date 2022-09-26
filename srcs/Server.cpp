#include "header.hpp"

int	InitialSetup(void)
{
	struct sockaddr_in	sa;
	int					SocketFD;
	std::stringstream	ss;

	if (IP_ADRESS)
		ss << IP_ADRESS;
	else
		ss << "127.0.0.1";
	SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SocketFD == -1)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	sa.sin_addr.s_addr = htonl(IP_ADRESS);

	if (bind(SocketFD,(struct sockaddr *)&sa, sizeof(sa)) == -1)
	{
		perror("bind failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	std::cout<<"SERVER PORT: "<<COL_Y<<"1100"<<COL_RES<<std::endl;
	std::cout<<"SERVER IP: "<<COL_Y<<ss.str().c_str()<<COL_RES<<std::endl;
	if (listen(SocketFD, 100) == -1)
	{
		perror("listen failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	return SocketFD;
}

int main(void)
{
	struct pollfd fds[FD_SETSIZE];
	u_char	buff[BUFF_SIZE];
	int	readed = 0;
	int ret = 0;
	int flag = 0;
	unsigned int CountConnects = 1;
	std::ofstream fout;
	
	for (int i = 1; i < FD_SETSIZE; i++)
		fds[i].fd = -1;
	fds[0].fd = InitialSetup();
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	while (true)
	{
		int CountFD;

		if (flag > 0)
		{
			std::cout << "exit\n";
			exit(EXIT_SUCCESS);
		}
		if ((CountFD = poll(fds, CountConnects, -1)) < 0)
		{
			perror("POLL CRASH");
			exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < CountConnects; i++)
		{
			if (fds[i].fd > 0 && (fds[i].revents & POLLIN) == POLLIN)
			{
				++flag;
				if (!i)
				{
					flag = 0;
					fds[CountConnects].fd = accept(fds[i].fd, NULL, NULL);
					std::cout << COL_R << "NEW CONNECT" << COL_RES << '\n';
					fds[CountConnects].events = POLLIN;
					fds[CountConnects].revents = 0;
					++CountConnects;
				}
				else
				{
					char	buff[BUFF_SIZE];
					
					flag = 0;
					readed = read(fds[i].fd, buff, BUFF_SIZE);
					std::string cmd(buff);
					
					fds[i].revents = 0;
					fout.open("log.txt", std::ios::app);
					if (!fout.is_open())
					{
					 	perror("cannot file");
					 	exit(EXIT_FAILURE);
					}
					std::cout << COL_B << "MESSAGE " << i << COL_RES << '\n';
					if((!(strncmp( cmd.c_str(), "SELECT ", 8)) || !(strncmp( cmd.c_str(), "select ", 8))
						|| !(strncmp( cmd.c_str(), "CREATE TABLE ", 14)) || !(strncmp( cmd.c_str(), "create table ", 14))
						|| !(strncmp( cmd.c_str(), "UPDATE ", 8)) || !(strncmp( cmd.c_str(), "update ", 8))
						|| !(strncmp( cmd.c_str(), "INNER ", 7)) || !(strncmp( cmd.c_str(), "inner ", 7))))
					{
						//while(!fout.eof())
						//{
							fout << buff << '\n';
						//}
					}
					else
						printf("{%s}\n", buff);
					fout.close();
					if (!readed)
					{
						write(fds[i].fd, "end", 3);
						write(1, "end\n", 4);
						fds[i].fd = -1;
						--CountConnects;
						continue ;
					}
					buff[readed] = 0;
					write(fds[i].fd, "i got message", 13);
					fds[i].revents = 0;
				}
			}
		}
	}
	return 0;
}
