#include <iostream>
#include <Serial.hpp>
#include <ModbusMasterRTU.hpp>

int main()
{
    try
    {
        prism::io::SerialParams params = {"/dev/com1", 115200, 8, 'n', "1", 200ms};
        prism::proto::ModbusMasterRTU mb(params);
        if(!mb.Setup())
            throw std::runtime_error("Ошибка настройки протокола");

        try
        {
            auto result = mb.ReadInputRegister(0x01, 0x0001, 0x0001);
			// print result.data()
        }
        catch(const std::exception& e)
        {
           std::cerr << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}