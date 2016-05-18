# ![](https://cdn2.iconfinder.com/data/icons/flat-database/512/hash_indexes-24.png)Indexer

###Intro 

This program implements a tokenizer and sorted list inorder to manage tokenizing and organizting a directory filled with other files and directorys. The files can contain different types of strings where special characters and white spaces are the delimiters. The purpose is to read, format, and compile these files in a friendly-reader JSON format. The format  alphabetically lists the files along with the occurences. Noting the number of occurences of each token and in which file it was found in.

###Directory
It can take in either a file or a directory as an argument. A pointer is used to traverse deeper into the directory to find out the rest of the files and/or other folders.It uses recursion to keep opening the folders for further processing.

###Tokenizer
The tokenizer reads in a string breaking up each token and returns it once called upon.


###Sorted List

The sorted list uses two linked lists. The first list manages the foldernames, while the second list manages the occurences of words. 


###Output File

Once the program completes it saves all the information in an output file.
