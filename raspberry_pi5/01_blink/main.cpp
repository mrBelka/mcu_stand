#include <gpiod.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
  const std::string chip_path = "/dev/gpiochip4";
  unsigned int line_offset = 17; // GPIO pin number/offset

  try {
    auto request = gpiod::chip(chip_path)
        .prepare_request()
        .set_consumer("cpp-blink-example")
        .add_line_settings(
            line_offset,
            gpiod::line_settings()
                .set_direction(gpiod::line::direction::OUTPUT)
        )
        .do_request();

    std::cout << "Blinking GPIO " << line_offset << "..." << std::endl;

    for (int i = 0; i < 10; ++i) {
        request.set_value(line_offset, gpiod::line::value::ACTIVE);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        request.set_value(line_offset, gpiod::line::value::INACTIVE);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}