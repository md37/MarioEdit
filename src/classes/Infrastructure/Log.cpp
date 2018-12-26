#include "Log.hpp"

#include <iostream>

bool Log::autoLine = true;

void Log::line() {
    std::cout << "----------------------------------------------------------" << std::endl;
}

void Log::out(std::string label) {
    if (autoLine) {
        Log::line();
    }
    std::cout << "[ " << label << " ]" << std::endl;
}

void Log::out(bool value, std::string label) {
    if (autoLine) {
        Log::line();
    }
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << (value ? "true" : "false") << std::endl;
}

void Log::out(sf::Vector2f vector, std::string label) {
    if (autoLine) {
        Log::line();
    }
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << vector.x << "x" << vector.y << std::endl;
}

void Log::out(sf::Uint32 value, std::string label) {
    if (autoLine) {
        Log::line();
    }
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << value << std::endl;
}

void Log::out(sf::Rect<float> rect, std::string label=std::string("")) {
    if (autoLine) {
        Log::line();
    }
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << rect.left << "," << rect.top << " " << rect.width << "x" << rect.height << std::endl;
}

void Log::out(std::unique_ptr<Scale> &scale, std::string label=std::string("")) {
    if (autoLine) {
        Log::line();
    }
    if (!label.empty()) {
        std::cout << "[ " << label << " ] ";
    }
    std::cout << scale->getCurrent() << " (" << scale->getRatio() << "x)" << std::endl;
}

void Log::turnOnAutoLine(bool autoLine) {
    Log::autoLine = autoLine;
}
