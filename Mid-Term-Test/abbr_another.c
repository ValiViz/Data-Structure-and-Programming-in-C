#include <stdio.h>
#include <string.h>

int main() {
    char string[500];
    scanf("%s", string);
    char* bottom    = NULL;

    const int length = strlen(string);
    // we use 'length' to do iteration instead of 
    // while(string[i] == '\n') to prevent
    // linux '\n' '\r' hacking
    for (int i = 0; i <= length; i++) {
        if (i == length) {
            // if the iteration is ending,
            // we immediately output once
            // this output logic is the same as code at the 
            // end of 'for' loop and is explained there
            if (&string[i - 1] == bottom) {
                putchar(string[i - 1]);
            } else {
                printf("%c-%c", *bottom, string[i - 1]);
            }
            bottom = &string[i];
            break;
        }

        if (bottom == NULL) {
            // if there's nothing at the bottom, use this as
            // bottom and continue;
            bottom = &string[i];
            continue;
        }

        if (string[i] == string[i - 1] + 1) {
            continue;
        }

        // the continous addition interruped
        // we check if we need to print one char
        // or a char range
        if (&string[i - 1] == bottom) {
            // the addition just kept for one char and stopped
            putchar(string[i - 1]);
        } else {
            // the addition kept for more than one char
            printf("%c-%c", *bottom, string[i - 1]);
        }
        // finally reset bottom pointer
        bottom = &string[i];
    }
    return 0;
}