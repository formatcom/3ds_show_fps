#include <string.h>
#include <stdio.h>
#include <3ds.h>

// HZ 3DS
#define TICKS_PER_SEC  (268111856)

void gameLoop() {
	u64 nowTicks, deltaTicks, lastTicks = 0, countTicks = 0;

	uint frame = 0, fps = 0;

	// loop principal
	while (aptMainLoop()) {
		frame++;

		nowTicks = svcGetSystemTick(); // ticks actuales
		deltaTicks = nowTicks - lastTicks;
		lastTicks = nowTicks;

		// Acumulamos el total de los ticks hasta
		// que lleguemos a un segundo (TICKS_PER_SEC)
		countTicks += deltaTicks;

		// Al paso de un segundo actualizamos los fps
		if (countTicks >= TICKS_PER_SEC) {
			fps = frame;
			frame = 0; countTicks = 0;
		}

		gspWaitForVBlank();

		// escribimos por pantalla los fps
		printf("\x1b[3;0HFPS: %d", fps);

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

	}

}


int main(int argc, char **argv) {

	// Inicializa el apartado grafico
	gfxInitDefault();

	// Inicializa una unica consola, en este caso la top
	consoleInit(GFX_TOP, NULL);

	// Iniciamos el gameLoop
	gameLoop();

	gfxExit();
	return 0;
}
