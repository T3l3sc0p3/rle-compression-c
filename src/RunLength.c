#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define ll long long int

void printUsage();
void printVersion();
void printBanner();
char * RLE(char *input, char t);
char * RLD(char *input);

int main(int argc, char *argv[]) {
    int encodeFlag = 0, decodeFlag = 0, bannerFlag = 0, helpFlag = 0, versionFlag = 0;
    char t;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--banner")) {
            bannerFlag = 1;
        } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            helpFlag = 1;
        } else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
            versionFlag = 1;
        } else if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--encode")) {
            encodeFlag = 1;
        } else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--decode")) {
            decodeFlag = 1;
        }
    }
    if (bannerFlag) printBanner();
    // Handle the case when no flags are set
    if (!(encodeFlag + decodeFlag + helpFlag + versionFlag))
    {
        printf("Error: You haven't set any flags yet so I don't know what to do next :(\n");
        printUsage();
        return 1;
    }
    // Handle case when both encode and decode flags are set
    if (encodeFlag && decodeFlag) {
        printf("Error: You can't encode and decode simultaneously!\n");
        return 1;
    }
    if (helpFlag) {
        printUsage();
        return 0;
    }
    if (versionFlag) {
        printVersion();
        return 0;
    }
    if (encodeFlag) {
        printf("Choose encoding type (c for character+number, other for number+character): ");
        scanf("%c", &t);
        while (getchar() != '\n');
    }
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--banner") ||
            !strcmp(argv[i], "-e") || !strcmp(argv[i], "--encode") ||
            !strcmp(argv[i], "-d") || !strcmp(argv[i], "--decode")) {
            continue;
        }
        char *path = argv[i];
        FILE *fi = fopen(path, "r");
        if (!fi) {
            printf("Error: File %s doesn't exist or invalid file path!\n", path);
            continue;
        }
        fseek(fi, 0, SEEK_END);
        ll length = ftell(fi);
        fseek(fi, 0, SEEK_SET);
        char *buf = (char*)malloc(length + 1);
        fread(buf, 1, length, fi);
        buf[length] = '\0';
        fclose(fi);
        if (encodeFlag) {
            char *encoded;
            encoded = RLE(buf, tolower(t));
            free(buf);
            char *filename = (char*)malloc(strlen(path) + strlen(".enc")+1);
            strcpy(filename, path);
            strcat(filename, ".enc");
            FILE *fo = fopen(filename, "w");
            if (!fo) {
                printf("Error: Failed to create output file %s\n", filename);
                free(encoded);
                free(filename);
                return 1;
            }
            fprintf(fo, "%s", encoded);
            fclose(fo);
            printf("Run-length encoding successfully for file %s. Encoded content saved to %s\n", path, filename);
            free(encoded);
            free(filename);
        } 
        else if (decodeFlag) {
            // Check if file has ".enc" extension and remove it, after then add ".dec" extension
            char *filename;
            if (strstr(path, ".enc") != NULL) {
                filename = (char*)malloc(strlen(path) - 3 + strlen(".dec") + 1);
                strncpy(filename, path, strlen(path) - 4);
                filename[strlen(path) - 4] = '\0';
                strcat(filename, ".dec");
            } else {
                filename = (char*)malloc(strlen(path) + strlen(".dec") + 1);
                strcpy(filename, path);
                strcat(filename, ".dec");
            }
            char *decoded = RLD(buf);
            free(buf);
            FILE *fo = fopen(filename, "w");
            if (!fo) {
                printf("Failed to create output file %s\n", filename);
                free(decoded);
                free(filename);
                return 1;
            }
            fprintf(fo, "%s", decoded);
            fclose(fo);
            printf("Run-length decoding successfully for file %s. Decoded content saved to %s\n", path, filename);
            free(decoded);
            free(filename);
        }
    }
    return 0;
}

// Just a simple usage function ~~
void printUsage() {
    printf("Usage:\n"
           "\t./rle-compression [options] [files]\n"
           "Options:\n"
           "\t-b,  --banner\t\tDisplay the banner\n"
           "\t-e,  --encode\t\tEncode content of files\n"
           "\t-d,  --decode\t\tDecode content of files\n"
           "\t-h,  --help\t\tDisplay this help and exit\n"
           "\t-v,  --version\t\tShow this program version\n"
           "Examples:\n"
           "\t./rle-compression -b -e test.txt\n"
           "\t./rle-compression -b -d test.txt.enc\n");
}

// Print current version
void printVersion()
{
    printf("rle-compression 0.1\n");
}

// Just a simple ASCII banner
void printBanner()
{
    printf(
"       _                                                        _\n"
"      | |                                                      (_)\n"
"  _ __| | ___ ______ ___ ___  _ __ ___  _ __  _ __ ___  ___ ___ _  ___  _ __  \n"
" | '__| |/ _ \\______/ __/ _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __| |/ _ \\| '_ \\ \n"
" | |  | |  __/     | (_| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ | (_) | | | |\n"
" |_|  |_|\\___|      \\___\\___/|_| |_| |_| .__/|_|  \\___||___/___/_|\\___/|_| |_|\n"
"                                       | |                                    \n"
"                                       |_|                                    \n");
}

// Run-Length encode
char * RLE(char *input, char t) {
    int length = strlen(input), idx = 0, count = 1, i = 0;
    char* res = (char*)malloc(2*length+1);
    for (;i < length-1; i++) {
        if (input[i] == input[i+1]) {
            count++;
        }
        else {
            if (t == 'c') {
                res[idx++] = input[i];
                idx += sprintf(res + idx, "%d", count);
            } else {
                idx += sprintf(res + idx, "%d", count);
                res[idx++] = input[i];
            }
            count = 1;
        }
    }
    res[idx] = '\0';
    return res;
}

// Run-length decode
char * RLD(char *input) {
    int length = strlen(input), idx = 0, i = 0;
    char* res = (char*)malloc(length + 1);
    if (isdigit((char)input[0])) {
        // Number+Character encoding
        while (i < length) {
            int count = 0;
            while (isdigit(input[i])) {
                count = count * 10 + (input[i] - '0');
                i++;
            }
            char c = input[i];
            res = (char*)realloc(res, idx + count + 1);
            for (int j = 0; j < count; j++) {
                res[idx++] = c;
            }
            i++;
        }
    } else {
        // Character+Number encoding
        while (i < length) {
            char c = input[i++];
            int count = 0;
            while (isdigit(input[i])) {
                count = count * 10 + (input[i] - '0');
                i++;
            }
            res = (char*)realloc(res, idx + count + 1);
            for (int j = 0; j < count; j++) {
                res[idx++] = c;
            }
        }
    }
    res[idx] = '\0';
    return res;
}
