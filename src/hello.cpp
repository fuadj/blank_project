#include <iostream>
#include <string>
#include <stdio.h>
#include "console.h"
using namespace std;

int findDNAMatch(string s1, string s2, int start = 0);

int main() {
    string hay = "TAACGGTACGTC";
    string sub_1 = "TTGCC";
    string sub_2 = "TGC";
    const char *fmt = "Location of sub(%s) over (%s) is [%d]\n";

    printf("\n\n");
    printf(fmt, sub_1.c_str(), hay.c_str(), findDNAMatch(hay, sub_1));
    printf(fmt, sub_2.c_str(), hay.c_str(), findDNAMatch(hay, sub_2));
    printf(fmt, sub_2.c_str(), hay.c_str(), findDNAMatch(hay, sub_2, findDNAMatch(hay, sub_2) + 1));
    printf("\n\n");

    return 0;
}

int findDNAMatch(string hey, string needle, int start) {
    string mirror_dna;
    for (int i = 0; i < needle.length(); i++) {
        char ch = needle[i];
        char inverse;

        switch (ch) {
            case 'T': inverse = 'A'; break;
            case 'A': inverse = 'T'; break;
            case 'C': inverse = 'G'; break;
            case 'G': inverse = 'C'; break;
        }

        mirror_dna += inverse;
    }

    return hey.find(mirror_dna, start);
}
