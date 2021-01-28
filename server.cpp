#include <bits/stdc++.h>
#include <windows.h>
#define Qsize 15 
using namespace std;

void cmd(const string &str){
    system(str.c_str());
}
struct submit{
    string team, question, result, submitTime;
    int score;
};
struct teamScore{
    string name;
    int score[Qsize];
    int total;
    string lastTime;
    teamScore(){
        for(int i = 0 ; i < Qsize; i++) score[i] = 0;
        total = 0;
        lastTime = "99:99:99.99";
    }
};
bool subcmp(const submit& s1, const submit&s2){
    return s1.submitTime > s2.submitTime;
}
bool scorecmp(const teamScore& t1, const teamScore& t2){
    if(t1.total != t2.total) return t1.total > t2.total;
    return t1.lastTime < t2.lastTime;
}
vector<submit> submitlist;
vector<teamScore> ranking(25);

int kmp(const string& str, const string& pattern);

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    fstream sub;
    cmd("rd /s /q testrepo");
    while(true){
        cmd("git clone https://github.com/Hackerifyouwant/testrepo.git");
        vector<teamScore> tempscore(25);
        ranking.clear();
        ranking = tempscore;
	    fstream board;
	    fstream sublist;
	    board.open("scoreboard.txt", ios::in|ios::out|ios::trunc);
	    sublist.open("submission.txt", ios::in|ios::out|ios::trunc);
	    sublist << "# Submission List\n";
	    sublist << "team    | question  | results  | score | submit time\n";
	    sublist << "------|-----:|-----:| ----:|-----\n";
	    board << "# Scoreboard\n";
	    board << "rank | team | PA | PB | PC | PD | PE | PF | PG | PH | PI | PJ | PK | PL | PM | PN | PO | total\n";
	    board << "----|----:|-----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----:|----\n";
	    
	    submitlist.clear();
        string team = "team00";
        string question, result, submitTime;
        int score;
        string buffer;
        for(int i = 0; i <= 24; i++){
            team[4] = i / 10 + '0';
            team[5] = i % 10 + '0';
            ranking[i].name = team;
            sub.open("./testrepo/" + team + "_submission.md");
            if(!sub) {
                cout << "Fail to open team_submission.md!!\n";
                exit(1);
                continue;
            }
            getline(sub,buffer);
            getline(sub,buffer);
            getline(sub,buffer); // 吃掉前3行
            while(sub >> question >> buffer >> result >> buffer >> score >> buffer >> submitTime){
//            	if(submitTime >= "10:45:00.00") continue;//凍結 
            	if(submitTime[0] == '9') submitTime = "0" + submitTime;
                submitlist.push_back((submit){team, question, result, submitTime, score});
                if(ranking[i].score[question[1]-'A'] < score) {
                	ranking[i].score[question[1]-'A'] = score;
                	ranking[i].lastTime = submitTime;
				}
            }
            if(sub.is_open())sub.close();
            ranking[i].total = 0;
            for(int j = 0; j < Qsize; j++) ranking[i].total += ranking[i].score[j];
        }
        sort(submitlist.begin(), submitlist.end(), subcmp);
        sort(ranking.begin(), ranking.end(), scorecmp);
        for(auto &s : submitlist){
            sublist << s.team << " | " << s.question << " | " << s.result << " | " << s.score << " | " << s.submitTime << '\n';
        }
        int ctr = 1;
        for(auto &t : ranking){
            board << ctr << " | " << t.name << " | ";
            for(int i = 0; i < Qsize; i++){
                board << t.score[i] << " | ";
            }
            board << t.total << '\n';
            ctr++;
        }
        board << "\n\n";
        sublist << "\n\n";
        if(sub.is_open()) sub.close();
	    if(board.is_open()) board.close();
	    if(sublist.is_open()) sublist.close();
//	    cmd("cd testrepo && git pull --rebase");
	    cmd("type scoreboard.txt > ./testrepo/scoreboard.md");
	    cmd("type submission.txt > ./testrepo/submission.md");
	    cmd("cd testrepo && echo update time: %time% >> submission.md");
	    cmd("cd testrepo && echo update time: %time% >> scoreboard.md");
	    cmd("cd testrepo && git add *.md");
	    cmd("cd testrepo && git commit -m \"live update\"");
	    string log, logmaster, str;
	    fstream f1, f2;
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
	    	Sleep(15000);
	    }
	    cmd("rd /s /q testrepo");
        Sleep(15000);
    }
    return 0;
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

