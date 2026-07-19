#include <iostream>				//  Included for basic IO (input/output) operations
#include <string>				//  Included for strings
#include <vector>				//  Included for vectors (dynamically-sized containers)
#include <cmath>				//  Included for things like floor(), ceil(), fmod() (floating-point modulo), sin(), and cos()
#include <ctime>				//  Included for things like time(0)
#include <random>				//  Included for random number generation
#include <algorithm>			//  Included for algorithmic functions, like sorting and counting elements in a range
#include <fstream>				//  Included for file access
#include <filesystem>			//  Included for file/folder exploring
#include <type_traits>			//  Included in order to deduce if a type is integer-like or floating-point-like
#include <limits>				//  Included in order to be able to get the maximum value of a specific integer type

//  --- <optional> ---
//  
//  This include allows you to use a template class called "optional" that can either "be a value" or "be empty."
//  Basically, whenever you use certain SFML functions and methods that either COUlD or COULD NOT have a valid
//  return type, it will likely return an optional object, which you can safely check whether it has a valid value
//  inside it or if it is empty.
//  
//  EXAMPLE USE CASE OF AN std::optional:
//  
//  If you have a function that goes through a list of elements and tries to find one of a specific kind to return,
//  then you can make the function return an std::optional so that if NONE of the elements in the vector matches,
//  you can return an empty optional object instead of figuring out what the heck to return if no element in the
//  vector matches the search criteria.
//  
//  TEMPLATE DECLARATION (where target type to work with is T):
//  std::optional<T>
//  
//  EMPTY OPTIONAL RETURN VARIABLE (what to return if the optional function should return empty):
//  std::nullopt
//  
//  -------------------------------------------------------------------------------------------------------
//  
#include <optional>				//  Included for optionals

//  --- <unordered_map> --
//  
//  Unordered maps are basically key-value containers. They are like arrays and vectors, but instead of being stored
//  using integer indices (like 0 is the first element and 1 is the second element and so on), they instead use an
//  input "key" that corresponds to an output "value."
//  
//  EXAMPLE USE CASE OF AN std::unordered_map:
//  
//  If you have a container of integer values where order does not matter and you would like to access the values by
//  some string ID instead of the value's index in an array or vector, you would use an std::unordered_map where the
//  key type is string and the value type is int.

//  TEMPLATE DECLARATION (where key type is K and value type is V):
//  std::unordered_map<K, V>
//  
#include <unordered_map>		//  Included for unordered maps


//  --- <unordered_set> --
//  
//  Unordered sets are basically arrays/vectors but the elements have no order they are stored in (no access through
//  indexes or by key). They basically just store values in no specific order.
//  
//  EXAMPLE USE CASE OF AN std::unordered_set:
//  
//  If you have a class that stores a list of strings and the only thing that matters is whether the list has a specific
//  string, you would use an unordered_set to store those strings.

//  TEMPLATE DECLARATION (where value type is T):
//  std::unordered_set<T>
//  
#include <unordered_set>		//  Included for unordered sets


#include <SFML/Graphics.hpp>	//  Included for SFML graphics capabilities, like windows, sprites, texts, etc.
#include <SFML/Audio.hpp>		//  Included for SFML audio capabilities, like sounds, muisc, etc.

//  --- USING NAMESPACE STD; ---
//  
//  This just makes sure we don't have to do std:: on every standard library variable or
//  function.
//  
//  -------------------------------------------------------------------------------------------------------
//  
using namespace std;


//  --- ASSETS LOADER ---
//  
//  This handles how assets like images, sounds, and more are handled. Either they can be
//  loaded by file OR they can be loaded by memory. Loading by file makes it so that the
//  program just needs the files in a folder called "assets/." Loading by memory requires
//  a special tool that I won't bring in yet but I will later if we think we need it.
//  
//  -------------------------------------------------------------------------------------------------------
//  
#include "assets_loader.hpp"

//  --- RANDOM HELPERS ---
//  
//  This is just a helper library for more easily controlling random number generation.
//  Not only does it have automatic type deduction (integer types generate from 0 to their
//  max while floating-point types generate from 0.0 to 1.0), but it can generate integers
//  up to 64 bytes large.
//  
//  -------------------------------------------------------------------------------------------------------
//  
#include "random.hpp"

//  --- 2D VECTOR STRUCT ---
//  
//  This is a struct that stores two double (like a coordinate). SFML has something
//  similar called "sf::Vector," but this custom-made struct allows you to do actual
//  direct operations using operator overloads (e.g. vec1 + vec2 or vec * 2.0).
//  -------------------------------------------------------------------------------------------------------
#include "vec2.hpp"

//  --- MAIN GRAPHICS ---
//  
//  This contains very, very many helper classes that makes using SFML much easier.
//  -------------------------------------------------------------------------------------------------------
#include "graphics/all.hpp"

//  --- KEYBIND ---
//  
//  This contains a very simple struct of variable name = keybind to use for quick bind
//  manipulation. It also contains a default WASD keybind variable.
//  -------------------------------------------------------------------------------------------------------
#include "keybind.hpp"

//  --- VIEWPORT ---
//  
//  This contains an easier way to control a camera and sprites in the world. You can
//  change the location and size of the viewport and then pass sprites through it to
//  render into the world given the size and location of the sprite. All of this is
//  done in units rather than pixels, which is what SFML does. This means that a
//  program using a viewport can change its resolution and not affect the graphics
//  much.
//  
//  By default, the size of a viewport sets the width to that size. However, if you want
//  to guarantee that the viewport contains a certain area, you can set the size to either
//  the width, the height, to fit an area, or to fill an area.
//  -------------------------------------------------------------------------------------------------------
#include "viewport.hpp"

//  --- ENTITY ---
//  
//  This contains details about an actor in the world. It will eventually have collision
//  and animation (though animation may be a separate class), but that's not integrated
//  yet.
//  
//  It mainly features physics calculations and an input-based movement method.
//  
//  -------------------------------------------------------------------------------------------------------
//  
#include "entity.hpp"
