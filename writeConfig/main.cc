#include <iostream>  
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>  

/**
 * This demo shows how to parser ini file with cpp.
 *
 * Build:
 * First, you have to make sure you have alredy installed boost lib,
 * then link to boost lib when you build it.
 * you don't need to download boost lib if you have the boost path in the other project, just link it with the exist path.
 * it will generated a directory and zip in the current path.
 *
 * in this demo, use g++ main.cc -I /theBoostLibPath -o configFile
 * /theBoostLibPath is the path where the boost is.
 *
 * */

int main()  
{  
	boost::property_tree::ptree pt;  

	// read ini file
	boost::property_tree::ini_parser::read_ini("/home/Esme/8888.ini", pt); 
 
	// write section, key, value to ptree. 
	pt.put<std::string>("OVERLAY.OverlayFontName","type1");  // write
	pt.put<std::string>("OVERLAY.AuthorName","name");
	pt.put<std::string>("Other.Name","no");
 
	// get value from ptree
	std::cout << pt.get<std::string>("OVERLAY.OverlayFontName") << std::endl;  // read
 
	// write to ini file
	boost::property_tree::ini_parser::write_ini("/home/xinxin/.intel/.civ/8888.ini",pt);
 
	return 0;  
} 
