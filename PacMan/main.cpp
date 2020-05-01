//
//  main.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//
#include "AllInterfaces.h"
#include "PacManView.hpp"
#include "Settings.hpp"

int main(int argc, const char * argv[]) {
    pacman::impl::Settings::getInstance()->start();
    pacman::impl::PacManView pacManView;
    pacManView.run();
    return 0;
}
