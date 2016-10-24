#include <chrono>
#include <thread>

#include "message.h"
#include "message_bus.h"
#include "framework.h"

//----------

int main() {
	framework fwk;
	if (!fwk.init()) { 
		std::cerr << "ERROR: Failed to load framework\n";
		return -1; 
	}

	message_bus bus;

	render_system r (&fwk, &bus);
	input_system i (&fwk, &bus);
	game_logic logic (&fwk, &bus);

	bus.attach_system(&r);
	bus.attach_system(&i);
	bus.attach_system(&logic);
	logic.init();

	bus.running = true;

	while(bus.running) {
		bus.update();
	}

	return 0;
}
