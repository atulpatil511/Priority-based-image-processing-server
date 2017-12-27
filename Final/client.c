#include "csapp.c"

void millisleep(int milliseconds)
{
	usleep(milliseconds * 1000);
}
int main(int argc, char **argv)
{	
	int imgsize,count;
	int clientfd,ifd,port,oimgfd;
	int size2;
	char *host, buf[MAXLINE],ibuf[MAXLINE];
	rio_t rio,rio_i;
	char *image;
	image =argv[3];
	ifd=Open(image,O_RDWR, 0);
	if (argc != 4) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	//port = atoi(argv[2]);
	
	clientfd = Open_clientfd(host,argv[2]);
	Rio_readinitb(&rio, clientfd);
	Rio_readinitb(&rio_i,ifd);

	count=0;
	while (1) {
		imgsize=Rio_readlineb(&rio_i,ibuf, MAXLINE);
		if(imgsize<=0)
			break;
		Rio_writen(clientfd,ibuf,imgsize);
		count=count+imgsize;
		//printf("Bytes sent: %d\n",count);
	}
	
	Close(clientfd);
	millisleep(32000);
	if (fork()==0)
	{
		execl("/home/prkmufc/EOS_assignments/Project/bscfle/DisplayImage","./DisplayImage","out_grey.png",(char *)NULL);
	}
	if (fork()==0)
	{
		execl("/home/prkmufc/EOS_assignments/Project/bscfle/DisplayImage","./DisplayImage",image,(char *)NULL);
	}
	exit(0);
}
