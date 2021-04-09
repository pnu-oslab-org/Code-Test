#include <iostream>
#include <string>

using namespace std;

char result[1000001];

int main()
{
    string str,bomb;
    int index=0;

    cin >> str >> bomb;

    for(int i=0; i<str.size(); i++) {
        int j = (int) bomb.size();

        result[index++] = str[i];

        if(str[i] == bomb[--j]) {
            bool check = false;
            int size = index - (int) bomb.length();

            for(int k=index-1; k>=size; k--) {
                check = (result[k] == bomb[j--]);
                if (!check)
                    break;
            }

            if (check)
                index -= bomb.size();
        }
    }

    if(index==0) {
        cout<<"FRULA"<<endl;
    } else {
        for(int i=0; i<index; i++)
            cout<<result[i];
        cout<<endl;
    }

    return 0;
}
