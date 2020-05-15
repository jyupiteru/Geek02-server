
#include<WinSock2.h>
#include<stdio.h>


int main(void)
{
	
	WSADATA wsaData;
	SOCKET sock;
	SOCKET sock0;

	//接続先の情報を入れる構造体
	sockaddr_in addr;
	sockaddr_in client;
	int len;
	
	//winsock2の初期化
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
	//winsock2のエラー処理　必須！
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

	//ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	
	//socketのエラー処理
	if (sock0 == INVALID_SOCKET)
	{
		printf("error : %d\n", WSAGetLastError());
		return 1;
	}

	//ソケットの設定
	addr.sin_family = AF_INET;					//アドレスファミリ
	addr.sin_port = htons(12345);				//ポート番号
	addr.sin_addr.S_un.S_addr = INADDR_ANY;		//IPアドレス

	//addrの情報をソケットに割り当てる
	if (bind(sock0, (sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("bind : %d", WSAGetLastError());
		return 1;
	}

	//TCPクライアントからの接続要求を待てる状態にする
	if (listen(sock0, 5) != 0)
	{
		printf("listen : %d\n", WSAGetLastError());
		return 1;
	}
	
	while (1)//ここがあると単純なTCPクライアントからの接続要求を複数回受け付けれる（何回も作っているから）
	{
		//TCPクライアントからの接続要求を受け付ける
		len = sizeof(client);
		
		
		sock = accept(sock0, (sockaddr *)&client, &len);
		if (sock == INVALID_SOCKET)
		{
			printf("accept : %d\n", WSAGetLastError());
			return 1;
		}

		//5文字送信
		int n = send(sock, "HELLO", 5, 0);//送りたいメッセージ、メッセージの長さ、
		if (n < 1)
		{
			printf("send : %d\n", WSAGetLastError());
			break;
		}

		//TCPセッションの終了
		closesocket(sock);
	}
	//winsockの終了
	WSACleanup();

	getchar();
}