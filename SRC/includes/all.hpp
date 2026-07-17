#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <optional>
#include <type_traits>
#include <limits>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//  --- USING NAMESPACE STD; ---
//  
//  This just makes sure we don't have to do std:: on every standard library variable or
//  function.
//  
//  -------------------------------------------------------------------------------------------------------
//  
using namespace std;

#include "assets_loader.hpp"
#include "random.hpp"
#include "vec2.hpp"
#include "graphics/all.hpp"
#include "keybind.hpp"
#include "viewport.hpp"
#include "entity.hpp"
