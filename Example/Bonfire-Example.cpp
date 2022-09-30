#include "Bonfire.hpp"


// theres some issues relating to exporting classes
// something about all the std libraries being inline makes 
// it so that the dll compiler and the client exe compiler
// may not be configured exactly the same so you may get implementations
// of the standard library - every class is an implementation of std

// https://stackoverflow.com/questions/6840576/how-to-export-a-c-class-from-a-dll
// says that the implementation might look something like a class factory that is 
// exported
// extern "C" BONFIRE_API MyClass* createMyClass(){
//		return new MyClass();
// }
// dont forget the extern "C" here or C++ will name mangle
// so instead of getting the class exported, you get a pointer to the class which
// was created on the dl side.


//for some reason it does not like the separater "::" but other ones work

int main() {
	Logger logger = Logger("bonFireLogger", "log.txt", "", "INFO", " : ", 1);
	logger.addFileHandler("handlerLog.txt", "", "INFO");


	logger.info("Hello world");
}