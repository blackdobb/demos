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

struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;

int main() {

	using namespace std;
    cout << "HOME : " << homedir << endl;

    return 0;
}


















