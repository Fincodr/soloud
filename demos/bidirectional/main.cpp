/*
SoLoud audio engine
Copyright (c) 2013-2014 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

// BiDirectionalWav example by Fincodr

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "soloud.h"
#include "soloud_biwav.h"
#include "soloud_thread.h"

#ifdef _MSC_VER
#include <conio.h>
int mygetch()
{
	return _getch();
}
#else
#include <termios.h>
#include <unistd.h> 
int mygetch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

// Entry point
int main(int argc, char *argv[])
{
	// Declare some variables
	SoLoud::Soloud soloud; // Engine core
	SoLoud::BiWav music;

	// Initialize SoLoud
	soloud.init();

	// Load background music
	SoLoud::result music_loaded = music.load("assets/practicetrack.ogg"); // sin_100.wav");

	// Initial direction is backwards (reversed)
	bool bReversed = true; 

	if (music_loaded == SoLoud::SO_NO_ERROR)
	{
		// Music settings
		music.setReversed(bReversed);
		music.setLooping(true);

		std::cout << "Playing music. Press <r> to reverse, <z> to reset and <q> to quit" << std::endl;

		// Start playing the background music
		int hMusic = soloud.play(music);

		int ch = 0;
		while (ch != 'q') {
			ch = mygetch();
			switch (ch) {
			case 'r':
				bReversed = bReversed ? false : true;
				if (!bReversed) {
					std::cout << "\n--<[FORWARD]>--\n";
				} else {
					std::cout << "\n--<[BACKWARD]>--\n";
				}
				soloud.setReversed(hMusic, bReversed);
				break;
			case 'z':
				std::cout << "\n--<[RESET]>--\n" << std::endl;
				bReversed = false;
				soloud.setReversed(hMusic, bReversed);
				soloud.seek(hMusic, 0.0f);
				break;
			}
		}

	} 
	else 
	{
		printf("%s\n", "Cannot find audio track or other error");
	}

	// Clean up SoLoud
	soloud.deinit();

	// All done.
	return 0;
}