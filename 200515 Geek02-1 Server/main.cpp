
#include<WinSock2.h>
#include<stdio.h>


int main(void)
{
	
	WSADATA wsaData;
	SOCKET sock;
	SOCKET sock0;

	//�ڑ���̏�������\����
	sockaddr_in addr;
	sockaddr_in client;
	int len;
	
	//winsock2�̏�����
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
	//winsock2�̃G���[�����@�K�{�I
	if (err != 0)
	{
		switch (err)
		{
		case WSASYSNOTREADY:		//System Not Ready 
				//�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��ĂȂ�
			printf("WSASYSNOTREADY");
			break;

		case WSAVERNOTSUPPORTED:	//Version Not Supported
				//�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����ĂȂ�
			printf("WSAVERNOTSUPPORTED");
			break;

		case WSAEINPROGRESS:		//Error In Progress
				//�u���b�L���O����̎��s���A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			printf("WSAEINPROGRESS");
			break;

		case WSAEPROCLIM:			//Process Limited
				//winsock�������ł���ő�v���Z�X���ɒB����
			printf("WSAEPROCLIM");
			break;

		case WSAEFAULT:				//Fault
				//�������ł���lpWSAData�͗L���ȃ|�C���^�łȂ�
			printf("WSAEFAULT");
			break;
		}
	}

	//�\�P�b�g�̍쐬
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	
	//socket�̃G���[����
	if (sock0 == INVALID_SOCKET)
	{
		printf("error : %d\n", WSAGetLastError());
		return 1;
	}

	//�\�P�b�g�̐ݒ�
	addr.sin_family = AF_INET;					//�A�h���X�t�@�~��
	addr.sin_port = htons(12345);				//�|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = INADDR_ANY;		//IP�A�h���X

	//addr�̏����\�P�b�g�Ɋ��蓖�Ă�
	if (bind(sock0, (sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("bind : %d", WSAGetLastError());
		return 1;
	}

	//TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	if (listen(sock0, 5) != 0)
	{
		printf("listen : %d\n", WSAGetLastError());
		return 1;
	}
	
	while (1)//����������ƒP����TCP�N���C�A���g����̐ڑ��v���𕡐���󂯕t�����i���������Ă��邩��j
	{
		//TCP�N���C�A���g����̐ڑ��v�����󂯕t����
		len = sizeof(client);
		
		
		sock = accept(sock0, (sockaddr *)&client, &len);
		if (sock == INVALID_SOCKET)
		{
			printf("accept : %d\n", WSAGetLastError());
			return 1;
		}

		//5�������M
		int n = send(sock, "HELLO", 5, 0);//���肽�����b�Z�[�W�A���b�Z�[�W�̒����A
		if (n < 1)
		{
			printf("send : %d\n", WSAGetLastError());
			break;
		}

		//TCP�Z�b�V�����̏I��
		closesocket(sock);
	}
	//winsock�̏I��
	WSACleanup();

	getchar();
}