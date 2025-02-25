
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

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
	
	BOOL yes = 1;//TIME_WAIT回避用

	char buf[2048];
	char inbuf[2048];

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
	addr.sin_port = htons(12345);				//サーバー側のポート番号
	addr.sin_addr.S_un.S_addr = INADDR_ANY;		//IPアドレス

	//本来は1ポート1個だが複数作れるようにする
	setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

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
	
	//応答用のHTTPメッセージを作成
	memset(buf, 0, sizeof(buf));
	_snprintf(buf, sizeof(buf),
		"HTTP/1.0 200 OK\r\n"
		"Content-Length: 20\r\n"
		"Content-Type: text/html\r\n"
		"\r\n"
		"HELLO\r\n");

	
	while (1)//ここがあると単純なTCPクライアントからの接続要求を複数回受け付けれる（何回も作っているから）
	{
		//TCPクライアントからの接続要求を受け付ける
		len = sizeof(client);
		
		//ソケットを受け取り繋ぐ
		sock = accept(sock0, (sockaddr *)&client, &len);
		if (sock == INVALID_SOCKET)
		{
			printf("accept : %d\n", WSAGetLastError());
			return 1;
		}

		//どのクライアントからリクエストを受け取ったか表示
		printf("accept connection from %s,port = %d\n", 
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		memset(inbuf, 0, sizeof(inbuf));
		recv(sock, inbuf, sizeof(inbuf), 0);

		//5文字送信
		int n = send(sock, buf, strlen(buf), 0);//送りたいメッセージ、メッセージの長さ、
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