
#include<WinSock2.h>
#include<stdio.h>


int main(void)
{
	
	WSADATA wsaData;

	//winsockの初期化 第一引数にはwinsockのバージョンを入れる
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
	//winsockのエラー処理　必須！
	if (err != 0)
	{
		switch (err)
		{
		case WSASYSNOTREADY:		//System Not Ready 
				//ネットワークサブシステムがネットワークへの接続を準備できてない
			printf("WSASYSNOTREADY");
			break;

		case WSAVERNOTSUPPORTED:	//Version Not Supported
				//要求されたwinsockのバージョンがサポートされてない
			printf("WSAVERNOTSUPPORTED");
			break;

		case WSAEINPROGRESS:		//Error In Progress
				//ブロッキング操作の実行中、またはサービスプロバイダがコールバック関数を処理している
			printf("WSAEINPROGRESS");
			break;

		case WSAEPROCLIM:			//Process Limited
				//winsockが処理できる最大プロセス数に達した
			printf("WSAEPROCLIM");
			break;

		case WSAEFAULT:				//Fault
				//第二引数であるlpWSADataは有効なポインタでない
			printf("WSAEFAULT");
			break;
		}
	}

	SOCKET sock;

	sock = socket(AF_UNSPEC, SOCK_STREAM, 0);
	
	//socketが正常に実行できているかの確認
	if (sock == INVALID_SOCKET)
	{
		printf("error : %d\n", WSAGetLastError());
		return 1;
	}

	//winsockの終了
	WSACleanup();

	getchar();
}