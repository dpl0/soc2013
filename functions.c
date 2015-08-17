void
limitfd(int fd)
{
	cap_rights_t rights;

	if (fd == OUT_FILENO)
	  rights = CAP_READ|CAP_FSTAT|CAP_WRITE|CAP_FCHMOD|CAP_FCHOWN|CAP_FUTIMES;
	else if (fd == IN_FILENO)
	  rights = CAP_WRITE|CAP_READ|CAP_FSTAT;
	else if (fd == STDERR_FILENO)
	  rights = CAP_WRITE;
	else if ( fd == cwd )
	  rights = CAP_UNLINKAT|CAP_LOOKUP;

	if (cap_rights_limit(fd, rights) < 0 && errno != ENOSYS){
	  fprintf ( stderr, "%s: Couldn't limit rights for descriptor %d: %s.\n", 
		 progName, fd, strerror(errno));
	  setExit(1);
	  exit(exitValue);
	}
}

extern void
cap_init()
{
	if (cap_rights_limit(STDIN_FILENO, CAP_READ) < 0 && errno != ENOSYS){
		message_error("%d: %s", STDIN_FILENO, strerror(errno));
		exit(E_ERROR);
	}

	if (cap_rights_limit(STDOUT_FILENO, CAP_WRITE) < 0 && errno != ENOSYS){
		message_error("%d: %s", STDOUT_FILENO, strerror(errno));
		exit(E_ERROR);
	}

	if (cap_rights_limit(STDERR_FILENO, CAP_WRITE) < 0 && errno != ENOSYS){
		message_error("%d: %s", STDERR_FILENO, strerror(errno));
		exit(E_ERROR);
	}

	if (cap_enter() < 0 && errno != ENOSYS){
		message_error("cap_enter: %s", strerror(errno));
		exit(E_ERROR);
	}
	return;
}

#define DATALEN CMSG_LEN(sizeof(int))

int
sendfd(int s, int fd)
{	
	struct msghdr msg;	
	struct cmsghdr *cmsg;
	struct iovec io[1];
	char buf[1] = { "!" };
	int ret;

	io[0].iov_base = buf;
	io[0].iov_len = 1;

	if( (cmsg = malloc(DATALEN)) == NULL )
	  return -1;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = io;
	msg.msg_iovlen = 1;
	msg.msg_control =cmsg;
	msg.msg_controllen = DATALEN;

	cmsg->cmsg_len = DATALEN;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg) = fd;
	if( (ret = sendmsg(s, &msg, 0)) <= 0)
	  return -1;
	free(cmsg);
	return 0;
}

int
recvfd(int s)
{
	int fd;
	struct msghdr msg;	
	struct cmsghdr cmsg;
	char buf[1] = { "!" };
	struct iovec io[1];

	io[0].iov_base = buf;
	io[0].iov_len = 1;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = io;
	msg.msg_iovlen = 1;
	msg.msg_control = &cmsg;
	msg.msg_controllen = DATALEN;

	cmsg.cmsg_len = DATALEN;
	cmsg.cmsg_level = SOL_SOCKET;
	cmsg.cmsg_type = SCM_RIGHTS;
	if(recvmsg(s, &msg, 0) < 0)
		return -1;
	fd = *(int *)CMSG_DATA(&cmsg);
	return 0;
}