#include <asuro.h>

int main (void) {
	Init();
	EncoderInit();

	while(1) {
		GoTurn(200,  0, 150);
		GoTurn(  0, 90, 150);
	}
}

