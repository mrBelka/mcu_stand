#include <gpiod.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    const std::string chip_path = "/dev/gpiochip4";
    unsigned int line_offset = 17;
    
    try {
        auto request = gpiod::chip(chip_path)
            .prepare_request()
            .set_consumer("cpp-input-example")
            .add_line_settings(
                line_offset,
                gpiod::line_settings()
                    .set_direction(gpiod::line::direction::INPUT)
                    // Опционально: включить подтягивающий резистор
                    // .set_bias(gpiod::line::bias::PULL_UP)
                    // .set_bias(gpiod::line::bias::PULL_DOWN)
            )
            .do_request();
        
        std::cout << "Reading GPIO " << line_offset << " (press Ctrl+C to exit)" << std::endl;
        
        while (true) {
            gpiod::line::value val = request.get_value(line_offset);
            std::cout << "GPIO " << line_offset << " = " 
                      << (val == gpiod::line::value::ACTIVE ? "HIGH (1)" : "LOW (0)") 
                      << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}