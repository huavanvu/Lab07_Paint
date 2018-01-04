// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SocketPair.h"
#include<conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object




WCHAR* stringToWCHAR(string s) {
	WCHAR* a = new WCHAR[s.length()];
	for (int i = 0; i < s.length(); i++)
		a[i] = s[i];
	a[s.length()] = '\0';
	return a;
}

string message_403() {
	string body;
	body = body +
		"<html>\r\n" +
		"<head><title>403 Forbidden</title><head>\r\n"
		"<body>\r\n" +
		"<h1> 403 Forbidden</h1>\r\n" +
		"<p>You don't have permission to access / on this server.</p>\r\n" +
		"</body>\r\n" +
		"</html>\r\n";

	stringstream convert;
	convert << body.length();
	string strlen_body = convert.str();

	string header;
	header = header +
		"HTTP/1.0 403 Forbidden\r\n" +
		"Content-type: text/html\r\n" +
		"Connection: close\r\n" +
		"Content-Length: ";

	string message = header + strlen_body + "\r\n\r\n" + body;
	return message;
}

bool goodWeb(string host, fstream &blackList) {
	string list;
	blackList.seekg(0);
	while (!blackList.eof()) {
		getline(blackList, list);
		if (list == host)
			return false;
	}
	return true;
}
// cái này bữa t gửi m à
// chính nó
// cái m gửi xong m nói còn 30' số phận 
// vãi loz
// t thật là...
// đù má cái lỗi này là sao @@
// m gởi chứ ai
// t nói là bản chưa hoàn chỉnh mà =))
// mà t đâu có từng bị lỗi này
// ê m cái này là đọc file à
// chạy thread đó con
// sửa bug giùm t =))
// lỗi chưa từng gặp thì sửa cái qq à
// chúc mừng chúc mừng, t đi ngủ 
// đm cứu t
// vấn đáp demo ông thầy coi qq gì
// m ráng suaawr cái lỗi máu chó đó đi rồi kêu t
// t còn del biết code sao sửa đc
// t chịu thua, sửa được cái đó là xong
// vậy giờ sao??????????
// nhờ cao nhân khác coi đi
DWORD WINAPI THREAD(LPVOID ServerClient) {
	SocketPair* socketPair = (SocketPair*)ServerClient;
	socketPair->Client.Attach(socketPair->Proxy);
	cout << "Da co Client ket Noi !!!" << endl << endl;

	char temp[513];
	stringstream s;
	string firstL, twoL;
	socketPair->Client.Receive(temp, 512);
	string hostTemp;
	s << temp;
	s >> hostTemp;
	s >> hostTemp;
	string host;
	if (hostTemp.find(HTTP) != -1)
		host.append(hostTemp, 7, hostTemp.find('/', 7) - 7);
	else
		return 1;

	cout << host << endl;
	//------------------------------------------
	// trang bị cấm, ĐẶT ĐOẠN NÀY SAU KHI TÁCH ĐƯỢC TÊN DOMAIN, vd: kenh14.vn
	if (!goodWeb(host, socketPair->blackList))
	{
		string chuoicangui = message_403();
		socketPair->Client.Send(chuoicangui.c_str(), chuoicangui.length()); // gửi thông báo 403 Forbidden
		socketPair->Client.Close();
		return 1;
	}
	//------------------------------------------

	WCHAR *wchar_host = NULL;
	wchar_host = stringToWCHAR(host);
	CSocket client_that;
	client_that.Create();
	client_that.Connect(wchar_host, 80);

	string chuoicangui1(temp);
	string chuoicangui;
	if (hostTemp.find("http://") != -1) {
		chuoicangui.append(chuoicangui1, 0, chuoicangui1.find("HTTP"));
		chuoicangui.erase(4, 7 + host.length());
		//if (chuoicangui == "GET / ") 
		//chuoicangui = "GET ";
		chuoicangui = chuoicangui + "HTTP/1.1\r\nHost: " + host + "\r\nUser-Agent: eXecutive DEMO Client\r\n\r\n";
		chuoicangui.push_back(0);
	}


	client_that.Send(chuoicangui.c_str(), chuoicangui.length());

	//Nhan tra ve cua chuoi tu trang web muon truy cap
	while (1)
	{
		char chuoinhan[513];
		memset(chuoinhan, 0, 512);

		int flag = client_that.Receive(chuoinhan, 512);
		//cout << chuoinhan << endl;
		if (flag == 0 || flag == -1)
			break;

		socketPair->Client.Send(chuoinhan, flag);
		//đọc dòng 1,2,6
	}
	socketPair->Client.Close();
	client_that.Close();
	return 1;
}




int main()
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.

		// Khoi tao thu vien Socket
		if (AfxSocketInit() == FALSE)
		{
			cout << "Khong the khoi tao Socket Libraray";
			return FALSE;
		}

		CSocket ServerSocket; //cha
							  // Tao socket cho server, dang ky port la 1234, giao thuc TCP
		if (ServerSocket.Create(8888) == 0) //SOCK_STREAM or SOCK_DGRAM., sv phải có port (8888)
		{
			cout << "Khoi tao that bai !!!" << endl;
			cout << ServerSocket.GetLastError();
			return FALSE;
		}
		cout << "Server khoi tao thanh cong !!!" << endl;
		if (ServerSocket.Listen(1) == FALSE)
		{
			cout << "Khong the lang nghe tren port nay !!!" << endl;
			ServerSocket.Close();
		
			return FALSE;
		}


		while (true) {
			SocketPair *socketPair = new SocketPair;

				// cl ảo đc tạo ra từ sv để kết nối với sv
				// Khoi tao mot socket de duy tri viec ket noi va trao doi du lieu
				socketPair->blackList.open("blacklist.conf", ios::in);
				if (!socketPair->blackList.good())
					return 0;
				ServerSocket.Accept(socketPair->Client);
				socketPair->Proxy = socketPair->Client.Detach();//ddeer ko bi loi
				CreateThread(0, 0, THREAD, (LPVOID)&socketPair, 0, 0);
				
			
		}
		ServerSocket.Close();
	}
	_getch();
	return nRetCode;
}

