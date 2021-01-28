#include<iostream>
using namespace std;

int main(){
	string s;
	int n;
	cin >> s >> n;
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 'A' && s[i] <= 'Z'){
			int x = int(s[i]) + n % 26;
			if(x < 'A')x += 26;
			else if(x > 'Z')x -= 26;
			s[i] = char(x);	
		}else{
			int x = int(s[i]) + n % 26;
			if(x < 'a')x += 26;
			else if(x > 'z')x -= 26;
			s[i] = char(x);
			
		}
	}
	cout << s << endl;
	return 0;
}
