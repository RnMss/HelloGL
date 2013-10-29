#include <cstdio>
#include <cstring>

const int buflen = 128;
char buf[buflen];

char dict[256][5];

void init_dict() {
	for (int i=32; i<127; ++i) {
		sprintf(dict[i], "%c", (char)i);
	}
	for (int i=0; i<32; ++i) {
		sprintf(dict[i], "\\x%x", i);
	}
	for (int i=127; i<256; ++i) {
		sprintf(dict[i], "\\x%x", i);
	}
	sprintf(dict['\n'], "\\n");
	sprintf(dict['\t'], "\\t");
	sprintf(dict['\r'], "\\r");
}

int main(int argc, const char *argv[]) {
	init_dict();

	for ( ; ; ) {
		char *sret = fgets(buf, buflen, stdin);
		if (sret != buf) {
			break;
		}

		fputs("  \"", stdout);
		for (int i=0; buf[i]; ++i) {
			unsigned char c = buf[i];
			fputs(dict[c], stdout);
		}
		fputs("\"\n", stdout);
	}

	return 0;
}