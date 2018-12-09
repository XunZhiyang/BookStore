#include<iostream>
#include<fstream>
#include<string>
#include "pch.h"
using namespace std;

string a="abcdefg";
string b="hijklmn";
// string a, b;
int main()
{
    // cin >> a;
    // cin >> b;
    // a+='"';
    // b+='"';
    // a.reserve();
    // b.reserve();
    ofstream out("file");
    out.write((a.c_str()), 7);
    // out << a;
    // out.seekp(7);
    printf("%d\n",out.tellp());
    out.write((b.c_str()), 7);
    // out << b;
    // out.seekp(80);
    printf("%d\n",out.tellp());
    //out.seekp(0,ios::end);
    b="sssss ";
    // out.write(reinterpret_cast<char *> (&b), 7);
    // out << b;
    printf("%d\n",out.tellp());
    out.close();
    fstream in;
    in.open("file");
    in.seekg(0);
    // string c;
    // in >> c;
    // cout<<c<<endl;
    char c[8];
    c[7] = '\0';
    for(;;) {
        // in.getline(c, 7, '"');
        in.read(c, 7);
        string p = c;
        // in >> c
        if(in.eof()) break;
        cout << p << endl;
    }
    // while (!in.eof())
    // {
    //     // in.read(reinterpret_cast<char *> (&c), 7);
    //     in >> c;
    //     cout<<c<<endl;
    // }
    in.close();
    return 0;
}
