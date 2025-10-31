#include "EPOSController.h"
#include <iostream>
#include <unistd.h>

int main(int argc, const char **argv) {
  // Create EPOS controller instance with default parameters
  // EPOS4, USB connection, node ID 1
  EPOSController epos;

  // Initialize the device
  std::cout << "Initializing EPOS device..." << std::endl;
  if (!epos.initialize()) {
    std::cerr << "Failed to initialize EPOS device" << std::endl;
    return 1;
  }

  // Example 1: Velocity Control
  std::cout << "\n=== Velocity Control Demo ===" << std::endl;
  if (epos.activateVelocityMode()) {
    // Move with different velocities
    epos.moveWithVelocity(100);
    sleep(2);

    epos.moveWithVelocity(500);
    sleep(2);

    epos.moveWithVelocity(1000);
    sleep(2);

    // Stop velocity movement
    epos.haltVelocityMovement();
  }

  // Example 2: Position Control
  std::cout << "\n=== Position Control Demo ===" << std::endl;
  if (epos.activatePositionMode()) {
    // Move to different positions
    epos.moveToPosition(5000, true, true);
    sleep(2);

    epos.moveToPosition(-10000, true, true);
    sleep(2);

    epos.moveToPosition(0, true, true);
    sleep(2);

    // Stop position movement
    epos.haltPositionMovement();
  }

  // Get current position and velocity
  int position = 0;
  int velocity = 0;
  if (epos.getPosition(position)) {
    std::cout << "Current position: " << position << std::endl;
  }
  if (epos.getVelocity(velocity)) {
    std::cout << "Current velocity: " << velocity << std::endl;
  }

  // Disable and close device
  epos.disable();
  epos.close();

  std::cout << "\nEPOS demo completed successfully" << std::endl;
  return 0;
}
