# Moon 
This repository was created for Moon, a React-inspired language. Moon doesn't require any libraries or servers; everything you need is in this repository.
## Description
Just as the moon has phases, front-end web development also evolves in different stages. That's why the name Moon fits perfectly. You don't need servers or external programs: everything you need is right here, in this folder.
## Installation
1. Clone my repository: 
 git clone https://github.com/1vicxtr/Moon.git
2. Now you'll have my repository
in the /components/ folder, where you'll create .mn files.
3. If you're using Linux, you'll have the option to run ./watcher.
The executable will call the compiler every time you save a .mn file, saving you time.
4. If you are using Windows you will need to run moon-compiler.exe
***
# Syntax 


Moon's syntax is very friendly.
~~~~
// Home.mn
component Home{

 p(text: "Mensaje");

 h1(text: "Hello Word"); 

 int n = 5;
 
 string = "hello word!";
}
~~~~

***
## Version
Moon is in its first quarter phase (v1.1), so you can now write HTML tags and text inside them. In addition to declaring variables (int and string), I'm of course working on improving the syntax.