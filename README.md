UML TO CODE - Convert your UML diagrams into template code!
============================================================

### Overview
Core idea of our project is to allow the user to get a full project
outlay for constructed classes, and to remove the tiring work of
writing function declarations, then their respective definitions while
looking at their UML diagram. We provide a simple GUI wizard that allows
you to create class UML diagrams interactively and then create a full project
of required classes that you only need to implement later on.

### How it works
* Pick a name for your project
* Select project directory
* Construct required class diagrams using our GUI wizard
* Click EXPORT AS and select target language (currently only c++ is supported)
* Open generated files in your favorite editor and begin coding!

### Supported languages:
List of currently supported languages is:
* C++ (done)
* Java (planned)
* PHP (planned)
* C# (planned)

Supporting wide variety of languages is not the main focus at the moment,
and later on, it should be easy to extend the app to support more.

### How it's made
Project is created using c++11, Qt libraries and flex/bison parsing package. 

##### Requried libs
* Qt5
* GNU Bison
* GNU Flex
* qmake

### Future plans
Once our core functionality (exporting UML class diagrams) is complete,
we hope to extend the app with additional features like drawing vector images of UML diagrams,
generating documentation, allowing creation of other types of UML diagrams and similar.

### Contact
Feel free to contact us using GitHub regarding anything. Any suggestions and ideas are always welcome.
