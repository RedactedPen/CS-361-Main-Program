#ifndef TRANSMIT_HPP
#define TRANSMIT_HPP

#include <iostream>

#define CONVERTER 54325
#define COLORER 54326
#define SELECTOR 54327
#define PHRASE 54328

//Handles sending a request to a microservice
//Returns the recieved response, or an empty string if an 
//error occured
std::string send_request(int port_no, std::string req);


#endif