#include<stdio.h>
#include<string.h>
void print(char a,char b) {
      while(a<b-1) {
        a++;
        printf("%c",a);
      }
}
char s[10000];
int main() {
    scanf("%s",s);
    for(int i=0;i<strlen(s);i++) {
        if(s[i+1]=='-') {
            if((s[i]>='a'&&s[i+2]<='z'&&s[i]<s[i+2])||(s[i]>='0'&&s[i]<='9'&&s[i]<s[i+2])||(s[i]>='A'&&s[i+2]<='Z'&&s[i]<s[i+2])) {
                printf("%c",s[i]);
                print(s[i],s[i+2]);
                i++;
            }
        } else {
            printf("%c",s[i]);
        }
    }
    return 0;
}