#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/**
 * This demo is used to get user's home path in Linux. 
 * eg. /home/ubuntu
 *
 * Build: g++ -o getUserPath
 * */


// getuid(): to get the user id of current user
// getpwuid to get the password entry(which includes the home directory) of the user
// also, you could see pw->pw_name to get username, pw->pw_passwd get password and etc.
struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;

int main() {

	using namespace std;
	cout << "HOME : " << homedir << endl;
       	return 0;
}


















