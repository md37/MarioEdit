#include "Log.hpp"

#include <iostream>

void Log::line() {
    std::cout << "----------------------------------------------------------" << std::endl;
}

void Log::out(std::string label) {
    std::cout << "[ " << label << " ]" << std::endl;
}

void Log::out(sf::Rect<float> rect, std::string label=std::string("")) {
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << rect.left << "," << rect.top << " " << rect.width << "x" << rect.height << std::endl;
}

void Log::out(std::unique_ptr<Scale> &scale, std::string label=std::string("")) {
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << scale->getCurrent() << " (" << scale->getRatio() << "x)" << std::endl;
}
