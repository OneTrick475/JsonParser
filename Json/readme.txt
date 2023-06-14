Json Parser

The project can function both as a library and a cli but is built with the intention of it working like a library. The cli is just for easier testing and to implement the command pattern.
Trying to break the cli with invalid input might cause undefined behaviour. 
Trying to break the functions with invalid arguments will cause a proper exception to be thrown. The exception will have a message containing information about the error.

The reason there is no validate function is because validation is done at the same time as reading from the file, meaning that the parse function will throw an exception if the file is not valid

Format: this is the json format that I have designed the program for and trying to alter it will cause an invalid json format exception(or potentially undefined behaviour tho that is less likely)

strings(including keys) are always in ""
there is : after the key with not spaces
there is a space between : and the key

"key": value

after each key-value pair there is a comma(except the last)

double values use a . (no ,)

for booleans - true and false, there is not "" around them

for lists - each element in the last can be any valid json value,
values are separated by commas and each value is on a new row
the opening bracket [ is one row above the first value and the closing is one row below the last value

for objects - each object starts with a { and ends with a } on new rows. Everything else is as described above

Example: (extended version in file.txt for tests)

{
  "formed": 2016,
  "secretBase": "Super tower",
  "active": true,
  "smth":  {
      "secretIdentity": "Dan Jukes",
      "powers": [
	"Radiation resistance", 
	"Turning tiny", 
	]
    },
  "members": [
    {
      "name": "Molecule Man",
      "age": 29,
      "secretIdentity": "Dan Jukes",
      "powers": [
	"Radiation resistance", 
	"Turning tiny", 
	"Radiation blast"
	]
    },
    {
      "name": "Madame Uppercut",
      "age": 39.31,
      "secretIdentity": "Jane Wilson",
      "powers": [
        "Million tonne punch",
        "Damage resistance",
        "Superhuman reflexes"
      ]
    }
  ]
}


Functions
1. Parse - takes a path to a file and parses it if the file exists and the format is valid. If the file cant be opened a runtime_error is thrown and if the format is wrong
an invalid_argument error is thrown
2. Print
3. Search - takes a key and returns a list of all values that match this key (at any level of nesting)
4. Set - takes a path and a string representing a json value and sets the value at that path to the given string parsed as json value. If the path or the value format is wrong
an invalid_argument exception is thrown

side note: to correctly pass a string to all functions that require a string representing a json value it should be surrounded by "" - for example   set("some/path", "\"SomeString\"")

5. Delete - takes a path and deletes the element at that path. If the path is invalid an invalid_argument exception is thrown.
6. Move - takes two paths and moves the value from the first to the second. The value is deleted from the first path and if there is a value in the second path its overwriten.
if any of the paths are invalid an invalid_argument is thrown
7. Save - takes a path to a Json value - by default the whole json (for the cli use "" to indicate the whole json) and saves it in the current file(the file from which json was parsed)
invalid path throws an invalid argument exception
8. Save as - takes a file path and a path to a json value - by default the whole json (for the cli use "" to indicate the whole json) and saves it in the file thats passed to the function
If the file cant be opened a runtime_error is thrown and if the value path is invalid an invalid_argument exception is thrown

for both print and save, the json will be in the correct format described above and it will also have proper indentation to make it readable


For the data structures - functions that were not required for the project might be missing

