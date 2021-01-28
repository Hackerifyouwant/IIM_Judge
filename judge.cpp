#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <windows.h>
#include <thread>
#define Qsize 15
using namespace std;

vector<string> code = {
    "PA.cpp",
    "PB.cpp",
    "PC.cpp",
    "PD.cpp",
    "PE.cpp",
    "PF.cpp",
    "PG.cpp",
    "PH.cpp",
    "PI.cpp",
    "PJ.cpp",
    "PK.cpp",
    "PL.cpp",
    "PM.cpp",
    "PN.cpp",
    "PO.cpp"
};
vector<string> stdexe = {
    ".\\stdexe\\PA.exe",
    ".\\stdexe\\PB.exe",
    ".\\stdexe\\PC.exe",
    ".\\stdexe\\PD.exe",
    ".\\stdexe\\PE.exe",
    ".\\stdexe\\PF.exe",
	".\\stdexe\\PG.exe",
	".\\stdexe\\PH.exe",
	".\\stdexe\\PI.exe",
	".\\stdexe\\PJ.exe",
	".\\stdexe\\PK.exe",
	".\\stdexe\\PL.exe",
	".\\stdexe\\PM.exe",
	".\\stdexe\\PN.exe",
	".\\stdexe\\PO.exe"
};
vector<int> timeLimit = {
	3000, //PA
	3000, //PB
	3000, //PC
	3000, //PD
	3000, //PE
	3000, //PF
	3000, //PG
	3000, //PH
	3000, //PI
	3000, //PJ
	3000, //PK
	3000, //PL
	3000, //PM
	3000, //PN
	3000 //PO
};
struct stdpoint{
	int ac;
	int score;
};
vector<stdpoint> point[Qsize] = {
	{ {15,100} }, //PA
	{ {5,80}, {10,20} }, //PB
	{ {3,80}, {10,20} }, //PC
	{ {10,100} }, //PD
	{ {1,20}, {5,80} }, //PE
	{ {1,30}, {10,70} }, //PF
	{ {10,200} }, //PG
	{ {10,200} }, //PH
	{ {3,100},{6,30},{9,20},{10,20},{15,30} }, //PI
	{ {1,20},{10,180} }, //PJ
	{ {10,500} }, //PK
	{ {10,500} }, //PL
	{ {9,150},{10,50},{40,300}}, //PM
	{ {3,100},{6,100},{7,100},{15,200} }, //PN
	{ {1,10},{2,590},{6,400} }//PO
};//give point
vector<string> pass = {
	"1161600645276312086",//00
	"9120858854011954176",//01
	"11403672129377284778",//02
	"16106851318241236190",//03
	"7505362212639305056",//04
	"4340829246309530352",//05
	"8457658525508668529",//06
	"14750692848948102112",//07
	"4849556893638929523",//08
	"10684590813672576286",//09
	"12580444782592529261",//10
	"15744869808342778265",//11
	"5284386902360226614",//12
	"17701551130199329813",//13
	"15682192332403167456",//14
	"3528482582133192368",//15
	"15081669479839490267",//16
	"16345392660906430544",//17
	"740808813235598034",//18
	"4565305586655455154",//19
	"757711663213919411",//20
	"2346346556707671216",//21
	"7757769129762506563",//22
	"1745823704143993913",//23
	"3859459213024515079"//24
};
vector<string> testcase[Qsize];
string acc; // ex: team01
bool kill = false;
bool run = false;

bool fileCompare(const string &f1, const string &f2);
void cmd(const string &str);
void genTestCase(const int &p);
int kmp(const string& str, const string& pattern);
void timekill();
/* Unfinish task:
	1.測資
	2.題敘
	3.Time Limit
	4.給分標準
	5.account password (O
	6.github repository 
	7.server code update to Qsize = 15 (O
	8. 標程加密 
*/
int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(0);
//    cmd("echo off");
	srand((unsigned int) time(NULL));
	cmd("if exist testrepo ( rd /s /q testrepo > Nul 2> Nul )");
    fstream file;
    fstream in;
    fstream team;
    fstream submitfile;
    fstream temp;
    team.open("teaminfo.txt");
    if(!team){
        cout << "Log in fail!\n";
        cmd("pause");
        exit(0);
    }
    string password;
    team >> acc;
    team >> password;
    int key = (acc[4] - '0') * 10 + (acc[5] - '0'); 
    if(pass[key] != password){
        cout << "Incorrect account or password!\n";
        cmd("pause");
        exit(0);
    }
    team.close();

//    cmd("git clone https://g...content-available-to-author-only...b.com/Hackerifyouwant/testrepo.git");
//    cmd("attrib +h testrepo");
//    submitfile.open("./testrepo/" + acc+"_submission.md", ios::app);
    
	fstream f;
	f.open("temp.txt", ios::out);
	f.close();
    for(int i = 0; i < Qsize; i++){
        if(file.is_open()) file.close();
        file.open(code[i]);
        if(!file) continue;
        cout << "Juding P" << (char)('A'+i) << "...\n";
        genTestCase(i);
        temp.open("temp.txt", ios::app);
	    if(!temp){
	    	cout << "Fail to open temp.txt!\n";
	    	system("pause");
	    	exit(1);
		}
//		cmd("attrib +h temp.txt");
        int result = 0; // 0: AC   1: CE    2: WA    3:TLE   4: RE  
        int ac = 0;// Accepted testcase 
        cmd("g++ -std=c++11 -o code " + code[i]);
        in.open("code.exe");
        if(!in)
            result = 1;
        else{
//        	cmd("attrib +h code.exe");
            int totalTime = 0;// unit: ms
            thread th(timekill);
            kill = false;
            run = true;
            for(int j = 0; j < testcase[i].size(); j++){
                // cmd("echo " + testcase[i][j] + " > input.txt");
                cmd("echo create > input.txt");
//                cmd("attrib +h input.txt");
                in.close();
                in.open("input.txt", ios::out);
                in << testcase[i][j];
                in.close();
                int start = clock();
                cmd("code.exe < input.txt > output.txt && echo %errorlevel% > errormsg.txt");
                totalTime += clock() - start;
                fstream f;
                int msg = -1;
                f.open("errormsg.txt");
                if(!f){
                	result = 4;
					break;
				}
				f >> msg;
				if(msg) {
					result = 4;
					break;
				}
				if(f.is_open())f.close();
				cmd("del /f /s /q errormsg.txt > Nul 2> Nul");
//                cmd("attrib +h output.txt");
                if(totalTime > timeLimit[i]){
                    result = 3;
                    break;
                }
                cmd("echo 57086ebc9d789f0caabce72c2d340a64323045df8d6e94766f8300b42dce7d01 >> input.txt");
                cmd(stdexe[i] + " < input.txt > answer.txt");
//                cmd("attrib +h answer.txt");
                if(!fileCompare("output.txt", "answer.txt")){
                    result = 2;
                    break;
                }
                ac++;
            }
            run = false;
            th.join();
            if(kill) result = 3;
            cout << "Runtime = " << totalTime << " ms\n";
        }
        if(in.is_open()) in.close();
        cmd("del /f /s /q input.txt > Nul 2> Nul");
	    cmd("del /f /s /q output.txt > Nul 2> Nul");
	    cmd("del /f /s /q answer.txt > Nul 2> Nul");
	    cmd("del /f /s /q code.exe > Nul 2> Nul");
        string question = "PA";
        question[1] = i + 'A';
        int score = 0;
        cout << question << ": " << ac << "/" << testcase[i].size() << " testcases passed!\n";
        for(int j = 0; j < point[i].size(); j++)
        	if(ac >= point[i][j].ac) score += point[i][j].score;
        if(!result){
			temp << question << " | AC | " << score << " | ";
			cout << "result: Accepted\n";
		}
        else if(result == 1) {
        	temp << question << " | CE | " << score << " | ";
        	cout << "result: Compile Error\n";
		}
        else if(result == 2) {
        	temp << question << " | WA | " << score << " | ";
        	cout << "result: Wrong Answer\n";
		}
        else if(result == 3) {
        	temp << question << " | TLE | " << score << " | ";
        	cout << "result: Time Limit Exceeded\n";
        }
        else if(result == 4) {
        	temp << question << " | RE | " << score << " | ";
        	cout << "result: Runtime Error\n";
        }
        cout << "score: " << score << "\n\n";
//        cmd("cd testrepo && echo %time% >> " + acc + "_submission.md");
		temp.close();
		cmd("echo %time% >> temp.txt");
    }

    if(file.is_open()) file.close();
    if(team.is_open()) team.close();
    if(in.is_open()) in.close();
    if(submitfile.is_open()) submitfile.close();
    if(temp.is_open()) temp.close(); 
    cmd("git clone https://github.com/Hackerifyouwant/testrepo.git");
//    cmd("attrib +h testrepo");
//    cmd("git pull");
    cmd("type temp.txt >> .\\testrepo\\" + acc + "_submission.md");
    cmd("cd testrepo && git add " + acc + "_submission.md");
    cmd("cd testrepo && git commit -m \"update submission\"");
    
//    cmd("del /f /s /q *.cpp");
    cmd("if exist temp.txt del /f /s /q temp.txt > Nul 2> Nul");
//    cmd("cd testrepo && git pull --rebase"); 
//    cmd("cd testrepo && git push -u origin master");
	fstream f1, f2;
	string log, logmaster, str;
    while(true){
    	cmd("cd testrepo && git pull --rebase");
    	cmd("cd testrepo && git push -u origin master");
    	cmd("cd testrepo && ( git log -1 ) > ../log.txt");
    	cmd("cd testrepo && ( git log origin/master -10 ) > ../logmaster.txt");
    	f1.open("log.txt");
    	f2.open("logmaster.txt");
    	log.clear();
	    logmaster.clear();
    	while(getline(f1, str)) log += str + "\n";
    	while(getline(f2, str)) logmaster += str + "\n";
    	f1.close();
    	f2.close();
    	if(kmp(logmaster, log) != -1) break;
    	Sleep(rand() % 10000);
    }
//    system("pause");
    cmd("rd /s /q testrepo > Nul 2> Nul") ;
    cmd("del /f /s /q log.txt > Nul 2> Nul");
    cmd("del /f /s /q logmaster.txt > Nul 2> Nul");
    cmd("del /f /s /q *.cpp > Nul 2> Nul"); 
    cout << "\n\nJudge評測結束 請關閉\n";
    system("pause");
    return 0;
}

bool fileCompare(const string &f1, const string &f2){
    ifstream file1, file2;
    string str, str1, str2;
    file1.open(f1);
    file2.open(f2);
    while(getline(file1,str1)) {
    	if(!getline(file2, str2)) return false;
    	if(str1 != str2) return false;
    }
    if(getline(file2, str2)) return false;
    file1.close();
    file2.close();
    return true;
}
void cmd(const string &str){
    system(str.c_str());
}
void genTestCase(const int & p){
	if(!p){ //PA
		string s;
		int arr[3];
		for(int i = 0; i < 15; i++){
			s.clear();
			arr[0] = rand();
			arr[1] = rand();
			arr[2] = rand();
			sort(arr,arr+3);
			s = to_string(arr[0]) + " " + to_string(arr[1]) + " " + to_string(arr[2]) + "\n";
			testcase[0].push_back(s);
		} 
	}
	else if(p == 1){ //PB
		testcase[1].push_back("3 4 5 \n");
		testcase[1].push_back("7 24 25 \n");
		testcase[1].push_back("8 15 17 \n");
		testcase[1].push_back("5 12 13 \n");
		testcase[1].push_back("20 21 29 \n");
		int a, b, c;
		string s;
		for(int i = 0; i < 5; i++){
			s.clear();
			a = rand() % 1000 + 1;
			b = rand() % 1000 + 1;
			c = rand() % (abs(a+b) - abs(a-b) + 1) + abs(a-b) + 1;
			s = to_string(a) + " " + to_string(b) + " " + to_string(c) + "\n";
			testcase[1].push_back(s);
		}
	}
	else if(p == 2){ //PC
		string s;
		testcase[2].push_back("1\n 698745\n");
		s = "3\n";
		for(int i = 0; i < 3; i++) s += to_string(3*rand()) + " ";
		testcase[2].push_back(s + "\n"); 
		s = "10\n";
		for(int i = 0; i < 10; i++) s += to_string(10*rand()) + " ";
		testcase[2].push_back(s + "\n"); 
		
		int n;
		for(int i = 0; i < 7; i++){
			n = rand() % 100 + 50;
			s = to_string(n) + "\n";
			for(int j = 0; j < n; j++)
				s += to_string(rand()) + " ";
			testcase[2].push_back(s+"\n");
		}
	}
	else if(p == 3){//PD
		int a, b, c;
		for(int i = 0; i < 10; i++){
			a = rand() + 1;
			b = rand() + 1;
			c = rand() + 1;
			testcase[3].push_back(to_string(a)+" "+to_string(b)+" "+to_string(c)+"\n");
		}
	}
	else if(p == 4){//PE
	    testcase[4].push_back("Orphan\n");
	    testcase[4].push_back("Alice\n");
	    testcase[4].push_back("Bob\n");
	    testcase[4].push_back("visitorckw\n");
	    testcase[4].push_back("mr.NTD\n");
	}
	else if(p == 5){ //PF
		testcase[p].push_back("1\n100\n");// n = 1
		testcase[p].push_back("2\n10 90\n");// n = 2
		testcase[p].push_back("3\n6 24 70\n");// n = 3
		testcase[p].push_back("4\n75 5 5 15\n");// n = 4
		testcase[p].push_back("5\n9 1 15 62 13\n");//n = 5
		for(int i = 0; i < 4; i++){
			string str;
			str.clear();
			int num = 0, temp, ctr = 0;
			while(true){
				temp = rand() % 99 + 1;
				if( temp + num >= 100) break;
				num += temp;
				str += to_string(temp) + " ";
				ctr++;
			}
			str += to_string(100 - num) + "\n";
			ctr++;
			testcase[p].push_back(to_string(ctr) + "\n" + str);
		}
		string s = "100\n";
		for(int i = 0; i < 100; i++) s += "1 ";
		testcase[p].push_back(s+"\n");//n = 100
	}
	else if(p == 6){ // PG
		string str;
		for(int i = 0; i < 10; i++){
			str.clear();
			int n = rand() % 300 + 1;
			str += to_string(n) + "\n";
			for(int j = 0; j < n; j++)
				str += to_string(rand()) + " ";
			str += "\n";
			testcase[p].push_back(str);
		}
	}
	else if(p == 7){ //PH
		for(int i = 0; i < 10; i++){
			int a = rand() + 1;
			int b = a + rand();
			testcase[p].push_back(to_string(a) + " " + to_string(b) + "\n");
		}
	}
	else if(p == 8){ //PI
		int n;
		string str(100,'A');
		for(int i = 0; i < 3; i++){
			n = rand() % 26;
			for(int j = 0; j < 100; j++)
				str[i] = 'A' + rand() % 26;
			testcase[p].push_back(str + " "+to_string(n)+"\n");
		}//simple case
		for(int i = 0; i < 3; i++){
			n = INT_MAX;
			for(int j = 0; j < 100; j++)
				str[i] = 'A' + rand() % 26;
			testcase[p].push_back(str + " "+to_string(n)+"\n");
		}// n = INT_MAX case
		for(int i = 0; i < 3; i++){
			n = - rand() % 26;
			for(int j = 0; j < 100; j++)
				str[i] = 'A' + rand() % 26;
			testcase[p].push_back(str + " "+to_string(n)+"\n");
		}// n = negative
		for(int i = 0; i < 90; i++) str[i] = 'z';
		testcase[p].push_back(str + " 25\n");//overflow testcase
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 100; j++){
				bool big = rand() % 2;
				if(big) str[j] = rand() % 26 + 'A';
				else str[j] = rand() % 26 + 'a';
			}
			testcase[p].push_back(str+" "+to_string(rand()) + "\n");
		}//random testcase
	}
	else if(p == 9){ // PJ
		testcase[p].push_back("3\n");
		for(int i = 0; i < 9; i++)
			testcase[p].push_back(to_string(rand() % 30 + 1) + "\n");
	}
	else if(p == 10){ // PK
		for(int i = 0; i < 3; i++){
			testcase[p].push_back("2\n0 0\n0 0\n0 0\n1 1\n");
			testcase[p].push_back("2\n0 1\n1 0\n0 0\n1 1\n");
		}
		string s = "10\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 0 1 1 1 1\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 1 1 1 1 1\n";
		s += "0 0 0 1 0 0 0 1 1 1\n";
		s += "1 1 0 0 0 1 0 0 0 0\n";
		s += "0 0\n9 9\n";
		testcase[p].push_back(s);
		s = "10\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 1 1 1 1 1\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 1 1 1 1 1\n";
		s += "0 0 0 1 0 0 0 1 1 1\n";
		s += "1 1 0 0 0 1 1 0 0 0\n";
		s += "0 0\n9 9\n";
		testcase[p].push_back(s);
		s = "7\n";
		s += "1 1 1 1 1 1 1\n";
        s += "1 0 0 0 0 0 1\n";
        s += "1 0 1 0 1 0 1\n";
        s += "1 0 0 1 0 1 1\n";
        s += "1 1 0 1 0 1 1\n";
        s += "1 0 0 0 0 0 1\n"; 
        s += "1 1 1 1 1 1 1\n";
		s += "1 1\n5 5\n"; 
        testcase[p].push_back(s);
        s = "7\n";
		s += "1 1 1 1 1 1 1\n"; 
        s += "1 0 0 0 0 0 1\n";
        s += "1 0 1 0 1 0 1\n";
        s += "1 0 0 1 0 1 1\n";
        s += "1 1 1 1 0 1 1\n";
        s += "1 0 0 0 0 0 1\n"; 
        s += "1 1 1 1 1 1 1\n";
		s += "1 1\n5 5\n"; 
        testcase[p].push_back(s);
	}
	else if(p == 11){ // PL
		for(int i = 0; i < 2; i++){
			testcase[p].push_back("2\n0 0\n0 0\n0 0\n1 1\n");
			testcase[p].push_back("2\n0 1\n0 0\n0 0\n1 1\n");
			testcase[p].push_back("2\n0 0\n1 0\n0 0\n1 1\n");
		}
		string s;
		s = "5\n";
		s += "0 1 1 1 1\n";
		s += "0 0 1 1 1\n";
		s += "1 0 0 1 1\n";
		s += "1 1 0 0 1\n";
		s += "1 1 1 0 0\n";
		s += "0 0\n4 4\n";
		testcase[p].push_back(s);
		s = "5\n";
		s += "0 0 0 1 1\n";
		s += "1 0 0 0 1\n";
		s += "1 0 1 0 1\n";
		s += "1 0 0 0 1\n";
		s += "1 0 0 0 0\n";
		s += "0 0\n4 4\n";
		testcase[p].push_back(s);
		s = "10\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 1 0 1 1 1\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 1 1 1 1 1\n";
		s += "0 0 0 1 0 0 0 1 1 1\n";
		s += "1 1 0 0 0 1 0 0 0 0\n";
		s += "0 0\n9 9\n";
		testcase[p].push_back(s);
		s = "10\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 1 1 1 1 0 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 0 1 1 1 1 1 1 1\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "1 1 0 1 1 1 1 1 1 0\n";
		s += "0 0 0 0 0 0 0 0 0 0\n";
		s += "0 1 1 1 1 1 1 0 1 1\n";
		s += "0 0 0 1 0 0 0 1 1 1\n";
		s += "1 1 0 0 0 1 0 0 0 0\n";
		s += "0 0\n9 9\n";
		testcase[p].push_back(s);
	}
	else if(p == 12){ //PM
		for(int i = 1; i <= 9; i++)
			testcase[p].push_back(to_string(i)+"\n");
		testcase[p].push_back("0\n");
		for(int i = 0; i < 6; i++)
			for(int j = 35; j <= 39; j++)
				testcase[p].push_back(to_string(j)+"\n");
	}
	else if(p == 13){ //PN
		for(int i = 0; i < 3; i++){
			int x = rand() % 10 + 5;
			int y = x;
//			int y = rand() % 10 + 5;
			int k = 1;
			string s;
			s.clear();
			s += to_string(x) + " " + to_string(y) + " " + to_string(k) + "\n";
			for(int a = 0; a < x; a++){
				for(int b = 0; b < y; b ++){
					s += to_string(rand()) + " ";
				}
				s += "\n";
			}
			testcase[p].push_back(s);
		}
		for(int i = 0; i < 3; i++){
			int x = rand() % 10 + 5;
			int y = x;
			int k = 2;
			string s;
			s.clear();
			s += to_string(x) + " " + to_string(y) + " " + to_string(k) + "\n";
			for(int a = 0; a < x; a++){
				for(int b = 0; b < y; b ++){
					s += to_string(rand()) + " ";
				}
				s += "\n";
			}
			testcase[p].push_back(s);
		}
		for(int i = 0; i < 1; i++){
			int x = rand() % 10 + 5;
			int y = x;
			int k = INT_MAX;
			string s;
			s.clear();
			s += to_string(x) + " " + to_string(y) + " " + to_string(k) + "\n";
			for(int a = 0; a < x; a++){
				for(int b = 0; b < y; b ++){
					s += to_string(rand()) + " ";
				}
				s += "\n";
			}
			testcase[p].push_back(s);
		}
		for(int i = 0; i < 8; i++){
			int x = rand() % 10 + 5;
			int y = rand() % 10 + 5;
			int k = rand() % 2 + 2;
			string s;
			s.clear();
			s += to_string(x) + " " + to_string(y) + " " + to_string(k) + "\n";
			for(int a = 0; a < x; a++){
				for(int b = 0; b < y; b ++){
					s += to_string(rand()) + " ";
				}
				s += "\n";
			}
			testcase[p].push_back(s);
		}
	}
	else if(p == 14){ //PO
		string str;
		str.clear();
		str += "5 2 0 1 4 7 8 9 3\n";
		str += "1 4 9 2 8 3 7 5 0\n";
		str += "3 7 8 6 5 9 1 2 4\n";
		str += "4 1 7 8 0 2 9 6 5\n";
		str += "9 3 5 7 1 6 4 8 2\n";
		str += "6 8 0 5 9 4 3 7 1\n";
		str += "8 9 1 4 2 0 6 3 7\n";
		str += "7 5 4 3 6 8 2 1 9\n";
		str += "2 6 3 9 0 1 5 4 0\n";
		testcase[p].push_back(str);
		str.clear();
		str += "0 0 9 8 1 3 0 5 7\n";
		str += "5 3 0 6 0 7 0 8 0\n";
		str += "8 0 7 0 0 0 0 1 3\n";
		str += "0 7 0 0 8 0 5 6 0\n";
		str += "9 0 0 4 5 1 3 7 8\n";
		str += "0 0 5 0 3 0 4 2 0\n";
		str += "0 0 0 1 7 5 0 0 0\n";
		str += "0 0 0 0 0 9 7 4 0\n";
		str += "7 0 3 0 0 0 0 0 0\n";
		testcase[p].push_back(str);
		str.clear();
		str += "0 0 0 9 0 0 0 0 0\n";
		str += "0 6 0 0 0 0 0 0 1\n";
		str += "0 0 0 7 0 5 0 0 0\n";
		str += "7 0 5 0 0 0 0 0 0\n";
		str += "0 0 0 0 0 0 2 0 0\n";
		str += "0 0 1 0 8 0 0 0 4\n";
		str += "0 0 0 0 6 0 0 0 0\n";
		str += "0 0 0 0 0 0 0 7 9\n";
		str += "0 2 3 0 4 0 0 0 0\n";
		testcase[p].push_back(str);
		str.clear();
		str += "6 0 0 0 0 0 3 0 0\n";
		str += "0 0 0 0 1 0 0 0 0\n";
		str += "0 0 1 0 9 5 0 0 0\n";
		str += "0 0 0 0 0 0 0 0 1\n";
		str += "8 0 0 2 0 0 0 0 0\n";
		str += "7 4 0 0 0 0 0 0 9\n";
		str += "0 9 0 0 0 0 2 0 0\n";
		str += "0 0 5 0 0 0 0 0 0\n";
		str += "0 0 0 7 0 0 8 0 0\n";
		testcase[p].push_back(str);
		str.clear();
		str += "0 0 0 0 7 9 0 0 0\n";
		str += "0 4 0 0 0 2 0 0 0\n";
		str += "0 8 0 0 0 0 0 1 0\n";
		str += "0 0 0 2 0 0 0 0 0\n";
		str += "1 0 0 0 0 0 9 0 7\n";
		str += "0 0 7 0 0 0 6 0 0\n";
		str += "0 0 0 8 5 0 0 2 0\n";
		str += "0 0 0 0 0 0 0 4 0\n";
		str += "0 0 9 0 0 0 0 0 0\n";
		testcase[p].push_back(str);
		str.clear();
		str += "0 5 0 9 0 0 0 0 0\n";
		str += "0 0 0 0 0 0 0 6 0\n";
		str += "0 2 0 0 0 0 3 4 0\n";
		str += "0 0 6 0 4 0 0 0 0\n";
		str += "0 0 0 0 3 0 0 0 2\n";
		str += "0 0 0 0 0 0 0 0 9\n";
		str += "0 0 0 8 0 0 0 7 0\n";
		str += "0 0 4 0 0 0 0 0 0\n";
		str += "0 8 0 5 0 0 0 0 1\n";
		testcase[p].push_back(str);
	}
}
int kmp(const string& str, const string& pattern) {
	// Step 0. Should not be empty string
	if( str.size() == 0 || pattern.size() == 0)
		return -1;

	// Step 1. Compute failure function
	int failure[pattern.size()];
	std::fill( failure, failure+pattern.size(), -1);

	for(int r=1, l=-1; r<pattern.size(); r++) {

		while( l != -1 && pattern[l+1] != pattern[r])
			l = failure[l];

		// assert( l == -1 || pattern[l+1] == pattern[r]);
		if( pattern[l+1] == pattern[r])
			failure[r] = ++l;
	}

	// Step 2. Search pattern
	int tail = -1;
	for(int i=0; i<str.size(); i++) {

		while( tail != -1 && str[i] != pattern[tail+1])
			tail = failure[tail];

		if( str[i] == pattern[tail+1])
			tail++;

		if( tail == pattern.size()-1)
			return i - tail;
	}

	return -1;
}
void timekill(){
	for(int i = 0; i < 4; i++){
		Sleep(3000);
		if(!run) return;
	}
	if(run) {
		cmd("taskkill /f /im code.exe > Nul 2> Nul");
		kill = true;
	}
}
