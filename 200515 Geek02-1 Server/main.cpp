
#include<WinSock2.h>
#include<stdio.h>


int main(void)
{
	
	WSADATA wsaData;

	//winsock�̏����� �������ɂ�winsock�̃o�[�W����������
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
	//winsock�̃G���[�����@�K�{�I
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

	SOCKET sock;

	sock = socket(AF_UNSPEC, SOCK_STREAM, 0);
	
	//socket������Ɏ��s�ł��Ă��邩�̊m�F
	if (sock == INVALID_SOCKET)
	{
		printf("error : %d\n", WSAGetLastError());
		return 1;
	}

	//winsock�̏I��
	WSACleanup();

	getchar();
}