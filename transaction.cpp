/**
 * Class .cpp file. This class is the parent class of all the transaction classes. It has a abstract function
 * "Perform Transaction" which all child classes must implement. This abstract function will take advantage of
 * polymorphism at run time, letting the compiler decide which "Perform Transaction" to execute depending on the child
 * class calling the function.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include "transaction.h"

#include <sstream>

Transaction::~Transaction() {

}
