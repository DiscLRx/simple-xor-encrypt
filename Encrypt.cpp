#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
	
	for(int i = 1; i < argc; i++){
		cout << "正在处理 " << argv[i] << "..." << endl;
		
		//目标路径
		string newFilePath = argv[i];
		string passwd;
		string filePath = argv[i];
		int abc = filePath.substr(filePath.rfind("\\")).find("_passwd_");
		if (abc>=0) {
			newFilePath = filePath.substr(0, filePath.rfind("_passwd_"));
			int passwdStart = filePath.rfind("_passwd_") + 8;
			passwd = (char*)filePath.substr(passwdStart).data();
		}
		else {
			string selfPath = argv[0];
			int passwdStart = selfPath.rfind("_passwd_") + 8;
			int passwdLength = selfPath.find(".exe") - passwdStart;
			passwd = (char*)selfPath.substr(passwdStart, passwdLength).data();
			newFilePath += "_passwd_";
			newFilePath += passwd;
		}
		cout << "password:" << passwd << endl << endl;

		//用于读取文件的数组
		char* buffer = new char[passwd.length()];
		for (int i = 0; i < passwd.length(); i++) {
			buffer[i] = '\0';
		}
			

		ifstream infile(argv[i], ios::in | ios::binary);
		ofstream outfile(newFilePath, ios::out | ios::binary);
		
		if (!infile.is_open()) {
			cout << "error" << endl;
			continue;
		}

		//读取数据并于密码进行异或
		while (!infile.eof()) { 
			infile.read(buffer, sizeof(buffer));
			for(int i = 0; i < passwd.length(); i++){
				buffer[i] = buffer[i] ^ passwd[i];
			}
			outfile.write(buffer, sizeof(buffer));
		}

		infile.close();
		outfile.close();
	}

	cout << endl << "Everything is done!" << endl;
	system("pause");
}
